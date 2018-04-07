#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct tagNode
{
    struct tagNode *parent;
    struct tagNode *left_child, *right_child;
    int key;
}Node;

typedef struct tagTree
{
    Node *root;
}Tree;

Node *BST_Search(Node *root, int key)
{
    Node *node;
    assert(NULL != root);

    node = root;
    while(NULL != node)
    {
        if(key == node->key)
        {
            break;
        }
        else if(key > node->key)
        {
            node = node->right_child;
        }
        else
        {
            node = node->left_child;
        }
    }

    return node;
}

Node *BST_Minimum(Node *root)
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

Node *BST_Maximum(Node *root)
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

Node *BST_Predecessor(Node *node)
{
    Node *parent;
    if(NULL == node)
    {
        return NULL;
    }

    if(NULL != node->left_child)
    {
        return BST_Maximum(node->left_child);
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

Node *BST_Successor(Node *node)
{
    Node *parent;
    if(NULL == node)
    {
        return NULL;
    }

    if(NULL != node->right_child)
    {
        return BST_Minimum(node->right_child);
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

void BST_Walk_InOrder(Node *root)
{
    if(NULL != root)
    {
        BST_Walk_InOrder(root->left_child);
        printf("%d  ", root->key);
        BST_Walk_InOrder(root->right_child);
    }
    return;
}

void BST_Walk_PreOrder(Node *root)
{
    if(NULL != root)
    {
        printf("%d  ", root->key);
        BST_Walk_PreOrder(root->left_child);
        BST_Walk_PreOrder(root->right_child);
    }
    return;
}

void BST_Walk_PostOrder(Node *root)
{
    if(NULL != root)
    {
        BST_Walk_PostOrder(root->left_child);
        BST_Walk_PostOrder(root->right_child);
        printf("%d  ", root->key);
    }
    return;
}

void BST_Insert(Tree *tree, Node *new)
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
    
    return;
}

int BST_Delete(Tree *tree, Node *old)
{
    Node *node, *parent, *successor;
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
            node->right_child->parent = NULL;
        }
        else if(NULL == node->right_child)
        {
            tree->root = node->left_child;
            node->left_child->parent = NULL;
        }
        else
        {
            successor = BST_Minimum(node->right_child);
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
            successor->parent = NULL;
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
            successor = BST_Minimum(node->right_child);
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

int BST_Build(Tree *tree, int count, int array[])
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
        BST_Insert(tree, node);
    }
    
    return 0;   
}

void BST_Destroy(Node *root)
{
    if(NULL == root)
    {
        return;
    }
    BST_Destroy(root->left_child);
    BST_Destroy(root->right_child);
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
    
