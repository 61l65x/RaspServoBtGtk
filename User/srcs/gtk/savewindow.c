#include "../../gtk_functions.h"
#include "../../bt_functions.h"


void saveUser(char *s){
    printf("nam: %s", s);
}


static void saveButtonClicked(GtkButton *button, gpointer user_data) {
    GtkEntryBuffer *nameEntry = GTK_ENTRY_BUFFER(user_data);
    const gchar *name = gtk_entry_buffer_get_text(nameEntry);
    
    // Now you have the user's name in the 'name' variable
   // printf("User's Name: %s\n", name);

    // You can send the name to your sendCommand function if needed
    char command[128];
    snprintf(command, sizeof(command),"%s", name);
    saveUser(command);
}

//MAIN WINDOW
void saveWindow() {

    // SAVEWINDOW
    GtkWidget *saveWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(saveWindow), "Save user");
    gtk_window_set_default_size(GTK_WINDOW(saveWindow), 400, 200);

    //GRID 
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    //entry
    GtkEntryBuffer *nameBuffer = gtk_entry_buffer_new(NULL, -1);
    GtkWidget *nameEntry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(nameBuffer));
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Enter your name");

    //BUTTON
    GtkWidget *saveButton = gtk_button_new_with_label("Save");

    // attach
    gtk_grid_attach(GTK_GRID(grid), nameEntry,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), saveButton,  1, 2, 1, 1);

    // SAVE CALLBACK
    g_signal_connect(saveButton, "clicked", G_CALLBACK(saveButtonClicked), nameBuffer);
    gtk_window_set_child(GTK_WINDOW(saveWindow), grid);
    gtk_widget_show(saveWindow);
}