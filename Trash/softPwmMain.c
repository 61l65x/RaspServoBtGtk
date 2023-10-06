#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <errno.h>
#include <string.h>



#define SERVO_PIN 1 //GPIO 18, Board 12, Wiringpi 1
#define PWM_MIN 1
#define PWM_MAX 23
#define PWM_RANGE 200
int currPwm = 1;

void saveUserSettings(char *name){
    
}


void moveServoSmoothly(int targetPosition) {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi\n");
        return;
    }

    softPwmCreate(SERVO_PIN, 0, PWM_RANGE); // Initialize servo PWM pin

    int currentPosition = PWM_MIN; // Start from the minimum position
    int step = (targetPosition - currentPosition > 0) ? 1 : -1; // Determine the direction of movement

    while (currentPosition != targetPosition) {
        softPwmWrite(SERVO_PIN, currentPosition);

        currentPosition += step;

        usleep(100); 
    }

    sleep(1);
    softPwmStop(SERVO_PIN);
}

int servoMove(char *s){

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi\n");
        return -1;
    }
    softPwmCreate(SERVO_PIN  , 0, 100);  // Initialize servo PWM pin
	
	//MG-995 max 25

    if (!strcmp(s, "OPEN")){
        softPwmWrite(SERVO_PIN, PWM_MIN);
    }
	else if (!strcmp(s, "HALF")){
		softPwmWrite(SERVO_PIN, (PWM_MAX + PWM_MIN) / 2);
	}
    else if (!strcmp(s, "CLOSE")){
        softPwmWrite(SERVO_PIN, PWM_MAX);
    }
    else{
        moveServoSmoothly(atoi(s));
    }

    // STOP SERVO
	sleep(2);
    softPwmStop(SERVO_PIN);
    return 0;
}

int receiveMsg(int client_socket){
   
   //RESEIVE MSG
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {return -1;}
    buffer[bytes_received] = '\0';

    // CHECK COMMAND
    char *header = strtok(buffer, ":");
    if (header != NULL) {
        char *command = strtok(NULL, ":");
        printf("command %s\n", command);
        
        if(command != NULL){
            
            if (strcmp(header, "MOVE") == 0){
                servoMove(command);
            }
            else if (strcmp(header, "SAVE")){
                saveUserSettings(command);
            }
        }
    }
	else send(client_socket, "NOT VALID !", 11, 0);

    return 0;
}


int main(void) {

    // Create a Bluetooth RFCOMM socket.
    int server_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Bind to "C8:7F:54:98:B6:09" rfcomm channel 4
    struct sockaddr_rc server_addr;
    server_addr.rc_family = AF_BLUETOOTH;
    str2ba("B8:27:EB:BB:5A:DA", &server_addr.rc_bdaddr);
    server_addr.rc_channel = 4;
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //WAIT CONNECTION
    listen(server_socket, 1);

    // ACCEPT CONNECTION
    struct sockaddr_rc client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
	if (client_socket != -1){printf("Connected !\n");}

    // COMMUNICATE
    while (1) {
        
		if(receiveMsg(client_socket) == -1)return 1;
 
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
