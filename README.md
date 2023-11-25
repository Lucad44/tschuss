# tschuss
Simple and fast customisable dropdown power menu for Linux systems.
Please read the instructions below in order to configure it and customise it properly.

# Customisation - CSS
Modify the `style.css` file in order to change the colour, background, font, borders and everything else CSS-related.

There's a `#window` label that allows you to customise the main window where everything is placed upon.

Then there are 5 button labels (namely `#button-shutdown`, `#button-reboot`, `#button-logout`, `#button-hibernate` and `#button-suspend`) 
whose properties you can edit in order to modify each of the 5 buttons individually. 

If you need to modify all the `button` category at once, there's a `button` (**W/O** the '#', otherwise it won't work) label which shall suit your needs.

If you wish you can modify and rebuild the c-code directly if you need to change the labels' names, or make any other change.

# Configuration
Edit the `tschuss.conf` configuration file, where you'll be able to to modify the size, ability to move it with your cursor and more.

**Location**

There are 9 possible locations which can be specified either by name or by number, the corresponding number is listed next to the names below, the default is centre.
1. center 0
2. top_left 1
3. top 2
4. top_right 3
5. right 4
6. bottom_right 5
7. bottom 6
8. bottom_left 7
9. left 8 

In order to edit the location, you must insert a parameter (0-8 or the text equivalent) after the launch tschuss command.

For example:

    `tschuss 1`

if you wish to launch it in the top-left corner.

I highly recommend either setting up an hotkey to open the dropdown menu or a designated button. Check your desktop entry wiki if you don't know how to do that.
