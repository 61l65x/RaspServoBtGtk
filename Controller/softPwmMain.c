#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO_PIN 1 //GPIO 18, Board 12, Wiringpi 1

int servoMove(char *s){

    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi\n");
        return -1;
    }
    softPwmCreate(SERVO_PIN  , 0, 200);  // Initialize servo PWM pin
	
	//MG-995 max 25
    int pwm_min = 1;  
    int pwm_max = 23; 

    if (!strcmp(s, "open")){
        softPwmWrite(SERVO_PIN, pwm_min);
    }
	else if (!strcmp(s, "half")){
		softPwmWrite(SERVO_PIN, pwm_max / 2);
	}
    else if (!strcmp(s, "close")){
        softPwmWrite(SERVO_PIN, pwm_max);
    }

    // STOP SERVO
	sleep(2);
    softPwmStop(SERVO_PIN);
    return 0;
}

int handleCommands(int client_socket){
   
   //RESEIVE MSG
	char *errmsg = "Not valid command ape!\n";
	char *successmsg = "Success !\n";
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        return -1;
    }
    buffer[bytes_received] = '\0';

    //CHECK MSG
    if(strcmp(buffer, "open") == 0){
        servoMove("open");
		send(client_socket, successmsg, strlen(successmsg), 0);
    }
    else if (strcmp(buffer, "close") == 0){
        servoMove("close");
		send(client_socket, successmsg, strlen(successmsg), 0);
    }
	else if (strcmp(buffer, "half") == 0){
		servoMove("half");
		send(client_socket, successmsg, strlen(successmsg), 0);
	}
	else send(client_socket, errmsg, strlen(errmsg), 0);

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
        
		if(handleCommands(client_socket) == -1)return 1;
 
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
