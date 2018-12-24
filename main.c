#include <stdlib.h>
#include <gtk/gtk.h>

void on_window_destroy(GtkWidget *wid, gpointer data)
{
    gtk_main_quit();
}
/* Callback for close button */
void on_button_clicked(GtkWidget *button, GtkTextBuffer *buffer)
{
    GtkTextIter start;
    GtkTextIter end;
    gchar *text;
    /* Obtain iters for the start and end of points of the buffer */
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    /* Get the entire buffer text. */
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    /* Print the Text */
    g_print("%s", text);

    g_free(text);
    gtk_main_quit();
}

static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;
  GtkWidget *text_view = NULL;
  GtkTextBuffer *buffer;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "Simple Multiline Text Imput");
  gtk_window_set_default_size(GTK_WINDOW(win), 300, 300);
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /* Create a vertical box with buttons */
  vbox = gtk_vbox_new (FALSE, 2);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  /* Create a multiline text widget */
  text_view = gtk_text_view_new();
  gtk_box_pack_start (GTK_BOX (vbox), text_view, 1, 1, 0);

  /* Obtaining the buffer associatid with the widget */
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  /* Set the default buffer text. */
  gtk_text_buffer_set_text(buffer, "Salut acesta este textul!", -1);

//  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
//  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
//  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", on_button_clicked, buffer);
  gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);

  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
