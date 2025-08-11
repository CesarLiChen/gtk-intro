#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

static void file_selected(GtkFileChooserButton *btn, gpointer ptr)
{
    printf("%s selected\n",
           gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(btn)));
}

static void save_file(GtkWidget *btn, gpointer ptr)
{
    GtkWidget *sch = gtk_file_chooser_dialog_new(
        "Save file",
        GTK_WINDOW(ptr),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        // Order somehow important
        "Cancel", 0, "Ok", 1, NULL);

    if (gtk_dialog_run(GTK_DIALOG(sch)) == 1)
    {
        printf("%s selected\n",
               gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(sch)));
    }
    gtk_widget_destroy(sch);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(win), box);

    /* First argument is the title for the file chooser.
     Second determines what the file chooser window will do. */
    GtkWidget *fc_btn = gtk_file_chooser_button_new(
        "Select file",
        GTK_FILE_CHOOSER_ACTION_OPEN
    );
    g_signal_connect(fc_btn, "file-set", G_CALLBACK(file_selected), NULL);

    /* We had to create the button to open the dialog with the handler
     function. */
    GtkWidget *sv_btn = gtk_button_new_with_label("Save THIS");
    g_signal_connect(sv_btn, "clicked", G_CALLBACK(save_file), win);

    gtk_box_pack_start(GTK_BOX(box), fc_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), sv_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
