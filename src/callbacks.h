#include <gtk/gtk.h>


void
on_treeview1_gp_row_activated             (GtkTreeView     *treeview,
                                            GtkTreePath     *path,
                                            GtkTreeViewColumn *column,
                                            gpointer         user_data);

void
on_button_modifier_gp_clicked             (GtkWidget       *objet,
                                            gpointer         user_data);

void
on_button_ajouter_gp_clicked              (GtkWidget       *objet,
                                            gpointer         user_data);

void
on_button_rechercher_gp_clicked           (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_afficher_gp_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_valider_ajout_gp_clicked        (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_button_valider_modification_gp_clicked (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_button_valider_suppression_gp_clicked  (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_comboboxentry_nom_gp_changed         (GtkComboBox     *combobox,
                                        gpointer         user_data);


void
on_radiobutton_a_partir_gp_toggled       (GtkToggleButton *togglebutton,
                                            gpointer         user_data);

void
on_radiobutton_date_exacte_gp_toggled     (GtkToggleButton *togglebutton,
                                            gpointer         user_data);



void
on_button_notification_gp_clicked      (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview1_gp_cursor_changed         (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_button_detail_gp_clicked            (GtkWidget      *objet,
                                        gpointer         user_data);


void
on_button_afficher_valeur_gp_clicked   (GtkWidget      *objet,
                                        gpointer         user_data);

void
on_button_valider_ajout_valeur_gp_clicked
                                        (GtkWidget      *objet,
                                        gpointer         user_data);



void
on_button_ajouter_valeur_gp_clicked    (GtkWidget      *objet,
                                        gpointer         user_data);

void
on_button_p2_notification_gp_clicked   (GtkWidget      *objet,
                                        gpointer         user_data);

void
on_entry_id_gp_insert_text             (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gpointer         position,
                                        gpointer         user_data);

void
on_button_p2_rechercher_gp_clicked     (GtkWidget      *objet,
                                        gpointer         user_data);
