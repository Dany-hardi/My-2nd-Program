#include <stdio.h>
#include <stdlib.h>

// Structures pour les différents types de listes
typedef struct NodeSimple {
    int data;
    struct NodeSimple* next;
} NodeSimple;

typedef struct NodeDouble {
    int data;
    struct NodeDouble* next;
    struct NodeDouble* prev;
} NodeDouble;


// 1. SUPPRESSION DE TOUTES LES OCCURRENCES DANS UNE LISTE SIMPLE


NodeSimple* supprimerOccurrences(NodeSimple* head, int element) {
    NodeSimple* current = head;
    NodeSimple* prev = NULL;
    
    // Supprimer en tête tant que l'élément est trouvé
    while (current != NULL && current->data == element) {
        head = current->next;
        free(current);
        current = head;
    }
    
    // Supprimer dans le reste de la liste
    while (current != NULL) {
        if (current->data == element) {
            prev->next = current->next;
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    return head;
}


// 2. INSERTION DANS UNE LISTE SIMPLEMENT CHAÎNÉE TRIÉE


NodeSimple* insererTrieSimple(NodeSimple* head, int element) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = element;
    nouveau->next = NULL;
    
    // Liste vide ou insertion en tête
    if (head == NULL || head->data >= element) {
        nouveau->next = head;
        return nouveau;
    }
    
    // Trouver la position d'insertion
    NodeSimple* current = head;
    while (current->next != NULL && current->next->data < element) {
        current = current->next;
    }
    
    // Insérer après current
    nouveau->next = current->next;
    current->next = nouveau;
    
    return head;
}


// 3. INSERTION DANS UNE LISTE DOUBLEMENT CHAÎNÉE TRIÉE

NodeDouble* insererTrieDouble(NodeDouble* head, int element) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    nouveau->data = element;
    nouveau->next = NULL;
    nouveau->prev = NULL;
    
    // Liste vide
    if (head == NULL) {
        return nouveau;
    }
    
    // Insertion en tête
    if (head->data >= element) {
        nouveau->next = head;
        head->prev = nouveau;
        return nouveau;
    }
    
    // Trouver la position d'insertion
    NodeDouble* current = head;
    while (current->next != NULL && current->next->data < element) {
        current = current->next;
    }
    
    // Insérer après current
    nouveau->next = current->next;
    nouveau->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = nouveau;
    }
    current->next = nouveau;
    
    return head;
}


// 4. INSERTION TÊTE/QUEUE LISTE SIMPLEMENT CHAÎNÉE CIRCULAIRE

NodeSimple* insererTeteCirculaireSimple(NodeSimple* head, int element) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = element;
    
    if (head == NULL) {
        nouveau->next = nouveau; // Pointe sur lui-même
        return nouveau;
    }
    
    // Trouver le dernier nœud
    NodeSimple* dernier = head;
    while (dernier->next != head) {
        dernier = dernier->next;
    }
    
    nouveau->next = head;
    dernier->next = nouveau;
    
    return nouveau; // Le nouveau nœud devient la tête
}

NodeSimple* insererQueueCirculaireSimple(NodeSimple* head, int element) {
    NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
    nouveau->data = element;
    
    if (head == NULL) {
        nouveau->next = nouveau;
        return nouveau;
    }
    
    // Trouver le dernier nœud
    NodeSimple* dernier = head;
    while (dernier->next != head) {
        dernier = dernier->next;
    }
    
    nouveau->next = head;
    dernier->next = nouveau;
    
    return head; // La tête reste inchangée
}


// 5. INSERTION TÊTE/QUEUE LISTE DOUBLEMENT CHAÎNÉE CIRCULAIRE

NodeDouble* insererTeteCirculaireDouble(NodeDouble* head, int element) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    nouveau->data = element;
    
    if (head == NULL) {
        nouveau->next = nouveau;
        nouveau->prev = nouveau;
        return nouveau;
    }
    
    NodeDouble* dernier = head->prev;
    
    nouveau->next = head;
    nouveau->prev = dernier;
    head->prev = nouveau;
    dernier->next = nouveau;
    
    return nouveau; // Le nouveau nœud devient la tête
}

NodeDouble* insererQueueCirculaireDouble(NodeDouble* head, int element) {
    NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
    nouveau->data = element;
    
    if (head == NULL) {
        nouveau->next = nouveau;
        nouveau->prev = nouveau;
        return nouveau;
    }
    
    NodeDouble* dernier = head->prev;
    
    nouveau->next = head;
    nouveau->prev = dernier;
    head->prev = nouveau;
    dernier->next = nouveau;
    
    return head; // La tête reste inchangée
}


void afficherListeSimple(NodeSimple* head) {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }
    
    NodeSimple* current = head;
    printf("Liste: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != NULL && current != head);
    printf("\n");
}

void afficherListeDouble(NodeDouble* head) {
    if (head == NULL) {
        printf("Liste vide\n");
        return;
    }
    
    NodeDouble* current = head;
    printf("Liste: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != NULL && current != head);
    printf("\n");
}

NodeSimple* creerListeSimple(int arr[], int n) {
    if (n == 0) return NULL;
    
    NodeSimple* head = (NodeSimple*)malloc(sizeof(NodeSimple));
    head->data = arr[0];
    head->next = NULL;
    
    NodeSimple* current = head;
    for (int i = 1; i < n; i++) {
        NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
        nouveau->data = arr[i];
        nouveau->next = NULL;
        current->next = nouveau;
        current = nouveau;
    }
    
    return head;
}


NodeSimple* saisirListeSimple() {
    int n, element;
    printf("Combien d'éléments voulez-vous saisir ? ");
    scanf("%d", &n);
    
    if (n <= 0) return NULL;
    
    NodeSimple* head = NULL;
    NodeSimple* dernier = NULL;
    
    printf("Entrez les %d éléments :\n", n);
    for (int i = 0; i < n; i++) {
        printf("Élément %d : ", i + 1);
        scanf("%d", &element);
        
        NodeSimple* nouveau = (NodeSimple*)malloc(sizeof(NodeSimple));
        nouveau->data = element;
        nouveau->next = NULL;
        
        if (head == NULL) {
            head = nouveau;
            dernier = nouveau;
        } else {
            dernier->next = nouveau;
            dernier = nouveau;
        }
    }
    
    return head;
}

NodeDouble* saisirListeDouble() {
    int n, element;
    printf("Combien d'éléments voulez-vous saisir ? ");
    scanf("%d", &n);
    
    if (n <= 0) return NULL;
    
    NodeDouble* head = NULL;
    NodeDouble* dernier = NULL;
    
    printf("Entrez les %d éléments :\n", n);
    for (int i = 0; i < n; i++) {
        printf("Élément %d : ", i + 1);
        scanf("%d", &element);
        
        NodeDouble* nouveau = (NodeDouble*)malloc(sizeof(NodeDouble));
        nouveau->data = element;
        nouveau->next = NULL;
        nouveau->prev = dernier;
        
        if (head == NULL) {
            head = nouveau;
        } else {
            dernier->next = nouveau;
        }
        dernier = nouveau;
    }
    
    return head;
}

void afficherMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Supprimer toutes les occurrences d'un élément\n");
    printf("2. Insérer dans une liste simple triée\n");
    printf("3. Insérer dans une liste double triée\n");
    printf("4. Insérer en tête/queue (liste simple circulaire)\n");
    printf("5. Insérer en tête/queue (liste double circulaire)\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

// MAIN PROGRAM

int main() {
    printf("=== EXERCICES INF 231 - LISTES CHAÎNÉES ===\n");
    
    int choix;
    do {
        afficherMenu();
        scanf("%d", &choix);
        
        switch (choix) {
            case 1: {
                printf("\n--- SUPPRESSION D'OCCURRENCES ---\n");
                NodeSimple* liste = saisirListeSimple();
                printf("Liste initiale : ");
                afficherListeSimple(liste);
                
                int element;
                printf("Quel élément voulez-vous supprimer ? ");
                scanf("%d", &element);
                
                liste = supprimerOccurrences(liste, element);
                printf("Liste après suppression : ");
                afficherListeSimple(liste);
                break;
            }
            
            case 2: {
                printf("\n--- INSERTION TRIÉE (LISTE SIMPLE) ---\n");
                printf("Créez votre liste triée initiale :\n");
                NodeSimple* liste = saisirListeSimple();
                printf("Liste initiale : ");
                afficherListeSimple(liste);
                
                int element;
                printf("Quel élément voulez-vous insérer ? ");
                scanf("%d", &element);
                
                liste = insererTrieSimple(liste, element);
                printf("Liste après insertion : ");
                afficherListeSimple(liste);
                break;
            }
            
            case 3: {
                printf("\n--- INSERTION TRIÉE (LISTE DOUBLE) ---\n");
                printf("Créez votre liste triée initiale :\n");
                NodeDouble* liste = saisirListeDouble();
                printf("Liste initiale : ");
                afficherListeDouble(liste);
                
                int element;
                printf("Quel élément voulez-vous insérer ? ");
                scanf("%d", &element);
                
                liste = insererTrieDouble(liste, element);
                printf("Liste après insertion : ");
                afficherListeDouble(liste);
                break;
            }
            
            case 4: {
                printf("\n--- LISTE SIMPLE CIRCULAIRE ---\n");
                NodeSimple* liste = NULL;
                int nbElements, element, position;
                
                printf("Combien d'éléments à insérer ? ");
                scanf("%d", &nbElements);
                
                for (int i = 0; i < nbElements; i++) {
                    printf("Élément %d : ", i + 1);
                    scanf("%d", &element);
                    printf("Insérer en (1)tête ou (2)queue ? ");
                    scanf("%d", &position);
                    
                    if (position == 1) {
                        liste = insererTeteCirculaireSimple(liste, element);
                    } else {
                        liste = insererQueueCirculaireSimple(liste, element);
                    }
                }
                
                printf("Liste circulaire (10 premiers éléments) : ");
                if (liste != NULL) {
                    NodeSimple* temp = liste;
                    for (int i = 0; i < 10 && i < nbElements * 2; i++) {
                        printf("%d ", temp->data);
                        temp = temp->next;
                    }
                    printf("...\n");
                }
                break;
            }
            
            case 5: {
                printf("\n--- LISTE DOUBLE CIRCULAIRE ---\n");
                NodeDouble* liste = NULL;
                int nbElements, element, position;
                
                printf("Combien d'éléments à insérer ? ");
                scanf("%d", &nbElements);
                
                for (int i = 0; i < nbElements; i++) {
                    printf("Élément %d : ", i + 1);
                    scanf("%d", &element);
                    printf("Insérer en (1)tête ou (2)queue ? ");
                    scanf("%d", &position);
                    
                    if (position == 1) {
                        liste = insererTeteCirculaireDouble(liste, element);
                    } else {
                        liste = insererQueueCirculaireDouble(liste, element);
                    }
                }
                
                printf("Liste circulaire (10 premiers éléments) : ");
                if (liste != NULL) {
                    NodeDouble* temp = liste;
                    for (int i = 0; i < 10 && i < nbElements * 2; i++) {
                        printf("%d ", temp->data);
                        temp = temp->next;
                    }
                    printf("...\n");
                }
                break;
            }
            
            case 0:
                printf("Au revoir !\n");
                break;
                
            default:
                printf("Choix invalide ! Essayez encore.\n");
        }
        
    } while (choix != 0);
    
    return 0;
}
