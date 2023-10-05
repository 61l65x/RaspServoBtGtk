#include "../../gtk_functions.h"
#include "../../bt_functions.h"

int wincount = 0;

//CSS
GtkCssProvider *cssProvider;

// CALLBACKS FUNCTIONS MAINW
static void openCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("MOVE:OPEN");}
static void halfCommand(GtkWidget      *widget, gpointer user_data) {sendCommand("MOVE:HALF");}
static void closeCommand(GtkWidget     *widget, gpointer user_data) {sendCommand("MOVE:CLOSE");}
static void manualCommand(GtkWidget    *widget, gpointer user_data) {if (!wincount)sliderWindow();}
static void saveCommand(GtkWidget      *widget, gpointer user_data) {saveWindow();}
static void exitCommand(GtkWidget      *widget, gpointer user_data) {exit(EXIT_SUCCESS);}

//MAINWINDOW*********************************
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

    //LABEL
    const gchar *markup_text = "<span foreground='white' font_desc='Sans 12'><b>| SERVO CONTROLLER |</b></span>";
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), markup_text);

    //INITIALIZE CSS
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    //BUTTONS 
    GtkWidget *open =      gtk_button_new_with_label("Open");
    GtkWidget *half =      gtk_button_new_with_label("Half");
    GtkWidget *close =     gtk_button_new_with_label("Close");
    GtkWidget *manual =    gtk_button_new_with_label("Manual");
    GtkWidget *save =    gtk_button_new_with_label("Save settings");
    GtkWidget *exit =      gtk_button_new_with_label("Exit");
 
    //size
    gtk_widget_set_size_request( open,      150,  50); 
    gtk_widget_set_size_request( half,      150,  50); 
    gtk_widget_set_size_request( close,     150,  50);
    gtk_widget_set_size_request( manual,    120,  50);
    gtk_widget_set_size_request( save ,     120,  50); 
    gtk_widget_set_size_request( exit,      120,  50); 
    //attach
    gtk_grid_attach(GTK_GRID(grid),  label,      1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid),  open,       1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  half,       1, 2, 1, 1); 
    gtk_grid_attach(GTK_GRID(grid),  close,      1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  manual,     1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  save,       1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),  exit,       1, 6, 1, 1);

    //functions
    g_signal_connect(open,     "clicked",  G_CALLBACK(openCommand),    NULL);
    g_signal_connect(half,     "clicked",  G_CALLBACK(halfCommand),    NULL);
    g_signal_connect(close,    "clicked",  G_CALLBACK(closeCommand),   NULL);
    g_signal_connect(manual,   "clicked",  G_CALLBACK(manualCommand),  NULL);
    g_signal_connect(save,     "clicked",  G_CALLBACK(saveCommand),    NULL);
    g_signal_connect(exit,     "clicked",  G_CALLBACK(exitCommand),    NULL);
    /*****************************************************************/

    gtk_window_present(GTK_WINDOW(window));
}
/***************   GTK CODE   *****************/