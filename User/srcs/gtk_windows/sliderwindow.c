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
    const gchar *markup_text1 = "<span foreground='white'> <b>| Left Servo |</b>.</span>";
    GtkWidget *labelLeft = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(labelLeft), markup_text1);
    const gchar *markup_text2 = "<span foreground='white'> <b>| Right Servo |</b>.</span>";
    GtkWidget *labelRight = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(labelRight), markup_text2);
    //slider 
    GtkWidget *sliderRight = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 180.0, 1.0);
    GtkWidget *sliderLeft = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 180.0, 1.0);
    gtk_range_set_value(GTK_RANGE(sliderRight), 1.0);
    gtk_widget_set_size_request(sliderRight, 300, -1);
    gtk_range_set_value(GTK_RANGE(sliderLeft), 1.0);
    gtk_widget_set_size_request(sliderLeft, 300, -1);
    //attach
    gtk_grid_attach(GTK_GRID(grid), labelLeft,    1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), labelRight,   2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), sliderRight,  1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), sliderLeft,   2, 5, 1, 1);
    /***************** GRID END   ********/

    //functionality
    g_signal_connect(sliderRight, "value-changed", G_CALLBACK(sliderValueChanged), NULL);
    g_signal_connect(sliderLeft, "value-changed", G_CALLBACK(sliderValueChanged), NULL);
    gtk_window_set_child(GTK_WINDOW(manualWindow), grid);
    gtk_widget_show(manualWindow);
}
