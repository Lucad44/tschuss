#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>

#include "conf.h"
#include "buttons.h"

void button_clicked(GtkWidget *widget, gpointer data, button buttons_cfg[N]) {
    const char *label = gtk_widget_get_name(widget);
    for (int i = 0; i < N; ++i) {
        if (strcmp(label, button_names[i]) == 0) {
            system(buttons_cfg[i].action);
        }
    }
}

void gen_buttons(GtkWidget *grid, struct Config *st, button buttons_cfg[N]) {
    GtkWidget *buttons[N];
    for (int i = 0, j = 0; i < N; ++i) {
        if (!buttons_cfg[i].selected) {
            continue;
        }
        buttons[i] = gtk_button_new_with_label(buttons_cfg[i].label);
        gtk_widget_set_size_request(buttons[i], 1, 1);
        gtk_widget_set_name(buttons[i], button_names[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), (gpointer) buttons_cfg[i].label);
        gtk_grid_attach(GTK_GRID(grid), buttons[i], j % st->columns, j / st->columns + 1, 1, 1);
        j++;
    }
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data, button buttons_cfg[N]) {
    guint keyval = event->keyval;
    if (keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    for (int i = 0; i < N; ++i) {
        if (buttons_cfg[i].bind == keyval) {
            system(buttons_cfg[i].action);
            return TRUE;
        }
    }
    return FALSE;
}