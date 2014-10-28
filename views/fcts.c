#include "../header.h"

///Afficher les infos du contact
void show_contact(GtkWidget *combo,gpointer hbox)
{
    GtkWidget* vboxright= NULL;
    GtkWidget* table=NULL;
    GList *liste;
    GtkWidget* label[7];
    GtkWidget* text[7];
    t_contact *contact;
    int i;


    contact=get_active_data(combo);
    if(contact!=NULL)
    {
        liste=gtk_container_get_children(hbox);
        vboxright = (GtkWidget*) g_list_nth_data(liste, 1);
        gtk_widget_destroy(vboxright);

        vboxright = gtk_vbox_new (TRUE, 5);
        gtk_container_add (hbox, vboxright);

        table=gtk_table_new(11,2,TRUE);

        gtk_container_add (vboxright, table);

        gtk_table_attach(table,gtk_image_new_from_pixbuf(contact->image) , 1, 2, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

        for(i=0; i<7; i++)
        {
            text[i] = gtk_label_new("NULL");
            gtk_table_attach(table, text[i], 0, 1, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
            label[i] = gtk_label_new("NULL");
            gtk_table_attach(table, label[i], 1, 2, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
        }
        gtk_label_set_text(text[0],"Nom: ");
        gtk_label_set_text(text[1],"Prenom: ");
        gtk_label_set_text(text[2],"Telephone: ");
        gtk_label_set_text(text[3],"Adresse: ");
        gtk_label_set_text(text[4],"Email: ");
        gtk_label_set_text(text[5],"Date de naissance: ");
        gtk_label_set_text(text[6],"Note: ");

        gtk_label_set_text(label[0],contact->nom);
        gtk_label_set_text(label[1],contact->prenom);
        gtk_label_set_text(label[2],contact->tel);
        gtk_label_set_text(label[3],contact->adresse);
        gtk_label_set_text(label[4],contact->mail);
        gtk_label_set_text(label[5],contact->birthday);
        gtk_label_set_text(label[6],contact->note);

        gtk_widget_show_all (vboxright);
    }
}

///Ajouter un contact
void add_contact(GtkWidget *wid,t_liste_contacts *liste_contacts)
{
    GtkWidget *vboxright,*table, *win;
    GtkButton *button,*chooser;
    GList *liste;
    GtkWidget *label[7];
    GtkWidget* text[7];
    t_contact *contact;
    int i;

    contact=new_contact(liste_contacts);

    wid=gtk_widget_get_ancestor (wid,GTK_TYPE_HBOX);
    liste=gtk_container_get_children(wid);
    vboxright = (GtkWidget*) g_list_nth_data(liste, 1);
    gtk_widget_destroy(vboxright);

    button=gtk_button_new_with_label ("Sauvegarder");
    chooser=gtk_button_new_with_label ("Choisir image...");

    vboxright = gtk_vbox_new (TRUE, 0);

    ///Table
    table = gtk_table_new(12,2,TRUE);
    gtk_table_set_row_spacings(table, 6);
    gtk_table_set_col_spacings(table, 6);
    gtk_container_add(vboxright,table);

    gtk_container_add (wid,vboxright);
    //gtk_container_add(vboxright, gtk_image_new_from_pixbuf(contact->image));
    gtk_table_attach(table,gtk_image_new_from_pixbuf(contact->image) , 1, 2, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

    for(i=0; i<7; i++)
    {
        label[i] = gtk_label_new("NULL");
        gtk_table_attach(table, label[i], 0, 1, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
        text[i]= gtk_entry_new();
        gtk_entry_set_editable(text[i], "0");
        gtk_table_attach(table, text[i], 1, 2, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

    }

    gtk_table_attach(table, chooser, 0, 1, 11, 12, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
    gtk_table_attach(table, button, 1, 2, 11, 12, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

    gtk_label_set_text(label[0],"Nom:");
    gtk_label_set_text(label[1],"Prenom:");
    gtk_label_set_text(label[2],"Telephone:");
    gtk_label_set_text(label[3],"Adresse");
    gtk_label_set_text(label[4],"Email:");
    gtk_label_set_text(label[5],"Anniversaire:");
    gtk_label_set_text(label[6],"Note:");

    gtk_widget_show_all (wid);

    g_signal_connect (chooser, "clicked", G_CALLBACK (choose_file), contact);
    g_signal_connect (button, "clicked", G_CALLBACK (sauvegarder), liste_contacts);
}

///Sauvegarder le contact lors de l'ajout
void sauvegarder(GtkWidget *wid,t_liste_contacts *liste_contacts)
{
    char temp[100];
    GtkWidget* text[7],*combo,*hbox,*vbox;
    GList *liste;
    t_contact *contact;
    int i;

    (liste_contacts->nb_contact)++;
    contact=liste_contacts->ancre;
    if(contact->next==NULL)
        contact=liste_contacts->ancre;
    else
    {
        while(contact->next!=NULL)
        {
            contact=contact->next;
        }
    }

    wid=gtk_widget_get_ancestor (wid,GTK_TYPE_TABLE);
    liste=gtk_container_get_children(wid);

    for(i=0; i<7; i++)
    {
        //printf("%d",((14-2*i)+(contact->nb_ouverture)));
        text[i] = (GtkWidget*) g_list_nth_data(liste, ((14-2*i)+(contact->nb_ouverture)));
    }


    printf("%s\n",gtk_entry_get_text(text[0]));
    sprintf(temp, "%s", gtk_entry_get_text(text[0]));
    contact->nom=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->nom ,temp);

    printf("%s\n",gtk_entry_get_text(text[1]));
    sprintf(temp, "%s", gtk_entry_get_text(text[1]));
    contact->prenom=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->prenom ,temp);

    printf("%s\n",gtk_entry_get_text(text[2]));
    sprintf(temp, "%s", gtk_entry_get_text(text[2]));
    contact->tel=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->tel ,temp);

    printf("%s\n",gtk_entry_get_text(text[3]));
    sprintf(temp, "%s", gtk_entry_get_text(text[3]));
    contact->adresse=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->adresse ,temp);

    printf("%s\n",gtk_entry_get_text(text[4]));
    sprintf(temp, "%s", gtk_entry_get_text(text[4]));
    contact->mail=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->mail ,temp);

    printf("%s\n",gtk_entry_get_text(text[5]));
    sprintf(temp, "%s", gtk_entry_get_text(text[5]));
    contact->birthday=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->birthday ,temp);

    printf("%s\n",gtk_entry_get_text(text[6]));
    sprintf(temp, "%s", gtk_entry_get_text(text[6]));
    contact->note=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->note ,temp);

    hbox=gtk_widget_get_ancestor (wid,GTK_TYPE_HBOX);
    liste=gtk_container_get_children(hbox);
    vbox = (GtkWidget*) g_list_nth_data(liste, 0);
    liste=gtk_container_get_children(vbox);
    combo = (GtkWidget*) g_list_nth_data(liste, 3);

    gtk_widget_destroy(combo);
    combo=combo_affichage(vbox, liste_contacts);
    gtk_widget_show_all (combo);
    g_signal_connect (combo, "changed", G_CALLBACK (show_contact), hbox);
    show_contact(combo,hbox);
}

///Création d'un nouveau contact dans la liste chainée
t_contact *new_contact(t_liste_contacts *liste_contacts)
{
    t_contact *contact,*tmp;

    contact=(t_contact *)malloc(sizeof(t_contact));
    tmp=liste_contacts->ancre;
    if(tmp==NULL)
        liste_contacts->ancre=contact;
    else
    {
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=contact;
    }
    contact->image = gdk_pixbuf_new_from_file_at_size("images/unknown.png", 100, 100, NULL);
    contact->img=(char*)malloc((strlen("images/unknown.png")+1)*sizeof(char));
    strcpy(contact->img,"images/unknown.png");
    contact->img[strlen(contact->img)]='\0';
    contact->nb_ouverture=0;
    contact->next=NULL;

    return contact;
}

///Supprimer le contact
void remove_contact(GtkWidget *wid,t_liste_contacts *liste_contacts)//Fonction qui supprime l'element courant du GtkComboBox
{
    GtkTreeModel *model;
    GtkWidget *combo,*vbox,*hbox;
    GList *liste;
    GtkTreeIter iter;
    t_contact *contact,*prec_contact,*tmp;

    hbox=gtk_widget_get_ancestor (wid,GTK_TYPE_HBOX);
    liste=gtk_container_get_children(hbox);
    vbox = (GtkWidget*) g_list_nth_data(liste, 0);
    liste=gtk_container_get_children(vbox);
    combo = (GtkWidget*) g_list_nth_data(liste, 3);

    if(liste_contacts->ancre!=NULL)
    {
        contact=get_active_data(combo);
        printf("\nRemove %s %s",contact->prenom,contact->nom);
        gtk_widget_destroy(combo);

        prec_contact=liste_contacts->ancre;
        if(prec_contact!=contact)
        {
            while(prec_contact->next!=contact)
            {
                prec_contact=prec_contact->next;
            }
            tmp=prec_contact->next;
            prec_contact->next=prec_contact->next->next;
            free(tmp);
        }
        else
        {
            liste_contacts->ancre=prec_contact->next;
            free(prec_contact);
        }
        liste_contacts->nb_contact--;
        combo=combo_affichage(vbox, liste_contacts);

        ///Problème avec le gtk_list_store_remove => Crash
        /*
        ///On recupere le modele qu'on a cree.
        model = gtk_combo_box_get_model (combo);
        printf("%d",&iter);
        /// On recupere le GtkTreeIter de l'element courant.
        if (gtk_combo_box_get_active_iter (combo, &iter))
        {
             //On supprime l'element courant.
           gtk_list_store_remove (model, &iter);
        }*/
        printf("\nContact deleted");
        gtk_widget_show_all (combo);
        g_signal_connect (combo, "changed", G_CALLBACK (show_contact), hbox);
        show_contact(combo,hbox);
    }
}


///Modifier le contact actif
void modify_contact(GtkWidget *wid,t_liste_contacts *liste_contacts)
{
   //t_contact *contact,*prec_contact;
    GtkTreeModel *model;
    GtkWidget *combo;
    GList *liste;
    GtkTreeIter iter;
    t_contact *contact,*prec_contact,*tmp;
    GtkWidget *vboxright,*table;
    GtkButton *button,*chooser;
    GtkWidget *label[7];
    GtkWidget* text[7];
    int i;

    wid=gtk_widget_get_ancestor (wid,GTK_TYPE_VBOX);
    liste=gtk_container_get_children(wid);
    combo = (GtkWidget*) g_list_nth_data(liste, 3);

    if(liste_contacts->ancre!=NULL)
    {
        contact=get_active_data(combo);
        contact->nb_ouverture=0;
        combo=combo_affichage(wid, liste_contacts);
        printf("\nModify %s %s",contact->prenom,contact->nom);
        gtk_widget_destroy(combo);

        wid=gtk_widget_get_ancestor (wid,GTK_TYPE_HBOX);
        liste=gtk_container_get_children(wid);
        vboxright = (GtkWidget*) g_list_nth_data(liste, 1);
        gtk_widget_destroy(vboxright);

        button=gtk_button_new_with_label ("Sauvegarder");
        chooser=gtk_button_new_with_label ("Choisir image...");

        vboxright = gtk_vbox_new (TRUE, 0);

        ///Table
        table = gtk_table_new(12,2,TRUE);
        gtk_table_set_row_spacings(table, 6);
        gtk_table_set_col_spacings(table, 6);
        gtk_container_add(vboxright,table);

        gtk_container_add (wid,vboxright);
        //gtk_container_add(vboxright, gtk_image_new_from_pixbuf(contact->image));
        gtk_table_attach(table,gtk_image_new_from_pixbuf(contact->image) , 1, 2, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

        for(i=0; i<7; i++)
        {
            label[i] = gtk_label_new("NULL");
            gtk_table_attach(table, label[i], 0, 1, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
            text[i]= gtk_entry_new();
            gtk_entry_set_editable(text[i], "0");
            gtk_table_attach(table, text[i], 1, 2, i+3, i+4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

        }

        gtk_table_attach(table, chooser, 0, 1, 11, 12, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
        gtk_table_attach(table, button, 1, 2, 11, 12, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);

        gtk_label_set_text(label[0],"Nom:");
        gtk_label_set_text(label[1],"Prenom:");
        gtk_label_set_text(label[2],"Telephone:");
        gtk_label_set_text(label[3],"Adresse");
        gtk_label_set_text(label[4],"Email:");
        gtk_label_set_text(label[5],"Anniversaire:");
        gtk_label_set_text(label[6],"Note:");

        gtk_entry_set_text(text[0],contact->nom);
        gtk_entry_set_text(text[1],contact->prenom);
        gtk_entry_set_text(text[2],contact->tel);
        gtk_entry_set_text(text[3],contact->adresse);
        gtk_entry_set_text(text[4],contact->mail);
        gtk_entry_set_text(text[5],contact->birthday);
        gtk_entry_set_text(text[6],contact->note);


        gtk_widget_show_all (wid);

        g_signal_connect (chooser, "clicked", G_CALLBACK (choose_file), contact);
        g_signal_connect (button, "clicked", G_CALLBACK (sauvegarder_modif), liste_contacts);
    }

    //combo=combo_affichage(wid, liste_contacts);

    ///Problème avec le gtk_list_store_remove => Crash
    /*
    ///On recupere le modele qu'on a cree.
    model = gtk_combo_box_get_model (combo);
    printf("%d",&iter);
    /// On recupere le GtkTreeIter de l'element courant.
    if (gtk_combo_box_get_active_iter (combo, &iter))
    {
         //On supprime l'element courant.
       gtk_list_store_remove (model, &iter);
    }*/


    gtk_widget_show_all (combo);

}

///Fonction pour choisir l'image
void choose_file(GtkWidget *wid,t_contact *contact)
{
    GtkWidget *dialog,*table,*win,*image;
    GList *liste;

///Récupérer la window
    win=gtk_widget_get_toplevel (wid);
///Récupérer la table
    table=gtk_widget_get_ancestor (wid,GTK_TYPE_TABLE);
///Récupérer les enfants de la table
    liste=gtk_container_get_children(table);
///L'image est le 16e élément (en partant du bas de la table)
    image = (GtkWidget*) g_list_nth_data(liste, 16);


    dialog = gtk_file_chooser_dialog_new ("Choisir image...",
                                          win,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        ///Détruire l'ancienne image
        gtk_widget_destroy(image);
        ///Ajouter la nvlle image
        contact->img = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        contact->nb_ouverture++;
        printf("\n%s",contact->img);
        contact->image = gdk_pixbuf_new_from_file_at_size(contact->img, 100, 100, NULL);
        gtk_table_attach(table,gtk_image_new_from_pixbuf(contact->image) , 1, 2, 0, 3, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0,0);
        gtk_widget_show_all (table);
    }

    gtk_widget_destroy (dialog);
}

///Sauvegarder les modifs
void sauvegarder_modif(GtkWidget *wid,t_liste_contacts * liste_contact)
{
    char temp[100];
    GtkWidget* text[7],*combo,*hbox,*vbox,*win;
    GList *liste;int i;
    GList *liste2;
    t_contact *contact;

    hbox=gtk_widget_get_ancestor (wid,GTK_TYPE_HBOX);
    liste=gtk_container_get_children(hbox);
    vbox = (GtkWidget*) g_list_nth_data(liste, 0);
    liste=gtk_container_get_children(vbox);
    combo = (GtkWidget*) g_list_nth_data(liste, 3);

    contact=get_active_data(combo);

    wid=gtk_widget_get_ancestor (wid,GTK_TYPE_TABLE);
    liste=gtk_container_get_children(wid);


    for(i=0; i<7; i++)
    {
        text[i] = (GtkWidget*) g_list_nth_data(liste, ((14-2*i)+(contact->nb_ouverture)));
    }


    printf("%s\n",gtk_entry_get_text(text[0]));
    sprintf(temp, "%s", gtk_entry_get_text(text[0]));
    contact->nom=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->nom ,temp);

    printf("%s\n",gtk_entry_get_text(text[1]));
    sprintf(temp, "%s", gtk_entry_get_text(text[1]));
    contact->prenom=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->prenom ,temp);

    printf("%s\n",gtk_entry_get_text(text[2]));
    sprintf(temp, "%s", gtk_entry_get_text(text[2]));
    contact->tel=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->tel ,temp);

    printf("%s\n",gtk_entry_get_text(text[3]));
    sprintf(temp, "%s", gtk_entry_get_text(text[3]));
    contact->adresse=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->adresse ,temp);

    printf("%s\n",gtk_entry_get_text(text[4]));
    sprintf(temp, "%s", gtk_entry_get_text(text[4]));
    contact->mail=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->mail ,temp);

    printf("%s\n",gtk_entry_get_text(text[5]));
    sprintf(temp, "%s", gtk_entry_get_text(text[5]));
    contact->birthday=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->birthday ,temp);

    printf("%s\n",gtk_entry_get_text(text[6]));
    sprintf(temp, "%s", gtk_entry_get_text(text[6]));
    contact->note=(char*)malloc((strlen(temp)+1)*sizeof(char));//printf("ok\n");
    strcpy(contact->note ,temp);


    printf("\nContact modified");
    gtk_widget_destroy(combo);
    combo=combo_affichage(vbox, liste_contact);
    gtk_widget_show_all (combo);
    g_signal_connect (combo, "changed", G_CALLBACK (show_contact), hbox);
    show_contact(combo,hbox);
}
