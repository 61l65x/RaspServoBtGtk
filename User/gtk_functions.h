#ifndef GTK_FUNCTIONS_H
#define GTK_FUNCTIONS_H

#include <gtk/gtk.h>

// GTK
void sliderValueChanged(GtkRange *range, gpointer user_data);
void sliderWindow();
static void saveButtonClicked(GtkButton *button, gpointer user_data);
void saveWindow();
void activate(GtkApplication *app, gpointer user_data);

//SAVEUSER
int saveUser(const char *username);

#endif
