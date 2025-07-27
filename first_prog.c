#include <gtk/gtk.h>

/* Once compiled and ran, you'll notice that 
by clicking on the X closes the window but 
it will still be running in the terminal.
This is because gtk_main is not terminated 
until CTRL+C is done in the terminal. */

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);	
	/* Creates widget of type GtkWindow.
	There is a _new function for every type
	of widget in GTK. */
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(win);
	/* Runs the main loop of GTK. Hands control of 
	program to GTK itself. */ 
	gtk_main();
	return 0;
}
