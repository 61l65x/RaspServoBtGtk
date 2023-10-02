#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <unistd.h>
#include <gtk/gtk.h>

static int client_socket;
int wincount = 0;

void sendCommand(const char *command) {
    if (send(client_socket, command, strlen(command), 0) == -1) {
        perror("Failed to send command");
    }
}

/***************   GTK CODE   *****************/

//CALLBACK MANUALW
static void arrowLeftPressed(GtkWidget  *widget, gpointer user_data) {sendCommand("spinleft");}
static void arrowRightPressed(GtkWidget *widget, gpointer user_data) {sendCommand("spinright");}

static void showManualControlWindow() {

    // MANUALWINDOW
    GtkWidget *manualWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(manualWindow), "Manual Control");
    gtk_window_set_default_size(GTK_WINDOW(manualWindow), 200, 200);

    //GRID
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // BUTTOS
    GtkWidget *arrowLeftButton =  gtk_button_new_with_label("Spin Left");
    GtkWidget *arrowRightButton = gtk_button_new_with_label("Spin Right");
    //funcs
    g_signal_connect(arrowLeftButton,  "clicked", G_CALLBACK(arrowLeftPressed),  NULL);
    g_signal_connect(arrowRightButton, "clicked", G_CALLBACK(arrowRightPressed), NULL);
    //attach
    gtk_grid_attach(GTK_GRID(grid), arrowLeftButton,  1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), arrowRightButton, 2, 1, 1, 1);

    gtk_window_set_child(GTK_WINDOW(manualWindow), grid);
    gtk_widget_show(manualWindow);
}

// CALLBACK FUNCTIONS MAINW
static void openCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("open");}
static void halfCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("half");}
static void closeCommand(GtkWidget     *widget, gpointer user_data) {sendCommand("close");}
static void manualCommand(GtkWidget    *widget, gpointer user_data) {if (!wincount)showManualControlWindow();}
static void joyStickCommand(GtkWidget  *widget, gpointer user_data) {sendCommand("joystick");}
static void exitCommand(GtkWidget      *widget, gpointer user_data) {exit(EXIT_SUCCESS);}

static void activate(GtkApplication *app, gpointer user_data)
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

    //CSS
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    //************ BUTTONS *****************************************
    GtkWidget *open =      gtk_button_new_with_label("Open");
    GtkWidget *half =      gtk_button_new_with_label("Half");
    GtkWidget *close =     gtk_button_new_with_label("Close");
    GtkWidget *manual =    gtk_button_new_with_label("Manual");
    GtkWidget *joystick =  gtk_button_new_with_label("Joystick /ERR/");
    GtkWidget *exit =      gtk_button_new_with_label("Exit");
 
    //size
    gtk_widget_set_size_request( open,      150,  50); 
    gtk_widget_set_size_request( half,      150,  50); 
    gtk_widget_set_size_request( close,     150,  50);
    gtk_widget_set_size_request( manual,    120,  50); 
    gtk_widget_set_size_request( joystick,  120,  50); 
    gtk_widget_set_size_request( exit,      120,  50); 
    //attach
    gtk_grid_attach(GTK_GRID(grid),  open,       1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  half,       1, 2, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid),  close,      1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  manual,     1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  joystick,   1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  exit,       1, 6, 1, 1);

    //functions
    g_signal_connect(open,     "clicked", G_CALLBACK(openCommand),     NULL);
    g_signal_connect(half,     "clicked", G_CALLBACK(halfCommand),     NULL);
    g_signal_connect(close,    "clicked", G_CALLBACK(closeCommand),    NULL);
    g_signal_connect(manual,    "clicked", G_CALLBACK(manualCommand),  NULL);
    g_signal_connect(joystick, "clicked", G_CALLBACK(joyStickCommand), NULL);
    g_signal_connect(exit,     "clicked", G_CALLBACK(exitCommand),     NULL);
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
