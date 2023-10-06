#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define SERVO_PIN 18
#define MIN_PULSE_WIDTH 50  // Minimum pulse width for your servo
#define MAX_PULSE_WIDTH 250 // Maximum pulse width for your servo
#define SERVO_RANGE 180 // Servo's range in degrees

int server_socket, client_socket;

int map(int x, int in_min, int in_max, int out_min, int out_max){
	return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void setupWiring() {
    wiringPiSetupGpio(); // Initialize WiringPi
    pinMode(SERVO_PIN, PWM_OUTPUT); // Set the servo pin as PWM output
    pwmSetMode(PWM_MODE_MS); // Set PWM mode to mark-space
    pwmSetClock(192); // Set PWM frequency (approximately 50Hz, standard for servos)
    pwmSetRange(2000); // Set PWM range (typically 1000μs to 2000μs)
}

int controlServo() 
{
    char *successmsg = "Success !\n";
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        return -1;
    }

    int angle = atoi(buffer);
    printf("Received angle: %d\n", angle);

    if (angle < 0) {
        angle = 0;
    } else if (angle > SERVO_RANGE) {
        angle = SERVO_RANGE;
    }

    // Map the angle to the pulse width range
    int pulseWidth = map(angle, 0, SERVO_RANGE, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	
	//	pulseWidth + 100;

    // Send the pulse width to the servo
    pwmWrite(SERVO_PIN, pulseWidth);
}

int main(void) {
	
	//INIT wiringPi
	setupWiring();

    // BLUETOOTH
    server_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	struct sockaddr_rc server_addr;
    server_addr.rc_family = AF_BLUETOOTH;
    str2ba("B8:27:EB:BB:5A:DA", &server_addr.rc_bdaddr);
    server_addr.rc_channel = 4;
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_socket, 1);

    struct sockaddr_rc client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket != -1){printf("Connected !\n");}

	pwmWrite(SERVO_PIN, 0);
    // COMMUNICATE
      while (1) {
        // Update the servo position based on the slider's value
        controlServo();

        // Add code to update the slider value based on user input or feedback from the servo

        // Sleep for a short time to control the servo smoothly
        delay(10); // Adjust as needed
    }

	// Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
