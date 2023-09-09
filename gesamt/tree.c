#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "list.h"

tree_t *createNode(operators_t op, tree_t *left, tree_t *right)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = op;
    node->kids[0] = left;
    node->kids[1] = right;
    node->identifierName = (char *)NULL;

    return node;
}

tree_t *createIdentifierLeaf(char *name, int kind, int parameterIndex, int offset)
{
    if (kind == KIND_CLASS_VARIABLE)
    {
        return createClassVarIdentifierLeaf(name, offset);
    }
    else if (kind == KIND_PARAMETER)
    {
        return createParamIdentifierLeaf(name, parameterIndex);
    }
    else if (kind == KIND_VARIABLE)
    {
        return createLocalVarIdentifierLeaf(name, offset);
    }

    return NULL;
}

tree_t *createNumericalLeaf(long value)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_NUMBER;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->value = value;
    node->parameterIndex = -1;
    node->localVaroffset = -1;
    node->classVaroffset = -1;

    return node;
}

tree_t *createIfLabelLeaf(char *name)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_IF_ID;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = name;

    return node;
}

tree_t *createNULLLeaf()
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_NULL;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->parameterIndex = -1;
    node->localVaroffset = -1;
    node->classVaroffset = -1;

    return node;
}

tree_t *createClassVarIdentifierLeaf(char *name, int offset)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_CLASS_VAR_ID;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = name;
    node->classVaroffset = offset;
    node->parameterIndex = -1;
    node->localVaroffset = -1;

    return node;
}

tree_t *createLocalVarIdentifierLeaf(char *name, int offset)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_ID;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = name;
    node->classVaroffset = -1;
    node->parameterIndex = -1;
    node->localVaroffset = offset;

    return node;
}

tree_t *createParamIdentifierLeaf(char *name, int parameterIndex)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_PARAM_ID;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = name;
    node->localVaroffset = -1;
    node->parameterIndex = parameterIndex;
    node->classVaroffset = -1;

    return node;
}

tree_t *createNewObjectLeaf(char *className, int numberOfClassVar)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_NEW_OBJ;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = className;
    node->numberOfClassVar = numberOfClassVar;
    node->localVaroffset = -1;
    node->parameterIndex = -1;
    node->classVaroffset = -1;

    return node;
}

tree_t *createMethodLeaf(char *name, int maxParameterIndex)
{
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));

    node->op = OP_EMPTY_METHOD;
    node->kids[0] = (tree_t *)NULL;
    node->kids[1] = (tree_t *)NULL;
    node->identifierName = name;
    node->parameterIndex = maxParameterIndex;
    node->localVaroffset = -1;
    node->classVaroffset = -1;

    return node;
}

#define COUNT 10

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(tree_t *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->kids[1], space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printElem(root);

    // Process left child
    print2DUtil(root->kids[0], space);
}

void printElem(tree_t *root)
{
    if (root->op == OP_RETURN)
    {
        printf("RET : %s\n", root->regStor);
    }
    else if (root->op == OP_ADD)
    {
        printf("+\n");
    }
    else if (root->op == OP_MUL)
    {
        printf("*\n");
    }
    else if (root->op == OP_OR)
    {
        printf("OR\n");
    }
    else if (root->op == OP_GREATER)
    {
        printf(">\n");
    }
    else if (root->op == OP_NOT_EQUAL)
    {
        printf("#\n");
    }
    else if (root->op == OP_NOT)
    {
        printf("NOT\n");
    }
    else if (root->op == OP_NEG)
    {
        printf("- : %s\n", root->regStor);
    }
    else if (root->op == OP_NUMBER)
    {
        printf("%ld : %s\n", root->value, root->regStor);
    }
    else if (root->op == OP_ID)
    {
        printf("ID: %s - %s\n", root->identifierName, root->regStor);
    }
    else if (root->op == OP_PARAM_ID)
    {
        printf("PARAM: %s\n", root->identifierName);
    }
    else if (root->op == OP_CLASS_VAR_ID)
    {
        printf("CVAR: %s\n", root->identifierName);
    }
    else if (root->op == OP_NULL)
    {
        printf("NULLOP\n");
    }
    else if (root->op == OP_ASSIGN)
    {
        printf("ASSIGN\n");
    }
    else if (root->op == OP_COND)
    {
        printf("IF\n");
    }
    else if (root->op == OP_IF_ID)
    {
        printf("ID: %s", root->identifierName);
    }
    else if (root->op == OP_METHOD)
    {
        printf("METHOD: %s", root->regStor);
    }
    else if (root->op == OP_METHOD_EXPR)
    {
        printf("METHOD-PARAM: %s", root->regStor);
    }
    else if (root->op == OP_ONE_METHOD_EXPR)
    {
        printf("ONE METHOD-PARAM: %s", root->regStor);
    }
    else if (root->op == OP_EMPTY_METHOD)
    {
        printf("EMPTY METHOD-PARAM: %s", root->regStor);
    }
    else
    {
        printf("?\n");
    }
}

// Wrapper over print2DUtil()
void print2D(struct tree_t *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

tree_t *createNodeDEV(operators_t op, tree_t *left, tree_t *right)
{
    if (DEBUG == 1)
    {
        print2D(left);
    }
    return createNode(op, left, right);
}