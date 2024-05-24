#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* ���� ����� */
typedef enum {RED, BLACK} rb_color;

/* ��� ����� key_t */
typedef int key_t;

/* ���� ������ */
typedef struct rb_node
{
    key_t    key;
    rb_color color;
    /* ��������� �� ����� � ������ ���������, NULL ���� ��� nil-����;
     * ��������� �� ������������ �������, NULL ��� �����
     */
    struct rb_node *left, *right, *parent;
} rb_node;

/* ������ */
typedef struct rb_tree
{
    rb_node *root; /* NULL ��� ������� ������ �� ������ nil-���� */
} rb_tree;

/* �������� ������ */
rb_tree *rb_alloc()
{
    rb_tree *r = malloc (sizeof(rb_tree));
    if (!r) return NULL;

    r->root = NULL;
    return r;
}


int count_nodes(rb_node *root)
{
    if (root == NULL)
         return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);

}


int height(rb_node* node)
{
    if (node == NULL) {
        return 0;
    } else {
        int left_height = height(node->left);
        int right_height = height(node->right);
        return 1 + (left_height > right_height ? left_height : right_height);
    }
}

int max (int a, int b)
{
    if (a >= b) return a;
    return (b);
}

int blackHeight(rb_node* node) {
    if (node == NULL) {
        return 1; // ������ ��������� ����� ������ ������ 1
    }
    int leftHeight = blackHeight(node->left);
    int rightHeight = blackHeight(node->right);

    // ���� ���� ������, �� ����������� ������ ������ �� 1
    int height = (node->color == BLACK) ? 1 : 0;

    return height + max(leftHeight, rightHeight); // ���������� ������������ ������ ������ ���������
}

int redHeight(rb_node* node) {
    if (node == NULL) {
        return 0; // ������ ��������� ����� ������ ������ 1
    }
    int leftHeight = redHeight(node->left);
    int rightHeight = redHeight(node->right);

    // ���� ���� ������, �� ����������� ������ ������ �� 1
    int height = (node->color == RED) ? 1 : 0;

    return height + max(leftHeight, rightHeight); // ���������� ������������ ������ ������ ���������
}

typedef struct node {
int key;
int color; // 0 - ������, 1 - �������
struct node *left, *right;
} node;


int count_leaves(node *root)
{
if (!root) { // ���� ������� �� ����������, �� ��� �� ����
return 0;
}
if (!(root->left) && !(root->right)) { // ���� ������� �� ����� ��������, �� ��� ����
return 1;
}
// ���������� ������������� ����� � ������ ��������� � ��������� ����������
return count_leaves(root->left) + count_leaves(root->right);
}

/* ����������� ������� ����������� ���� � ������ ���� */
void rb_node_clear (rb_node *n)
{
    if (!n) return;
    rb_node_clear (n->left);
    rb_node_clear (n->right);
    free(n);
}

/* �������� ������ �� ������ */
void rb_free(rb_tree *t)
{
    rb_node_clear (t->root);
    free(t);
}

rb_node * rb_search (rb_tree *t, key_t key)
{
    rb_node *x = t->root;

    while (x)
    {
        if      (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return x;
    }

    return NULL;
}

rb_node * rb_min (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->left) x = x->left;
    return x;
}

rb_node * rb_max (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->right) x = x->right;
    return x;
}


/* ����� �������� ������ t ������ ���� x */
void rb_rotate_left (rb_tree *t, rb_node *x)
{
    rb_node *y = x->right;         /* ������� ����� ������ ���������                         */
    assert (y);                    /* �������� ����������� ��������, ���������               */
                                   /* ������������ �������� �� ������ ���������� ����������� */

    x->right = y->left;            /* ����� ������� y ���������� ������ �������� x           */
    if (y->left)
        y->left->parent = x;       /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->left = x;                   /* x ���������� ����� �������� y,                         */
    x->parent = y;                 /* � y - ��������� x                                      */
}

/* ������ �������� ������ t ������ ���� x */
void rb_rotate_right (rb_tree *t, rb_node *x)
{
    rb_node *y = x->left;          /* ������� ����� ������ ���������                         */
    assert (y);                    /* �������� ����������� ��������, ���������               */
                                   /* ������������ �������� �� ������ ���������� ����������� */

    x->left = y->right;            /* ������ ������� y ���������� ����� �������� x           */
    if (y->right)
        y->right->parent = x;      /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->right = x;                  /* x ���������� ������ �������� y,                        */
    x->parent = y;                 /* � y - ��������� x                                      */
}

/* ������� �������� � ������ key � ������ t ��� � ������� ������ ������
 * ���������� ��������� �� ����������� ������� ��� NULL � ������ �������
 * ������������� ����� ���������, ���������� NULL ���� ���� ������������
 */
rb_node *rb_bst_insert (rb_tree *t, key_t key)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* ����������� ����                      */
    if (!z) return NULL;

    z->key   = key;
    z->color = RED;                        /* ����������� ���� - �������            */
    z->left  = z->right   = NULL;

    while (x)
    {
        y = x;
        if (z->key == x->key)              /* ���� ��� ������������                 */
        {
            free(z);
            return NULL;
        }
        x = z->key < x->key ? x->left      /* ���������� �� ����� ����� ��� ������  */
                            : x->right;    /* � ����������� �� ����� item           */
    }

    z->parent = y;
    if (!y)                                /* ���� ��������� � ������               */
        t->root = z;
    else
    {
        if (z->key < y->key)               /* ����� ��� ������ �������� ����� z?    */
            y->left = z;
        else
            y->right = z;
    }

    return z;
}

/* ������� �������� � ������ key s � ������ t
 * ���������� 0 � ������ ������, ��������� �������� � ������ �������
 */
int rb_insert (rb_tree *t, key_t key)
{
    rb_node *x = rb_bst_insert(t, key);
    if (!x) return 1;

    /* �������� ���� � ���� x ������� ��������:
     * ��������� x ������������ ����� �� ����� ��� ���� � ������ ���������
     */
    while (x != t->root && x->parent->color == RED)
    {
        /* ������� ���� � ����������� �� ����, �������� �� �������� x
         * ������ ��� ����� �������� ������ ��������
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == RED)              /* ������ "������� ����"                         */
        {
            x->parent->color         = BLACK;  /* ����������                                     */
            y->color                 = BLACK;
            x->parent->parent->color = RED;
            x = x->parent->parent;             /* ����������� x �����                           */
                                               /* ( ������� ����, ��� ��� �������� x - �������, */
                                               /*   � ������ ����� �������� )                   */
        }
        else                                   /* ������ "������ ����"                          */
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {   /* ������ x - ������ �������, � ��� �������� - �����                            */
                x = x->parent;
                rb_rotate_left(t, x);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {   /* ������ x - ����� �������, � ��� �������� - ������     */
                x = x->parent;
                rb_rotate_right(t, x);
            }

            /* ������, ����� ���� �� ������� x � x � ����� �����������  */
            x->parent->color         = BLACK; /* ���������� */
            x->parent->parent->color = RED;
            /* �������� ������ ������� � ����������� �� ����,
             * � ����� ����������� ���� �� ������� � x
             */
            x == x->parent->left ? rb_rotate_right(t, x->parent->parent)
                                 : rb_rotate_left (t, x->parent->parent);
        }
    }

    t->root->color = BLACK;   /* ��������� ������� ������� ����� */
    return 0;
}

/* �������� �������� � ������ key �� ������ t
 * ���������� 0, ���� ������� ������, ��������� ��������, ���� �������� ���
 */
int rb_delete (rb_tree *t, key_t key)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* ��� 1 - �������� �������� �� ������ ������ */

    while (z && z->key != key)
        z = key < z->key ? z->left      /* ���������� �� ����� ����� ��� ������  */
                         : z->right;    /* � ����������� �� �����                */

    if (!z) return -1;                  /* ������� �� ������                     */

    /* ������� ���� y, ������� ����� ���������� ������ �� ������ */
    if (!z->left || !z->right)
         y = z;
    else
    {
        rb_tree r;
        r.root = z->right;
        y = rb_min (&r);

        z->key  = y->key;                /* �������� ����                        */
    }

    /* ������� ������������� ������� ���������� ���������� ���� */

    x = y->left ? y->left : y->right;

    if (!x) /* ���� x - NIL-����, ������������� ��� */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = BLACK;
        x         = n;
    }

    x->parent = y->parent;               /* x ����� ����� �������� �������� y   */

    if (!y->parent)                      /* ���� ��������� ������               */
        t->root = x;                     /* ������������� ������                */
    else                                 /* ����� ��������� ����� �������       */
    {                                    /* �������� ���������� ����            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == BLACK)               /* ���� ������ ������ �������,         */
    {                                    /* ���� ������������ RB-��������       */
        /* x ����������� "������ ������ ��������", ��� ��������� � ������
         * x ������ ����� ��������� �� ������ ������ �������, ���������� ����� �� �����
         *   ��� ���� �� �������� ������� ��������
         */
        while (x != t->root && x->color == BLACK)
        {
            rb_node *w = x == x->parent->left ? x->parent->right /* w - ����    */
                                              : x->parent->left; /* ������� x   */

            if (w->color == RED)                   /* ������ "���� - �������"   */
            {
                w->color         = BLACK;          /* ����������                */
                x->parent->color = RED;

                if (x == x->parent->left)          /* ������ ������� � ����� w  */
                {                                  /* � ����������� �� ����,    */
                    rb_rotate_left(t, x->parent);  /* ����� ��� ������ �������� */
                    w = x->parent->right;          /* �������� x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == BLACK) &&
                (!w->right || w->right->color == BLACK)
               )                                   /* ������ "��� ���������� --- ������"     */
            {                                      /* � �.�. NIL-���� ��������� ������       */
                w->color = RED;                    /* ���������� � ����� x                   */
                x = x->parent;                     /* ��������� ������� �������� x           */
                if (x->color == RED)               /* ���� �� ��� ������� - ���������� ����� */
                {
                    x->color = BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == BLACK))
                   ) /* ������ "��������������� ��������� ������" */
                {
                    w->color = RED;
                    if (x == x->parent->left)
                    {
                        w->left->color = BLACK;
                        rb_rotate_right(t, w);
                        w = x->parent->right;
                    }
                    else
                    {
                        w->right->color = BLACK;
                        rb_rotate_left(t, w);
                        w = x->parent->left;
                    }
                }
                /* ������ "������� ��������� ������" */
                w->color         = x->parent->color;
                x->parent->color = BLACK;

                if (x == x->parent->left)
                {
                    w->right->color = BLACK;
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    w->left->color = BLACK;
                    rb_rotate_right(t, x->parent);
                }

                x = t->root;   /* ����� �� ����� */
            }
        }

        x->color = BLACK;
    }

    free (y);  /* ������� ������� �� ������ */
    if (n)     /* ��������� � �������       */
    {
        if (n == t->root)                  /* ���� �������� ��������� ������� */
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left  = NULL;
            else
                n->parent->right = NULL;
        }
        free (n);
    }
    return 0;

}


void rb_print(const rb_node *t)
{
    if (t)
    {
        rb_print(t->left);

        printf ("%i (%s, ", t->key, t->color == RED ? "RED" : "BLACK");
        if (t->parent) printf("parent = %i) ", t->parent->key); else printf("root) ");

        rb_print(t->right);
    }
}


