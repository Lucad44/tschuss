# tschuss
Simple and fast highly customisable dropdown power menu for Linux systems.
Please read the instructions below in order to configure it and customise it properly.

![example1](images/preview1.png)

![example2](images/preview2.png)

*Note: if you notice the 'icons' are not exactly centred, it's because I'm using Nerd Fonts in the example pictures, which sometimes glitch*

# Dependencies

## Build dependencies

* GTK+
* GObject Introspection
* libconfig
* meson
* gtk-layer-shell (optional)

# Installation

## Meson

Just run these commands in the terminal. Be sure to have `git` and `meson` and `ninja` installed.

```
git clone https://github.com/Lucad44/tschuss
cd tschuss
meson setup build
meson compile -C build
sudo meson install -C build
```

The executable file will be in found in `.../tschuss/build/tschuss`, but meson will also install it in `/usr/local/bin`, so you can run it simply by typing `tschuss` in the terminal.

A default configuration and a default CSS file will be placed in the `/etc/tschuss/` folder. You should copy those files to a path of your liking and edit them there (default path `~/.config/tschuss/` is recommended).


# Run

Run `tschuss` and exit via the `ESC` key.

# Command line options

There currently are 5 command line options. You can find out about them via the `--help` command line option.

# Customisation

## CSS
Modify the `style.css` file in order to change the colour, background, font, raidiuses, borders and everything else CSS-related.

The default path is `~/.config/tschuss/style.css`, but you can edit the CSS file path via the `--css-file` command line option.

There's a `#window` label that allows you to customise the main window where everything is placed upon.

Then there are 6 button labels (namely `#shutdown`, `#reboot`, `#logout`, `#hibernate` and `#suspend`) 
whose properties you can edit in order to modify each of the 6 buttons individually. 

All the other single button labels inherit from this names, with a single hyphen in the middle.
For example, `#shutdown-title` to edit the text in the top of the button, `#shutdown-label` to edit the main label in the centre and `#shutdown-description` to edit the text under the main label.

If you need to modify all the `button` category at once, there's a `button` (**W/O** the '#') label which shall suit your needs.

The `#top-text` `#bottom-text` refer instead to the paragraph you can add above or under respectively the button grid.

# Configuration

Edit the `tschuss.conf` configuration file, in order to modify the window's and button grid's properties.

The default path for the config file is `~/.config/tschuss/tschuss.conf`, but you can set any path via the `--config-file` command line option, altough not recommended. 

For all the options with the *optional* tag, a default setting will be used if none is found in the config file. Instead, the program will be aborted for missing/invalid config values W/O the *optional* tag. 

The semicolons (`';'`) are completely optional in the configuration file.

## Window options

**Height** (`height`, *optional*)

The height of the current windows.

**Width** (`width`, *optional*)

Same thing, but in the other direction.

**Border width** (`border_width`, *optional*)

The distance between the button grid and the window external border.

**Columns** (`columns`, *optional*)

The number of columns which will be present in the grid. Keep in mind that this will also affect the number of buttons per row. The value should be in the range [1-6], otherwise the default one (2) will be used.

**Top paragraph** (`top_text`, *optional*)

Add a paragraph above the button grid (a title for example). If you don't want it just set the option to `""`.

**Bottom paragraph** (`bottom_text`, *optional*)

Same thing as above, but below the grid this time.

## Button options

Remember that you can set a different option for every button.

If you should set any of the following text options to `""` in order to turn them off, they shan't be displayed and the spacing and height will be fixed accordingly, so don't worry about it.

**Title** (`title`, *optional*)

Text which will be positioned in the top third of the button. 


**Label** (`label`)

Text which will be positioned in the middle of the button. 

**Image** (`image`, *optional*)

Image which will be positioned in the middle of the button, below the title but above the label.
While you could do that, I do not recommend having both a label and an image.
If you decide to use an image, you MUST also specify its width and height, in the `img_size` config parameter.

**Image size** (`img_size`, *optional* altough *required* if you set an image)

The width and height of the image used in the button, which you can scale however you like with this option. I'd recommend setting an equal value for both, so that the resulting image will be square, but you can do whatever you please.

*Note that the program will be aborted if an image is set but not its scaling width and height.*

**Description** (`description`, *optional*)

Text which will be position in the bottom third of the button.

**Action** (`action`)

The command which will be executed on the button press. There aren't any safety checks, so please don't do anything stupid (the string is parsed directly with the `system` function).

**Style** (`style`, *optional*)

The style context of the button. As of now, the only two valid options are "circular" and "flat" (default). 

**Selected** (`style`, *optional*)

A boolean value. Set it to `true` to turn on the button, otherwise the button which will be skipped and the next buttons shifted one position back, in order to not leave any holes.

**Invisible** (`invisible`, *optional*)

A boolean value. Similar to the `selected` option, but the buttons won't be shifted back with this option.
The two options are NOT mutually exclusive.

**Bind** (`bind`)

Set a key to execute the `action` command when the program is open. As of now, you must use an ASCII (and not UNICODE) character, and write it in the config as an integer, corresponding to its value on the ASCII table. For example `'a'` should be written as `97` in the config.
Check out https://en.wikipedia.org/wiki/ASCII for more information.

NOTE that the `ESC` key (27) is reserved for exiting the program.


# Final notes and troubleshooting

**IMPORTANT**

Keep in mind that all the required values (without the *optional* tag) in the configuration must be set to something for the program to start, otherwise it will output an error and abort.

**Transparent background**

I haven't had the possibility to check it myself, but you should be able to set a background transparency via the CSS file on X11 systems.

Instead if your system is running on, for example, Wayland, you must do it from your display server configuration file.
For example, on Hyprland you can add in your `hyprland.conf` config file this line:

`windowrule = opacity <opacity value> override,^(Tschuss)$`

**Moving the window to a certain position**

Again, you must do this from your display server's configuration. 
In Hyprland, for example, you could do:

`windowrule = move <x pixel> <y pixel>,^(Tschuss)$`

Keep in mind that coordinates are referring to bottom-left corner of the window on Hyprland.
If you need more information, look it up on your display server's wiki.
I'm fairly certain I could add the option to specify the coordinates directly in the program on X11, I'll eventually release an update if that's the case.

