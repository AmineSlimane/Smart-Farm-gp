#include <gtk/gtk.h>

typedef struct{
int jour;
int mois;
int annee;

char s_jour[100];
char s_mois[100];
char s_annee[100];
}date;


typedef struct{
int id;
int quantite;
int superficie;

char s_id[100];
char nom[100];
char variete[100];
char s_quantite[100];
char s_superficie[100];
char saison[100];
char sdate_plantation[100];
date date_plantation;
}plante;

typedef struct{
    int plante_id;
    int quantite;
    int rentabilite;
    int jour;
    int mois;
    int annee;

    char s_plante_id[250];
    char s_quantite[100];
    char s_rentabilite[100];
    char s_date_ajout[100];

    char s_nom[100];
    char s_variete[100];
    int  superficie;
    char s_date_plantation[100];
}plante_detail;




typedef struct{
    int test_id;
    int test_id_cas;
    int test_nom;
    int test_variete;
    int test_quantite;
    int test_quantite_cas;
    int test_superficie;
    int test_superficie_cas;
    int test_saison;
    int test_saison_cas;
    int test_global;
}verification;


void afficher_plante(GtkWidget *liste);
void ajouter_plante(plante p);
void supprimer_plante(char p_id_supp[10]);
void modifier_plante(plante p_nouv,plante p_modif);
void rechercher_plante(plante p,int x);
void afficher_recherche_avancee(GtkWidget *liste);

void msg_validation(char id[20], char validation[100], char methode[20]);
int date_comparaison (date date_input,date date_du_fichier);
void concatenation(char output[]);
verification input_verification(plante p,verification verif);
int is_integer (char test[]);

void afficher_plante2(GtkWidget *liste,plante_detail v_ajout);
void ajouter_plante_detail(plante_detail p_v_ajout);
plante rechercher_p2_plante(char p_rech_s_id[200]);