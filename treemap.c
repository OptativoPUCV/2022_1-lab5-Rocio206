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
}

TreeNode *minimum(TreeNode *x)
{

    return NULL;
}

void removeNode(TreeMap *tree, TreeNode *node)
{
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
    while (tree->current->left != NULL && tree->current->right != NULL){
        if (is_equal(tree, key, tree->current->pair->key) == 1) return tree->current->pair;
    
        else{
            if (tree->lower_than(tree->current->pair->key, key) == 0) tree->current = tree->current->right; 
    
            else tree->current = tree->current->right;
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
    return NULL;
}

Pair *nextTreeMap(TreeMap *tree)
{
    return NULL;
}
