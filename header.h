#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gerror.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct contact
{
    char *nom;
    char *prenom;
    char *tel;
    char *adresse;
    char *mail;
    char *birthday;
    char *note;
    char *img;
    GdkPixbuf *image;
    int nb_ouverture;
    struct contact *next;
}t_contact;

typedef struct liste
{
    t_contact *ancre;
    int nb_contact;

}t_liste_contacts;

void show_contact (GtkWidget *wid, gpointer data);
void remove_contact (GtkWidget *wid,t_liste_contacts *liste_contacts);
GtkWidget* combo_affichage(GtkWidget *vbox,t_liste_contacts *liste);
void remplir(t_liste_contacts *liste,GtkListStore *model);
void add_contact(GtkWidget *wid,t_liste_contacts *liste);
t_contact *get_active_data (GtkComboBox *combo);
t_contact *new_contact(t_liste_contacts *liste_contacts);
void sauvegarder(GtkWidget *,t_liste_contacts *);
void save_contacts(GtkWidget *,t_liste_contacts *);
void choose_file(GtkWidget *wid,t_contact *contact);
void modify_contact(GtkWidget *wid,t_liste_contacts *liste_contacts);
void sauvegarder_modif(GtkWidget *wid,t_liste_contacts *liste_contact);

#endif // HEADER_H_INCLUDED
