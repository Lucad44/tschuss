#include <gtk/gtk.h>
#include <ctype.h>

#include "conf.h"
#include "buttons.h"

void load_cfg_parameters(struct Config *st) {
    for (int i = 0; i < N; ++i) {
        button_labels[i] = st->labels[i];
        selected[i] = st->selected[i];
    }
    columns = st->columns;
}

char *str_to_lower(const char *s) {
    size_t len = strlen(s);
    char *res = (char *) malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i < len; ++i) {
        res[i] = tolower(s[i]);
    }
    res[len] = '\0';
    return res;
}

void button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = (const char *) data;
    for (int i = 0; i < N; ++i) {
        if (strcmp(label, button_labels[i]) == 0) {
            system(commands[i]);
        }
    }
}

void gen_buttons(GtkWidget *grid) {
    GtkWidget* buttons[N];
    for (int i = 0; i < N; ++i) {
        if (selected[i] == 0) {
            continue;
        }
        buttons[i] = gtk_button_new_with_label(button_labels[i]);
        gchar *button_name = g_strdup_printf("button-%s", str_to_lower(button_labels[i]));
        gtk_widget_set_name(buttons[i], button_name);
        g_free(button_name);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), (gpointer) button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), buttons[i], i % columns, i / columns + 1, 1, 1);
    }
}