#include "../header.h"

GtkWindow * createMainWindow()
{

    GtkWidget *win = NULL;
    GtkWidget *vbox = NULL;
    GtkWidget *vboxdroite = NULL;
    GtkWidget *hbox = NULL;
    GtkWidget *button[3];
    GtkWidget *label[7];
    GtkComboBox *combo=NULL;
    t_liste_contacts *liste_contacts;
    int i=0;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (win, "Gestionnaire contacts");
    gtk_window_set_default_size (win, 500, 300);
    gtk_container_set_border_width (win, 5);
    gtk_window_set_position (win, GTK_WIN_POS_CENTER);

    /* Ajout du conteneur principal et des boutons. */
    vbox = gtk_vbox_new (TRUE, 5);
    vboxdroite = gtk_vbox_new (TRUE, 5);
    hbox = gtk_hbox_new (TRUE, 5);

    gtk_container_add (hbox, vbox);
    gtk_container_add (hbox, vboxdroite);
    gtk_container_add (win, hbox);

    button[0] = gtk_button_new_with_label ("Ajouter un contact");
    gtk_box_pack_start (vbox, button[0], TRUE, TRUE, 2);
    button[1] = gtk_button_new_with_label ("Supprimer le contact");
    gtk_box_pack_start (vbox, button[1], TRUE, TRUE, 2);
    button[2] = gtk_button_new_with_label ("Modifier le contact");
    gtk_box_pack_start (vbox, button[2], TRUE, TRUE, 2);

    ///Lecture du fichier de sauvegarde et affichage de la combobox
    liste_contacts=read_contacts();
    combo=combo_affichage(vbox, liste_contacts);
    show_contact(combo,hbox);

    g_signal_connect (win, "destroy", G_CALLBACK (save_contacts), liste_contacts);
    g_signal_connect (combo, "changed", G_CALLBACK (show_contact), hbox);
    g_signal_connect (button[0], "clicked", G_CALLBACK (add_contact),liste_contacts);
    g_signal_connect (button[1], "clicked", G_CALLBACK (remove_contact),liste_contacts);
    g_signal_connect (button[2], "clicked", G_CALLBACK (modify_contact),liste_contacts);

    return win;
}
