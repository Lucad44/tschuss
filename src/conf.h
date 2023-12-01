#include <stdbool.h>
#include <gtk/gtk.h>

#pragma once

#ifndef CONF_H
#define CONF_H

#define N 6
#define MAX_USER_SZ 96
#define OPTIONS_NUM 8

static const char *cfg_file = "tschuss.conf";
static const char *css_file = "style.css";

static const char *button_names[N] = {"shutdown", "reboot", "logout", "hibernate", "suspend", "lock"};

extern bool quiet;

struct Config {
    int height;
    int width;
    int border_width;
    int columns;
    char *top_text;
    char *bottom_text;
};

typedef struct {
    char *title;
    char *label;
    char *description;
    char *action;
    char *style;
    bool selected;
    bool invisible;
    guint bind;
} button;

int get_cmd_args(int argc, char *argv[], char *cfg_path, char *css_path);

bool set_paths(bool valid_conf, char *cfg_path, char *css_path);

int load_css(const char *css_file);

int read_cfg(const char *cfg_file, struct Config *st, button *buttons[N]);

#endif