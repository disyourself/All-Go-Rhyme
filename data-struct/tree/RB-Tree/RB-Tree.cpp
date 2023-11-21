
#include <bits/types/struct_tm.h>
#include <ios>
#include <iostream>

enum Color
{
    RED = 0,
    BLACK
};


template <typename Type>
struct _RBTNode
{
    Color     color;
    Type      key;
    _RBTNode *left;
    _RBTNode *right;
    _RBTNode *_parent;

    _RBTNode(const Type &x = Type())
    {
        color = RED;
        left = right = _parent = nullptr;
        key                    = x;
    }
};


template <typename Type>
class RBTree
{
    using Node = _RBTNode<Type>;

  public:
    RBTree()
    {
        root = new Node;
    }
    ~RBTree()
    {
        destroy(root);
    }

  public:

    bool Insert(const Type &value)
    {
        Node *parent = nullptr;
        Node *node   = root;

        while (node != nullptr) {
            if (value == node->key) {
                return false;
            }

            parent = node;

            node = (value < node->key)
                       ? node->left
                       : node->right;
        }

        node = new Node(value);
        // 如果根节点位空
        if (parent == nullptr) {
            root          = node;
            root->_parent = nullptr;
        }
        else {
            if (value < parent->key) {
                parent->left = node;
            }
            else {
                parent->right = node;
            }
            node->_parent = parent;
        }

        // adjust balance
        Insert_Fixup(node);
        return true;
    }

  protected:
    // 1. 两个红色不能相连
    void Insert_Fixup(Node *node)
    {
        Node *uncle;
        // 父亲为 红色
        while (node->_parent->color == RED)
        {
            // 父节点为左节点
            if (node->_parent == node->_parent->_parent->left)
            {
                uncle = node->_parent->_parent->right;

                // 叔叔 也是 红色
                if (uncle->color == RED)
                {
                    node->_parent->color = uncle->color = BLACK;
                    node->_parent->_parent              = RED;

                    // 指向 祖父， 判断祖父的祖父是否为红色
                    node = node->_parent->_parent;
                }
                // 没有叔叔或则为黑
                else {
                    if (node == node->_parent->right)
                    {
                        node = node->_parent;
                        LeftRolate(node);
                    }
                    node->_parent->color          = BLACK;
                    node->_parent->_parent->color = RED;
                    RightRotate(node->_parent->_parent);
                }
            }
            // 父亲为 右节点
            else if (node->_parent == node->_parent->_parent->right)
            {
                uncle = node->_parent->_parent->left;

                if (uncle->color == RED) {
                    node->_parent->color = uncle->color = BLACK;

                    node->_parent->_parent = RED;

                    // 指向 祖父， 判断祖父的祖父是否为红色
                    node = node->_parent->_parent;
                }
                else {
                    if (node == node->_parent->left) {
                        node = node->_parent;
                        RightRotate(node);
                    }
                    node->_parent->color   = BLACK;
                    node->_parent->_parent = RED;
                }
            }
        }
    }

  private:
    Node *root;
};
