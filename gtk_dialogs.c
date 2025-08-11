#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void open_dialog(GtkWidget *wid, gpointer win_ptr)
{
    GtkWidget *dlg = gtk_dialog_new_with_buttons(
        // Text on title bar of dialog.
        "My dialog box",
        // Pointer to main window passed by g_signal_connect
        GTK_WINDOW(win_ptr),
        /* Controls behaviour of dialog. MODAL means that parent
         window will be locked. DESTROY_WITH_PARENT is for tidiness, in
         the case where the parent somehow closes/crashes, the dialog
         will also close. */
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        // Controls which buttons are displayed with a list of paired values.
        "Ok", 0, "Cancel", 1, NULL
    );

    /* Add label to dialog */
    GtkWidget *lbl = gtk_label_new("A question for you");

    gtk_container_add(
        GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))),
        lbl
    );
    gtk_widget_show(lbl);

    /* gtk_dialog_run automatically shows the widgets which are part
    of the dialog itself; everything else we have to show explicitly,
    like the lbl. */
    int result = gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);
    printf("Return code = %d\n");
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *dlg_btn = gtk_button_new_with_label("For dialog");
    g_signal_connect(dlg_btn, "clicked", G_CALLBACK(open_dialog), win);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), dlg_btn, TRUE, TRUE, 10);

    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
