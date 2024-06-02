#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

typedef struct livre {
    int ID;
    char Titre[30];
    char Auteur[30];
    char Description[100];
    char NomUtilisateur[50];
    float Prix;
    char Categorie[40];
    int quantite;
} Livre;

void Ajout(FILE* fichier, int N) {
    Livre livre;
    for (int i = 0; i < N; i++) {
        printf("Entrez ID : ");
        scanf("%d", &livre.ID);
        printf("Entrez titre : ");
        scanf(" %[^\n]", livre.Titre);
        printf("Entrez auteur : ");
        scanf(" %[^\n]", livre.Auteur);
        printf("Entrez Description : ");
        scanf(" %[^\n]", livre.Description);
        printf("Entrez nom_utilisateur : ");
        scanf(" %[^\n]", livre.NomUtilisateur);
        printf("Entrez Prix : ");
        scanf("%f", &livre.Prix);
        printf("Entrez Categorie : ");
        scanf(" %[^\n]", livre.Categorie);    
        printf("Entrez Quantité: ");
        scanf("%d", &livre.quantite);
          
        fprintf(fichier, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", livre.ID , livre.Titre , livre.Auteur , livre.Description , livre.NomUtilisateur , livre.Prix, livre.Categorie, livre.quantite);
    }
}

void modifier() {
    int ID, tr = 0;
    Livre livre;
    FILE *temp, *fichier;

    fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    temp = fopen("temp.csv", "wt");
    if (temp == NULL) {
        printf("Impossible d'ouvrir le fichier temporaire\n");
        fclose(fichier); 
        return;
    }

    printf("Entrez l'id:\n");
    scanf("%d", &ID);

    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        if (ID == livre.ID) {
            tr = 1;
            printf("Entrez le nouveau titre du livre:\n");
            scanf(" %[^\n]", livre.Titre);

            printf("Entrez le nouvel auteur du livre:\n");
            scanf(" %[^\n]", livre.Auteur);

            printf("Entrez la nouvelle description du livre:\n");
            scanf(" %[^\n]", livre.Description);

            printf("Entrez le nouveau nom utilisateur du livre:\n");
            scanf(" %[^\n]", livre.NomUtilisateur);

            printf("Entrez le nouveau prix du livre:\n");
            scanf("%f", &livre.Prix);

            printf("Entrez la nouvelle categorie du livre:\n");
            scanf(" %[^\n]", livre.Categorie);

            printf("Entrez la nouvelle quantite du livre:\n");
            scanf("%d", &livre.quantite);
        }
        fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n",
                livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
    }

    fclose(fichier);
    fclose(temp);

    if (!tr) {
        printf("Le livre n'existe pas\n");
        remove("temp.csv");
    } else {
        if (remove("test3.csv") != 0) {
            printf("Erreur lors de la suppression du fichier original.\n");
            return;
        }
        if (rename("temp.csv", "test3.csv") != 0) {
            printf("Erreur lors du renommage du fichier temporaire.\n");
            return;
        }
        printf("Le livre a été modifié avec succès.\n");
    }
}

void suppression() {
    int ID, trouve = 0;
    printf("Entrez l'ID du livre à supprimer : ");
    scanf("%d", &ID);

    FILE *fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "wt");
    if (temp == NULL) {
        printf("Impossible d'ouvrir le fichier temporaire\n");
        fclose(fichier);
        return;
    }

    Livre livre;
    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        if (ID == livre.ID) {
            trouve = 1;
            printf("Le livre suivant a été supprimé :\n");
            printf("%d | %s | %s | %s | %s | %.2f | %s | %d\n",
                   livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
        } else {
            fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n",
                    livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
        }
    }

    fclose(fichier);
    fclose(temp);

    if (!trouve) {
        printf("Aucun livre trouvé avec l'ID spécifié.\n");
        remove("temp.csv"); // Clean up the temporary file if no book was found
    } else {
        if (remove("test3.csv") != 0) {
            printf("Erreur lors de la suppression du fichier original.\n");
            return;
        }
        if (rename("temp.csv", "test3.csv") != 0) {
            printf("Erreur lors du renommage du fichier temporaire.\n");
            return;
        }
        printf("Le livre a été supprimé avec succès.\n");
    }
}

void supprimerDernierLivre() {
    FILE *fichier, *tempFichier;
    Livre livre;
    int count = 0, i = 0;

    fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    tempFichier = fopen("temp.csv", "wt");
    if (tempFichier == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichier);
        return;
    }

    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        count++;
    }

    rewind(fichier);

    while (i < count - 1 && fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        fprintf(tempFichier, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", 
                livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
        i++;
    }

    fclose(fichier);
    fclose(tempFichier);

    remove("test3.csv");
    rename("temp.csv", "test3.csv");
    printf("Le dernier livre a été supprimé avec succès.\n");
}

void rechercherParID() {
    int ID, found = 0;
    Livre livre;
    FILE *fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    printf("Entrez l'ID du livre à rechercher : ");
    scanf("%d", &ID);

    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        if (livre.ID == ID) {
            printf("\nLivre trouvé :\n");
            printf("ID | Titre | Auteur | Description | Nom Utilisateur | Prix | Catégorie | Quantité\n");
            printf("--------------------------------------------------------------------------------------------\n");
            printf("%d | %s | %s | %s | %s | %.2f | %s | %d\n",
                   livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun livre trouvé avec l'ID spécifié.\n");
    }

    fclose(fichier);
}

void afficherParnom() {
    char nomutilisateur[50];
    Livre livre;
    FILE *fichier;
    int found = 0;
    fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    printf("Entrez le nom d'utilisateur : ");
    scanf(" %[^\n]", nomutilisateur);

    printf("\n--- Livres de l'utilisateur '%s' ---\n", nomutilisateur);
    printf("ID | Titre | Auteur | Description | Nom Utilisateur | Prix | Catégorie | Quantité\n");
    printf("--------------------------------------------------------------------------------------------\n");
    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        if (strcasecmp(livre.NomUtilisateur, nomutilisateur) == 0) {
            printf("%d | %s | %s | %s | %s | %.2f | %s | %d\n", 
                   livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun livre trouvé pour l'utilisateur '%s'.\n", nomutilisateur);
    }

    fclose(fichier);
}

void afficherParCategorie() {
    char categorieRecherchee[40];
    Livre livre;
    FILE *fichier;
    int found = 0;

    fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    printf("Entrez la catégorie à rechercher : ");
    scanf(" %[^\n]", categorieRecherchee);
    printf("\n--- Livres dans la catégorie '%s' ---\n", categorieRecherchee);
    printf("ID | Titre | Auteur | Description | Nom Utilisateur | Prix | Catégorie | Quantité\n");
    printf("--------------------------------------------------------------------------------------------\n");
    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        if (strcasecmp(livre.Categorie, categorieRecherchee) == 0) {
            printf("%d | %s | %s | %s | %s | %.2f | %s | %d\n", 
                   livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun livre trouvé dans la catégorie '%s'.\n", categorieRecherchee);
    }

    fclose(fichier);
}

void menu() {
    printf("0: Effectuer un remplissage\n");
    printf("1: Ajout\n");
    printf("2: Affichage\n");
    printf("3: Modification\n");
    printf("4: Suppression\n");
    printf("5: Rechercher par ID\n");
    printf("6: Afficher les livres par categorie\n");
    printf("7: Supprimer le dernier livre enregistre\n");   
}
void menu2() {
    printf("0: Effectuer un remplissage\n");
    printf("1: Ajout\n");
    printf("2: Affichage\n");
    printf("3: Rechercher par ID\n");
    printf("4: Afficher les livres par categorie\n");
    printf("5: Chercher par nom\n");   
}
void menu3() {
    printf("1: Affichage des livres dispo\n");
    printf("2: Acheter un livre\n");
    printf("3: Louer un livre\n");
}
void louer(char Client[]) {
    FILE *fichier1, *fichier2, *temp;
    char cherche_nom[30];
    Livre e;
    int produit_trouve = 0, quantite_user = 1, nouvelle_quantite;
    float prix_total;
    fichier1 = fopen("test3.csv", "rt");
    fichier2 = fopen("achats.csv", "a");
    temp = fopen("temp.csv", "wt");
    if (fichier1 == NULL || fichier2 == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    printf("Entrez le titre du produit que vous cherchez : ");
    scanf(" %[^\n]", cherche_nom);
    while (fscanf(fichier1, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n", &e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, &e.Prix, e.Categorie, &e.quantite) == 8) {
        if (strcmp(e.Titre, cherche_nom) == 0) {
            produit_trouve = 1;
            printf("Ce produit est disponible.\n");
            
            if (quantite_user <= e.quantite) {
                nouvelle_quantite = e.quantite - quantite_user;
                prix_total = quantite_user * e.Prix; 
                
                fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, nouvelle_quantite);
                fprintf(fichier2, "%s,%s,%s,%.2f,%d\n", Client, e.Titre, e.Categorie, e.Prix, 0);
                
                printf("Location effectuée avec succès. Nouvelle quantité disponible : %d\n", nouvelle_quantite);
            } else {
                printf("La quantité demandée n'est pas disponible.\n");
                fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, e.quantite);
            }
        } else {
            fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, e.quantite);
        }
    }
    if (!produit_trouve) {
        printf("Ce produit n'existe pas.\n");
    }    
    fclose(fichier1);
    fclose(fichier2);
    fclose(temp);
    remove("test3.csv");
    rename("temp.csv", "test3.csv");
}

void Affichage() {
    FILE *fichier = fopen("test3.csv", "rt");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour affichage.\n");
        return;
    }

    Livre livre;
    printf("ID | Titre                       | Auteur                    | Description                                  | Nom Utilisateur          | Prix   | Catégorie             | Quantité\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fscanf(fichier, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n",
                  &livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, &livre.Prix, livre.Categorie, &livre.quantite) == 8) {
        printf("%2d | %-27s | %-25s | %-42s | %-24s | %6.2f | %-22s | %8d\n", 
               livre.ID, livre.Titre, livre.Auteur, livre.Description, livre.NomUtilisateur, livre.Prix, livre.Categorie, livre.quantite);
    }

    fclose(fichier);
}

void achatproduit(char Client[]) {
    FILE *fichier1, *fichier2, *temp;
    char cherche_nom[30];
    Livre e;
    int produit_trouve = 0, quantite_user = 1, nouvelle_quantite;
    float prix_total;

    fichier1 = fopen("test3.csv", "rt");
    fichier2 = fopen("achats.csv", "a");
    temp = fopen("temp.csv", "wt");

    if (fichier1 == NULL || fichier2 == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }
    
    printf("Entrez le titre du produit que vous cherchez : ");
    scanf(" %[^\n]", cherche_nom);
    
    while (fscanf(fichier1, "%d; %29[^;]; %29[^;]; %99[^;]; %49[^;]; %f; %39[^;]; %d\n", &e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, &e.Prix, e.Categorie, &e.quantite) == 8) {
        if (strcmp(e.Titre, cherche_nom) == 0) {
            produit_trouve = 1;
            printf("Ce produit est disponible.\n");
            
            if (quantite_user <= e.quantite) {
                nouvelle_quantite = e.quantite - quantite_user;
                prix_total = quantite_user * e.Prix; 
                
                fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, nouvelle_quantite);
                fprintf(fichier2, "%s,%s,%s,%.2f,%d\n", Client, e.Titre, e.Categorie, e.Prix, 1);
                
                printf("Achat effectué avec succès. Nouvelle quantité disponible : %d\n", nouvelle_quantite);
            } else {
                printf("La quantité demandée n'est pas disponible.\n");
                fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, e.quantite);
            }
        } else {
            fprintf(temp, "%d; %s; %s; %s; %s; %.2f; %s; %d\n", e.ID, e.Titre, e.Auteur, e.Description, e.NomUtilisateur, e.Prix, e.Categorie, e.quantite);
        }
    }
    
    if (!produit_trouve) {
        printf("Ce produit n'existe pas.\n");
    }
    
    fclose(fichier1);
    fclose(fichier2);
    fclose(temp);
    
    remove("test3.csv");
    rename("temp.csv", "test3.csv");
}

int main() {
    int N, choix;
    char nomclienttt[50];
    char interfacee, nomemploye[20], pass[20];
    
    printf("_________________________\n");  
    printf("1 : Interface employé  : \n");
    printf("2 : Interface client   : \n");
    scanf(" %c", &interfacee);
    printf("_________________________\n");  
    
    if (interfacee == '1') {
        printf("Donnez moi le nom de l'employé : "); 
        scanf("%s", nomemploye);
        printf("Entrez le mot de passe :\n");
        scanf("%s", pass);
        
        FILE *fichieremp = fopen("employees.csv", "rt");
        if (fichieremp == NULL) {
            printf("Impossible d'ouvrir le fichier des employés.\n");
            return 1;
        }

        char emp_name[20], emp_pass[20];
        int nature;
        int found = 0;
        int type ; 
        while (fscanf(fichieremp, "%19[^;];%19[^;];%d", emp_name, emp_pass, &nature) == 3) {
            if (strcasecmp(nomemploye, emp_name) == 0 && strcasecmp(pass, emp_pass) == 0 && nature ==0  ) {
                found = 1;
                type =1 ;
                break;
                
            }
            
            if (strcasecmp(nomemploye, emp_name) == 0 && strcasecmp(pass, emp_pass) == 0 && nature ==1  ) {
                found = 1;
                type =2 ;
                break;
            }
            
           
        }
        fclose(fichieremp);

        if (found ==0) {
            printf("Nom d'utilisateur ou mot de passe incorrect.\n");
            return 1;
        }

        if (type == 2 ) {
            do {
                menu();    
                printf("Entrez votre choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 0: {
                        printf("Entrez le nombre de livres à ajouter : ");
                        scanf("%d", &N);
                        FILE *fichier = fopen("test3.csv", "a+");
                        if (fichier != NULL) {
                            Ajout(fichier, N);
                            fclose(fichier);
                            printf("Les livres ont été ajoutés avec succès dans le fichier.\n");
                        }
                        break;
                    }
                    case 1: {
                        N = 1;
                        FILE *fichier = fopen("test3.csv", "a+");
                        if (fichier != NULL) {
                            Ajout(fichier, N);
                            fclose(fichier);
                            printf("Les livres ont été ajoutés avec succès dans le fichier.\n");
                        }
                        break;
                    }
                    case 2: {
                        Affichage();
                        break;
                    }
                    case 3: {
                        modifier();
                        break;
                    }
                    case 4: {
                        suppression();
                        break;
                    }
                    case 5: {
                        rechercherParID();
                        break;
                    }
                    case 6: {
                        afficherParCategorie();
                        break;
                    }
                    case 7: {
                        supprimerDernierLivre();
                        break;
                    }
                    default: {
                        printf("Choix invalide !\n");
                        break;
                    }
                }
            } while (choix != 8);
        } else if (type == 1) {
            do {
                menu2();
                printf("Entrez votre choix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 0: {
                        printf("Entrez le nombre de livres à ajouter : ");
                        scanf("%d", &N);
                        FILE *fichier = fopen("test3.csv", "a+");
                        if (fichier != NULL) {
                            Ajout(fichier, N);
                            fclose(fichier);
                            printf("Les livres ont été ajoutés avec succès dans le fichier.\n");
                        }
                        break;
                    }
                    case 2: {
                        Affichage();
                        break;
                    }
                    case 3: {
                        rechercherParID();
                        break;
                    }
                    case 4: {
                        afficherParCategorie();
                        break;
                    }
                    case 5: {
                        afficherParnom();
                        break;
                    }
                    default: {
                        printf("Choix invalide !\n");
                        break;
                    }
                }
            } while (choix != 6);
        }
    } else if (interfacee == '2') {
        printf("Donnez moi le nom_client : ");
        scanf("%s", nomclienttt);
        
        do {
            menu3();
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            switch (choix) {
                case 1: {
                    Affichage();
                    break;
                }
                case 2: {
                    achatproduit(nomclienttt);
                    break;
                }
                case 3: {
                    louer(nomclienttt);
                    break;
                }
                default: {
                    printf("Choix invalide !\n");
                    break;
                }
            }
        } while (choix != 4);
    }
    return 0;
}

