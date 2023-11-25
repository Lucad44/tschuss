#include <stdio.h>
#include <gtk/gtk.h>
#include <libconfig.h>
#include <string.h>

#include "conf.h"
#include "buttons.h"

int load_css(const char *css_file) {
    if (access(css_file, F_OK) == -1) {
        fprintf(stderr, "No '%s' file found.\n", css_file);
        return -1;
    }

    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GFile *css_fp = g_file_new_for_path(css_file);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
    return 0;
}

int read_cfg(const char *cfg_file, struct Config *st) {
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, cfg_file)) {
        fprintf(stderr, "%s:%d - %sConfig file '%s' not found\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg), cfg_file);
        config_destroy(&cfg);
        return -1;
    }

    const char *top_text, *bottom_text;
    if (!(config_lookup_int(&cfg, "columns", &st->columns) &&
        config_lookup_int(&cfg, "border_width", &st->border_width) &&
        config_lookup_string(&cfg, "top_text", &top_text) &&
        config_lookup_string(&cfg, "bottom_text", &bottom_text))) {
            fprintf(stderr, "Error in the '%s' config file: missing/invalid values.\n", cfg_file);
            config_destroy(&cfg);
            return -1;
    }
    size_t top_len = strlen(top_text), bottom_len = strlen(bottom_text);
    st->top_text = malloc(top_len + 1);
    st->bottom_text  = malloc(bottom_len + 1);
    strcpy(st->top_text, top_text);
    strcpy(st->bottom_text, bottom_text);
    config_setting_t *setting;

    setting = config_lookup(&cfg, "size");
    if (setting != NULL) {
        st->width = config_setting_get_int_elem(setting, 0);
        st->height = config_setting_get_int_elem(setting, 1);
    }
    else {
        fprintf(stderr, "Error in the 'position' configuration: invalid/missing values.\n");
        return -1;
    }


    setting = config_lookup(&cfg, "position");
    if (setting != NULL) {
        st->x = config_setting_get_int_elem(setting, 0);
        st->y = config_setting_get_int_elem(setting, 1);
    }
    else {
        fprintf(stderr, "Error in the 'position' configuration: invalid/missing values.\n");
        return -1;
    }

    setting = config_lookup(&cfg, "selected");
    if (setting != NULL) {
        for (int i = 0; i < N; ++i) {
            st->selected[i] = config_setting_get_int_elem(setting, i);
        }
    }
    else {
        fprintf(stderr, "Error in the 'selected' configuration: invalid/missing values.\n");
        return -1;
    }

    setting = config_lookup(&cfg, "labels");
    const char *label;
    if (setting != NULL) {
        for (int i = 0; i < N; ++i) {
            label = config_setting_get_string_elem(setting, i);
            size_t len = strlen(label);
            st->labels[i] = malloc(len + 1);
            strcpy(st->labels[i], label);
        }
    }
    else {
        fprintf(stderr, "Error in the 'labels' configuration: invalid/missing values.\n");
        return -1;
    }

    config_destroy(&cfg);
    return 0;
}
