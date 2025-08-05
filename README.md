# gtk-intro

GTK (formerly GTK+) - GIMP Toolkit.  
Toolkit for creating Graphical User Interfaces (GUIs).  
*Widgets* - the fundamental building block of GTK projects. 

Developed under a Fedora 41 system.
Installation and compilation instructions from [Fedora's documentation](https://developer.fedoraproject.org/tech/languages/c/gtk.html) on the matter.
- Install necessary packages:
- ```
  sudo dnf install gtk3-devel gstreamer1-devel clutter-devel webkit2gtk3-devel libgda-devel gobject-introspection-devel
  ```
- To compile (e.g. compiling a file called gtk_prog.c):
- ``gcc `pkg-config --cflags --libs gtk+-3.0` -o gtk_prog gtk_prog.c`` (remember the backticks)  
- To run executable that is created, do: `./gtk_prog`

### Follows An Introduction to C & GUI Programming book.

Specifically:  
Ch. 13: Intro to GTK  
- GTK -> GIMP Toolkit
- *Widgets* are the fundamental building blocks.
  - Everything on the screen (window, button, label) is a widget.

Ch. 14: First GTK Program  
- [first_prog.c](first_prog.c) 

Ch. 15: Buttons  
- [gtk_buttons.c](gtk_buttons.c)

Ch. 16: Labels and layout  
- [gtk_labels_layout.c](gtk_labels_layout.c) 
  - Box widget

Ch. 17: More advanced layout
- Worked on top of .c file from Ch. 16 
- `gtk_box_pack_start(name_of_box, widget, expand, fill, padding)`
- Nested vertical and horizontal boxes are perfectly fine and gives
better control over appearance there is simpler way. Tables.
- For below [gtk_tables.c](gtk_tables.c)
- GtkTable widget. [has since been deprecated]
- Use GtkGrid instead.

Ch. 18: GUI user input  
- GtkTextEntry [gtk_text_entry.c](gtk_text_entry.c)
- GtkSpinButton [gtk_spin_btn.c](gtk_spin_btn.c)
- GtkCheckButton [gtk_check_btn.c](gtk_check_btn.c)
- GtkRadioButton [gtk_radio_btn.c](gtk_radio_btn.c)

Ch. 19: Combo boxes and list stores 
- [gtk_combo_box.c](gtk_combo_box.c)
- List stores, although more complicated, makes it easier to sort incoming data for input into the combo boxes.
- [gtk_list_store.c](gtk_list_store.c)

Ch. 20: Tree views  
- Made for List Stores since they're designed to be the data store for GtkTreeView widget.
- [gtk_tree_views.c](gtk_tree_views.c)

Ch. 21: Menus 
- Menus and pop-up menus
- [gtk_menus.c](gtk_menus.c)

Ch. 22: Dialogs  
Ch. 23: Built-in dialogs  
Ch. 24: Customising widgets  
Ch. 25: Glade  
