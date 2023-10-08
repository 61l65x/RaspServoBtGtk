#include "../bt_functions.h"
#include "../gtk_functions.h"

int client_socket;

void sendCommand(const char *command) {
    if (send(client_socket, command, strlen(command), 0) == -1) {
        perror("Failed to send command");
    }
}

int main(int argc, char **argv) {

    // Create a Bluetooth RFCOMM socket
    if((client_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0){
        perror("Error: "); return 1;}

    // Connect to the server on the address "C8:7F:54:98:B6:09" on channel 4
    struct sockaddr_rc server_addr;
    server_addr.rc_family = AF_BLUETOOTH;
    str2ba("B8:27:EB:BB:5A:DA", &server_addr.rc_bdaddr);
    server_addr.rc_channel = 4;
    connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));


    //GTK APP
	gtk_init();
	GtkApplication *app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app,"activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	

    //CLEANUP
    g_object_unref(app);
    close(client_socket);
    return 0;
}
