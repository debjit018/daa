#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

struct TreeNode* insert(struct TreeNode *root, int data);
void inorder(struct TreeNode *root);
void reverseInorder(struct TreeNode *root);

int main() {
    struct TreeNode *root = NULL;
    int n, data, order;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter node data: ");
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Enter 1 for Ascending Order or 2 for Descending Order: ");
    scanf("%d", &order);

    if (order == 1) {
        printf("Sorted Data in Ascending Order: ");
        inorder(root);
    } else {
        printf("Sorted Data in Descending Order: ");
        reverseInorder(root);
    }

    return 0;
}

struct TreeNode* insert(struct TreeNode *root, int data) {
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
        newNode->data = data;
        return newNode;
    }
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void inorder(struct TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void reverseInorder(struct TreeNode *root) {
    if (root != NULL) {
        reverseInorder(root->right);
        printf("%d ", root->data);
        reverseInorder(root->left);
    }
}
