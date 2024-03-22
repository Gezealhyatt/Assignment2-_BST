#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};


struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct Node *insertNode(struct Node *root, int value) {
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    return root;
}


struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


int height(struct Node *root) {
    if (root == NULL)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


void printLevelAndHeight(struct Node *root, int key, int level) {
    if (root == NULL) {
        printf("Node not found in the BST\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
    } else if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}


void freeBST(struct Node *root) {
    if (root == NULL)
        return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

int main() {

    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);


    struct Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insertNode(root, arr[i]);


    printf("Height of the BST: %d\n", height(root));


    int key = 25;
    printf("Node: %d\n", key);
    printLevelAndHeight(root, key, 0);


    int deleteKey = 20;
    root = deleteNode(root, deleteKey);
    printf("Deleted node with key %d\n", deleteKey);


    printf("Height of the BST after deletion: %d\n", height(root));
    freeBST(root);

    return 0;
}
