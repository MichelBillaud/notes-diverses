// listes.c

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    struct Node *first;
} List;


void sl_init(List *list)
{
    list->first = NULL;
}

bool sl_is_empty(const List *list)
{
    return list->first == NULL;
}

void test_init()
{
    List l;
    sl_init(&l);
    assert("liste vide après initialisation" && sl_is_empty(&l));
}



void sl_add_first(List *list, int value)
{
    Node *n = malloc(sizeof(Node));
    // A faire : cas où l'allocation échoue
    n->value = value;
    n->next = list->first;
    list->first = n;
}

int sl_size(const List *list)
{
    int size = 0;
    for (Node *n = list->first; n != NULL; n = n->next) {
        size += 1;
    }
    return size;
}

int sl_value_at(const List *list, int index)
{
    Node *n = list->first;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }
    return n->value;
}

void test_add_first()
{
    List list;
    sl_init(&list);
    sl_add_first(&list, 10);
    sl_add_first(&list, 30);
    sl_add_first(&list, 20);

    assert("après 3 ajouts" && sl_size(&list) == 3);

    assert("premier de la liste"   && sl_value_at(&list, 0) == 20);
    assert("second de la liste"    && sl_value_at(&list, 1) == 30);
    assert("troisième de la liste" && sl_value_at(&list, 2) == 10);

}

bool sl_list_contains(const List *list, int values[], int nb_values)
{
    Node *node = list->first;
    for (int i = 0; i < nb_values; i++) {
        if (node == NULL) {
            return false;
        }
        if (node->value != values[i]) {
            return false;
        }
        node = node -> next;
    }
    return node == NULL;
}

void sl_add_last(List *list, int value)
{
    // recherche du dernier maillon
    Node *last = NULL;
    for (Node *n = list->first; n != NULL; n = n->next) {
        last = n;
    }
    // allocation nouveau maillon
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    // accrochage
    if (last == NULL) {
        // au début (la liste était vide)
        list->first = new_node;
    } else {
        // après le dernier
        last->next = new_node;
    }
}

void test_add_last()
{
    List list;
    sl_init(& list);

    sl_add_last(&list, 11);
    assert("après 1 ajout" && sl_size(&list) == 1);
    assert("après 1 ajout" &&sl_value_at(&list, 0) == 11);

    sl_add_last(&list, 333);
    assert("après 2 ajouts" && sl_size(&list) == 2);
    assert("après 2 ajouts" &&sl_value_at(&list, 1) == 333);

    sl_add_last(&list, 2);
    assert("après 3 ajouts" && sl_size(&list) == 3);
    assert("après 3 ajouts" && sl_value_at(&list, 2) == 2);


    int expected[] = { 11, 333, 2};
    assert("contenu après 3 ajouts à la fin" &&
           sl_list_contains(&list, expected, 3));
}

void sl_add_values(List *list, int values[], int nb_values)
{
    // recherche de l'adresse du pointeur auquel on accrochera le
    // premier élément supplémentaire
    Node **addr_ptr = & list->first;
    for (Node *n = list->first; n != NULL; n = n->next) {
        addr_ptr = &(n->next);
    }
    // ajout des éléments
    for (int i = 0; i < nb_values; i++) {
        Node *new_node = malloc(sizeof(Node));
        new_node->value = values[i];
        new_node->next = NULL;
        // chainage du maillon
        *addr_ptr = new_node;
        // c'est à lui qu'on accrochera les suivants
        addr_ptr = & new_node->next;
    }
}

void test_add_values()
{
    List list;
    sl_init(& list);

    int v1[] = {11, 22, 33};
    sl_add_values(&list, v1, 3);

    assert("construction liste" && sl_list_contains(&list, v1, 3));

    int v2[] = {44, 55};
    sl_add_values(&list, v2, 2);

    int expected[] = { 11, 22, 33, 44, 55};
    assert("ajout tableau" && sl_list_contains(&list, expected, 5));




}
int main()
{
    printf("# Tests\n");
    test_init();
    test_add_first();
    test_add_last();
    test_add_values();
    printf("# OK\n");
}