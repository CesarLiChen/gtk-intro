#include <gtk/gtk.h>
#include <string.h>

int count = 0;

// Add function to button.
void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

/* First argument is pointer to widget that
generated signal.
Last argument is a general purpose pointer, receives
pointer supplied as last argument to g_signal_connect() */
void count_button(GtkWidget *wid, gpointer ptr)
{
    char buffer [30];
    count++;

    char time[6];
    strcpy(time, (count == 1) ? "time" : "times");

    sprintf(buffer, "Button clicked %d %s", count, time);
    // Cast lbl(now ptr) pointer back to a Label.
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window - Label");

    // Connect handler function to clicked signal gen by button.
    // G_CALLBACK is the handler function.
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);

    // Below makes X button close program correctly.
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");

    GtkWidget *btn2 = gtk_button_new_with_label("Count button");
    // Last parameter asks for a pointer.
    g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);

    // Using a Box widget to put window with button and label
    // since a window can only have 1 widget.
    // gtk_box_new(orientation, spacing) - Orientation 0 - Hor, 1 - Ver
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    /* gtk_box_pack_start(name_of_box, widget, expand, fill, padding)

    expand: if TRUE, will enlarge in proportion. FALSE, will not)
    fill: no effect if expand is FALSE.
        - if expand TRUE, fill FALSE: widget itself stays same size but
        space around it grows.
        - if expand TRUE, fill TRUE: widget itself grows to fill increased
        space.
    padding: in pixels

    There is also a gtk_box_pack_end() which starts adding
    from the bottom. */
    gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

    // Then add Box to Win
    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}

