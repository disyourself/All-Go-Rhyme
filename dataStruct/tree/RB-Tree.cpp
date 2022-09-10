
/**
 * @brief Red Black Tree
 *
 */


#include <vcruntime.h>

#include <iostream>


using std::cout;

enum RBTColor
{
    RED,
    BLACK
};

template <class T>
class RBTNODE
{
  public:
    RBTColor color;
    T        key;
    RBTNODE *left;
    RBTNODE *right;
    RBTNODE *parent;

    RBTNODE (T value, RBTColor c, RBTNODE *p, RBTNODE *l, RBTNODE *r)
        : key (value), color (c), parent (p), left (l), right (r) {}
};

template <class T>
class RBTree
{
  private:
    RBTNODE<T> *mRoot;

  public:
    RBTree ();
    ~RBTree ();

  public:
    /* traversal */
    void preOrder ();
    void inOrder ();
    void postOrder ();

    RBTNODE<T> *search (T key);          // recursive find node by key
    RBTNODE<T> *iterativeSearch (T key); // none-recursive

    T maximum (); // return key of min node
    T minimum ();

    // find successor(前驱) node, that (key >= x->key)'s min node
    RBTNODE<T> *successor (RBTNODE<T> *x);
    RBTNODE<T> *predecessor (RBTNODE<T> *x);

    void insert (T key);
    void remove (T key);

    void destory ();
    void print ();

  private:
    /* traversal */
    void preOrder (RBTNODE<T> *tree) const;
    void inOrder (RBTNODE<T> *tree) const;
    void postOrder (RBTNODE<T> *tree) const;

    RBTNODE<T> *search (RBTNODE<T> *x, T key) const;          // recursive find node by key
    RBTNODE<T> *iterativeSearch (RBTNODE<T> *x, T key) const; // none-recursive

    RBTNODE<T> *minimum (RBTNODE<T> *tree); // return key of min node
    RBTNODE<T> *maximum (RBTNODE<T> *tree);

    void leftRotate (RBTNODE<T> *&root, RBTNODE<T> *x);
    void rightRotate (RBTNODE<T> *&root, RBTNODE<T> *y);

    void insert (RBTNODE<T> *&root, RBTNODE<T> *node);
    void insertFixUp (RBTNODE<T> *&root, RBTNODE<T> *node, RBTNODE<T> *parent);

    void destory (RBTNODE<T> *&tree);
    void print (RBTNODE<T> *&tree, T key, int direction);

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)

#define rb_set_black(r)     \
    do {                    \
        (r)->color = BLACK; \
    } while (0)

#define rb_set_red(r)     \
    do {                  \
        (r)->color = RED; \
    } while (0)

#define rb_set_parent(r, p) \
    do {                    \
        (r)->parent = (p);  \
    } while (0)
};

template <class T>
RBTree<T>::RBTree () : mRoot (nullptr)
{
    mRoot = nullptr;
}
template <class T>
RBTree<T>::~RBTree ()
{
    destory ();
}

/* Preorder */
template <class T>
void
RBTree<T>::preOrder (RBTNODE<T> *tree) const
{
    if (tree != nullptr) {
        cout << tree->key << " ";
        preOrder (tree->left);
        preOrder (tree->right);
    }
}
template <class T>
void
RBTree<T>::preOrder ()
{
    preOrder (mRoot);
}
/* Inorder */
template <class T>
void
RBTree<T>::inOrder (RBTNODE<T> *tree) const
{
    if (tree != nullptr) {
        preOrder (tree->left);
        cout << tree->key << " ";
        preOrder (tree->right);
    }
}
template <class T>
void
RBTree<T>::inOrder ()
{
    ineOrder (mRoot);
}
/*  Postorder */
template <class T>
void
RBTree<T>::postOrder (RBTNODE<T> *tree) const
{
    if (tree != nullptr) {
        preOrder (tree->left);
        preOrder (tree->right);
        cout << tree->key << " ";
    }
}
template <class T>
void
RBTree<T>::postOrder ()
{
    postOrder (mRoot);
}


// recursively find node by KEY
template <class T>
RBTNODE<T> *
RBTree<T>::search (RBTNODE<T> *x, T key) const
{
    // ????????????
    if (x == nullptr || x->left, key)
        return x;
    if (key < x->key)
        return search (x->left, key);
    else
        return search (x->right, key);
    for (int i = 0; i < 5; i++) {
    }
}

template <class T>
RBTNODE<T> *
RBTree<T>::search (T key)
{
    return search (mRoot, key);
}
// iteratively find node by KEY
template <class T>
RBTNODE<T> *
RBTree<T>::iterativeSearch (RBTNODE<T> *x, T key) const
{
    while (x != nullptr && x->key != key) {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}
template <class T>
RBTNODE<T> *
RBTree<T>::iterativeSearch (T key)
{
    return iterativeSearch (mRoot, key);
}


// Find minimun node while tree as root
template <class T>
RBTNODE<T> *
RBTree<T>::minimum (RBTNODE<T> *tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree;
}
template <class T>
T
RBTree<T>::minimum ()
{
    return minimum (mRoot);
}
template <class T>
RBTNODE<T> *
RBTree<T>::maximum (RBTNODE<T> *tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->right != nullptr) {
        tree = tree->right;
    }
    return tree;
}
template <class T>
T
RBTree<T>::maximum ()
{
    return maximum (mRoot);
}


template <class T>
RBTNODE<T> *
RBTree<T>::successor (RBTNODE<T> *x)
{
    // if x has rchild, so its successor is rchild's min node
    if (x->right != nullptr)
        return minimum (x->right);

    // if dosen't has rchild, there are 2 possiblities:
    // 1. x is a RIGHT child, so x's successor is x's parent
    // 2. x is a LEFT child, find x's MIN parent node and it must has left child
    RBTNODE<T> *y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = x->parent;
    }
    return y;
}


template <class T>
void
RBTree<T>::leftRotate (RBTNODE<T> *&root, RBTNODE<T> *x)
{
    RBTNODE<T> *y = x->right;
    x->right      = y->left;
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left   = x;
    x->parent = y;
}
template <class T>
void
RBTree<T>::rightRotate (RBTNODE<T> *&root, RBTNODE<T> *y)
{
    RBTNODE<T> *x = y->left;
    y->left       = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else {
        if (y->parent->right == y)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right  = y;
    y->parent = x;
}

template <class T>
void
RBTree<T>::insertFixUp (RBTNODE<T> *&root, RBTNODE<T> *node)
{
    RBTNODE<T> *parent, *gparent;

    while ((parent = rb_parent (node) && rb_is_red (parent)))
    {
        gparent = rb_parent (parent);

        if (parent == gparent->left)
        {
            {
                RBTNODE<T> *uncle = gparent->right;
                if (uncle && rb_is_red (uncle))
                {
                    rb_set_black (uncle);
                    rb_set_black (parent);
                    rb_set_red (gparent);
                    continue;
                }
            }
            if (parent->right == node) {
                RBTNODE<T> *tmp;
                leftRotate (root, parent);
                tmp    = parent;
                parent = node;
                node   = tmp;
            }

            rb_set_black (parent);
            rb_set_red (gparent);
            rightRotate (root, gparent);
        }
        else {
            {
                RBTNODE<T> *unc =
            }
        }
    }
}


int
main ()
{
    RBTree<int> rbt;
}