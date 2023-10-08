
#include "gtk_functions.h"
#include "bt_functions.h"

void loadWindow() {

    // LOADW
    GtkWidget *loadWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(loadWindow), "Load user");
    gtk_window_set_default_size(GTK_WINDOW(loadWindow), 400, 600);

    //BOX 
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_window_set_child(GTK_WINDOW(loadWindow), vbox);

    //GRID 
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(grid),  15);

    //spacing label
    GtkWidget *spacingLabel1 = gtk_label_new(""); 
    gtk_widget_set_size_request(spacingLabel1, -1, 30); 

    //BOX APPENDS HORIZONTAL ORDER
    gtk_box_append(GTK_BOX(vbox), spacingLabel1);
    gtk_box_append(GTK_BOX(vbox), grid); 

    //search User
    GtkEntryBuffer *searchBuffer = gtk_entry_buffer_new(NULL, -1);
    GtkWidget *searchEntry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(searchBuffer));
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchEntry), "Enter username");

    //BUTTON
    GtkWidget *searchButton = gtk_button_new_with_label("Search");

    // attach
    gtk_grid_attach(GTK_GRID(grid), searchEntry,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), searchButton,  2, 1, 1, 1);

    gtk_widget_show(loadWindow);
}
