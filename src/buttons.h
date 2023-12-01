#include <gtk/gtk.h>
#include "conf.h"

#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H

static button *buttons_cfg[N];

static char *command;

void load_buttons_struct(button *buttons_cfg_main[N]);

char *get_command(void);

void button_clicked(GtkWidget *widget, char *action);

void make_label(GtkWidget *vbox, const char *text, const char *name, GtkWidget *arr[N], int i);

void gen_buttons(GtkWidget *grid, struct Config *st);

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

#endif