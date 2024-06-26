// bluetooth_functions.h
#ifndef BLUETOOTH_FUNCTIONS_H
#define BLUETOOTH_FUNCTIONS_H


#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>

//Bluetooth fd
extern int client_socket;

// Function declarations
void sendCommand(const char *command);

#endif
