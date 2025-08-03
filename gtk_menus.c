#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void button_popup(GtkWidget *wid, gpointer ptr)
{
    GtkWidget *f_menu = gtk_menu_new();
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
    g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

    gtk_widget_show_all(f_menu);
    gtk_menu_popup_at_pointer(GTK_MENU(f_menu), NULL);
}

void main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close Window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    /* Menu bar */
    GtkWidget *mbar = gtk_menu_bar_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    /* Create menu item "File", then append to menu bar */
    GtkWidget *file_mi = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), file_mi);

    /* Create menu associated with menu item "File", then set
     as submenu of "File". */
    GtkWidget *f_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), f_menu);

    /* Create "Quit" menu item and add to submenu of "File". */
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
    /* Connect to end_program handler. */
    g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

    /* Pop-up menu */
    GtkWidget *pop_btn = gtk_button_new_with_label("Quit Pop-up");
    g_signal_connect(pop_btn, "clicked", G_CALLBACK(button_popup), NULL);

    gtk_box_pack_start(GTK_BOX(box), mbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), pop_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);
    gtk_main();
}
