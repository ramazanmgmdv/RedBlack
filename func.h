#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
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
rb_tree *rb_alloc() ;


/** \brief height ������� ������ ������
 *  \param node - ��������� �� ����
 *  \return ������ ������
 */
int height(rb_node* node);

/** \brief count_nodes ������� ���-�� ���������
 *  \param root - ��������� �� ����
 *  \return ���-�� ���������
 */
int count_nodes(rb_node *root);


/** \brief blackHeight ������� ������ ������
 *  \param node - ��������� �� ����
 *  \return ������ ������
 */

int blackHeight(rb_node* node);

/** \brief redHeight ������� ������� ������
 *  \param node - ��������� �� ����
 *  \return ������� ������
 */
int redHeight(rb_node* node);


/** \brief count_leaves ������� ���-�� �������
 *  \param root - ��������� �� ����
 *  \return ���-�� �������
 */
int count_leaves(rb_node *root);

/** \brief max ������� ��������
 *  \param � - ������ �����
 *  \param b - ������ ������ �����
 *  \return ��������
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
