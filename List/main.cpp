#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main()
{
    struct List * my_list = create_List();
    push_back(my_list, 12);
    double val = my_list -> first -> data;
    printf("%lf ", val);
    //print_List(my_list);
    return 0;
}
