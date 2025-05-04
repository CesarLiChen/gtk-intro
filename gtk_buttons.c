#include <gtk/gtk.h>

// Add function to button.
void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close window");

	// Connect handler function to clicked signal gen by button.
	// G_CALLBACK is the handler function.
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);

	// Below makes X button close program correctly.
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

	// GtkWindow is a child of GtkContainer
	// Cast win to GtkContainer
	gtk_container_add(GTK_CONTAINER (win), btn);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

