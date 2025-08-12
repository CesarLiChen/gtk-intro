#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *btn2 = gtk_button_new_with_label("My button");
    /* function takes as arguments: name of widget, followed by
     NULL-terminated list of property names and property values.
     Relief controls how the border looks.

     This disables the shading on the button. */
    g_object_set(G_OBJECT(btn2), "relief", GTK_RELIEF_NONE, NULL);

    GtkWidget *lbl = gtk_label_new("Custom Lable_eel");
    g_object_set(G_OBJECT(lbl),
                 "use_underline", TRUE, // doesn't seem to work
                 "angle", 45.0, NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), btn2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
