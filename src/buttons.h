#include <gtk/gtk.h>
#include "conf.h"

#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H

static int selected[N];
static const char *button_labels[N];
static const char *commands[] = {"shutdown now", "reboot", "whoami | loginctl terminate-user", "systemctl hibernate", "systemctl suspend", "lock"};

void load_labels(struct Config *st);

void button_clicked(GtkWidget *widget, gpointer data);

void gen_buttons(GtkWidget *vbox);

char *str_to_lower(const char *s);

#endif