/* 
author: wanzaiqidao@163.com
Description: write api for red black tree.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum tagColor
{
    RED,
    BLACK
}Color;
    
typedef struct tagNode
{
    struct tagTree *parent;
    struct tagTree *left_child, *right_child;
    int key;
    Color color;
}Node;

typedef struct tagTree
{
    Node *root;
}Tree;

Node *RB_Search(Node *root, int key)
{
    Node *node;

    node = root;
    while(T.nil != node)
    {
        if(key > node->key)
        {
            node = node->right_child;
        }
        else if(key < node->key)
        {
            node = node->left_child;
        }
        else
        {
            break;
        }
    }
    
    return node;
}

Node *RB_Minimum(Node *root)
{
    Node *node;

    if(NULL == root)
    {
        return NULL;
    }
    node = root;
    while(NULL != node->left_child)
    {
        node = node->left_child;
    }

    return node;
}

Node *RB_Maximum(Node *root)
{
    Node *node;

    if(NULL == node)
    {
        return NULL;
    }
    node = root;
    while(NULL != node->right_child)
    {
        node = node->right_child;
    }
    return node;
}

Node *RB_Predecessor(Node *node)
{
    Node *parent;
    if(NULL == node)
    {
        return NULL;
    }

    if(NULL != node->left_child)
    {
        return RB_Maximum(node->left_child);
    }
    else
    {
        parent = node->parent;
        while((NULL != parent) && (node == parent->left_child))
        {
            parent = parent->parent;
        }
        return parent;
    }
}

Node *RB_Successor(Node *node)
{
    Node *parent;
    if(NULL == node)
    {
        return NULL;
    }

    if(NULL != node->right_child)
    {
        return RB_Minimum(node->right_child);
    }
    else
    {
        parent = node->parent;
        while((NULL != parent) && (node == parent->right_child))
        {
            parent = node->parent;
        }
        return parent;
    }
}

void RB_Walk_InOrder(Node *root)
{
    if(NULL != root)
    {
        RB_Walk_InOrder(root->left_child);
        printf("%d  ", root->key);
        RB_Walk_InOrder(root->right_child);
    }
    return;
}

void RB_Walk_PreOrder(Node *root)
{
    if(NULL != root)
    {
        printf("%d  ", root->key);
        RB_Walk_PreOrder(root->left_child);
        RB_Walk_PreOrder(root->right_child);
    }
    return;
}

void RB_Walk_PostOrder(Node *root)
{
    if(NULL != root)
    {
        RB_Walk_PostOrder(root->left_child);
        RB_Walk_PostOrder(root->right_child);
        printf("%d  ", root->key);
    }
    return;
}

void RB_Rotate_Left(Tree *tree, Node *node)
{
    Node *parent, *left, *right;
    assert(NULL != tree);
    assert(NULL != node);

    parent = node->parent;
    right = node->right_child;
    assert(NULL != right);
    left = right->left_child;

    right->left_child = node;
    right->parent = parent;
    node->parent = right;
    node->right_child = left;
    if(NULL != left)
    {
        left->parent = node;
    }
    if(NULL != parent)
    {
        if(node == parent->left_child)
        {
            parent->left_child = right;
        }
        else
        {
            parent->right_child = right;
        }
    }
    else
    {
        tree->root = right;
    }

    return;
}

void RB_Rotate_Right(Tree *tree, Node *node)
{
    Node *parent, *left, *right;
    assert(NULL != tree);
    assert(NULL != node);

    left = node->left_child;
    assert(NULL != left);     
    right = left->right_child;
    left->right_child = node;
    parent = node->parent;
    node->parent = left;

    node->left_child = right;
    if(NULL != right)
    {
        right->parent = node;
    }

    left->parent = parent;
    if(NULL != parent)
    {
        if(node == parent->left_child)
        {
            parent->left_child = left;
        }
        else
        {
            parent->right_child = left;
        }
    }
    else
    {
        tree->root = left;
    }

    return;
}

void RB_Insert_Fixup(Tree *tree, Node *new)
{
    Node *left, *right, *brother, *parent, *uncle;
    assert(NULL != tree);
    assert(NULL != new);

    if(new == tree->root)
    {
        new->color = BLACK;
        return;
    }
    
    parent = new->parent;
    while(RED == parent->color)
    {
        if(parent == parent->parent->left_child)
        {
            uncle = parent->parent->right_child;
            if(RED == uncle->color)
            {
                parent->color = BLACK;
                uncle->color  = BLACK;
                parent->parent->color = RED;
                new = parent->parent;
            }
            else if(new == parent->left_child)
            {
                parent->parent->color = RED;
                parent->color = BLACK;
                RB_Rotate_Right(tree, parent->parent);
                break;
            }
            else
            {
                new = parent;
                RB_Rotate_Left(tree, parent);
            }
        }
        else
        {
            uncle = parent->parent->left_child;
            if(RED == uncle->color)
            {
                parent->color = BLACK;
                uncle->color  = BLACK;
                parent->parent->color = RED;
                new = parent->parent;
            }
            else if(new == parent->right_child)
            {
                parent->parent->color = RED;
                parent->color = BLACK;
                RB_Rotate_Left(tree, parent->parent);
                break;
            }
            else
            {
                new = parent;
                RB_Rotate_Right(tree, parent);
            }
        }

        parent = new->parent;
        if(NULL == parent)
        {
            break;
        }
    }
    
    tree->root->color = BLACK;
    return;
}

void RB_Insert(Tree *tree, Node *new)
{
    Node *node, *parent;
    assert(NULL != tree);
    
    if(NULL == tree->root)
    {
        tree->root = new;
        return;
    }

    node = tree->root;
    while(NULL != node)
    {
        parent = node;
        if(new->key > node->key)
        {
            node = node->right_child;
        }
        else
        {
            node = node->left_child;
        }
    }

    if(new->key > parent->key)
    {
        parent->right_child = new;
        new->parent = parent;
    }
    else
    {
        parent->left_child = new;
        new->parent = parent;
    }
    
    RB_Insert_Fixup(tree, new);
    return;
}

void RB_Delete_Fixup(Tree *tree, Node *old)
{
    Node *parent, *left, *right, *brother;
    assert(NULL != tree);
    assert(NULL != old);

    while((BLACK == old->color) && (old != tree->root))
    {
        parent = old->parent;
        if(old == parent->left_child)
        {
            brother = parent->right_child;
            left    = brother->left_child;
            right   = brother->right_child;
            
            if(RED == brother->color)
            {
                brother->color = BLACK;
                parent->color  = RED;
                RB_Rotate_Left(tree, parent);
                brother = parent->right_child;
            }
            else if((BLACK == left->color) && (BLACK == right->color))
            {
                old->color = RED;
                brother->color = RED;
                old = parent;
            }
            else if(RED == right->color)
            {
                right->color   = BLACK;
                brother->color = parent->color;
                parent->color  = BLACK;
                RB_Rotate_Left(tree, parent);
                break;
            }
            else
            {
                left->color    = BLACK;
                brother->color = RED;
                RB_Rotate_Right(tree, brother);
            }
        }
        else
        {
            brother = parent->left_child;
            left    = brother->left_child;
            right   = brother->right_child;
            
            if(RED == brother->color)
            {
                brother->color = BLACK;
                parent->color  = RED;
                RB_Rotate_Right(tree, parent);
                brother = parent->left_child;
            }
            else if((BLACK == left->color) && (BLACK == right->color))
            {
                old->color = RED;
                brother->color = RED;
                old = parent;
            }
            else if(RED == left->color)
            {
                left->color = BLACK;
                brother->color = parent->color;
                parent->color  = BLACK;
                RB_Rotate_Right(tree, parent);
                break;
            }
            else
            {
                right->color   = BLACK;
                brother->color = RED;
                RB_Rotate_Left(tree, brother);
            }
        }
    }
    
    old->color = BLACK;
    return;
}

int RB_Delete(Tree *tree, Node *old)
{
    Node *node, *parent, *successor, *replace;
    Color original_color;
    assert(NULL != tree);

    node = tree->root;
    while(NULL != node)
    {
        if(old->key > node->key)
        {
            node = node->right_child;
        }
        else if(old->key < node->key)
        {
            node = node->left_child;
        }
        else
        {
            break;
        }
    }

    if(NULL == node)
    {
        return -1;
    }

    parent = node->parent;
    if(NULL == parent)
    { 
        if((NULL == node->left_child) && (NULL == node->right_child))
        {
            tree->root = NULL;
        }
        else if(NULL == node->left_child)
        {
            tree->root = node->right_child;
            tree->root->color = BLACK;
            node->right_child->parent = NULL;
        }
        else if(NULL == node->right_child)
        {
            tree->root = node->left_child;
            tree->root->color = BLACK;
            node->left_child->parent = NULL;
        }
        else
        {
            successor = RB_Minimum(node->right_child);
            original_color = successor->color;
            replace = successor->right_child;
            if(successor != node->right_child)
            {
                if(NULL != successor->right_child)
                {
                    successor->parent->left_child = successor->right_child;
                    successor->right_child->parent = successor->parent;
                }
                else
                {
                    successor->parent->left_child = NULL;
                }
                successor->right_child = node->right_child;
                node->right_child->parent = successor;
            }
            successor->left_child = node->left_child;
            node->left_child->parent = successor;
            tree->root = successor;
            tree->root->color = BLACK;
            successor->parent = NULL;
            if((BLACK == original_color) && (NULL != replace))
            
        }
    }
    else
    { 
        if((NULL == node->left_child) && (NULL == node->right_child))
        {
            if(node == parent->left_child)
            {
                parent->left_child = NULL;
            }
            else
            {
                parent->right_child = NULL;
            }
        }
        else if(NULL == node->left_child)
        {
            if(node == parent->left_child)
            {
                parent->left_child = node->right_child;
                node->right_child->parent = parent;
            }
            else
            {
                parent->right_child = node->right_child;
                node->right_child->parent = parent;
            }
        }
        else if(NULL == node->right_child)
        {
            if(node == parent->left_child)
            {
                parent->left_child = node->left_child;
                node->left_child->parent = parent;
            }
            else
            {
                parent->right_child = node->left_child;
                node->left_child->parent = parent;
            }
        }
        else
        {
            successor = RB_Minimum(node->right_child);
            if(successor != node->right_child)
            {
                if(NULL != successor->right_child)
                {
                    successor->parent->left_child = successor->right_child;
                    successor->right_child->parent = successor->parent;
                }
                else
                {
                    successor->parent->left_child = NULL;
                }
                successor->right_child = node->right_child;
                node->right_child->parent = successor;
            }
            successor->left_child = node->left_child;
            node->left_child->parent = successor;
            if(node == parent->left_child)
            {
                parent->left_child = successor;
            }
            else
            {
                parent->right_child = successor;
            }
            successor->parent = parent;
        }
    }
    free(node);
    
    return 0;
}

int RB_Build(Tree *tree, int count, int array[])
{
    int index;
    Node *node;
    assert(NULL != tree);
    assert(NULL != array);
    
    for(index=0; index<count; index++)
    {
        node = (Node *)malloc(sizeof(Node));
        if(NULL == node)
        {
            return -1;
        }
        memset(node, 0, sizeof(Node));
        node->key = array[index];
        RB_Insert(tree, node);
    }
    
    return 0;   
}

void RB_Destroy(Node *root)
{
    if(NULL == root)
    {
        return;
    }
    RB_Destroy(root->left_child);
    RB_Destroy(root->right_child);
    free(root);
    return;
}

int main(int argc, char *argv[])
{
    Tree *tree;
    int index, tmp, *array, ret;
    Node *node;
    assert(argc > 1);

    tree = (Tree *)malloc(sizeof(Tree));
    if(NULL == tree)
    {
        return -1;
    }
    memset(tree, 0, sizeof(Tree));

    array = (int *)malloc(sizeof(int)*(argc-1));
    if(NULL == array)
    {
        free(tree);
        return -1;
    }
    memset(array, 0, sizeof(int)*(argc-1));
    
    for(index=1; index<argc; index++)
    {
        array[index-1] = atoi(argv[index]);
    }
    ret = BST_Build(tree, argc-1, array);
    if(-1 == ret)
    {
        BST_Destroy(tree->root);
        free(tree);
    }

    printf("The sequence is:\n");
    BST_Walk_InOrder(tree->root);
    printf("\n");

    node = BST_Maximum(tree->root);
    if(NULL != node)
    {
        printf("The maximum is:%d\n", node->key);
    }
    node = BST_Predecessor(node);
    if(NULL != node)
    {
        printf("The predecessor is:%d\n", node->key);
    }

    node = BST_Minimum(tree->root);
    if(NULL != node)
    {
        printf("The minimum is:%d\n", node->key);
    }
    node = BST_Successor(node);
    if(NULL != node)
    {
        printf("The successor is:%d\n", node->key);
    }

    tmp = array[(argc-1)/2];
    node = BST_Search(tree->root, tmp);
    if(NULL != node)
    {
        printf("delete a node whose key is %d\n", node->key);
        BST_Delete(tree, node);
        printf("the new sequence is:\n");
        BST_Walk_InOrder(tree->root);
        printf("\n");
    }

    BST_Destroy(tree->root);
    free(tree);
    free(array);

    return 0;
}