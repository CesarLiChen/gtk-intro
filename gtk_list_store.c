#include <gtk/gtk.h>

GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void check_toggle1(GtkWidget *wid, gpointer ptr)
{
    printf("The state of the button 1 is %s\n",
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)) ? "On" : "Off" );

    printf("The state of the button 2 is %s\n",
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ptr)) ? "On" : "Off" );
}

void combo_changed(GtkWidget *wid, gpointer ptr)
{
    int sel = gtk_combo_box_get_active(GTK_COMBO_BOX(wid));
    /* Gives error for list store */
    char *selected = gtk_combo_box_text_get_active_text(
        GTK_COMBO_BOX_TEXT(wid));
    printf("The value of the combo is %d %s\n", sel, selected);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");
    GtkWidget *rad1 = gtk_radio_button_new_with_label(NULL, "Button 1");
    GSList *group = gtk_radio_button_get_group(
        GTK_RADIO_BUTTON(rad1));
    GtkWidget *rad2 = gtk_radio_button_new_with_label(group, "Button 2");
    g_signal_connect(rad1, "toggled", G_CALLBACK(check_toggle1), rad2);

    /* List stores */
    int pos = 0;
    /* gtk_list_store_new(num_cols, types_of_data); */
    GtkListStore *ls = gtk_list_store_new(1, G_TYPE_STRING);
    /* gtk_list_store_insert_with_values(
        list_store, iterator, position_index, column_for_data, data, terminates_list_of_pairs);
    */
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Option 1", -1);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Option 2", -1);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Option 3", -1);

    /* Use model ls, cast model to GtkTreeModel since this is the data
    that is used by a combo box */
    GtkWidget *comb = gtk_combo_box_new_with_model(GTK_TREE_MODEL(ls));

    /* Cell renderer is a code object used to create graphical
    representation of data in a table. In this case a text renderer. */
    GtkCellRenderer *rend = gtk_cell_renderer_text_new();

    /* Add renderer to cell layout of combo box, meaning that renderer
    will be called when the combox box wants to display some data.
    Last parameter, is whether or not the data is expanded to fill free
    space in the layout. It does not have effect on combo box. */
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comb), rend, FALSE);
    /* Sets 'text attribute of cell renderer to the data from the
    supplied column number (0) of the list store. This will cause
    renderer to display the data in column 0 as text in the
    combo box */
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(comb), rend, "text", 0);

    /* EXAMPLE (why list stores are better)
    For real life scenarios the options being put are not going to come
    in order. With list stores they can be sorted.

    Below takes original list store and sorts it alphabetically.

    GtkTreeModelSort *sorted = GTK_TREE_MODEL_SORT(
        gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(ls)));

    gtk_tree_sortable_set_sort_column_id(
        GTK_TREE_SORTABLE(sorted), 0, GTK_SORT_ASCENDING);

    GtkWidget *comb = gtk_combo_box_new_with_model(
        GTK_TREE_MODEL(sorted));
    */
    g_signal_connect(comb, "changed", G_CALLBACK(combo_changed), NULL);

    GtkAdjustment *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
    txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), rad1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), rad2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), txt, 0, 1, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), comb, 0, 3, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 5, 2, 2);

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
