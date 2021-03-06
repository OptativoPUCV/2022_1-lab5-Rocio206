#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode
{
    Pair *pair;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
};

struct TreeMap
{
    TreeNode *root;
    TreeNode *current;
    int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2)
{
    if (tree->lower_than(key1, key2) == 0 &&
        tree->lower_than(key2, key1) == 0)
        return 1;
    else
        return 0;
}

TreeNode *createTreeNode(void *key, void *value)
{
    TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
        return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2))
{
    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    map->lower_than = lower_than;
    map->root = NULL;
    map->current = map->root;

    return map;
}

void insertTreeMap(TreeMap *tree, void *key, void *value)
{
    tree->current = tree->root;

    while (tree->current != NULL)
    {

        if (is_equal(tree, key, tree->current->pair->key) == 1)
            return;
        else
        {
            if (tree->lower_than(tree->current->pair->key, key) == 1)
            {
                if (tree->current->right == NULL)
                    break;
                tree->current = tree->current->right;
            }
            else
            {
                if (tree->current->left == NULL)
                    break;
                tree->current = tree->current->left;
            }
        }
    }
    if (tree->lower_than(tree->current->pair->key, key) == 1)
    {
        tree->current->right = createTreeNode(key, value);
        tree->current->right->parent = tree->current;
        tree->current = tree->current->right;
    }
    else
    {
        tree->current->left = createTreeNode(key, value);
        tree->current->left->parent = tree->current;
        tree->current = tree->current->left;
    }
}

TreeNode *minimum(TreeNode *x)
{
    if (x == NULL)
        return NULL;
    while (x->left != NULL)
    {
        x = x->left;
    }

    return x;
}

void removeNode(TreeMap *tree, TreeNode *node)
{

    if (node == tree->root)
    {
        tree->root = NULL;
        free(node);
        return;
    }
    if (node->left != NULL && node->right != NULL)
    { // dos hijos

        TreeNode *min = minimum(node->right);
        node->pair = min->pair;
        removeNode(tree, min);
    }
    else if (node->left == NULL && node->right == NULL)
    { /// ningun hijo
        if (node == node->parent->left)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
    }
    else // un hijo
    {
        if (tree->lower_than(node->pair->key, node->parent->pair->key) == 1)
        {

            if (node->left != NULL)
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else
            {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }
        }
        else
        {

            if (node->left != NULL)
            {

                node->left->parent = node->parent;
                node->parent->left = node->left;
                //printf("key hijo iz despues %d******", *(int *)node->parent->left->pair->key);
            }
            else
            {
                //printf("key hijo der %d******", *(int *)node->right->pair->key);
                node->right->parent = node->parent;
                node->parent->left = node->right;
            }
            free(node);
        }
    }
}

void eraseTreeMap(TreeMap *tree, void *key)
{
    if (tree == NULL || tree->root == NULL)
        return;

    if (searchTreeMap(tree, key) == NULL)
        return;
    TreeNode *node = tree->current;
    removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key)
{
    tree->current = tree->root;
    while (tree->current != NULL)
    {
        if (is_equal(tree, key, tree->current->pair->key) == 1)
        {
            // printf("--------%d_---------",tree->current->pair->key);
            return tree->current->pair;
        }

        else
        {
            if (tree->lower_than(tree->current->pair->key, key) == 1)
                tree->current = tree->current->right;

            else
                tree->current = tree->current->left;
        }
    }

    return NULL;
}

Pair *upperBound(TreeMap *tree, void *key)
{

    return NULL;
}

Pair *firstTreeMap(TreeMap *tree)
{

    tree->current = tree->root;

    while (tree->current->left != NULL)
    {
        tree->current = tree->current->left;
    }
    return tree->current->pair;
}

Pair *nextTreeMap(TreeMap *tree)
{
    if (tree->current->right != NULL)
    {
        // printf("key current->right : %d\n", *(int *)tree->current->right->pair->key);
        // printf("key minimum : %d\n", *(int *)minimum(tree->current->right)->pair->key);

        return minimum(tree->current->right)->pair;
    }
    // printf("key current : %d", *(int *)tree->current->pair->key);
    while (tree->lower_than(tree->current->parent, tree->current) == 1)
    {
        tree->current = tree->current->parent;
    }
    // printf("key current luego del ciclo : %d", *(int *)tree->current->pair->key);

    return tree->current->pair;
}
