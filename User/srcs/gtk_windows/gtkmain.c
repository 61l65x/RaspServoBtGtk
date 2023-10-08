#include "../../gtk_functions.h"
#include "../../bt_functions.h"

// CSS
GtkCssProvider *cssProvider;

// CALLBACKS FUNCTIONS MAINW
static void fastCommand(GtkWidget *widget, gpointer user_data) { fastWindow(); }
static void manualCommand(GtkWidget *widget, gpointer user_data) { sliderWindow(); }
static void saveCommand(GtkWidget *widget, gpointer user_data) { saveWindow(); }
static void loadCommand(GtkWidget *widget, gpointer user_data) { loadWindow(); }
static void exitCommand(GtkWidget *widget, gpointer user_data) { exit(EXIT_SUCCESS); }

// MAINWINDOW*********************************
void activate(GtkApplication *app, gpointer user_data)
{
    // INITIALIZE CSS
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // MAINWINDOW 1.
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "SERVO APP");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 500);

    // BOX 2.
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // GRID  3.
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

     //LABELS
    GtkWidget *headerLabel = gtk_label_new("SERVO CONTROL");
    gtk_widget_add_css_class(GTK_WIDGET(headerLabel), "header-main");
    GtkWidget *spacingLabel1 = gtk_label_new(""); 
    GtkWidget *spacingLabel2 = gtk_label_new(""); 
    gtk_widget_set_size_request(spacingLabel1, -1, 30); 
    gtk_widget_set_size_request(spacingLabel2, -1, 30); 
    
    //BOX APPENDS HORIZONTAL ORDER
    gtk_box_append(GTK_BOX(vbox), spacingLabel1);
    gtk_box_append(GTK_BOX(vbox), headerLabel); 
    gtk_box_append(GTK_BOX(vbox), spacingLabel2);
    gtk_box_append(GTK_BOX(vbox), grid); 

    //BUTTONS----------------------
    GtkWidget *fast = gtk_button_new_with_label("Fast Controls");
    GtkWidget *manual = gtk_button_new_with_label("Manual Control");
    GtkWidget *save = gtk_button_new_with_label("Save settings");
    GtkWidget *load = gtk_button_new_with_label("Load settings");
    GtkWidget *exit = gtk_button_new_with_label("Exit");
    //size
    gtk_widget_set_size_request(fast,   120, 50);
    gtk_widget_set_size_request(manual, 120, 50);
    gtk_widget_set_size_request(save,   120, 50);
    gtk_widget_set_size_request(load,   120, 50);
    gtk_widget_set_size_request(exit,   120, 50);
    //grid attach
    gtk_grid_attach(GTK_GRID(grid), fast,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), manual, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), save,   1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), load,   1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), exit,   1, 5, 1, 1);
    // connect signal handlers
    g_signal_connect(fast,   "clicked", G_CALLBACK(fastCommand),   NULL);
    g_signal_connect(manual, "clicked", G_CALLBACK(manualCommand), NULL);
    g_signal_connect(save,   "clicked", G_CALLBACK(saveCommand),   NULL);
    g_signal_connect(load,   "clicked", G_CALLBACK(loadCommand),   NULL);
    g_signal_connect(exit,   "clicked", G_CALLBACK(exitCommand),   NULL);
    //BUTTON END -------------------------------------------

    // Show everything
    gtk_window_present(GTK_WINDOW(window));
}
