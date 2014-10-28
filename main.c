#include "header.h"

int main (int argc, char ** argv)
{
    gtk_init (& argc, & argv);

    gtk_widget_show_all(createMainWindow());

    gtk_main ();
    return 0;
}
