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

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    GtkWidget *lbl = gtk_label_new("My label");

    /* Radio buttons
    gtk_radio_button_new_with_label(group, name)
    
    First button created can have NULL as it's group */ 
    GtkWidget *rad1 = gtk_radio_button_new_with_label(NULL, "Button 1");
    GSList *group = gtk_radio_button_get_group(
        GTK_RADIO_BUTTON(rad1));
    /* Second button is added to the same group as the first button */
    GtkWidget *rad2 = gtk_radio_button_new_with_label(group, "Button 2");

    g_signal_connect(rad1, "toggled", G_CALLBACK(check_toggle1), rad2);

    GtkAdjustment *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
    txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), rad1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), rad2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), txt, 0, 1, 2, 2);
    gtk_grid_attach(GTK_GRID(grid), btn, 0, 3, 2, 2);    

    gtk_container_add(GTK_CONTAINER(win), grid);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}

