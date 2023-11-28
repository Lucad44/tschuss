#include <gtk/gtk.h>
#include "conf.h"

#pragma once

#ifndef BUTTONS_H
#define BUTTONS_H

void button_clicked(GtkWidget *widget, gpointer data, button buttons_cfg[N]);

void gen_buttons(GtkWidget *grid, struct Config *st, button buttons_cfg[N]);

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data, button buttons_cfg[N]);

#endif