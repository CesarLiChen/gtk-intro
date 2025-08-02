#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void row_selected(GtkWidget *wid, gpointer ptr)
{
    GtkTreeSelection *sel;
    GtkTreeModel *model;
    /* We need an iterator to find out which row is selected. An iterator
     is a data structure which stores the location of a row in a list store. */
    GtkTreeIter iter;
    char *option;

    /* Gets the tree view selection. It will store which row (or rows)
     are currently highlighted. */
    sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(wid));
    /* Checks whether selection is valid. Important to Checks as
     next line will cause a crash if no row is selected. */
    if (gtk_tree_selection_get_selected(sel, &model, &iter))
    {
        /* Get actual value from model and iterator.
         After the model argument, next are the paired values. The first
         one is the column to be read, and the second one is the pointer
         to where the data should be written. Since many pairs could
         be arguments, the -1 says that it is the end of entries.*/
        gtk_tree_model_get(model, &iter, 0, &option, -1);
        printf("The selected row contains the text %s\n", option);
    }
}

void main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close Window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    int pos = 0;

    /* Create 2-col list store, col 0 -> text string, col 1 -> pixbuf (or
    pixel buffer, used to store images) */
    GtkListStore *ls = gtk_list_store_new(2, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    /* Create GdkPixbuf with smal image. */
    GdkPixbuf *icon = gtk_icon_theme_load_icon(
        gtk_icon_theme_get_default(), "dialog-ok-apply", 32, 0, NULL);

    /* String into col 0 and icon image into col 1 */
    gtk_list_store_insert_with_values(
        ls, NULL, pos++, 0, "Option 1", 1, icon, -1);
    gtk_list_store_insert_with_values(
        ls, NULL, pos++, 0, "Option 2", 1, icon, -1);
    gtk_list_store_insert_with_values(
        ls, NULL, pos++, 0, "Option 3", 1, icon, -1);

    /* Creates GtkTreeView to display list store. */
    GtkWidget *tv = gtk_tree_view_new_with_model(
        GTK_TREE_MODEL(ls));

    /* Create renderers for all types of data we want to display.
    For us, Text renderer and Pixbuf renderer. */
    GtkCellRenderer *prend = gtk_cell_renderer_pixbuf_new();
    GtkCellRenderer *trend = gtk_cell_renderer_text_new();

    /* Insert columns into the tree view. -1 means inserting at the end.
    3rd parameter - column title.
    4th parameter - GtkCellRenderer
    5th, 6th parameter - passed to Cell Renderer itself and sets attribute
    of the renderer to the data in a certain column of the list store;
    e.g. we set pixbuf attribute of pixbuf renderer to the data in column 1,
    and then set text attribute of the text renderer to the data in column 0.
    Final argument is NULL to signify no more attributes to set, as some
    renderers accept more than 2.
    */
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(tv), -1, "Icon", prend, "pixbuf", 1, NULL);

    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(tv), -1, "Option", trend, "text", 0, NULL);

    g_signal_connect(tv, "cursor-changed", G_CALLBACK(row_selected), NULL);

    GtkWidget *grid = gtk_grid_new();
    // gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    // gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), tv, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 1, 2, 1);

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
}
