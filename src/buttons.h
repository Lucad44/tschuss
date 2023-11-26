#include <gtk/gtk.h>
#include "conf.h"

#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H

static const char *commands[] = {"shutdown now", "reboot", "whoami | loginctl terminate-user", "systemctl hibernate", "systemctl suspend", "lock"};
static const char *button_names[] = {"shutdown", "reboot", "login", "hibernate", "suspend", "lock"};

void button_clicked(GtkWidget *widget, gpointer data);

void gen_buttons(GtkWidget *grid, struct Config *st);

#endif