#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#define GLADE_HOOKUP_OBJECT(component,widget,name) \
      g_object_set_data_full (G_OBJECT (component), name, \
        gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)
#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "header_gp.h"

// Une Variable globale pour le stockage de la plante à modifier/supprimer et la passer en paramétre à la fonction modifier/supprimer
plante p_modif;
plante p_supp;

plante_detail v_ajout;

// Une Variable globale gtkwidget
GtkWidget *test_widget_notification_gp;
GtkWidget *test_widget_p2_notification_gp;
GtkWidget *for_changing_id;



//Une variable globale pour les boutton radio
int x=0; // Initialiser à la mode "À partir de"


void
on_treeview1_gp_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gint id;
gchar* nom;
gchar* variete;
gint quantite;
gint superficie;
gchar* saison;
gchar* sdate_plantation;

// to take the widget parent for treeview
GtkWidget *window_main_gp;
GtkWidget *objet_main_gp;
GtkWidget *window_suppression_gp;

char msg[100];

GtkWidget *input1,*input2,*input3,*input4,*input5,*input6,*input7,*input8,*input9;
char JOUR[5],MOIS[5],ANNEE[5];

GtkWidget *output;
plante p;


GtkTreeModel *model = gtk_tree_view_get_model(treeview);
if(gtk_tree_model_get_iter(model,&iter,path))
	{
	// Obtention des varietes de la ligne selectionnée
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&variete,3,&quantite,4,&superficie,5,&saison,6,&sdate_plantation,-1);
	
	// Copie des varietes obtenues dans la structure plante p pour la passer à la fonction de suppression
    p.id=id;
    strcpy(p.nom,nom);
    strcpy(p.variete,variete);
    p.quantite=quantite;
    p.superficie=superficie;
    strcpy(p.saison,saison);
	strcpy(p.sdate_plantation,sdate_plantation);

	// Appel à la fonction supprimer => ca sera dans le widget supprimer
	// supprimer_plante(p);

    objet_main_gp=&treeview->parent.widget;

    window_main_gp=lookup_widget(objet_main_gp,"window_main_gp");
    gtk_widget_destroy(window_main_gp);

    window_suppression_gp = create_window_suppression_gp ();
    gtk_widget_show(window_suppression_gp);

    input1=lookup_widget(window_suppression_gp,"label_id_supp_gp");
    input2=lookup_widget(window_suppression_gp,"label_nom_supp_gp");
    input3=lookup_widget(window_suppression_gp,"label_variete_supp_gp");
    input4=lookup_widget(window_suppression_gp,"label_quantite_supp_gp");
    input5=lookup_widget(window_suppression_gp,"label_saison_supp_gp");
    input6=lookup_widget(window_suppression_gp,"label_superficie_supp_gp");
    input7=lookup_widget(window_suppression_gp,"label_jour_supp_gp");
    input8=lookup_widget(window_suppression_gp,"label_mois_supp_gp");
    input9=lookup_widget(window_suppression_gp,"label_annee_supp_gp");

    sscanf( p.sdate_plantation, "%d-%d-%d", &p.date_plantation.jour, &p.date_plantation.mois, &p.date_plantation.annee );


    sprintf(p.s_id,"%d",p.id);
    // Passer le ID du plante à supprimer à la variable globale p_supp
    strcpy(p_supp.s_id,p.s_id);

    sprintf(p.s_quantite,"%d",p.quantite);
    sprintf(p.s_superficie,"%d",p.superficie);
    sprintf(p.date_plantation.s_jour,"%d",p.date_plantation.jour);
    sprintf(p.date_plantation.s_mois,"%d",p.date_plantation.mois);
    sprintf(p.date_plantation.s_annee,"%d",p.date_plantation.annee);


    concatenation(p.s_id);
    concatenation(p.nom);
    concatenation(p.variete);
    concatenation(p.s_quantite);
    concatenation(p.saison);
    concatenation(p.s_superficie);
    concatenation(p.date_plantation.s_jour);
    concatenation(p.date_plantation.s_mois);
    concatenation(p.date_plantation.s_annee);


    gtk_label_set_markup(GTK_LABEL(input1),_(p.s_id));
    gtk_label_set_markup(GTK_LABEL(input2),_(p.nom));
    gtk_label_set_markup(GTK_LABEL(input3),_(p.variete));
    gtk_label_set_markup(GTK_LABEL(input4),_(p.s_quantite));
    gtk_label_set_markup(GTK_LABEL(input5),_(p.saison));
    gtk_label_set_markup(GTK_LABEL(input6),_(p.s_superficie));
    gtk_label_set_markup(GTK_LABEL(input7),_(p.date_plantation.s_jour));
    gtk_label_set_markup(GTK_LABEL(input8),_(p.date_plantation.s_mois));
    gtk_label_set_markup(GTK_LABEL(input9),_(p.date_plantation.s_annee));


    }
}

// Boutton modifier de l'interface window_main_gp avec la ligne de TreeView selectionné qui permet de transférer les données de TreeView pour le ouvrir dans window_modification_gp
void
on_button_modifier_gp_clicked             (GtkWidget       *objet,
                                            gpointer         user_data)
{
GtkWidget *window_main_gp;
GtkWidget *window_modification_gp;

GtkWidget *treeview1_gp;
GtkTreeSelection *selection ;
GtkTreeModel *model;
GtkTreeIter iter;

gint id;
gchar* nom;
gchar* variete;
gint quantite;
gint superficie;
gchar* saison;
gchar* sdate_plantation;

plante p;

gint index_nom=-1;
gint index_variete=-1;

GtkWidget *input1,*combobox1,*combobox2,*input4,*input5,*input6,*JOUR,*MOIS,*ANNEE;
GdkColor color3;
gdk_color_parse ("#0077b6", &color3);
PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 25" );


	window_main_gp=lookup_widget(objet,"window_main_gp");

    treeview1_gp=lookup_widget(window_main_gp,"treeview1_gp");
    selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1_gp));

    if(gtk_tree_selection_get_selected(selection,&model,&iter)) {
        // Obtention des varietes de la ligne selectionnée
        gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&variete,3,&quantite,4,&superficie,5,&saison,6,&sdate_plantation,-1);

        p_modif.id=id;
        strcpy(p_modif.nom,nom);
        strcpy(p_modif.variete,variete);
        p_modif.quantite=quantite;
        p_modif.superficie=superficie;
        strcpy(p_modif.saison,saison);
        strcpy(p_modif.sdate_plantation,sdate_plantation);
    }

    gtk_widget_destroy(window_main_gp);

    window_modification_gp=create_window_modification_gp();
	gtk_widget_show(window_modification_gp);

    input1=lookup_widget(window_modification_gp,"entry_id_gp");
    combobox1=lookup_widget(window_modification_gp,"comboboxentry_nom_gp");
    combobox2=lookup_widget(window_modification_gp,"comboboxentry_variete_gp");
    input4=lookup_widget(window_modification_gp,"entry_quantite_gp");
    input5=lookup_widget(window_modification_gp,"entry_superficie_gp");
    input6=lookup_widget(window_modification_gp,"entry_saison_gp");
    JOUR=lookup_widget(window_modification_gp,"spinbutton_jour_gp");
    MOIS=lookup_widget(window_modification_gp,"spinbutton_mois_gp");
    ANNEE=lookup_widget(window_modification_gp,"spinbutton_annee_gp");

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(combobox1,fontDesc);
    gtk_widget_modify_font(combobox2,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);
    gtk_widget_modify_font(input5,fontDesc);
    gtk_widget_modify_font(input6,fontDesc);
    gtk_widget_modify_font(JOUR,fontDesc);
    gtk_widget_modify_font(MOIS,fontDesc);
    gtk_widget_modify_font(ANNEE,fontDesc);

    gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(JOUR, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(MOIS, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_SELECTED, &color3);

    sprintf(p_modif.s_id,"%d",p_modif.id);
    gtk_entry_set_text(GTK_ENTRY(input1),p_modif.s_id);

    if (strcmp(p_modif.nom,"Légumes_graines")==0){
        index_nom=0;
        if(strcmp(p_modif.variete,"Aubergine")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Concombre")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Courge")==0)
            index_variete=2;
        else if(strcmp(p_modif.variete,"Fève")==0)
            index_variete=3;
        else if(strcmp(p_modif.variete,"Piment")==0)
            index_variete=4;
        else if(strcmp(p_modif.variete,"Pois")==0)
            index_variete=5;
        else if(strcmp(p_modif.variete,"Poivron")==0)
            index_variete=6;
        else if(strcmp(p_modif.variete,"Tomate")==0)
            index_variete=7;
        else if(strcmp(p_modif.variete,"Céréales")==0)
            index_variete=8;
    }
    else if (strcmp(p_modif.nom,"Légumes_à_bulbe")==0){
        index_nom=1;
        if(strcmp(p_modif.variete,"Poireau")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Oignon")==0)
            index_variete=1;
    }
    else if (strcmp(p_modif.nom,"Légumes_tubercules")==0){
        index_nom=2;
        index_variete=0;
    }
    else if (strcmp(p_modif.nom,"Légumes_feuilles")==0){
        index_nom=3;
        if(strcmp(p_modif.variete,"Épinards")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Laitue")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Chou")==0)
            index_variete=2;
        else if(strcmp(p_modif.variete,"Betteraves")==0)
            index_variete=3;
    }
    else if (strcmp(p_modif.nom,"Fruits_à_noyau")==0){
        index_nom=4;
        if(strcmp(p_modif.variete,"Cerise")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Datte")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Olive")==0)
            index_variete=2;
        else if(strcmp(p_modif.variete,"Pêche")==0)
            index_variete=3;
        else if(strcmp(p_modif.variete,"Abricot")==0)
            index_variete=4;
    }
    else if (strcmp(p_modif.nom,"Fruits_à_pépin")==0){
        index_nom=5;
        if(strcmp(p_modif.variete,"Poire")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Pomme")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Coings")==0)
            index_variete=2;
    }
    else if (strcmp(p_modif.nom,"Fruits_à_coque")==0){
        index_nom=6;
        if(strcmp(p_modif.variete,"Pistache")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Noix_de_cajou")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Amande")==0)
            index_variete=2;
        else if(strcmp(p_modif.variete,"Noisette")==0)
            index_variete=3;
    }
    else if (strcmp(p_modif.nom,"Agrumes")==0){
        index_nom=7;
        if(strcmp(p_modif.variete,"Orange")==0)
            index_variete=0;
        else if(strcmp(p_modif.variete,"Citron")==0)
            index_variete=1;
        else if(strcmp(p_modif.variete,"Lime")==0)
            index_variete=2;
        else if(strcmp(p_modif.variete,"Mandarine")==0)
            index_variete=3;
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox1),index_nom);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox2),index_variete);

    sprintf(p_modif.s_quantite,"%d",p_modif.quantite);
    gtk_entry_set_text(GTK_ENTRY(input4),p_modif.s_quantite);

    sprintf(p_modif.s_superficie,"%d",p_modif.superficie);
    gtk_entry_set_text(GTK_ENTRY(input5),p_modif.s_superficie);

    gtk_entry_set_text(GTK_ENTRY(input6),p_modif.saison);

    // Convertir la chaine de caratére sdate_plantation en entrier (jour/mois/annee)
    sscanf( sdate_plantation, "%d-%d-%d", &p.date_plantation.jour, &p.date_plantation.mois, &p.date_plantation.annee );
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(JOUR),p.date_plantation.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(MOIS),p.date_plantation.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(ANNEE),p.date_plantation.annee);


}

// Boutton ajouter de l'interface window_main_gp qui permet de fermer window_main_gp et d'ouvrir window_ajout_gp
void
on_button_ajouter_gp_clicked              (GtkWidget       *objet,
                                            gpointer         user_data)
{

GtkWidget *window_main_gp;
GtkWidget *window_ajout_gp;
GtkWidget *input1,*combobox1,*combobox2,*input4,*input5,*input6,*JOUR,*MOIS,*ANNEE;
GdkColor color3;
gdk_color_parse ("#0077b6", &color3);
PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 25" );


	window_main_gp=lookup_widget(objet,"window_main_gp");
	gtk_widget_destroy(window_main_gp);
	window_ajout_gp=create_window_ajout_gp();
	gtk_widget_show(window_ajout_gp);

    input1=lookup_widget(window_ajout_gp,"entry_id_gp");
    combobox1=lookup_widget(window_ajout_gp,"comboboxentry_nom_gp");
    combobox2=lookup_widget(window_ajout_gp,"comboboxentry_variete_gp");
    input4=lookup_widget(window_ajout_gp,"entry_quantite_gp");
    input5=lookup_widget(window_ajout_gp,"entry_superficie_gp");
    input6=lookup_widget(window_ajout_gp,"entry_saison_gp");
    JOUR=lookup_widget(window_ajout_gp,"spinbutton_jour_gp");
    MOIS=lookup_widget(window_ajout_gp,"spinbutton_mois_gp");
    ANNEE=lookup_widget(window_ajout_gp,"spinbutton_annee_gp");

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(combobox1,fontDesc);
    gtk_widget_modify_font(combobox2,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);
    gtk_widget_modify_font(input5,fontDesc);
    gtk_widget_modify_font(input6,fontDesc);
    gtk_widget_modify_font(JOUR,fontDesc);
    gtk_widget_modify_font(MOIS,fontDesc);
    gtk_widget_modify_font(ANNEE,fontDesc);

    gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(JOUR, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(MOIS, GTK_STATE_SELECTED, &color3);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_SELECTED, &color3);
}


// Boutton rechercher de l'interface window_main_gp qui permet de faire une recherche avancé et de reload la TreeView
void
on_button_rechercher_gp_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *window_main_gp;
GtkWidget *treeview1_gp;
GtkWidget *input1;
GtkWidget *combobox1;
GtkWidget *JOUR;
GtkWidget *MOIS;
GtkWidget *ANNEE;

gint index_nom=-1;

PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 20" );


plante p_rech;

    input1=lookup_widget(objet,"entry_id_gp");
    combobox1=lookup_widget(objet,"combobox_filtre_nom_gp");
    JOUR=lookup_widget(objet,"spinbutton_jour_gp");
    MOIS=lookup_widget(objet,"spinbutton_mois_gp");
    ANNEE=lookup_widget(objet,"spinbutton_annee_gp");


    strcpy(p_rech.s_id,gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(p_rech.nom,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));
    p_rech.date_plantation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(JOUR));
    p_rech.date_plantation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(MOIS));
    p_rech.date_plantation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ANNEE));

    // Passer en argument les informations de recherche avancé et l'état de radio button (0: a partir / 1: date exacte)
	rechercher_plante(p_rech,x);

	// Reinitialiser à la mode "À partir de"
    x=0;

    // Update le treeview
    window_main_gp=lookup_widget(objet,"window_main_gp");
	gtk_widget_destroy(window_main_gp);
	window_main_gp=create_window_main_gp();
	gtk_widget_show(window_main_gp);
	treeview1_gp=lookup_widget(window_main_gp,"treeview1_gp");
	afficher_recherche_avancee(treeview1_gp);

    input1=lookup_widget(window_main_gp,"entry_id_gp");
    combobox1=lookup_widget(window_main_gp,"combobox_filtre_nom_gp");
    JOUR=lookup_widget(window_main_gp,"spinbutton_jour_gp");
    MOIS=lookup_widget(window_main_gp,"spinbutton_mois_gp");
    ANNEE=lookup_widget(window_main_gp,"spinbutton_annee_gp");

    gtk_entry_set_text(GTK_ENTRY(input1),p_rech.s_id);
    if (strcmp(p_rech.nom,"Tous")==0)
        index_nom=0;
    else if (strcmp(p_rech.nom,"Légumes_graines")==0)
        index_nom=1;
    else if (strcmp(p_rech.nom,"Légumes_à_bulbe")==0)
        index_nom=2;
    else if (strcmp(p_rech.nom,"Légumes_tubercules")==0)
        index_nom=3;
    else if (strcmp(p_rech.nom,"Légumes_feuilles")==0)
        index_nom=4;
    else if (strcmp(p_rech.nom,"Fruits_à_noyau")==0)
        index_nom=5;
    else if (strcmp(p_rech.nom,"Fruits_à_pépin")==0)
        index_nom=6;
    else if (strcmp(p_rech.nom,"Fruits_à_coque")==0)
        index_nom=7;
    else if (strcmp(p_rech.nom,"Agrumes")==0)
        index_nom=8;
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox1),index_nom);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(JOUR),p_rech.date_plantation.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(MOIS),p_rech.date_plantation.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(ANNEE),p_rech.date_plantation.annee);

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(JOUR,fontDesc);
    gtk_widget_modify_font(MOIS,fontDesc);
    gtk_widget_modify_font(ANNEE,fontDesc);

    remove("f_recherche.txt");
}

// Boutton afficher de n'importe quelle interface qui permet de destroy tous les window et d'ouvrir le window_main
void
on_button_afficher_gp_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_main_gp;
    GtkWidget *window_ajout_gp;
    GtkWidget *window_modification_gp;
    GtkWidget *window_suppression_gp;
    GtkWidget *window_p2_gp_detail;

    GtkWidget *treeview1_gp;
    GtkWidget *input1;
    GtkWidget *combobox1;
    GtkWidget *JOUR;
    GtkWidget *MOIS;
    GtkWidget *ANNEE;
    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 20" );


    window_ajout_gp=lookup_widget(objet,"window_ajout_gp");
    gtk_widget_destroy(window_ajout_gp);

    window_modification_gp=lookup_widget(objet,"window_modification_gp");
    gtk_widget_destroy(window_modification_gp);

    window_suppression_gp=lookup_widget(objet,"window_suppression_gp");
    gtk_widget_destroy(window_suppression_gp);

    window_p2_gp_detail=lookup_widget(objet,"window_p2_gp_detail");
    gtk_widget_destroy(window_p2_gp_detail);

    window_main_gp=create_window_main_gp();
    gtk_widget_show(window_main_gp);

    input1=lookup_widget(window_main_gp,"entry_id_gp");
    combobox1=lookup_widget(window_main_gp,"combobox_filtre_nom_gp");
    JOUR=lookup_widget(window_main_gp,"spinbutton_jour_gp");
    MOIS=lookup_widget(window_main_gp,"spinbutton_mois_gp");
    ANNEE=lookup_widget(window_main_gp,"spinbutton_annee_gp");
    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(JOUR,fontDesc);
    gtk_widget_modify_font(MOIS,fontDesc);
    gtk_widget_modify_font(ANNEE,fontDesc);

    combobox1=lookup_widget(window_main_gp,"combobox_filtre_nom_gp");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox1),0);

    treeview1_gp=lookup_widget(window_main_gp,"treeview1_gp");
    gtk_tree_view_set_enable_search (GTK_TREE_VIEW(treeview1_gp),TRUE);

    afficher_plante(treeview1_gp);
}


// Boutton valider "ajouter" dans l'interface window_ajout_gp qui permet de valider l'ajout
void
on_button_valider_ajout_gp_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{

plante p;

GtkWidget *input1,*combobox1,*combobox2,*input4,*input5,*input6,*JOUR,*MOIS,*ANNEE;
GtkWidget *controle1,*controle2,*controle3,*controle4,*controle5,*controle6;
GtkWidget *output;
char msg[200];

verification verif;
verif.test_id=0;
verif.test_nom=0;
verif.test_variete=0;
verif.test_quantite=0;
verif.test_superficie=0;
verif.test_saison=0;
verif.test_global=0;


GdkColor color1;
GdkColor color2;
gdk_color_parse ("green", &color1);
gdk_color_parse ("red", &color2);

GtkWidget *window_ajout_gp;
GtkWidget *window_notification;


test_widget_notification_gp=objet;

window_ajout_gp=lookup_widget(objet,"window_ajout_gp");


    input1=lookup_widget(objet,"entry_id_gp");
    combobox1=lookup_widget(objet,"comboboxentry_nom_gp");
    combobox2=lookup_widget(objet,"comboboxentry_variete_gp");
    input4=lookup_widget(objet,"entry_quantite_gp");
    input5=lookup_widget(objet,"entry_superficie_gp");
    input6=lookup_widget(objet,"entry_saison_gp");
    JOUR=lookup_widget(objet,"spinbutton_jour_gp");
    MOIS=lookup_widget(objet,"spinbutton_mois_gp");
    ANNEE=lookup_widget(objet,"spinbutton_annee_gp");

    strcpy(p.s_id,gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(p.nom,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));
    strcpy(p.variete,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2)));
    strcpy(p.s_quantite,gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(p.s_superficie,gtk_entry_get_text(GTK_ENTRY(input5)));
    strcpy(p.saison,gtk_entry_get_text(GTK_ENTRY(input6)));
    p.date_plantation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(JOUR));
    p.date_plantation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(MOIS));
    p.date_plantation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ANNEE));


    verif=input_verification(p,verif);

    controle1=lookup_widget(objet,"label_controle_id_gp");
    controle2=lookup_widget(objet,"label_controle_nom_gp");
    controle3=lookup_widget(objet,"label_controle_variete_gp");
    controle4=lookup_widget(objet,"label_controle_quantite_gp");
    controle5=lookup_widget(objet,"label_conrole_superficie_gp");
    controle6=lookup_widget(objet,"label_controle_saison_gp");


    gtk_widget_modify_bg(JOUR, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(MOIS, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(JOUR, GTK_STATE_SELECTED, &color1);
    gtk_widget_modify_bg(MOIS, GTK_STATE_SELECTED, &color1);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_SELECTED, &color1);


    if (verif.test_global==1) {

        if (verif.test_id==1) {
            gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color2);

            if (verif.test_id_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle1), "Cet identifiant existe déja");
            else if (verif.test_id_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle1), "Ce champs est obligatoire");
            else if (verif.test_id_cas == 3)
                gtk_label_set_text(GTK_LABEL(controle1), "L'identifiant doit être un entier");
        }
        else if (verif.test_id==0){
            gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle1), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_nom==1) {
            gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color2);
            gtk_label_set_text(GTK_LABEL(controle2), "Ce champs est obligatoire");
        }
        else if (verif.test_nom==0){
            gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle2), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_variete==1) {
            gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color2);
            gtk_label_set_text(GTK_LABEL(controle3), "Ce champs est obligatoire");
        }
        else if (verif.test_variete==0){
            gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle3), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_quantite==1) {
            gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color2);
            if (verif.test_quantite_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle4), "Ce champs est obligatoire");
            else if (verif.test_quantite_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle4), "La quantité doit être un entier");
        }
        else if (verif.test_quantite==0){
            gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle4), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_superficie==1) {
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color2);
            if (verif.test_superficie_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle5), "Ce champs est obligatoire");
            else if (verif.test_superficie_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle5), "La superficie doit être un entier");
        }
        else if (verif.test_superficie==0){
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
            gtk_label_set_markup(GTK_LABEL(controle5), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_saison==1) {
            gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color2);
            if (verif.test_saison_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle6), "Ce champs est obligatoire");
            else if (verif.test_saison_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle6), "LA saison doit ếtre : Été, Automne, Hiver ou Printemps");
        }
        else if (verif.test_saison==0){
            gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color1);

            gtk_label_set_markup(GTK_LABEL(controle6), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

    }

    else {
        gtk_label_set_markup(GTK_LABEL(controle1), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle2), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle3), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle4), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle5), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle6), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");

        gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color1);


        gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color1);


        // Pour la notification de validation de suppression
        window_notification = create_window_notification_gp();
        gtk_widget_show(window_notification);

        // Pour le message de validation
        output = lookup_widget(window_notification, "label_validation_gp") ;
        msg_validation(p.s_id,msg,"ajout");
        gtk_label_set_markup(GTK_LABEL(output),_(msg));

        ajouter_plante(p);
    }

}

// Boutton valider "modifier" dans l'interface window_modification_gp qui permet de valider la modification
void
on_button_valider_modification_gp_clicked (GtkWidget       *objet,
                                        gpointer         user_data)
{
plante p_nouv;

GtkWidget *input1,*combobox1,*combobox2,*input4,*input5,*input6,*JOUR,*MOIS,*ANNEE;
GtkWidget *controle1,*controle2,*controle3,*controle4,*controle5,*controle6;
GtkWidget *output;
char msg[200];

verification verif;
verif.test_id=0;
verif.test_nom=0;
verif.test_variete=0;
verif.test_quantite=0;
verif.test_superficie=0;
verif.test_saison=0;
verif.test_global=0;

GdkColor color1;
GdkColor color2;
gdk_color_parse ("green", &color1);
gdk_color_parse ("red", &color2);

GtkWidget *window_modification_gp;
GtkWidget *window_notification;

    test_widget_notification_gp=objet;

    window_modification_gp=lookup_widget(objet,"window_modification_gp");

    input1=lookup_widget(objet,"entry_id_gp");
    combobox1=lookup_widget(objet,"comboboxentry_nom_gp");
    combobox2=lookup_widget(objet,"comboboxentry_variete_gp");
    input4=lookup_widget(objet,"entry_quantite_gp");
    input5=lookup_widget(objet,"entry_superficie_gp");
    input6=lookup_widget(objet,"entry_saison_gp");
    JOUR=lookup_widget(objet,"spinbutton_jour_gp");
    MOIS=lookup_widget(objet,"spinbutton_mois_gp");
    ANNEE=lookup_widget(objet,"spinbutton_annee_gp");


    strcpy(p_nouv.s_id,gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(p_nouv.nom,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));
    strcpy(p_nouv.variete,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2)));
    strcpy(p_nouv.s_quantite,gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(p_nouv.s_superficie,gtk_entry_get_text(GTK_ENTRY(input5)));
    strcpy(p_nouv.saison,gtk_entry_get_text(GTK_ENTRY(input6)));
    p_nouv.date_plantation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(JOUR));
    p_nouv.date_plantation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(MOIS));
    p_nouv.date_plantation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ANNEE));

    if(strcmp(p_modif.s_id,p_nouv.s_id)==0){
        //juste pour le test
        strcpy(p_nouv.date_plantation.s_jour,"-1");}
    verif=input_verification(p_nouv,verif);
    strcpy(p_nouv.date_plantation.s_jour,"0");


    controle1=lookup_widget(objet,"label_controle_id_gp");
    controle2=lookup_widget(objet,"label_controle_nom_gp");
    controle3=lookup_widget(objet,"label_controle_variete_gp");
    controle4=lookup_widget(objet,"label_controle_quantite_gp");
    controle5=lookup_widget(objet,"label_conrole_superficie_gp");
    controle6=lookup_widget(objet,"label_controle_saison_gp");

    gtk_widget_modify_bg(JOUR, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(MOIS, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_NORMAL, &color1);
    gtk_widget_modify_bg(JOUR, GTK_STATE_SELECTED, &color1);
    gtk_widget_modify_bg(MOIS, GTK_STATE_SELECTED, &color1);
    gtk_widget_modify_bg(ANNEE, GTK_STATE_SELECTED, &color1);

    if (verif.test_global==1) {

        if (verif.test_id==1) {
            gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color2);

            if (verif.test_id_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle1), "Cet identifiant existe déja");
            else if (verif.test_id_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle1), "Ce champs est obligatoire");
            else if (verif.test_id_cas == 3)
                gtk_label_set_text(GTK_LABEL(controle1), "L'identifiant doit être un entier");
        }
        else if (verif.test_id==0){
            gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle1), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_nom==1) {
            gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color2);
            gtk_label_set_text(GTK_LABEL(controle2), "Ce champs est obligatoire");
        }
        else if (verif.test_nom==0){
            gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle2), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_variete==1) {
            gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color2);
            gtk_label_set_text(GTK_LABEL(controle3), "Ce champs est obligatoire");
        }
        else if (verif.test_variete==0){
            gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle3), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_quantite==1) {
            gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color2);
            if (verif.test_quantite_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle4), "Ce champs est obligatoire");
            else if (verif.test_quantite_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle4), "La quantité doit être un entier");
        }
        else if (verif.test_quantite==0){
            gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color1);
            gtk_label_set_markup(GTK_LABEL(controle4), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_superficie==1) {
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color2);
            if (verif.test_superficie_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle5), "Ce champs est obligatoire");
            else if (verif.test_superficie_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle5), "La superficie doit être un entier");
        }
        else if (verif.test_superficie==0){
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
            gtk_label_set_markup(GTK_LABEL(controle5), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

        if (verif.test_saison==1) {
            gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color2);
            gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color2);
            if (verif.test_saison_cas == 1)
                gtk_label_set_text(GTK_LABEL(controle6), "Ce champs est obligatoire");
            else if (verif.test_saison_cas == 2)
                gtk_label_set_text(GTK_LABEL(controle6), "LA saison doit ếtre : Été, Automne, Hiver ou Printemps");
        }
        else if (verif.test_saison==0){
            gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color1);
            gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color1);

            gtk_label_set_markup(GTK_LABEL(controle6), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        }

    }

    else {
        gtk_label_set_markup(GTK_LABEL(controle1), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle2), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle3), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle4), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle5), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");
        gtk_label_set_markup(GTK_LABEL(controle6), "<span font-weight=\"bold\" font=\"20\" color=\"green\">✓</span>");

        gtk_widget_modify_bg(input1, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(combobox1, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(combobox2, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input4, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input5, GTK_STATE_NORMAL, &color1);
        gtk_widget_modify_bg(input6, GTK_STATE_NORMAL, &color1);


        gtk_widget_modify_bg(input1, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(combobox1, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(combobox2, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input4, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input5, GTK_STATE_SELECTED, &color1);
        gtk_widget_modify_bg(input6, GTK_STATE_SELECTED, &color1);

        // Pour la notification de validation de suppression
        window_notification = create_window_notification_gp();
        gtk_widget_show(window_notification);

        // Pour le message de validation
        output = lookup_widget(window_notification, "label_validation_gp") ;
        msg_validation(p_modif.s_id,msg,"modification");
        gtk_label_set_markup(GTK_LABEL(output),_(msg));


        modifier_plante(p_nouv,p_modif);
    }
}

// Boutton valider "supprimer" dans l'interface window_supression_gp qui permet de valider la modification
void
on_button_valider_suppression_gp_clicked  (GtkWidget       *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_notification;
    GtkWidget *output;
    char msg[200];
    char test[100];

    supprimer_plante(p_supp.s_id);


    test_widget_notification_gp=objet;

    //test_widget_notification_gp=objet;

    // Pour la notification de validation de suppression
    window_notification = create_window_notification_gp();
    gtk_widget_show(window_notification);

        // Pour le message de validation
        output = lookup_widget(window_notification, "label_validation_gp") ;
        msg_validation(p_supp.s_id,msg,"suppression");
        gtk_label_set_markup(GTK_LABEL(output),_(msg));

}

// Boutton ok dans l'interface window_notiication_gp qui permet de retourner vers widget-main
void
on_button_notification_gp_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_main_gp;
    GtkWidget *window_ajout_gp;
    GtkWidget *window_modification_gp;
    GtkWidget *window_suppression_gp;
    GtkWidget *window_notification;
    GtkWidget *treeview1_gp;
    GtkWidget *input1;
    GtkWidget *combobox1;
    GtkWidget *JOUR;
    GtkWidget *MOIS;
    GtkWidget *ANNEE;
    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 20" );


    window_notification=lookup_widget(objet,"window_notification_gp");
    gtk_widget_destroy(window_notification);

    window_ajout_gp=lookup_widget(test_widget_notification_gp,"window_ajout_gp");
    gtk_widget_destroy(window_ajout_gp);

    window_modification_gp=lookup_widget(test_widget_notification_gp,"window_modification_gp");
    gtk_widget_destroy(window_modification_gp);

    window_suppression_gp=lookup_widget(test_widget_notification_gp,"window_suppression_gp");
    gtk_widget_destroy(window_suppression_gp);



    window_main_gp=create_window_main_gp();
    gtk_widget_show(window_main_gp);

    input1=lookup_widget(window_main_gp,"entry_id_gp");
    combobox1=lookup_widget(window_main_gp,"combobox_filtre_nom_gp");
    JOUR=lookup_widget(window_main_gp,"spinbutton_jour_gp");
    MOIS=lookup_widget(window_main_gp,"spinbutton_mois_gp");
    ANNEE=lookup_widget(window_main_gp,"spinbutton_annee_gp");
    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(JOUR,fontDesc);
    gtk_widget_modify_font(MOIS,fontDesc);
    gtk_widget_modify_font(ANNEE,fontDesc);

    combobox1=lookup_widget(window_main_gp,"combobox_filtre_nom_gp");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox1),0);

    treeview1_gp=lookup_widget(window_main_gp,"treeview1_gp");
    gtk_tree_view_set_enable_search (GTK_TREE_VIEW(treeview1_gp),TRUE);

    afficher_plante(treeview1_gp);
}

void
on_comboboxentry_nom_gp_changed         (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    GtkWidget *window_ajout_gp;
    GtkWidget *objet_ajout_gp;
    GtkWidget *combobox_2;
    plante p;
    int i;


    objet_ajout_gp=gtk_widget_get_toplevel(GTK_WIDGET(combobox));

    window_ajout_gp=lookup_widget(objet_ajout_gp,"window_ajout_gp");

    strcpy(p.nom,gtk_combo_box_get_active_text (GTK_COMBO_BOX(combobox)));
    combobox_2=lookup_widget(objet_ajout_gp,"comboboxentry_variete_gp");


    for (i=0;i<10;i++){
        gtk_combo_box_remove_text (GTK_COMBO_BOX (combobox_2),0);
    }
    if (strcmp(p.nom,"Légumes_graines")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Aubergine"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Concombre"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Courge"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Fève"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Piment"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Pois"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Poivron"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Tomate"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Céréales"));
    }
    else if (strcmp(p.nom,"Légumes_à_bulbe")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Poireau"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Oignon"));
    }
    else if (strcmp(p.nom,"Légumes_tubercules")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Pomme_de_terre "));
    }
    else if (strcmp(p.nom,"Légumes_feuilles")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Épinards"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Laitue"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Chou"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Betteraves"));
    }
    else if (strcmp(p.nom,"Fruits_à_noyau")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Cerise"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Datte"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Olive"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Pêche"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Abricot"));
    }
    else if (strcmp(p.nom,"Fruits_à_pépin")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Poire"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Pomme"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Coings"));
    }
    else if (strcmp(p.nom,"Fruits_à_coque")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Pistache"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Noix_de_cajou"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Amande"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Noisette"));
    }
    else if (strcmp(p.nom,"Agrumes")==0) {
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Orange"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Citron"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Lime"));
        gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_2), _("Mandarine"));
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_2),0);
}

// Boutton radio
void
on_radiobutton_a_partir_gp_toggled       (GtkToggleButton *togglebutton,
                                            gpointer         user_data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){
        x=0;
    }
}

void
on_radiobutton_date_exacte_gp_toggled     (GtkToggleButton *togglebutton,
                                            gpointer         user_data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))){
        x=1;
    }
}




void
on_treeview1_gp_cursor_changed         (GtkTreeView     *treeview,
                                        gpointer         user_data)
{
    GtkWidget *objet_main_gp;
    GtkWidget *fixed1_gp;
    GtkWidget *button_detail_gp;
    GtkTooltips *tooltips;
    GtkWidget *alignment15;
    GtkWidget *hbox15;
    GtkWidget *image15;
    GtkWidget *label56;

    GtkTreeSelection *selection ;
    GtkTreeModel *model;
    GtkTreeIter iter;

    gint id;
    gchar* nom;
    gchar* variete;
    gint quantite;
    gint superficie;
    gchar* saison;
    gchar* sdate_plantation;

    char test[200];

    plante p_detail;

    selection=gtk_tree_view_get_selection(treeview);

    if(gtk_tree_selection_get_selected(selection,&model,&iter)) {
        // Obtention des varietes de la ligne selectionnée
        gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&variete,3,&quantite,4,&superficie,5,&saison,6,&sdate_plantation,-1);

        p_detail.id=id;
        strcpy(p_detail.nom,nom);
        strcpy(p_detail.variete,variete);
        p_detail.quantite=quantite;
        p_detail.superficie=superficie;
        strcpy(p_detail.saison,saison);
        strcpy(p_detail.sdate_plantation,sdate_plantation);
    }


    sprintf(p_detail.s_id,"%d",p_detail.id);
    strcpy(test,"Voir historique du plante ");
    strcat(test,p_detail.s_id);
    strcat(test," spécifique");


    tooltips = gtk_tooltips_new ();

    objet_main_gp=&treeview->parent.widget;

    fixed1_gp=lookup_widget(objet_main_gp,"fixed1_gp");
//    button_detail_gp=lookup_widget(objet_main_gp,"button_detail_gp");
//    gtk_widget_destroy(button_detail_gp);

    button_detail_gp = gtk_button_new ();
    gtk_widget_show (button_detail_gp);
    gtk_fixed_put (GTK_FIXED (fixed1_gp), button_detail_gp, 1375, 805);
    gtk_widget_set_size_request (button_detail_gp, 175, 50);
    //gtk_tooltips_set_tip (tooltips, button_detail_gp, _(""), NULL);
    //gtk_tooltips_set_tip (tooltips, button_detail_gp, _(test), NULL);
    gtk_widget_set_tooltip_text (button_detail_gp, test);


    alignment15 = gtk_alignment_new (0.5, 0.5, 0, 0);
    gtk_widget_show (alignment15);
    gtk_container_add (GTK_CONTAINER (button_detail_gp), alignment15);

    hbox15 = gtk_hbox_new (FALSE, 2);
    gtk_widget_show (hbox15);
    gtk_container_add (GTK_CONTAINER (alignment15), hbox15);

    image15 = gtk_image_new_from_stock ("gtk-copy", GTK_ICON_SIZE_BUTTON);
    gtk_widget_show (image15);
    gtk_box_pack_start (GTK_BOX (hbox15), image15, FALSE, FALSE, 0);

    label56 = gtk_label_new_with_mnemonic (_("Voir historiques"));
    gtk_widget_show (label56);
    gtk_box_pack_start (GTK_BOX (hbox15), label56, FALSE, FALSE, 0);

    g_signal_connect ((gpointer) button_detail_gp, "clicked",
                      G_CALLBACK (on_button_detail_gp_clicked),
                      NULL);


    GLADE_HOOKUP_OBJECT_NO_REF (objet_main_gp, objet_main_gp, "window_main_gp");

    GLADE_HOOKUP_OBJECT (objet_main_gp, button_detail_gp, "button_detail_gp");

}


void
on_button_detail_gp_clicked            (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_p2_gp_detail;
    GtkWidget *window_main_gp;
    GtkWidget *titre_label;
    GtkWidget *treeview1_gp;
    GtkWidget *treeview2_gp;


    GtkTreeSelection *selection ;
    GtkTreeModel *model;
    GtkTreeIter iter;

    gint id;
    gchar* nom;
    gchar* variete;
    gint quantite;
    gint superficie;
    gchar* saison;
    gchar* sdate_plantation;

    char test[300];

    plante p_detail;

    GtkWidget *input1,*input2,*input3,*input4;

    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 17" );

    window_main_gp=lookup_widget(objet,"window_main_gp");

    treeview1_gp=lookup_widget(window_main_gp,"treeview1_gp");

    selection=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1_gp));

    if(gtk_tree_selection_get_selected(selection,&model,&iter)) {
        // Obtention des varietes de la ligne selectionnée
        gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&nom,2,&variete,3,&quantite,4,&superficie,5,&saison,6,&sdate_plantation,-1);

        p_detail.id=id;
        strcpy(p_detail.nom,nom);
        strcpy(p_detail.variete,variete);
        p_detail.quantite=quantite;
        p_detail.superficie=superficie;
        strcpy(p_detail.saison,saison);
        strcpy(p_detail.sdate_plantation,sdate_plantation);
    }


    v_ajout.plante_id=p_detail.id;
    strcpy(v_ajout.s_nom,nom);
    strcpy(v_ajout.s_variete,variete);
    v_ajout.superficie=superficie;
    strcpy(v_ajout.s_date_plantation,sdate_plantation);


    gtk_widget_destroy(window_main_gp);

    window_p2_gp_detail = create_window_p2_gp_detail();
    gtk_widget_show(window_p2_gp_detail);

    sprintf(p_detail.s_id,"%d",p_detail.id);
    strcpy(test,"<span color=\"#00442D\" font=\"40\" font-family=\"monospace\"  font-weight=\"bold\" > Historique du plante ");
    strcat(test,p_detail.s_id);
    strcat(test,"</span>");

    titre_label=lookup_widget(window_p2_gp_detail,"label_titre");
    gtk_label_set_markup(GTK_LABEL(titre_label),test);

    input1=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    input2=lookup_widget(window_p2_gp_detail,"label_input_nom");
    input3=lookup_widget(window_p2_gp_detail,"label_input_variete");
    input4=lookup_widget(window_p2_gp_detail,"label_input_date");


    gtk_entry_set_text(GTK_ENTRY(input1),_(p_detail.s_id));
    gtk_label_set_text(GTK_LABEL(input2),_(p_detail.nom));
    gtk_label_set_text(GTK_LABEL(input3),_(p_detail.variete));
    gtk_label_set_text(GTK_LABEL(input4),_(p_detail.sdate_plantation));

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(input2,fontDesc);
    gtk_widget_modify_font(input3,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);

    treeview2_gp=lookup_widget(window_p2_gp_detail,"treeview2_gp");
    afficher_plante2(treeview2_gp,v_ajout);

    for_changing_id=window_p2_gp_detail;
}



void
on_button_ajouter_valeur_gp_clicked    (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_p2_gp_detail;
    GtkWidget *window_p2_gp_ajout;
    GtkWidget *input1,*input2,*input3,*input4;
    GtkWidget *output1,*output2,*output3,*output4;
    gchar title[150];
    gchar nom[150];
    gchar variete[150];
    gchar date[150];
    GdkColor color3;
    gdk_color_parse ("#0077b6", &color3);
    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 25" );
    char test[300];


    window_p2_gp_detail=lookup_widget(objet,"window_p2_gp_detail");
    input1=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    input2=lookup_widget(window_p2_gp_detail,"label_input_nom");
    input3=lookup_widget(window_p2_gp_detail,"label_input_variete");
    input4=lookup_widget(window_p2_gp_detail,"label_input_date");

    strcpy(title,gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(nom,gtk_label_get_text(GTK_LABEL(input2)));
    strcpy(variete,gtk_label_get_text(GTK_LABEL(input3)));
    strcpy(date,gtk_label_get_text(GTK_LABEL(input4)));

    gtk_widget_destroy(window_p2_gp_detail);

    strcpy(v_ajout.s_plante_id,title);
    strcpy(v_ajout.s_nom,nom);
    strcpy(v_ajout.s_variete,variete);
    strcpy(v_ajout.s_date_plantation,date);

    window_p2_gp_ajout=create_window_p2_gp_ajout();
    gtk_widget_show(window_p2_gp_ajout);

    output1=lookup_widget(window_p2_gp_ajout,"label79");
    output2=lookup_widget(window_p2_gp_ajout,"label82");
    output3=lookup_widget(window_p2_gp_ajout,"entry2");
    output4=lookup_widget(window_p2_gp_ajout,"entry3");



    strcpy(test,"<span color=\"#00442D\" font=\"40\" font-family=\"monospace\"  font-weight=\"bold\" >Ajout des données\n du plante ");
    strcat(test,_(title));
    strcat(test,"</span>");

    gtk_label_set_markup(GTK_LABEL(output1),_(test));
    gtk_label_set_markup(GTK_LABEL(output2),_(nom));


    gtk_widget_modify_font(output2,fontDesc);
    gtk_widget_modify_font(output3,fontDesc);
    gtk_widget_modify_font(output4,fontDesc);


    gtk_widget_modify_bg(input2, GTK_STATE_SELECTED, &color3);


}



void
on_button_valider_ajout_valeur_gp_clicked(GtkWidget      *objet,
                                          gpointer         user_data)
{
    GtkWidget *window_p2_gp_ajout;
    GtkWidget *window_p2_notification_gp;

    GtkWidget *calendrier;

    GtkWidget *input1,*input2,*input3;

    GtkWidget *output;

    plante_detail p_v_ajout;

    guint jour,mois,annee;

    gchar msg[200];


    test_widget_p2_notification_gp=objet;

    window_p2_gp_ajout=lookup_widget(objet,"window_p2_gp_ajout");
    calendrier=lookup_widget(objet,"calendar1");

    input1=lookup_widget(objet,"label82");
    input2=lookup_widget(objet,"entry2");
    input3=lookup_widget(objet,"entry3");


    strcpy(p_v_ajout.s_plante_id,v_ajout.s_plante_id);
    strcpy(p_v_ajout.s_quantite,gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(p_v_ajout.s_rentabilite,gtk_entry_get_text(GTK_ENTRY(input3)));

    gtk_calendar_get_date(GTK_CALENDAR(calendrier),&annee,&mois,&jour);
    p_v_ajout.jour=jour;
    p_v_ajout.mois=mois+1;
    p_v_ajout.annee=annee;

    ajouter_plante_detail(p_v_ajout);

    // Pour la notification de validation de l'ajout
    window_p2_notification_gp=create_window_p2_notification_gp();
    gtk_widget_show(window_p2_notification_gp);


    // Pour le message de validation
    output = lookup_widget(window_p2_notification_gp, "label_p2_validation_gp") ;
    msg_validation(p_v_ajout.s_plante_id,msg,"ajout_valeur");
    gtk_label_set_markup(GTK_LABEL(output),_(msg));

}





void
on_button_afficher_valeur_gp_clicked   (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_p2_gp_ajout;
    GtkWidget *window_p2_gp_detail;
    GtkWidget *treeview2_gp;

    GtkWidget *titre_label,*input1,*input2,*input3,*input4;

    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 17" );

    gchar test[200];


    window_p2_gp_ajout=lookup_widget(objet,"window_p2_gp_ajout");
    gtk_widget_destroy(window_p2_gp_ajout);


    window_p2_gp_detail = create_window_p2_gp_detail();
    gtk_widget_show(window_p2_gp_detail);

    input1=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    input2=lookup_widget(window_p2_gp_detail,"label_input_nom");
    input3=lookup_widget(window_p2_gp_detail,"label_input_variete");
    input4=lookup_widget(window_p2_gp_detail,"label_input_date");

    strcpy(test,"<span color=\"#00442D\" font=\"40\" font-family=\"monospace\"  font-weight=\"bold\" > Historique du plante ");
    strcat(test,v_ajout.s_plante_id);
    strcat(test,"</span>");

    titre_label=lookup_widget(window_p2_gp_detail,"label_titre");
    gtk_label_set_markup(GTK_LABEL(titre_label),test);

    gtk_entry_set_text(GTK_ENTRY(input1),_(v_ajout.s_plante_id));
    gtk_label_set_text(GTK_LABEL(input2),_(v_ajout.s_nom));
    gtk_label_set_text(GTK_LABEL(input3),_(v_ajout.s_variete));
    gtk_label_set_text(GTK_LABEL(input4),_(v_ajout.s_date_plantation));

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(input2,fontDesc);
    gtk_widget_modify_font(input3,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);

    treeview2_gp=lookup_widget(window_p2_gp_detail,"treeview2_gp");
    afficher_plante2(treeview2_gp,v_ajout);

}



void
on_button_p2_notification_gp_clicked   (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_p2_notification_gp;
    GtkWidget *window_p2_gp_ajout;
    GtkWidget *window_p2_gp_detail;

    GtkWidget *treeview2_gp;

    GtkWidget *titre_label,*input1,*input2,*input3,*input4;

    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 17" );

    gchar test[200];


    window_p2_notification_gp=lookup_widget(objet,"window_p2_notification_gp");
    gtk_widget_destroy(window_p2_notification_gp);

    window_p2_gp_ajout=lookup_widget(test_widget_p2_notification_gp,"window_p2_gp_ajout");
    gtk_widget_destroy(window_p2_gp_ajout);

    window_p2_gp_detail = create_window_p2_gp_detail();
    gtk_widget_show(window_p2_gp_detail);

    input1=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    input2=lookup_widget(window_p2_gp_detail,"label_input_nom");
    input3=lookup_widget(window_p2_gp_detail,"label_input_variete");
    input4=lookup_widget(window_p2_gp_detail,"label_input_date");

    strcpy(test,"<span color=\"#00442D\" font=\"40\" font-family=\"monospace\"  font-weight=\"bold\" > Historique du plante ");
    strcat(test,v_ajout.s_plante_id);
    strcat(test,"</span>");

    titre_label=lookup_widget(window_p2_gp_detail,"label_titre");
    gtk_label_set_markup(GTK_LABEL(titre_label),test);

    gtk_entry_set_text(GTK_ENTRY(input1),_(v_ajout.s_plante_id));
    gtk_label_set_text(GTK_LABEL(input2),_(v_ajout.s_nom));
    gtk_label_set_text(GTK_LABEL(input3),_(v_ajout.s_variete));
    gtk_label_set_text(GTK_LABEL(input4),_(v_ajout.s_date_plantation));

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(input2,fontDesc);
    gtk_widget_modify_font(input3,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);

    treeview2_gp=lookup_widget(window_p2_gp_detail,"treeview2_gp");
    afficher_plante2(treeview2_gp,v_ajout);
}






void
on_entry_id_gp_insert_text             (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gpointer         position,
                                        gpointer         user_data)
{
//    GtkWidget *window_p2_gp_detail;
//    GtkWidget *treeview2_gp;
//
//    g_print("%s-",new_text);
//
//    window_p2_gp_detail=lookup_widget(for_changing_id,"window_p2_gp_detail");
//    gtk_widget_destroy(window_p2_gp_detail);
//    window_p2_gp_detail = create_window_p2_gp_detail();
//    gtk_widget_show(window_p2_gp_detail);
//    treeview2_gp=lookup_widget(for_changing_id,"treeview2_gp");
//    sscanf(new_text,"%d",v_ajout.plante_id );
//    afficher_plante2(treeview2_gp,v_ajout);


//    GtkWidget *input1;
//    gchar test[100];
//    input1=lookup_widget(for_changing_id,"entry_id_gp");
//    strcpy(test,gtk_entry_get_text(GTK_ENTRY(input1)));
//    g_print("%s",test);
}


void
on_button_p2_rechercher_gp_clicked     (GtkWidget      *objet,
                                        gpointer         user_data)
{
    GtkWidget *window_p2_gp_detail;
    GtkWidget *treeview2_gp;
    GtkWidget *output;
    GtkWidget *input1,*input2,*input3,*input4,*titre_label;
    plante p_detail;
    gchar test[250];
    PangoFontDescription *fontDesc =pango_font_description_from_string( "monospace 17" );
    plante p_test;

    window_p2_gp_detail=lookup_widget(objet,"window_p2_gp_detail");
    output=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    strcpy(p_detail.s_id,gtk_entry_get_text(GTK_ENTRY(output)));
    sscanf(p_detail.s_id,"%d",&v_ajout.plante_id );

    gtk_widget_destroy(window_p2_gp_detail);
    window_p2_gp_detail=create_window_p2_gp_detail();
    gtk_widget_show(window_p2_gp_detail);
    treeview2_gp=lookup_widget(window_p2_gp_detail,"treeview2_gp");
    afficher_plante2(treeview2_gp,v_ajout);


    strcpy(test,"<span color=\"#00442D\" font=\"40\" font-family=\"monospace\"  font-weight=\"bold\" > Historique du plante ");
    strcat(test,p_detail.s_id);
    strcat(test,"</span>");

    titre_label=lookup_widget(window_p2_gp_detail,"label_titre");
    gtk_label_set_markup(GTK_LABEL(titre_label),test);

    input1=lookup_widget(window_p2_gp_detail,"entry_id_gp");
    input2=lookup_widget(window_p2_gp_detail,"label_input_nom");
    input3=lookup_widget(window_p2_gp_detail,"label_input_variete");
    input4=lookup_widget(window_p2_gp_detail,"label_input_date");

    p_test=rechercher_p2_plante(p_detail.s_id);

    strcpy(p_detail.nom,p_test.nom);

    gtk_entry_set_text(GTK_ENTRY(input1),_(p_detail.s_id));
    gtk_label_set_text(GTK_LABEL(input2),_(p_detail.nom));
    gtk_label_set_text(GTK_LABEL(input3),_(p_test.variete));
    gtk_label_set_text(GTK_LABEL(input4),_(p_test.sdate_plantation));

    gtk_widget_modify_font(input1,fontDesc);
    gtk_widget_modify_font(input2,fontDesc);
    gtk_widget_modify_font(input3,fontDesc);
    gtk_widget_modify_font(input4,fontDesc);

}

