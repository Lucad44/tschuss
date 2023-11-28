#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>

#include "conf.h"
#include "buttons.h"

void load_buttons_struct(button *buttons_cfg_main[N]) {
    for (int i = 0; i < N; ++i) {
        buttons_cfg[i] = buttons_cfg_main[i];
    }
}

void button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_widget_get_name(widget);
    for (int i = 0; i < N; ++i) {
        if (strcmp(label, button_names[i]) == 0) {
            continue;
        }
    }
}

void gen_buttons(GtkWidget *grid, struct Config *st) {
    GtkWidget *buttons[N];
    for (int i = 0, j = 0; i < N; ++i) {
        if (!buttons_cfg[i]->selected) {
            continue;
        }
        buttons[i] = gtk_button_new_with_label(buttons_cfg[i]->label);
        gtk_widget_set_size_request(buttons[i], 1, 1);
        gtk_widget_set_name(buttons[i], button_names[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), (gpointer) buttons_cfg[i]->label);
        gtk_grid_attach(GTK_GRID(grid), buttons[i], j % st->columns, j / st->columns + 1, 1, 1);
        j++;
    }
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    guint keyval = event->keyval;
    if (keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    FILE *f = fopen("debug.txt", "a");
    for (int i = 0; i < N; ++i) {
        if (keyval == buttons_cfg[i]->bind) {
            system(buttons_cfg[i]->action);
            return TRUE;
        }
    }
    fclose(f);
    return FALSE;
}