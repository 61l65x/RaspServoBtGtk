#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <gtk/gtk.h>

static int client_socket;


/***************   GTK CODE   *****************/
void sendCommand(const char *command) {
    if (send(client_socket, command, strlen(command), 0) == -1) {
        perror("Failed to send command");
    }
}

// Callback functions for button click events
static void sendOpenCommand(GtkWidget *widget, gpointer user_data) {sendCommand("open");}
static void sendHalfCommand(GtkWidget *widget, gpointer user_data) {sendCommand("half");}
static void sendCloseCommand(GtkWidget *widget, gpointer user_data) {sendCommand("close");}
static void ExitCommand(GtkWidget *widget, gpointer user_data) {exit(EXIT_SUCCESS);}

static void activate(GtkApplication *app, gpointer user_data)
{
    // MAINWINDOW
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Servo Control");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 120);

	// GRID
    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);

    //CSS
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    //************ BUTTONS *****************************************
    GtkWidget *open = gtk_button_new_with_label("open");
    GtkWidget *half = gtk_button_new_with_label("half");
    GtkWidget *close = gtk_button_new_with_label("close");
    GtkWidget *exit = gtk_button_new_with_label("exit");
    //size
    gtk_widget_set_size_request(open, 200, 50); 
    gtk_widget_set_size_request(half, 200, 50); 
    gtk_widget_set_size_request(close, 200, 50);  
    gtk_widget_set_size_request(exit, 200, 50); 
    //attach
    gtk_grid_attach(GTK_GRID(grid), open,  1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), half,  1, 2, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid), close, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), exit,  1, 4, 1, 1);
    //functions
    g_signal_connect(open, "clicked", G_CALLBACK(sendOpenCommand), NULL);
    g_signal_connect(half, "clicked", G_CALLBACK(sendHalfCommand), NULL);
    g_signal_connect(close, "clicked", G_CALLBACK(sendCloseCommand), NULL);
    g_signal_connect(exit, "clicked", G_CALLBACK(ExitCommand), NULL);
    /*****************************************************************/


    gtk_window_present(GTK_WINDOW(window));
}
/***************   GTK CODE   *****************/

int main(int argc, char **argv) {

    // Create a Bluetooth RFCOMM socket
    client_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

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
