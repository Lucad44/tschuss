#include <stdbool.h>
#include <gtk/gtk.h>

#pragma once

#ifndef CONF_H
#define CONF_H

#define N 6
#define MAX_USER_SZ 96
#define CONF_OPTS 6
#define BUTTON_OPTS 8

#define DEF_H 100
#define DEF_W 200
#define DEF_BW 5
#define DEF_COLS 2
#define DEF_TOP_TEXT "Power Menu"
#define DEF_BOTTOM_TEXT ""


#define DEF_TITLE ""
#define DEF_STYLE "flat"
#define DEF_SEL 1
#define DEF_INV 0

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