#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>

#include "buttons.h"
#include "conf.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window, "window");
    struct Config config;
    button *buttons_cfg[N];
    for (int i = 0; i < N; ++i) {
        buttons_cfg[i] = malloc(sizeof(button));
    }

    if (read_cfg(cfg_file, &config, buttons_cfg) == -1 || load_css(css_file) == -1) {
        fprintf(stderr, "File error. Aborting the process.\n");
        return -1;
    }

    gtk_window_set_title(GTK_WINDOW(window), "tschuss");
    gtk_widget_set_size_request(window, config.width, config.height);
    gtk_container_set_border_width(GTK_CONTAINER(window), config.border_width);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);

    if (strcmp(config.top_text, "")) {
        GtkWidget *top_label = gtk_label_new(config.top_text);
        gtk_widget_set_name(top_label, "top-text");
        gtk_grid_attach(GTK_GRID(grid), top_label, 0, 0, config.columns, 1);
    }

    load_buttons_struct(buttons_cfg);
    gen_buttons(grid, &config);

    if (strcmp(config.bottom_text, "")) {
        GtkWidget *bottom_label = gtk_label_new(config.bottom_text);
        gtk_widget_set_name(bottom_label, "bottom-text");
        gtk_grid_attach(GTK_GRID(grid), bottom_label, 0, N / config.columns + 1 + (config.columns >= 4), config.columns, 1);
    }

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}