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
- `gcc gtk_prog.c -o gtk_prog \`pkg-config --cflags --libs gtk+-3.0\``
- To run executable that is created, do: `./gtk_prog`
