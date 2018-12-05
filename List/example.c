#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef double elem_t;

int main()
{
    struct List * my_list = create_List();
    push_back(my_list, 11);
    push_back(my_list, 12);
    push_back(my_list, 13);
    push_back(my_list, 14);
    push_back(my_list, 15);
    push_back(my_list, 16);
    push_back(my_list, 17);
    push_back(my_list, 18);
    push_front(my_list, 10);

    struct Node * go;
    go = Node_FindNext(my_list -> first, 16);
    printf("%f!!!\n", go -> data);
    InsertBefore(my_list, my_list ->last, -666);

    print_List(my_list);
    pop_back(my_list);
    pop_back(my_list);
    delete_Node(my_list, go);
    delete_Node(my_list, my_list -> first);
    print_List(my_list);
    erase_List(my_list);
    return 0;
}

