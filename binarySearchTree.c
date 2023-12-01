#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
    int value;
    struct node_ *left;
    struct node_ *right;
} tree;

tree *search(tree *root, int value){
    if(root == NULL || root->value == value){
        return root;
    }
    
    if(value > root->value){
        return search(root->right, value);
    }else{
        return search(root->left, value);
    }
}

tree *insertNode(tree *root, tree *node){
    if(root == NULL){
        return node;
    }

    if(node->value > root->value){
        root->right = insertNode(root->right, node);
    }else{
        root->left = insertNode(root->left, node);
    }
    return root;
}

tree *searchParent(tree *root, tree *node){
    if(root == node){
        return NULL;
    }

    if(root->left == node || root->right == node){
        return root;
    }

    if(node->value > root->value){
        return searchParent(root->right, node);
    }else{
        return searchParent(root->left, node);
    }
}

tree *removeRoot(tree *root){
    tree *p, *q;
    if(root->left == NULL){
        q = root->right;
        free(root);
        return q;
    }

    p = root;
    q = root->left;

    while(q->right !=NULL){
        p = q;
        q = q->right;
    }

    if(p != root){
        p->right = q->left;
        q->left = root->left;
    }
    q->right = root->right;
    free(root);
    return q;

}

tree *removeNode(tree *root, int value){
    tree *node = search(root, value);

    if(node!=NULL){
        tree *parent = searchParent(root, node);
        if(parent != NULL){
            if(parent->left == node){
                parent->left = removeRoot(node);
            }else{
                parent->right = removeRoot(node);
            }
        }else{
            root = removeRoot(root);
        }
    }
    return root;
}

tree *createNode(int value)
{
    tree *new_node = (tree *)malloc(sizeof(tree));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void printInOrder(tree *root){
    if(root){
        if(root->left != NULL){
            printInOrder(root->left);
        }
        printf("%d ", root->value);
        if(root->right != NULL){
            printInOrder(root->right);
        }
    }
}

void printPreOrder(tree *root){
    if(root){
        printf("%d ", root->value);
        if(root->left != NULL){
            printPreOrder(root->left);
        }
        if(root->right != NULL){
            printPreOrder(root->right);
        }
    }
}
void printPostOrder(tree *root){
    if(root){
        if(root->left != NULL){
            printPostOrder(root->left);
        }
        if(root->right != NULL){
            printPostOrder(root->right);
        }
        printf("%d ", root->value);
    }
}



void freeTree(tree *root)
{
    if (root != NULL)
    {
        if (root->left != NULL)
        {
            freeTree(root->left);
        }
        if (root->right != NULL)
        {
            freeTree(root->right);
        }
        free(root);
    }
}




void readOption(int *answer)
{
    printf("\n-----------------------\n");
    printf("Choose one of these options:\n");
    printf("0 - exit\n");
    printf("1 - insert\n");
    printf("2 - remove\n");
    printf("3 - print\n");
    scanf("%d", answer);
    printf("-----------------------\n");
}

int main()
{
    tree *root = NULL;

    int answer = 1;

    while (answer != 0)
    {
        readOption(&answer);
        if (answer == 0)
        {
            freeTree(root);
        }
        else if (answer == 1)
        {
            printf("value to be inserted: ");
            int value;
            scanf("%d", &value);
            if (search(root, value) == NULL)
            {
                tree *new_node = createNode(value);
                root = insertNode(root, new_node);
            }
        }

        else if (answer == 2)
        {
            int value;
            printf("value to be removed: ");
            scanf("%d", &value);
            root = removeNode(root, value);
        }
        else if (answer == 3)
        {
            int order;
            printf("\t1 - preorder\n\t2 - inorder\n\t3 - postorder\n");
            scanf(" %d", &order);
            printf("\n-----------------------\n");
            if (order == 1)
            {
                printPreOrder(root);
            }
            else if (order == 2)
            {
                printInOrder(root);
            }
            else if (order == 3)
            {
                printPostOrder(root);
            }
            else
            {
                printf("Invalid Option.\n");
            }
        }
        else
        {
            printf("Invalid Option.\n");
        }
    }

    return 0;
}

