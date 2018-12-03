#include <stdio.h>
#include <stdlib.h>
#include "List.h"


typedef double elem_t;

const int signal = 0xBEDABEDA;

enum errors
{
    ALLOCATION_ERROR = 0,
    OKAY = 1,
    NOTOKAY,
    INVALID_NODE_POINTER,
    INVALID_LIST_POINTER,
    INVALID_CANARY,
    INVALID_SIZE,
    INVALID_CHECKSUM,
    POP_ERROR,
    DELETE_ERROR,
    PUSH_ERROR,
    INSERT_ERROR
};


struct List * create_List()
{
    struct List * new_list = (struct List *) calloc(1, sizeof(struct List));
    if (new_list == NULL)
    {
        printf("Could not allocate memory\n");
        return ALLOCATION_ERROR;
    }

    new_list -> first = NULL;
    new_list -> last = NULL;
    new_list -> size = 0;
    new_list -> canary1 = signal;
    new_list -> canary2 = signal;
    CALC_LIST_CHECK_SUM(new_list);

    return new_list;
}

int erase_List(struct List * my_list)
{
    ISCORRECTLIST(my_list);

    struct Node * current_node = my_list -> last;
    while (current_node != NULL)
    {
        current_node = current_node -> prev;
        free(my_list -> last);
        my_list -> last = current_node;
    }

    free(my_list);

    return 0;
}

struct Node * create_Node()
{
    struct Node * new_node = (struct Node *) calloc (1, sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("Could not allocate memory\n");
        return ALLOCATION_ERROR;
    }

    new_node -> next = NULL;
    new_node -> prev = NULL;
    new_node -> data = -10101010;
    new_node -> canary1 = signal;
    new_node -> canary2 = signal;
    CALC_NODE_CHECK_SUM(new_node);

    return new_node;
};

int delete_Node(struct List * my_list, struct Node * my_node)
{
    ISCORRECTLIST(my_list);
    ISCORRECTNODE(my_node);

    struct Node * prev_node = my_node -> prev;
    struct Node * next_node = my_node -> next;

    if (prev_node == NULL) // if my_node is first
    {
        my_list -> first = next_node;
        my_list -> first -> prev = NULL;
        my_list -> size -= 1;
        free(my_node);

        CALC_NODE_CHECK_SUM(next_node);
        CALC_LIST_CHECK_SUM(my_list);
        ISCORRECTLIST(my_list);
        return 0;
    }

    if (next_node == NULL) // if my_node is last
    {
        my_list -> last = prev_node;
        my_list -> last -> next = NULL;
        my_list -> size -= 1;
        free(my_node);

        CALC_NODE_CHECK_SUM(prev_node);
        CALC_LIST_CHECK_SUM(my_list);
        ISCORRECTLIST(my_list);
        return 0;
    }

    prev_node -> next = next_node;
    next_node -> prev = prev_node;
    my_list -> size -= 1;

    CALC_NODE_CHECK_SUM(next_node);
    CALC_NODE_CHECK_SUM(prev_node);
    CALC_LIST_CHECK_SUM(my_list);
    ISCORRECTLIST(my_list);
    free(my_node);

    return 0;
}

int push_back(struct List * my_list, elem_t value)
{
    ISCORRECTLIST(my_list);

    struct Node * new_node = create_Node();

    if (my_list -> first == NULL)
    {
        my_list -> first = new_node;
        my_list -> last = new_node;
        new_node -> data = value;
        my_list -> size += 1;

        CALC_NODE_CHECK_SUM(new_node);
        CALC_LIST_CHECK_SUM(my_list);
        ISCORRECTLIST(my_list);
        return 0;
    }

    new_node -> prev = my_list -> last;
    new_node -> data = value;
    my_list -> last -> next = new_node;
    my_list -> last = new_node;
    my_list -> size += 1;

    CALC_LIST_CHECK_SUM(my_list);
    CALC_NODE_CHECK_SUM(my_list -> last);
    CALC_NODE_CHECK_SUM(my_list -> last -> prev);
    ISCORRECTLIST(my_list);
    return 0;
}

int push_front(struct List * my_list, elem_t value)
{
    ISCORRECTLIST(my_list);

    struct Node * new_node = create_Node();

    if (my_list -> first == NULL)
    {
        my_list -> first = new_node;
        my_list -> last = new_node;
        new_node -> data = value;
        my_list -> size += 1;

        CALC_LIST_CHECK_SUM(my_list);
        CALC_NODE_CHECK_SUM(new_node);
        ISCORRECTLIST(my_list);
        return 0;
    }

    new_node -> next = my_list -> first;
    new_node -> data = value;
    my_list -> first -> prev = new_node;
    my_list -> first = new_node;
    my_list -> size += 1;

    CALC_NODE_CHECK_SUM(my_list -> first -> next);
    CALC_NODE_CHECK_SUM(my_list -> first);
    CALC_LIST_CHECK_SUM(my_list);
    ISCORRECTLIST(my_list);
    ISCORRECTNODE(my_list -> first);
    ISCORRECTNODE(my_list -> first -> next);
    return 0;
}

elem_t pop_back(struct List * my_list)
{
    ISCORRECTLIST(my_list);
    if (my_list -> last == NULL)
    {
        printf("\nYou want to pop clear List\n");
        return POP_ERROR;
    }

    struct Node * prev_last = my_list -> last -> prev;
    elem_t value = my_list -> last -> data;
    free(my_list -> last);
    prev_last -> next = NULL;
    my_list -> last = prev_last;
    my_list -> size -= 1;

    CALC_NODE_CHECK_SUM(my_list -> last -> prev);
    CALC_NODE_CHECK_SUM(my_list -> last);
    CALC_LIST_CHECK_SUM(my_list);
    ISCORRECTLIST(my_list);
    return value;
}

int print_List(struct List * my_list)
{
    ISCORRECTLIST(my_list);

    struct Node * current_node = my_list -> first;
    int i = 0;
    printf("\nThere is\n    struct List \"your_list\" [%p]\n    size = %d\n" , my_list, my_list -> size);
    while(current_node != NULL)
    {
        printf("    [%d] = %f\n", i, current_node -> data);
        current_node = current_node -> next;
        ++i;
    }

    return 0;
}

struct Node * Node_FindNext(struct Node * begin_search, elem_t value_to_find)
{
    ISCORRECTNODE(begin_search);

    struct Node * cur_ptr = begin_search;
    while (cur_ptr != NULL)
    {
        if (cur_ptr -> data == value_to_find)
           {
              return cur_ptr;
           }

        cur_ptr = cur_ptr -> next;
    }

    return NULL;
}

int Node_CalculateIndex(struct Node * node)
{
    ISCORRECTNODE(node);
    struct Node * cur_ptr = node;
    int i = 0;
    while(cur_ptr != NULL)
    {
        cur_ptr = cur_ptr -> prev;
        ++i;
    }
    return i;
}

int InsertAfter(struct List * my_list, struct Node * my_node, elem_t value)
{
    ISCORRECTNODE(my_node);
    ISCORRECTLIST(my_list);

    struct Node * new_node = create_Node();
    struct Node * next_my_node = my_node -> next;

    if (next_my_node == NULL)
    {
        push_back(my_list, value);
        return 0;
    }

    next_my_node -> prev = new_node;
    new_node -> next = next_my_node;
    my_node -> next = new_node;
    new_node -> prev = my_node;
    new_node -> data = value;
    my_list -> size += 1;

    CALC_NODE_CHECK_SUM(my_node);
    CALC_NODE_CHECK_SUM(new_node);
    CALC_NODE_CHECK_SUM(next_my_node);
    CALC_LIST_CHECK_SUM(my_list);
    ISCORRECTLIST(my_list);
    ISCORRECTNODE(new_node);
    ISCORRECTNODE(next_my_node);
    ISCORRECTNODE(my_node);
    return 0;
}


int InsertBefore(struct List * my_list, struct Node * my_node, elem_t value)
{
    ISCORRECTNODE(my_node);
    ISCORRECTLIST(my_list);

    struct Node * new_node = create_Node();
    struct Node * prev_my_node = my_node -> prev;

    if (prev_my_node == NULL)
    {

        push_front(my_list, value);

        return 0;
    }

    prev_my_node -> next = new_node;
    new_node -> prev = prev_my_node;
    my_node -> prev = new_node;
    new_node -> next = my_node;
    new_node -> data = value;
    my_list -> size += 1;

    CALC_NODE_CHECK_SUM(new_node);
    CALC_NODE_CHECK_SUM(prev_my_node);
    CALC_NODE_CHECK_SUM(my_node);
    CALC_LIST_CHECK_SUM(my_list);

    ISCORRECTLIST(my_list)
    ISCORRECTNODE(new_node);
    ISCORRECTNODE(prev_my_node);
    ISCORRECTNODE(my_node);
    return 0;
}

int ListOk(struct List * my_list)
{
    if (my_list == NULL)
    {
        printf("Your List has valid poiner, your_list [NULL]\n");
        return INVALID_LIST_POINTER;
    }

    if (my_list -> canary1 != signal || my_list -> canary2 != signal)
    {
        printf("Security list has been breached,\n\
                canary 1 == %x, canary 2 == %x, but should be\n\
                canary 1 == %x, canary 2 == %x\n", my_list -> canary1,
                my_list -> canary2, signal, signal);
        return INVALID_CANARY;
    }

    if (my_list -> size < 0)
    {
        printf("Invalid size, your_list -> size = %d\n", my_list -> size);
        return INVALID_SIZE;
    }

    if (CALC_LIST_CHECK_SUM(my_list) != my_list -> checksum)
    {
        printf("Invalid checksum, \nyour_list -> checksum = %d, but should be\n\
               your_list -> checksum = %d\n", CALC_LIST_CHECK_SUM(my_list), my_list -> checksum);
        return INVALID_CHECKSUM;
    }

    return OKAY;
}

int NodeOk(struct Node * my_node)
{
    if (my_node == NULL)
    {
        printf("Your Node has valid poiner, your_node [NULL]\n");
        return INVALID_NODE_POINTER;
    }
    if (my_node -> canary1 != signal || my_node -> canary2 != signal)
    {
        printf("Security node has been breached,\n\
                canary 1 == %x, canary 2 == %x, but should be\n\
                canary 1 == %x, canary 2 == %x\n", my_node -> canary1,
                my_node -> canary2, signal, signal);
        return INVALID_CANARY;
    }

    if (CALC_NODE_CHECK_SUM(my_node) != my_node -> checksum)
    {
        printf("Invalid checksum, \nyour_node -> checksum = %d, but should be\n\
               your_node -> checksum = %d\n", CALC_NODE_CHECK_SUM(my_node), my_node -> checksum);
        return INVALID_CHECKSUM;
    }

    return OKAY;

}



