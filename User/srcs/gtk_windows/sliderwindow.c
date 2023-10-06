#include "../../gtk_functions.h"
#include "../../bt_functions.h"

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