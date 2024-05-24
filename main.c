#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h"
int main()
{
    rb_tree *t = rb_alloc(); //t - указатель на корень
    setlocale(LC_ALL, "Russian");
    int Q, i, a;
    printf ("введите количество элементов дерева ");
    scanf ("%d", &Q);
    printf ("введите элементы дерева ");
    for (i=0; i<Q ; i++)
    {
        scanf ("%d", &a);
        rb_insert(t, a);
    }

    rb_print(t->root); printf("\n");

    printf ("%d\n", count_nodes (t->root));

    printf ("%d\n", height(t -> root));

    printf ("%d\n", blackHeight(t -> root));

    printf ("%d\n", redHeight(t -> root));

    printf ("%d\n", count_leaves(t -> root) );
    rb_free(t);
    return 0;

}
