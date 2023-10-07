#include "../bt_functions.h"
#include "../gtk_functions.h"

static void openCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("OPEN");}
static void halfCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("HALF");}
static void closeCommand(GtkWidget     *widget, gpointer user_data) {sendCommand("CLOSE");}

void fastWindow(void)
{
    // SAVEWINDOW
    GtkWidget *fastWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(fastWindow), "Fast controls");
    gtk_window_set_default_size(GTK_WINDOW(fastWindow), 400, 200);

    //GRID 
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(grid),  15);


    //BUTTON
    GtkWidget *open =      gtk_button_new_with_label("Open");
    GtkWidget *half =      gtk_button_new_with_label("Half");
    GtkWidget *close =     gtk_button_new_with_label("Close");
    //sizes
    gtk_widget_set_size_request( open,      150,  50); 
    gtk_widget_set_size_request( half,      150,  50); 
    gtk_widget_set_size_request( close,     150,  50);
    // attach
    gtk_grid_attach(GTK_GRID(grid), open,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), half,   1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), close,  1, 3, 1, 1);

    g_signal_connect(open,     "clicked",  G_CALLBACK(openCommand),    NULL);
    g_signal_connect(half,     "clicked",  G_CALLBACK(halfCommand),    NULL);
    g_signal_connect(close,    "clicked",  G_CALLBACK(closeCommand),   NULL);

    gtk_window_set_child(GTK_WINDOW(fastWindow), grid);
    gtk_widget_show(fastWindow);
 
}

