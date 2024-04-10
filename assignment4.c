#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node *left, *right;
};


struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}


int search(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}


struct Node* constructUtil(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;


    struct Node* node = newNode(post[*postIndex]);
    (*postIndex)--;


    if (inStart == inEnd)
        return node;

    int inIndex = search(in, inStart, inEnd, node->data);


    node->right = constructUtil(in, post, inIndex + 1, inEnd, postIndex);
    node->left = constructUtil(in, post, inStart, inIndex - 1, postIndex);

    return node;
}


struct Node* bst_construct(int in[], int post[], int n) {
    int postIndex = n - 1;
    return constructUtil(in, post, 0, n - 1, &postIndex);
}


void bfs_traversal(struct Node* root) {
    if (root == NULL)
        return;


    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* tempNode = queue[front++];
        printf("%d ", tempNode->data);

        if (tempNode->left)
            queue[rear++] = tempNode->left;

        if (tempNode->right)
            queue[rear++] = tempNode->right;
    }
}

int main() {
    int in[] = {5, 10, 15, 20, 25, 30, 45};
    int post[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(in) / sizeof(in[0]);

    struct Node* root = bst_construct(in, post, n);

    printf("Breadth-first-search (DFS) traversal:\n");
    bfs_traversal(root);

    return 0;
}

