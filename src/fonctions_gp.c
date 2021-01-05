#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header_gp.h"
#include "callbacks.h"
#include <gtk/gtk.h>


enum{
    EID,
    ENOM,
    EVARIETE,
    EQUANTITE,
    ESUPERFICIE,
    ESAISON,
	ESDATE_PLANTATION,
    EDATE_PLANTATION,
	COLUMNS
     };

enum table2{
    E_D_ANNEE,
    E_D_QUANTITE,
    E_D_RENDEMENT,
    E_D_RENDEMENT_EV,
    E_D_RENTABILITE,
    E_D_RENTABILITE_EV,
    E_D_SUPERFICIE
};

int i=1; // declaration du i , compteur de test


///////////////////////////////////////////////////////////////////////////////////////////////
void afficher_plante(GtkWidget *liste)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter	iter;
GtkListStore *store;

FILE *f;

int id_i;
int quantite_i;
int superficie_i;

char id[20];
char nom[20];
char variete[20];
char quantite[20];
char superficie[20];
char saison[20];
char sdate_plantation[20];


store=NULL;

	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{

	renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    gtk_tree_view_column_set_sizing(column,200);
    g_object_set(renderer, "font", "Monospace bold 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,0);
    column->resizable=TRUE;
    column->min_width=100;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nom générique", renderer, "text",ENOM, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

    g_object_set(renderer, "editable", TRUE,"font", "Monospace 20", NULL);
    //g_signal_connect(renderer, "edited", (GCallback) cell_edited_callback, NULL);


    gtk_tree_view_column_set_sort_column_id(column,1);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=300;


    renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("Variété", renderer, "text",EVARIETE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    g_object_set(renderer, "font", "Monospace 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,2);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=250;

    renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text",EQUANTITE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    g_object_set(renderer, "font", "Montserrat 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,3);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=100;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Superficie", renderer, "text",ESUPERFICIE, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    g_object_set(renderer, "font", "Monospace 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,4);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=100;


    renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("Saison de récolte", renderer, "text",ESAISON, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    g_object_set(renderer, "font", "Monospace 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,5);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=200;


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",ESDATE_PLANTATION, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
    g_object_set(renderer, "font", "Monospace 20", NULL);
    gtk_tree_view_column_set_sort_column_id(column,6);
    column->resizable=TRUE;
    column->reorderable=TRUE;
    column->min_width=200;


	store=gtk_list_store_new (7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
	f=fopen("plante.txt", "r");
	if(f==NULL)
	{
		return;
	}
	else
	{
	f = fopen("plante.txt","a+");
		while(fscanf(f,"%d %s %s %d %s %d %s\n",&id_i,nom,variete,&quantite_i,saison,&superficie_i,sdate_plantation)!=EOF)
		{
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter,EID,id_i,ENOM,nom,EVARIETE,variete,EQUANTITE,quantite_i,ESUPERFICIE,superficie_i,ESAISON,saison,ESDATE_PLANTATION,sdate_plantation, -1);
		}
	fclose(f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
	}
        gtk_tree_view_set_level_indentation(GTK_TREE_VIEW (liste),5);
}
}

///////////////////////////////////////////////////////////////////////////////////////////////
void ajouter_plante(plante p) {

    // Pointeur sur fichier
	FILE *f;


	f=fopen("plante.txt","a+");
	if(f!=NULL)
	{
	fprintf(f,"%s %s %s %s %s %s %d-%d-%d \n",p.s_id,p.nom,p.variete,p.s_quantite,p.saison,p.s_superficie,p.date_plantation.jour,p.date_plantation.mois,p.date_plantation.annee);
	fclose(f);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void supprimer_plante(char p_id_supp[10]) {

    // Pointeur sur fichier
    FILE *f=NULL;
    FILE *tmp=NULL;
    // Structure plante
    plante p;


    // Ouverture de fichier en mode "Lecture" grâce au mode d'accés "r"
    f=fopen("plante.txt","r");

    // Ouverture d'un fichier texte en mode "Ecriture" grâce au mode d'accés "w"
    tmp=fopen("tmp.txt","w");


    // Vérification que le fichier a bien été ouvert
    if (f!=NULL) {

        /* Traitement : Copie de tous les enregistrements en remplaçant l'enregistrement à supprimer */
        while(fscanf(f,"%s %s %s %s %s %s %s \n",p.s_id,p.nom,p.variete,p.s_quantite,p.saison,p.s_superficie,p.sdate_plantation)!=EOF){
            if ( (strcmp(p.s_id,p_id_supp)!=0) ) {
                fprintf(tmp,"%s %s %s %s %s %s %s \n",p.s_id,p.nom,p.variete,p.s_quantite,p.saison,p.s_superficie,p.sdate_plantation);}
        }

        fclose(f);
        fclose(tmp);
        remove("plante.txt");
        rename("tmp.txt","plante.txt");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void modifier_plante(plante p_nouv,plante p_modif) {

    // Pointeur sur fichier
    FILE *f=NULL;
    FILE *tmp=NULL;
    // Structure plante
    plante p;


    // Ouverture de fichier en mode "Lecture" grâce au mode d'accés "r"
    f=fopen("plante.txt","r");

    // Ouverture d'un fichier texte en mode "Ecriture" grâce au mode d'accés "w"
    tmp=fopen("tmp.txt","w");

    // Vérification que le fichier a bien été ouvert
    if (f!=NULL) {

        /* Traitement : Copie de tous les enregistrements en remplaçant l'enregistrement à modifier */
        while(fscanf(f,"%s %s %s %s %s %s %s \n",p.s_id,p.nom,p.variete,p.s_quantite,p.saison,p.s_superficie,p.sdate_plantation)!=EOF){
            if ( (strcmp(p.s_id,p_modif.s_id)==0) ) {
                fprintf(tmp,"%s %s %s %s %s %s %d-%d-%d \n",p_nouv.s_id,p_nouv.nom,p_nouv.variete,p_nouv.s_quantite,p_nouv.saison,p_nouv.s_superficie,p_nouv.date_plantation.jour,p_nouv.date_plantation.mois,p_nouv.date_plantation.annee);}
            else {
                fprintf(tmp,"%s %s %s %s %s %s %s \n",p.s_id,p.nom,p.variete,p.s_quantite,p.saison,p.s_superficie,p.sdate_plantation);}
            }
        }

        fclose(f);
        fclose(tmp);
        remove("plante.txt");
        rename("tmp.txt","plante.txt");
}

///////////////////////////////////////////////////////////////////////////////////////////////

void rechercher_plante(plante p_rech,int x) {

	// Pointeur sur fichier
        FILE *f=NULL;
        FILE *f_recherche=NULL;
	// Structure plante
		plante p;


    // Ouverture de fichier en mode "Lecture" grâce au mode d'accés "r"
        f=fopen("plante.txt","r");

    // Ouverture d'un fichier texte en mode "Ecriture" grâce au mode d'accés "w"
        f_recherche=fopen("f_recherche.txt","w");

    // Vérification que le fichier a bien été ouvert
        if (f!=NULL) {
            // Traitement
            while (fscanf(f, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite, p.s_superficie,p.saison, p.sdate_plantation) != EOF) {

				sscanf( p.sdate_plantation, "%d-%d-%d", &p.date_plantation.jour, &p.date_plantation.mois, &p.date_plantation.annee );

                // Si l'utulisateur a choisi le mode "Date exacte"
                if(x==1){
					/* L'utulisateur a spécifié :
                    Réference : "Input"
                    Nom : "Tous"
                    Date : "jj-mm-aaaa" */
					if ( ((strcmp(p.s_id, p_rech.s_id)) == 0) && ((strcmp("Tous", p_rech.nom)) == 0) && (p.date_plantation.jour==p_rech.date_plantation.jour) && (p.date_plantation.mois==p_rech.date_plantation.mois) && (p.date_plantation.annee==p_rech.date_plantation.annee) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
					/* L'utulisateur a spécifié :
					Réference : ""
					Nom : "Input"
					Date : "jj-mm-aaaa" */
					else if ( ((strcmp("", p_rech.s_id)) == 0) && ((strcmp(p.nom, p_rech.nom)) == 0)  && (p.date_plantation.jour==p_rech.date_plantation.jour) && (p.date_plantation.mois==p_rech.date_plantation.mois) && (p.date_plantation.annee==p_rech.date_plantation.annee) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
					/* L'utulisateur a spécifié :
					Réference : "Input"
					Nom : "Input"
					Date : "jj-mm-aaaa" */
					else if ( ((strcmp(p.s_id, p_rech.s_id)) == 0) && ((strcmp(p.nom, p_rech.nom)) == 0)  && (p.date_plantation.jour==p_rech.date_plantation.jour) && (p.date_plantation.mois==p_rech.date_plantation.mois) && (p.date_plantation.annee==p_rech.date_plantation.annee) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
					/* L'utulisateur a spécifié :
					Réference : ""
					Nom : "Tous"
					Date : "jj-mm-aaaa" */
					else if ( ((strcmp("", p_rech.s_id)) == 0) && ((strcmp("Tous", p_rech.nom)) == 0)  && (p.date_plantation.jour==p_rech.date_plantation.jour) && (p.date_plantation.mois==p_rech.date_plantation.mois) && (p.date_plantation.annee==p_rech.date_plantation.annee) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
                }

				// Si l'utulisateur a choisi le mode "À partir de"
				else if(x==0){
					/* L'utulisateur a spécifié :
                    Réference : "Input"
                    Nom : "Tous"
                    Date : "jj-mm-aaaa" */
					if ( ((strcmp(p.s_id, p_rech.s_id)) == 0) && ((strcmp("Tous", p_rech.nom)) == 0) && (date_comparaison(p_rech.date_plantation,p.date_plantation)==1)  ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
						/* L'utulisateur a spécifié :
                        Réference : ""
                        Nom : "Input"
                        Date : "jj-mm-aaaa" */
					else if ( ((strcmp("", p_rech.s_id)) == 0) && ((strcmp(p.nom, p_rech.nom)) == 0)  && (date_comparaison(p_rech.date_plantation,p.date_plantation)==1) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
						/* L'utulisateur a spécifié :
                        Réference : "Input"
                        Nom : "Input"
                        Date : "jj-mm-aaaa" */
					else if ( ((strcmp(p.s_id, p_rech.s_id)) == 0) && ((strcmp(p.nom, p_rech.nom)) == 0)  && (date_comparaison(p_rech.date_plantation,p.date_plantation)==1) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
						/* L'utulisateur a spécifié :
                        Réference : ""
                        Nom : "Tous"
                        Date : "jj-mm-aaaa" */
					else if ( ((strcmp("", p_rech.s_id)) == 0) && ((strcmp("Tous", p_rech.nom)) == 0)  && (date_comparaison(p_rech.date_plantation,p.date_plantation)==1) ) {
						fprintf(f_recherche, "%s %s %s %s %s %s %s \n", p.s_id, p.nom, p.variete, p.s_quantite,
								p.s_superficie, p.saison, p.sdate_plantation);
					}
				}

			}
        }
          fclose(f);
          fclose(f_recherche);
	}

void afficher_recherche_avancee(GtkWidget *liste){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter	iter;
GtkListStore *store;

FILE *f_recherche=NULL;

int id_i;
int quantite_i;
int superficie_i;

char id[20];
char nom[20];
char variete[20];
char quantite[20];
char superficie[20];
char saison[20];
char sdate_plantation[20];



store=NULL;

    store=gtk_tree_view_get_model(liste);
    if (store==NULL)
    {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Identifiant", renderer, "text",EID, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        gtk_tree_view_column_set_sizing(column,200);
        g_object_set(renderer, "font", "Monospace bold 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,0);
        column->resizable=TRUE;
        column->min_width=100;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom générique", renderer, "text",ENOM, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,1);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=300;


        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Variété", renderer, "text",EVARIETE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,2);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=250;

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text",EQUANTITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Montserrat 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,3);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=100;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Superficie", renderer, "text",ESUPERFICIE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,4);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=100;


        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Saison de récolte", renderer, "text",ESAISON, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,5);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=200;


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de plantation", renderer, "text",ESDATE_PLANTATION, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,6);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=150;

        store=gtk_list_store_new (7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
        f_recherche=fopen("plante.txt", "r");
        if(f_recherche==NULL)
        {
            return;
        }
        else
        {
            f_recherche = fopen("f_recherche.txt","a+");
            while(fscanf(f_recherche,"%d %s %s %d %s %d %s\n",&id_i,nom,variete,&quantite_i,saison,&superficie_i,sdate_plantation)!=EOF)
            {
                gtk_list_store_append (store, &iter);
                gtk_list_store_set (store, &iter,EID,id_i,ENOM,nom,EVARIETE,variete,EQUANTITE,quantite_i,ESUPERFICIE,superficie_i,ESAISON,saison,ESDATE_PLANTATION,sdate_plantation, -1);
            }
            fclose(f_recherche);
            gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
            g_object_unref (store);
        }
        gtk_tree_view_set_level_indentation(GTK_TREE_VIEW (liste),5);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void msg_validation(char id[], char validation[], char methode[])
{


    if(strcmp(methode,"ajout")==0) {
        strcpy(validation,"<span font_weight=\"bold\" font=\"25\">L'ajout du plante \nde <span color=\"green\">réference ");
        strcat(validation,id);
        strcat(validation,"</span> est terminée \navec succés !</span>");
	}
	else if(strcmp(methode,"modification")==0) {
        strcpy(validation,"<span font_weight=\"bold\" font=\"25\">La modificatioin du plante \nde <span color=\"#0077b6\">réference ");
        strcat(validation,id);
        strcat(validation,"</span> est terminée \navec succés !</span>");
	}
    else if(strcmp(methode,"suppression")==0) {
        strcpy(validation,"<span font_weight=\"bold\" font=\"25\">La suppression du plante \nde <span color=\"#660708\">réference ");
        strcat(validation,id);
        strcat(validation,"</span> est terminée \navec succés !</span>");
    }
    else if(strcmp(methode,"ajout_valeur")==0) {
        strcpy(validation,"<span font_weight=\"bold\" font=\"25\">L'ajout des données au plante \nde <span color=\"#660708\">réference ");
        strcat(validation,id);
        strcat(validation,"</span> est terminée \navec succés !</span>");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

int date_comparaison (date date_input,date date_du_fichier){

	// date_input : saisie par l'utilisateur
	// date_du_fichier : lis du fichier

	int a_afficher=0;

	if (date_du_fichier.annee>date_input.annee) {
		a_afficher=1;}
	else if (date_du_fichier.annee==date_input.annee) {
		if (date_du_fichier.mois>date_input.mois) {
			a_afficher=1;}
		else if (date_du_fichier.mois==date_input.mois){
			if (date_du_fichier.jour>=date_input.jour) {
				a_afficher=1;}
		}
	}
	return a_afficher;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void concatenation(char output[]) {

    char test[100];

    strcpy(test,"<span color=\"#660708\" font_weight=\"bold\"font=\"20\">");
    strcat(test,output);
    strcat(test,"</span>");
    strcpy(output,test);
}

///////////////////////////////////////////////////////////////////////////////////////////////

verification input_verification(plante p_test,verification verif) {

    // Pointeur sur fichier
    FILE *f = NULL;

    // Ouverture de fichier en mode "Lecture" grâce au mode d'accés "r"
    f = fopen("plante.txt", "r");

    plante p_lis;


    // Vérification que le fichier a bien été ouvert
    if (f != NULL) {

        /* Traitement : Copie de tous les enregistrements en remplaçant l'enregistrement à modifier */
        while (fscanf(f, "%s %s %s %s %s %s %s \n", p_lis.s_id, p_lis.nom, p_lis.variete, p_lis.s_quantite,
                      p_lis.saison, p_lis.s_superficie, p_lis.sdate_plantation) != EOF) {
            // Test id
            if ( ( ( strcmp(p_test.s_id,p_lis.s_id ) ==0 ) && ( strcmp (p_test.date_plantation.s_jour,"-1")!=0) )  || (strcmp(p_test.s_id,"")==0) || (is_integer(p_test.s_id)==0) ) {
                verif.test_id=1;
                verif.test_global=1;
                if( (strcmp(p_test.s_id,p_lis.s_id)==0) && ( strcmp (p_test.date_plantation.s_jour,"-1")!=0) ) {
                    verif.test_id_cas=1;}
                else if(strcmp(p_test.s_id,"")==0) {
                    verif.test_id_cas=2;}
                else if(is_integer(p_test.s_id)==0) {
                    verif.test_id_cas=3;}
            }

            // Test nom
            if ((strcmp(p_test.nom,"")==0)) {
                verif.test_nom=1;
                verif.test_global=1;}

            // Test variete
            if ((strcmp(p_test.variete,"")==0)) {
                verif.test_variete=1;
                verif.test_global=1;}

            // Test quantité
            if ((strcmp(p_test.s_quantite,"")==0)||(is_integer(p_test.s_quantite)==0)) {
                verif.test_quantite=1;
                verif.test_global=1;
                if(strcmp(p_test.s_quantite,"")==0) {
                    verif.test_quantite_cas=1;}
                else if(is_integer(p_test.s_quantite)==0) {
                    verif.test_quantite_cas=2;}
            }

            // Test saison
            if (strcmp(p_test.saison,"")==0) {
                verif.test_saison=1;
                verif.test_global=1;
                verif.test_saison_cas=1;
            }
            else if ( (strcmp(p_test.saison,"Été")!=0) && (strcmp(p_test.saison,"été")!=0) && (strcmp(p_test.saison,"Hiver")!=0) && (strcmp(p_test.saison,"hiver")!=0) &&
                 (strcmp(p_test.saison,"Automne")!=0) && (strcmp(p_test.saison,"automne")!=0) && (strcmp(p_test.saison,"Printemps")!=0) && (strcmp(p_test.saison,"printemps")!=0) ) {
                verif.test_saison=1;
                verif.test_global=1;
                verif.test_saison_cas=2;
            }

            // Test superficie
            if ((strcmp(p_test.s_superficie,"")==0)||(is_integer(p_test.s_superficie)==0)) {
                verif.test_superficie=1;
                verif.test_global=1;
                if(strcmp(p_test.s_superficie,"")==0) {
                    verif.test_superficie_cas=1;}
                else if(is_integer(p_test.s_superficie)==0) {
                    verif.test_superficie_cas=2;}
            }
        }
    }
    fclose(f);
    return verif;
}
int is_integer (char test[]) {
    int a;
    int length_av;
    int length_ap;
    char controle[50];

    strcpy(controle,test);
    length_av=strlen(controle);

    a=atoi(controle);

    sprintf(controle,"%d",a);

    length_ap=strlen(controle);


    if(length_av==length_ap)
    { return 1; }
    else
    { return 0; }
}


//////////////////////////////////  /Partie 2  ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void afficher_plante2(GtkWidget *liste,plante_detail v_ajout)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter	iter;
    GtkListStore *store;

    FILE *f;


//    G_TYPE_FLOAT
    int plante_id;
    int annee;
    int mois;
    int jour;
    int quantite;

    float rendement;
    char s_rendement[20];
    float evolution_rendement;
    char s_evolution_rendement[20];
    float prev_rendement=0;


    int rentabilite;
    int evolution_rentabilite;
    char s_evolution_rentabilite[20];
    float prev_rentabilite=0;


    store=NULL;

    store=gtk_tree_view_get_model(liste);
    if (store==NULL)
    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Annee de récolte", renderer, "text",E_D_ANNEE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        gtk_tree_view_column_set_sizing(column,200);
        g_object_set(renderer, "font", "Monospace bold 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,0);
        column->resizable=TRUE;
        column->min_width=150;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Quantité récoltée ( En tonne )", renderer, "text",E_D_QUANTITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "editable", TRUE,"font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,1);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=210;

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Rendement agricole ( Qt/Sup )", renderer, "text",E_D_RENDEMENT, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,2);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=230;

        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Evolution de rendement ( N%N-1 )", renderer, "text",E_D_RENDEMENT_EV, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Montserrat 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,3);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=250;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Rentabilité ( En DT )", renderer, "text",E_D_RENTABILITE, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,4);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=170;


        renderer = gtk_cell_renderer_text_new ();
        column = gtk_tree_view_column_new_with_attributes("Evolution du rentabilité ( N%N-1 )", renderer, "text",E_D_RENTABILITE_EV, NULL);
        gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        g_object_set(renderer, "font", "Monospace 20", NULL);
        gtk_tree_view_column_set_sort_column_id(column,5);
        column->resizable=TRUE;
        column->reorderable=TRUE;
        column->min_width=250;



        store=gtk_list_store_new (6, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
        f=fopen("plante_historique.txt", "r");
        if(f==NULL)
        {
            return;
        }
        else
        {
            f = fopen("plante_historique.txt","a+");
            while(fscanf(f,"%d %d %dDT %d-%d-%d\n",&plante_id,&quantite,&rentabilite,&jour,&mois,&annee)!=EOF)
            {
                if(v_ajout.plante_id==plante_id) {
                    // Le rendement est la quantité recolté sur la superficie
                    rendement=(float)quantite*100/v_ajout.superficie;
                    sprintf(s_rendement, "%.2f", rendement);
                    strcat(s_rendement, "%");


                    // L'evolution du rendement
                    evolution_rendement=(float)prev_rendement*100/rendement;
                    sprintf(s_evolution_rendement, "%.2f", evolution_rendement);
                    strcat(s_evolution_rendement, "%");

                    // L'evolution du rentabilite
                    evolution_rentabilite=(float)(100*(rentabilite-prev_rentabilite/rentabilite));
                    sprintf(s_evolution_rentabilite, "%.2f", evolution_rentabilite);
                    strcat(s_evolution_rentabilite, "%");

                    prev_rendement=rendement;
                    prev_rentabilite=(float)rentabilite;

                    gtk_list_store_append (store, &iter);
                    gtk_list_store_set (store, &iter,E_D_ANNEE,annee,E_D_QUANTITE,quantite,E_D_RENDEMENT,s_rendement,E_D_RENDEMENT_EV,s_evolution_rendement,E_D_RENTABILITE,rentabilite,ESAISON,s_evolution_rentabilite, -1);

                }
                }
            fclose(f);
            gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
            g_object_unref (store);
        }
        gtk_tree_view_set_level_indentation(GTK_TREE_VIEW (liste),5);
    }
}


void ajouter_plante_detail(plante_detail p_v_ajout) {

    // Pointeur sur fichier
    FILE *f;


    f=fopen("plante_historique.txt","a+");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %sDT %d-%d-%d\n",p_v_ajout.s_plante_id,p_v_ajout.s_quantite,p_v_ajout.s_rentabilite,p_v_ajout.jour,p_v_ajout.mois,p_v_ajout.annee);
        fclose(f);
    }
}

plante rechercher_p2_plante(char p_rech_s_id[200]) {

    // Pointeur sur fichier
    FILE *f=NULL;
    FILE *f_recherche=NULL;
    // Structure plante
    plante p;
    int trouve;


    // Ouverture de fichier en mode "Lecture" grâce au mode d'accés "r"
    f=fopen("plante.txt","r");


    // Vérification que le fichier a bien été ouvert
    if (f!=NULL) {
        // Traitement
        while (fscanf(f, "%s %s %s %s %s %s %s \n",p.s_id,p.nom,p.variete,p.s_quantite,p.s_superficie,p.saison,p.sdate_plantation) != EOF) {

            if ( (strcmp(p.s_id, p_rech_s_id)) == 0) {
                trouve=1;
                return p;
            }
            else{
                trouve=0;
            }
        }
        if (trouve==0) {
            strcpy(p.nom,"introuvalbe");
            strcpy(p.variete,"introuvalbe");
            strcpy(p.sdate_plantation,"introuvalbe");
            return p;}

    }
    fclose(f);
}

