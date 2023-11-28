#include <stdbool.h>
#include <gtk/gtk.h>

#pragma once

#ifndef CONF_H
#define CONF_H

#define N 6

#define DEF_WIDTH 250
#define DEF_HEIGHT 250
#define DEF_X 800
#define DEF_Y 400
static const char *DEF_TOP = "Top Text";
static const char *DEF_BOTTOM = "Bottom Text";

static const char *cfg_file = "tschuss.conf";
static const char *css_file = "style.css";

static const char *button_names[] = {"shutdown", "reboot", "logout", "hibernate", "suspend", "lock"};

struct Config {
    int height;
    int width;
    int x; 
    int y;
    int border_width;
    int columns;
    char *top_text;
    char *bottom_text;
};

typedef struct {
    char *label;
    char *action;
    bool selected;
    guint bind;
} button;

int load_css(const char *css_file);

int read_cfg(const char *cfg_file, struct Config *st, button buttons[N]);

#endif