#include <stdio.h>
#include <gtk/gtk.h>
#include <libconfig.h>
#include <string.h>
#include <getopt.h>

#include "conf.h"

int get_cmd_args(int argc, char *argv[], char *cfg_path, char *css_path) {
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"quiet", no_argument, NULL, 'q'},
        {"config-file", required_argument, NULL, 'c'},
        {"css-file", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0}    
    };

    const char *version = "1.3.1";
    const char *help = 
        "Usage: tschuss [options]\n"
        "\n"
        "  -h, --help                  Show an help message and exit.\n"
        "  -v, --version               Show the current version and exit.\n"
        "  -q, --quiet                 Suppress all errors in the stdout (not recommended).\n"
        "  -c, --config-file <conf>    Enter the path to the config file. If no path is given, the default path shall be used.\n"
        "  -s, --css-file <css>        Enter the path to the css file. If no path is given, the default path shall be used.\n"
        "All the other config and style options are set and configured in the configuration and .css files.\n";

    int c;
    int option_index = 0;
    int quiet_flag = 0;
    while ((c = getopt_long(argc, argv, "c:s:hvq", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                g_print("%s\n", help);
                return 0;
            case 'v':
                g_print("tschuss's current version: %s\n", version);
                return 0;
            case 'q':
                quiet_flag++;
                break;
            case 'c':
                if (access(optarg, F_OK) == -1) {
                    fprintf(stderr, "Invalid path. Using the default one instead.\n");
                    return 0;
                }
                g_print("\n%s", optarg);
                strncpy(cfg_path, optarg, MAX_USER_SZ);
                break;
            case 's':
                if (access(optarg, F_OK) == -1) {
                    fprintf(stderr, "Invalid path. Using the default one instead.\n");
                    return 0;
                }
                g_print("\n%s", optarg);
                strncpy(css_path, optarg, MAX_USER_SZ);
                break;
            case '?':
                return 0;
            default:
                break;
        }
    }
    return 1 + quiet_flag;
}

bool set_paths(bool valid_conf, char *cfg_path, char *css_path) {
    const char *home = getenv("HOME");
    const char *xdg_config_home = getenv("XDG_CONFIG_HOME");
    char config[MAX_USER_SZ] = "";
    char css[MAX_USER_SZ] = "";
    if (!valid_conf) {
        if (home) {
            snprintf(config, MAX_USER_SZ, "%s/.config/tschuss/%s", home, cfg_file);
            snprintf(css, MAX_USER_SZ, "%s/.config/tschuss/%s", home, css_file);
            strncpy(cfg_path, config, MAX_USER_SZ);
            strncpy(css_path, css, MAX_USER_SZ);
            return true;
        }
        else if (xdg_config_home) {
            snprintf(config, MAX_USER_SZ, "%s/tschuss/%s", xdg_config_home, cfg_file);
            snprintf(css, MAX_USER_SZ, "%s/tschuss/%s", xdg_config_home, css_file);
            strncpy(cfg_path, config, MAX_USER_SZ);
            strncpy(css_path, css, MAX_USER_SZ);
            return true;
        }
        else {
            if (!quiet) {
                fprintf(stderr, "Environment variable HOME and XDG_CONFIG_HOME are not set."
                        "\nPlease fix your configuration. Aborting the process.\n");
            }
            return false;
        }
    }
    return true;
}

int load_css(const char *css_path) {
    if (access(css_path, F_OK) == -1) {
        if (!quiet)
            fprintf(stderr, "%s:syntax error\n", css_path);
        return -1;
    }

    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GFile *css_fp = g_file_new_for_path(css_path);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
    return 0;
}

int read_cfg(const char *cfg_path, struct Config *st, button *buttons_cfg[N]) {
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, cfg_path)) {
        if (!quiet) {
            fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                    config_error_line(&cfg), config_error_text(&cfg));
        }
        config_destroy(&cfg);
        return -1;
    }


    if (!config_lookup_int(&cfg, "border_width", &st->border_width)) {
            if (!quiet)
                fprintf(stderr, "Error in the '%s' config file: invalid 'border_width' value. Using the default one instead.\n", cfg_path);
            st->columns = DEF_BW;
    }
    if (!config_lookup_int(&cfg, "columns", &st->columns)) {
            if (!quiet)
                fprintf(stderr, "Error in the '%s' config file: invalid 'columns' value. Using the default one instead.\n", cfg_path);
            st->columns = DEF_COLS;
    }

    if (st->columns <= 0) {
        if (!quiet)
            fprintf(stderr, "Error in the '%s' config file: invalid 'columns' value. Using the default one instead.\n", cfg_path);
        st->columns = DEF_COLS;
    }
    
    const char *top_text, *bottom_text;
    if (!config_lookup_string(&cfg, "top_text", &top_text)) {
            if (!quiet)
                fprintf(stderr, "Error in the '%s' config file: invalid 'top_text' value. Using the default one instead.\n", cfg_path);
            size_t top_len = strlen(DEF_TOP_TEXT);
            st->top_text = malloc((top_len + 1) * sizeof(char));
            strncpy(st->top_text, DEF_TOP_TEXT, top_len + 1);
    }
    else {
        size_t top_len = strlen(top_text);
        st->top_text = malloc(sizeof(char) * (top_len + 1));
        strncpy(st->top_text, top_text, top_len + 1);
    }

    if (!config_lookup_string(&cfg, "bottom_text", &bottom_text)) {
            if (!quiet)
                fprintf(stderr, "Error in the '%s' config file: invalid 'bottom_text' value. Using the default one instead.\n", cfg_path);
            size_t bottom_len = strlen(DEF_BOTTOM_TEXT);
            st->bottom_text = malloc((bottom_len + 1) * sizeof(char));
            strncpy(st->bottom_text, DEF_BOTTOM_TEXT, bottom_len + 1);
    }
    else {
        size_t bottom_len = strlen(bottom_text);
        st->bottom_text = malloc(sizeof(char) * (bottom_len + 1));
        strncpy(st->bottom_text, bottom_text, bottom_len + 1);
    }

    config_setting_t *size = config_lookup(&cfg, "size");
    if (size != NULL) {
        int w_succ = config_setting_lookup_int(size, "width", &st->width);
        if (!w_succ) {
            if (!quiet)
                fprintf(stderr, "Error in the 'width' configuration: invalid/missing values. Using the default value instead.\n");
            st->width = DEF_W;
        }
        int h_succ = config_setting_lookup_int(size, "height", &st->height);
        if (!h_succ) {
            if (!quiet)
                fprintf(stderr, "Error in the 'height' configuration: invalid/missing values. Using the default value instead.\n");
            st->height = DEF_H;
        }
    }
    else {
        if (!quiet)
            fprintf(stderr, "Error in the 'position' configuration: invalid/missing values. Using the default values instead.\n");
        st->width = DEF_W;
        st->height = DEF_H;
    }

    for (int i = 0; i < N; ++i) {
        int valid_options[BUTTON_OPTS];
        config_setting_t *setting = config_lookup(&cfg, button_names[i]);
        if (setting != NULL) {
            const char *title;
            valid_options[0] = config_setting_lookup_string(setting, "title", &title);
            if (valid_options[0]) {
                size_t title_len = strlen(title);
                buttons_cfg[i]->title = malloc((title_len + 1) * sizeof(char));
                strncpy(buttons_cfg[i]->title, title, title_len + 1);
            }

            const char *label;
            valid_options[1] = config_setting_lookup_string(setting, "label", &label);
            size_t label_len = strlen(label);
            buttons_cfg[i]->label = malloc((label_len + 1) * sizeof(char));
            strncpy(buttons_cfg[i]->label, label, label_len + 1);

            const char *image;
            valid_options[2] = config_setting_lookup_string(setting, "image", &image);
            if (valid_options[2]) {
                size_t image_len = strlen(image);
                buttons_cfg[i]->image = malloc((image_len + 1) * sizeof(char));
                strncpy(buttons_cfg[i]->image, image, image_len + 1);
            }

            const char *description;
            valid_options[3] = config_setting_lookup_string(setting, "description", &description);
            if (valid_options[3]) {
                size_t description_len = strlen(description);
                buttons_cfg[i]->description = malloc((description_len + 1) * sizeof(char));
                strncpy(buttons_cfg[i]->description, description, description_len + 1);
            }

            const char *action;
            valid_options[4] = config_setting_lookup_string(setting, "action", &action);
            size_t action_len = strlen(action);
            buttons_cfg[i]->action = malloc((action_len + 1) * sizeof(char));
            strncpy(buttons_cfg[i]->action, action, action_len + 1);

            const char *style;
            valid_options[5] = config_setting_lookup_string(setting, "style", &style);
            if (valid_options[5]) {
                size_t style_len = strlen(style);
                buttons_cfg[i]->style = malloc((style_len + 1) * sizeof(char));
                strncpy(buttons_cfg[i]->style, style, style_len + 1);
            }

            int sel, inv, bind;
            valid_options[6] = config_setting_lookup_bool(setting, "selected", &sel);
            valid_options[7] = config_setting_lookup_bool(setting, "invisible", &inv);
            valid_options[8] = config_setting_lookup_int(setting, "bind", &bind);
            if (valid_options[6]) {
                buttons_cfg[i]->selected = (bool) sel;
            }
            if (valid_options[7]) {
                buttons_cfg[i]->invisible = (bool) inv;
            }
            buttons_cfg[i]->bind = (guint) bind;

            for (int j = 0; j < BUTTON_OPTS; ++j) {
                if (!valid_options[j]) {
                    if (!quiet)
                        fprintf(stderr, "Error in the '%s' button configuration: invalid/missing values. Using the default values instead.\n", button_names[i]);
                    switch (j) {
                        case 0:
                            size_t title_len = strlen("");
                            buttons_cfg[i]->title = malloc((title_len + 1) * sizeof(char));
                            strncpy(buttons_cfg[i]->title, "", title_len + 1);
                            break;
                        case 2:
                            size_t img_len = strlen("");
                            buttons_cfg[i]->image = malloc((img_len + 1) * sizeof(char));
                            strncpy(buttons_cfg[i]->image, "", img_len + 1);
                            break;
                        case 3:
                            size_t descr_len = strlen("");
                            buttons_cfg[i]->description = malloc((descr_len + 1) * sizeof(char));
                            strncpy(buttons_cfg[i]->description, "", descr_len + 1);
                            break;
                        case 5:
                            size_t style_len = strlen(DEF_STYLE);
                            buttons_cfg[i]->style = malloc((style_len + 1) * sizeof(char));
                            strncpy(buttons_cfg[i]->style, DEF_STYLE, style_len + 1);
                            break;
                        case 6:
                            buttons_cfg[i]->selected = (bool) DEF_SEL;
                            break;
                        case 7:
                            buttons_cfg[i]->invisible = (bool) DEF_INV;
                            break;
                        case 1:
                        case 4:
                        case 8:
                            if (!quiet)
                                fprintf(stderr, "Error in the '%s' button configuration: invalid/missing required values. Exiting.\n", button_names[i]);
                            return -1;
                        default:
                            break;
                    }
                }
            }
        }
        else {
            if (!quiet)
                fprintf(stderr, "Error in the '%s' button configuration: invalid/missing values. Exiting.\n", button_names[i]);
        }
    }
    
    config_destroy(&cfg);
    return 0;
}