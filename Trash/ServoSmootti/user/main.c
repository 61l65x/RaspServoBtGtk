
#include <bluetooth/bluetooth.h>
#include <gtk/gtk.h>
#include <sys/socket.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>

int client_socket;

void sendCommand(const char *command) {
    printf("%scc\n", command);
    if (send(client_socket, command, strlen(command), 0) == -1) {
        perror("Failed to send command");
    }
}

void sliderValueChanged(GtkRange *range, gpointer user_data) {
    double value = gtk_range_get_value(range);
    char command[32];
    snprintf(command, sizeof(command), "%.1f", value);
    sendCommand(command);
}

//WINDOW FOR SLIDER**************************
void sliderWindow() {

    // MANUALWINDOW
    GtkWidget *manualWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(manualWindow), "Slide Control");
    gtk_window_set_default_size(GTK_WINDOW(manualWindow), 400, 200);

    /******* GRID **************/
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    //label
    const gchar *markup_text = "<span foreground='white'> <b>| Adjust the slide to move servo |</b>.</span>";
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), markup_text);
    //slider 
    GtkWidget *slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 180.0, 1.0);
    gtk_range_set_value(GTK_RANGE(slider), 1.0);
    gtk_widget_set_size_request(slider, 300, -1);
    //attach
    gtk_grid_attach(GTK_GRID(grid), label, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), slider, 1, 5, 1, 1);
    /***************** GRID END   ********/

    //functionality
    g_signal_connect(slider, "value-changed", G_CALLBACK(sliderValueChanged), NULL);
    
    gtk_window_set_child(GTK_WINDOW(manualWindow), grid);
    gtk_widget_show(manualWindow);
}


static void manualCommand(GtkWidget    *widget, gpointer user_data) {sliderWindow();}
static void initCommand(GtkWidget    *widget, gpointer user_data) {sendCommand("init");}

void activate(GtkApplication *app, gpointer user_data)
{   

    // MAINWINDOW
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Servo Control");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 500);

	// GRID
    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    GtkWidget *manual =    gtk_button_new_with_label("Manual");
     GtkWidget *init=    gtk_button_new_with_label("Init");


    //size
    gtk_widget_set_size_request( manual,    120,  50);
       gtk_widget_set_size_request( init,    120,  50);
    //attach
    gtk_grid_attach(GTK_GRID(grid),  manual,      1, 0, 2, 1);
     gtk_grid_attach(GTK_GRID(grid),  init,      1, 2, 2, 1);
    //functions
    g_signal_connect(manual,     "clicked",  G_CALLBACK(manualCommand),    NULL);
     g_signal_connect(init,     "clicked",  G_CALLBACK(initCommand),    NULL);


    gtk_window_present(GTK_WINDOW(window));
}


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