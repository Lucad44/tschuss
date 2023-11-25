#include <gtk/gtk.h>
#include <ctype.h>

#include "conf.h"
#include "buttons.h"

char *str_to_lower(const char *s) {
    size_t len = strlen(s);
    char *res = (char *) malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i < len; ++i) {
        res[i] = tolower(s[i]);
    }
    res[len] = '\0';
    return res;
}

void button_clicked(GtkWidget *widget, gpointer data, struct Config *st) {
    const char *label = (const char *) data;
    for (int i = 0; i < N; ++i) {
        if (strcmp(label, st->labels[i]) == 0) {
            system(commands[i]);
        }
    }
}

void gen_buttons(GtkWidget *grid, struct Config *st) {
    GtkWidget *buttons[N];
    int j = 0;
    for (int i = 0; i < N; ++i) {
        if (st->selected[i] == 0) {
            st->unselected++;
            continue;
        }
        buttons[i] = gtk_button_new_with_label(st->labels[i]);
        gchar *button_name = g_strdup_printf("button-%s", str_to_lower(st->labels[i]));
        gtk_widget_set_name(buttons[i], button_name);
        g_free(button_name);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), (gpointer) st->labels[i]);
        gtk_grid_attach(GTK_GRID(grid), buttons[i], j % st->columns, j / st->columns + 1, 1, 1);
        j++;
    }
}