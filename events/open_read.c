#include "../header.h"

///Lecture des contacts dans le fichier de sauvegarde
t_liste_contacts *read_contacts()
 {
    int i;
    char tmp[100];
    FILE *fichier;
    t_liste_contacts *liste_contacts;
    t_contact *contact,*temp;

    liste_contacts=(t_liste_contacts*)malloc(sizeof(t_liste_contacts));
    liste_contacts->ancre=NULL;
    liste_contacts->nb_contact=0;

    fichier=fopen("config/contacts.txt","r");
    if(fichier!=NULL)
    {

        ///Lecture du nbr de contacts
        fscanf(fichier,"%d\n",&liste_contacts->nb_contact);

        ///Lecture et alloc des contacts
        for(i=0;i<liste_contacts->nb_contact;i++)
        {
            contact=(t_contact*)malloc(sizeof(t_contact));

            if(liste_contacts->ancre==NULL)
                liste_contacts->ancre=contact;
            else
                temp->next=contact;

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->nom=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->nom,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->prenom=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->prenom,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->tel=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->tel,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->adresse=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->adresse,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->mail=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->mail,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->birthday=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->birthday,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->note=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->note,tmp);

            fgets(tmp,100,fichier);
            tmp[strlen(tmp)-1]='\0';
            contact->img=(char*)malloc((strlen(tmp)+1)*sizeof(char));
            strcpy(contact->img,tmp);

            contact->image = gdk_pixbuf_new_from_file_at_size(contact->img, 100, 100, NULL);
            if(contact->image == NULL)
            {
                contact->image = gdk_pixbuf_new_from_file_at_size("images/unknown.png", 100, 100, NULL);
                contact->img=(char*)malloc((strlen("images/unknown.png")+1)*sizeof(char));
                strcpy(contact->img,"images/unknown.png");
                contact->img[strlen(contact->img)]='\0';
            }

            contact->next=NULL;
            temp=contact;
            ///fgets blanc pour le saut de ligne
            fgets(tmp,100,fichier);
        }

        fclose(fichier);
    }
    return liste_contacts;
 }

///Sauvegarde des contacts dans le fichier de contact
void save_contacts(GtkWidget *wid,t_liste_contacts *liste_contacts)
{
    FILE *fichier;
    t_contact *contact;
    int i;

    contact=liste_contacts->ancre;
    fichier=fopen("config/contacts.txt","w");
    if(fichier!=NULL)
    {
        fprintf(fichier,"%d\n\n",liste_contacts->nb_contact);
        for(i=0;i<liste_contacts->nb_contact;i++)
        {
            fprintf(fichier,"%s\n",contact->nom);
            fprintf(fichier,"%s\n",contact->prenom);
            fprintf(fichier,"%s\n",contact->tel);
            fprintf(fichier,"%s\n",contact->adresse);
            fprintf(fichier,"%s\n",contact->mail);
            fprintf(fichier,"%s\n",contact->birthday);
            fprintf(fichier,"%s\n",contact->note);
            fprintf(fichier,"%s\n",contact->img);
            fprintf(fichier,"\n");
            contact=contact->next;
        }
    }
    fclose(fichier);
    printf("\nGood Bye");
    gtk_main_quit();
}
