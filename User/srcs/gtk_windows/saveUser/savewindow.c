#include "../../../gtk_functions.h"
#include "../../../bt_functions.h"
#include <gtk/gtk.h>

//ERROR MSG FOR USER EXISTS
static GtkWidget *messageLabel = NULL;


static int validateInput(const gchar *text){
    
    if (strlen(text) < 3)return 0;
    return 1;
}

static void saveButtonClicked(GtkButton *button, gpointer user_data) {
    GtkEntryBuffer *nameEntry = GTK_ENTRY_BUFFER(user_data);
    const gchar *name = gtk_entry_buffer_get_text(nameEntry);

    //SAVE DATA TO JSON
    int reVal = saveUser(name);
    if (reVal == -1){perror("ERROR:JSON");exit(EXIT_FAILURE);}//ERROR
    
    if (reVal == 0){ //SUCCESS
        gtk_label_set_text(GTK_LABEL(messageLabel), "Success");  
    }
    else if (reVal == 3){ //USR EXISTS
        if (messageLabel != NULL) {
            gtk_label_set_text(GTK_LABEL(messageLabel), "User already exists.");
        }   
     }
}

static void entryChanged(GtkEditable *editable, gpointer user_data) {
    GtkEntryBuffer *entry = GTK_ENTRY_BUFFER(user_data);
    const gchar *text = gtk_entry_buffer_get_text(entry);

    gboolean isValid = validateInput(text);

    if (!isValid) {gtk_widget_add_css_class(GTK_WIDGET(editable), "invalid-entry");}
    else {gtk_widget_remove_css_class(GTK_WIDGET(editable), "invalid-entry");}
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
    gtk_grid_set_row_spacing(GTK_GRID(grid),  15);

    //entry
    GtkEntryBuffer *nameBuffer = gtk_entry_buffer_new(NULL, -1);
    GtkWidget *nameEntry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(nameBuffer));
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Enter your name");

    //BUTTON
    GtkWidget *saveButton = gtk_button_new_with_label("Save");

    // attach
    gtk_grid_attach(GTK_GRID(grid), nameEntry,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), saveButton,  1, 2, 1, 1);

    //entry message label
    messageLabel = gtk_label_new(NULL);
    gtk_label_set_wrap(GTK_LABEL(messageLabel), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(messageLabel), 30);
    gtk_widget_set_halign(messageLabel, GTK_ALIGN_CENTER);
    gtk_widget_add_css_class(GTK_WIDGET(messageLabel), "entry-msg");

    // attach the label to the grid
    gtk_grid_attach(GTK_GRID(grid), messageLabel, 1, 0, 1, 1);

    // SAVE CALLBACK
    g_signal_connect(saveButton, "clicked", G_CALLBACK(saveButtonClicked), nameBuffer);
    
    //CHECK VALIDATION
    g_signal_connect(nameEntry, "changed", G_CALLBACK(entryChanged), nameBuffer);

    gtk_window_set_child(GTK_WINDOW(saveWindow), grid);
    gtk_widget_show(saveWindow);
}