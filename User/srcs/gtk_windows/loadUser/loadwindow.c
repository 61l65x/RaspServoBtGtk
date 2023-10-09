
#include "gtk_functions.h"
#include "bt_functions.h"
#include "json_functions.h"

static GtkListStore *userListStore = NULL;


void updateUserList(GtkWidget *userTreeView) {

    userData *usersRoot;

    // Clear the current list
    gtk_list_store_clear(userListStore);

    // Load the user data from your JSON file or other data source



    //JATKA TAALTA
    //usersRoot = getUserData();
    //free(usersRoot);



    // Populate the list store with user data (username, etc.)
    // Example:
    // Insert a user into the list store
    GtkTreeIter iter;
    gtk_list_store_append(userListStore, &iter);
    gtk_list_store_set(userListStore, &iter, 0, "", -1); // Replace "User1" with actual data
    // Repeat the above two lines for each user

    // Refresh the user list
    gtk_tree_view_set_model(GTK_TREE_VIEW(userTreeView), GTK_TREE_MODEL(userListStore));
}





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

    //SPACING LABEL
    GtkWidget *spacingLabel1 = gtk_label_new(""); 
    gtk_widget_set_size_request(spacingLabel1, -1, 30); 





    
    //DATA BASE WINDOW

    // ScrolledWindow for userlist
    GtkWidget *userScrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_size_request(userScrolledWindow, -1, 300); // Set the desired height

    // Create the user list store
    userListStore = gtk_list_store_new(1, G_TYPE_STRING); // One column for usernames

    // Create the user tree view
    GtkWidget *userTreeView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(userListStore));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(userTreeView), TRUE); // Show column headers

    // Single col for usernames
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("All users", gtk_cell_renderer_text_new(), "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(userTreeView), column);

    // Add treeView to scrollWindow
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(userScrolledWindow), userTreeView);


    //TAALTA JATKA
    updateUserList(userTreeView);








    //BOX APPENDS HORIZONTAL ORDER
    gtk_box_append(GTK_BOX(vbox), spacingLabel1);
    gtk_box_append(GTK_BOX(vbox), grid);
    gtk_box_append(GTK_BOX(vbox), userScrolledWindow);

    //SEARCH BAR
    GtkEntryBuffer *searchBuffer = gtk_entry_buffer_new(NULL, -1);
    GtkWidget *searchEntry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(searchBuffer));
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchEntry), "Enter username");

    //SEARCH BUTTON
    GtkWidget *searchButton = gtk_button_new_with_label("Search");

    // attach
    gtk_grid_attach(GTK_GRID(grid), searchEntry,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), searchButton,  2, 1, 1, 1);

    gtk_widget_show(loadWindow);
}
