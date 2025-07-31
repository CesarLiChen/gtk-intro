#include <gtk/gtk.h>

GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void check_toggle(GtkWidget *wid, gpointer ptr)
{
    printf("The state of the button is %d\n",
        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");

    // Check buttons
    GtkWidget *chk = gtk_check_button_new_with_label("Check?");
    /* 
    - By default check btns are unchecked, to change behaviour:
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk), TRUE); 
    
    - To get current state of button [1-checked, 0-unchecked]:
    int state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk)); 
    */
   /* toggled signal instead of clicked signal */
    g_signal_connect(chk, "toggled", G_CALLBACK(check_toggle), NULL);

    GtkAdjustment *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
    txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), chk, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), txt, 0, 1, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 3, 2, 2);    

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}

