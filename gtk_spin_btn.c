#include <gtk/gtk.h>

GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void copy_text(GtkWidget *wid, gpointer ptr)
{
    // const makes variable not changeable by programmer.
    const char *input = gtk_entry_get_text(GTK_ENTRY (txt));
    gtk_label_set_text(GTK_LABEL(ptr), input);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");

    GtkWidget *btn2 = gtk_button_new_with_label("Copy button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(copy_text), lbl);

    /* GtkAdjustment is used to set range of values that a 
    spin button and other similar widgets can take. */

    /* gtk_adjustment_new(default, min, max, step_size, 
        'page_increments', 'page_increments'); 
        
    Page increments are used on other controls where 
    there are 2 different sets of buttons to
    change values. They not used on spin buttons. */
    GtkAdjustment *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
    /* gtk_spin_button_new(adjustment, climb_rate, decimal_places*/
    txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    /* gtk_grid_attach(grid, child, left, top, width, height) */
    gtk_grid_attach(GTK_GRID(grid), lbl, 0, 0, 1, 1);
    // gtk_grid_attach_next_to(GTK_GRID(grid), btn2, lbl, GTK_POS_RIGHT, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), txt, 0, 1, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 3, 2, 2);    

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}

