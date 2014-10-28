#include "../header.h"

///Création de la combobox
GtkWidget* combo_affichage(GtkWidget *vbox,t_liste_contacts *liste)
{
    GtkListStore      *model  = NULL;
    GtkCellRenderer   *cell   = NULL;
    GtkComboBox *combo;
    t_contact *contact;

    /*
     * Creation d'un modele pour le GtkComboBox. Ce modele permettra d'afficher
     * deux textes sur deux colonnes + une image + un pointeur de la stuct contact.
     */
    model=gtk_list_store_new (4,GDK_TYPE_PIXBUF,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_POINTER);


    /*
     * Creation d'un GtkComboBox avec son modele.
     */
    combo = gtk_combo_box_new_with_model (model);
    gtk_box_pack_start (vbox, combo, TRUE, TRUE, 0);


    /*
     * On met en place un gestionnaire de rendu des cellules. Il faut en
     * creer un par colonne et suivant le type de chaque donnees.
     *
     */

    cell = gtk_cell_renderer_pixbuf_new();
    gtk_cell_layout_pack_start( GTK_CELL_LAYOUT(combo), cell, FALSE );
    gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT(combo), cell, "pixbuf", 0, NULL );

    cell = gtk_cell_renderer_text_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), cell, FALSE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo),cell, "text", 1,NULL);

    cell = gtk_cell_renderer_text_new ();
    gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), cell, FALSE);
    gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo),cell, "text", 2,NULL);

    remplir(liste,model);
    gtk_combo_box_set_active (combo, 0);
    return combo;
}

///Remplissage combobox
void remplir(t_liste_contacts *liste,GtkListStore *model)
{
    GtkTreeIter iter;
    t_contact *tmp;
    int i;
    /*
       * Remplissage du magasin.
       */
    tmp=liste->ancre;
    for (i=0; i<(liste->nb_contact); i++)
    {
        /* Ajpout d'un nouvel element dans le magasin. */
        gtk_list_store_append (model, &iter);

        /* On rempli le nouvel element. */
        gtk_list_store_set (model, &iter,0,tmp->image,1,tmp->prenom, 2, tmp->nom,3,tmp,-1);
        tmp=tmp->next;
    }
}


///Récupérer le contact actif de la combobox
t_contact *get_active_data (GtkComboBox *combo)
{
    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    t_contact *contact;


    /* On recupere le modele qu'on a cree. */
    model = gtk_combo_box_get_model (combo);

    /* On recupere le GtkTreeIter de l'element courant. */
    if (gtk_combo_box_get_active_iter (combo, &iter))
    {
        /*
         * On recupere les donnees de l'element courant
         */
        gtk_tree_model_get (model,&iter,3,&contact,-1);
    }
    else
    contact=NULL;

    return contact;
}
