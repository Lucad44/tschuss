#include <gtk/gtk.h>
#include <ctype.h>

#include "conf.h"
#include "buttons.h"

void button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_widget_get_name(widget);
    for (int i = 0; i < N; ++i) {
        if (strcmp(label, button_names[i]) == 0) {
            system(commands[i]);
        }
    }
}

void gen_buttons(GtkWidget *grid, struct Config *st) {
    GtkWidget *buttons[N];
    for (int i = 0, j = 0; i < N; ++i) {
        if (st->selected[i] == 0) {
            st->unselected++;
            continue;
        }
        buttons[i] = gtk_button_new_with_label(st->labels[i]);
        gtk_widget_set_name(buttons[i], button_names[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), (gpointer) st->labels[i]);
        gtk_grid_attach(GTK_GRID(grid), buttons[i], j % st->columns, j / st->columns + 1, 1, 1);
        j++;
    }
}