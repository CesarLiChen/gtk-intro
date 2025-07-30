#include <gtk/gtk.h>
#include <string.h>

int count = 0;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}
void count_button(GtkWidget *wid, gpointer ptr)
{
    char buffer [30];
    count++;

    char time[6];
    strcpy(time, (count == 1) ? "time" : "times");

    sprintf(buffer, "Button clicked %d %s", count, time);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window - Label");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");

    GtkWidget *btn2 = gtk_button_new_with_label("Count button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);

    /* Tables are DEPRECATED, use GtkGrid instead 

    // gkt_table_new(rows, columns, homogenous_or_not)
    // homogenous in this case is whether the cell in the table
    // are identically sized.
    GtkWidget *tbl = gtk_table_new(2, 2, TRUE);

    // gtk_table_attach_defaults(table, widget, left_edges, right, top, bottom)
    gtk_table_attach_defaults(GTK_TABLE(tbl), lbl, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tbl), btn2, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tbl), btn, 0, 2, 1, 2);

    */

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    /* gtk_grid_attach(grid, child, left, top, width, height) */
    gtk_grid_attach(GTK_GRID(grid), lbl, 0, 0, 1, 2);
    // gtk_grid_attach_next_to(GTK_GRID(grid), btn2, lbl, GTK_POS_RIGHT, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 2, 2, 10);

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}

