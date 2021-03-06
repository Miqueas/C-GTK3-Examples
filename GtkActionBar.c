#include <gtk/gtk.h>

void app_activate(GApplication *self, gpointer data);
void app_startup(GApplication *self, gpointer data);

int main(int argc, char **argv) {
  const gchar *app_id = "com.github.Miqueas.C-GTK3-Examples.GtkActionBar";
  GtkApplication *app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}

void app_activate(GApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win, *header, *bar, *box;

  win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "My App",
    "subtitle", "An awesome app that you'll love",
    NULL
  );

  bar = g_object_new(
    GTK_TYPE_ACTION_BAR,
    "visible", TRUE,
    NULL
  );

  gtk_action_bar_pack_start(
    GTK_ACTION_BAR(bar),
    g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "Something", NULL)
  );

  gtk_action_bar_pack_end(
    GTK_ACTION_BAR(bar),
    g_object_new(GTK_TYPE_BUTTON, "visible", TRUE, "label", "A button", NULL)
  );

  box = g_object_new(
    GTK_TYPE_BOX,
    "visible", TRUE,
    "orientation", GTK_ORIENTATION_VERTICAL,
    NULL
  );

  gtk_box_pack_start(
    GTK_BOX(box),
    g_object_new(GTK_TYPE_LABEL, "visible", TRUE, "label", "App content", NULL),
    TRUE,
    TRUE,
    0
  );

  gtk_box_pack_end(
    GTK_BOX(box),
    bar,
    FALSE,
    TRUE,
    0
  );

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}