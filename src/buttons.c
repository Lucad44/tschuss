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

char *get_command(void) {
    return command;
} 

void button_clicked(GtkWidget *widget, char *action) {
    size_t action_len = strlen(action);
    command = malloc((action_len + 1) * sizeof(char));
    strncpy(command, action, action_len + 1);
    gtk_widget_destroy(widget);
    gtk_main_quit();
}

void gen_buttons(GtkWidget *grid, struct Config *st) {
    GtkWidget *buttons[N];
    GtkWidget *main_labels[N];
    GtkWidget *additional_labels[N];
    for (int i = 0, j = 0; i < N; ++i) {
        if (!buttons_cfg[i]->selected) {
            continue;
        }
        if (!buttons_cfg[i]->invisible) {
            buttons[i] = gtk_button_new();
            gtk_widget_set_size_request(buttons[i], 1, 1);
            gtk_widget_set_name(buttons[i], button_names[i]);
            gtk_widget_set_hexpand(buttons[i], TRUE);
            gtk_widget_set_vexpand(buttons[i], TRUE);

            GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_container_add(GTK_CONTAINER(buttons[i]), vbox);

            main_labels[i] = gtk_label_new(buttons_cfg[i]->label);
            gchar *main_name = g_strdup_printf("label-%s", button_names[i]);
            gtk_widget_set_name(main_labels[i], main_name);
            g_free(main_name);
            gtk_box_pack_start(GTK_BOX(vbox), main_labels[i], TRUE, TRUE, 0);

            additional_labels[i] = gtk_label_new(buttons_cfg[i]->description);
            gchar *additional_name = g_strdup_printf("description-%s", button_names[i]);
            gtk_widget_set_name(additional_labels[i], additional_name);
            g_free(additional_name);
            gtk_box_pack_start(GTK_BOX(vbox), additional_labels[i], TRUE, TRUE, 0);

            g_signal_connect(buttons[i], "clicked", G_CALLBACK(button_clicked), buttons_cfg[i]->action);
            gtk_grid_attach(GTK_GRID(grid), buttons[i], j % st->columns, j / st->columns + 1, 1, 1);
        }
        j++;
    }
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    guint keyval = event->keyval;
    if (keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    for (int i = 0; i < N; ++i) {
        if (keyval == buttons_cfg[i]->bind) {
            button_clicked(widget, buttons_cfg[i]->action);
            return TRUE;
        }
    }
    return FALSE;
}