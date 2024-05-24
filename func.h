#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
typedef enum {RED, BLACK} rb_color;

/* Тип ключа key_t */
typedef int key_t;

/* Узел дерева */
typedef struct rb_node
{
    key_t    key;
    rb_color color;
    /* указатель на левое и правое поддерево, NULL если это nil-узел;
     * указатель на родительский элемент, NULL для корня
     */
    struct rb_node *left, *right, *parent;
} rb_node;

/* Дерево */
typedef struct rb_tree
{
    rb_node *root; /* NULL для пустого дерева из одного nil-узла */
} rb_tree;

/* Создание дерева */
rb_tree *rb_alloc() ;


/** \brief height находит высоту дерева
 *  \param node - указатель на узел
 *  \return высота дерева
 */
int height(rb_node* node);

/** \brief count_nodes считает кол-во элементов
 *  \param root - указатель на узел
 *  \return кол-во элементов
 */
int count_nodes(rb_node *root);


/** \brief blackHeight находит черную высоту
 *  \param node - указатель на узел
 *  \return черная высота
 */

int blackHeight(rb_node* node);

/** \brief redHeight находит красную высоту
 *  \param node - указатель на узел
 *  \return красная высота
 */
int redHeight(rb_node* node);


/** \brief count_leaves находит кол-во листьев
 *  \param root - указатель на узел
 *  \return кол-во листьев
 */
int count_leaves(rb_node *root);

/** \brief max находит максимум
 *  \param а - первое число
 *  \param b - второе чилсло число
 *  \return максимум
 */
int max (int a, int b);


void rb_node_clear (rb_node *n);

void rb_free(rb_tree *t);

rb_node * rb_search (rb_tree *t, key_t key);

rb_node * rb_min (rb_tree *t);

rb_node * rb_max (rb_tree *t);

void rb_rotate_left (rb_tree *t, rb_node *x);

void rb_rotate_right (rb_tree *t, rb_node *x);

rb_node *rb_bst_insert (rb_tree *t, key_t key);

int rb_insert (rb_tree *t, key_t key);

int rb_delete (rb_tree *t, key_t key);

void rb_print(const rb_node *t);

#endif // FUNC_H_INCLUDED
