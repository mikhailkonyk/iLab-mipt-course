#include <stdio.h>

#define CALC_LIST_CHECK_SUM(list) (list -> checksum = (31 * (int)((list) -> first) + 28 * (int)((list) -> last)))

#define CALC_NODE_CHECK_SUM(node) (node -> checksum = (31 * (int)((node) -> prev) + 28 * (int)((node) -> next)))



#define ISCORRECTLIST(my_list) \
{\
    if (ListOk(my_list) != OKAY)\
    {\
        printf("Your List isn't OKAY\n");\
        return NOTOKAY;\
    }\
}

#define ISCORRECTNODE(node) \
{\
    if (NodeOk(node) != OKAY)\
    {\
        printf("Your Node isn't OKAY\n");\
        return NOTOKAY;\
    }\
}

typedef double elem_t;

struct List
{
    int canary1;
    struct Node * first;
    struct Node * last;
    size_t size;
    int checksum;
    int canary2;
};

struct Node
{
    int canary1;
    elem_t data;
    struct Node * next;
    struct Node * prev;
    int checksum;
    int canary2;
};

struct List * create_List();
int erase_List(struct List * my_list);
struct Node * create_Node();
int delete_Node(struct List * my_list, struct Node * my_node);
int push_back(struct List * my_list, elem_t value);
int push_front(struct List * my_list, elem_t value);
elem_t pop_back(struct List * my_list);
int print_List(struct List * my_list);
struct Node * Node_FindNext(struct Node * begin_search, elem_t value_to_find);
int Node_CalculateIndex(struct Node * node);
int InsertAfter(struct List * my_list, struct Node * my_node, elem_t value);
int InsertBefore(struct List * my_list, struct Node * my_node, elem_t value);
int NodeOk(struct Node * my_node);
int ListOk(struct List * my_list);
