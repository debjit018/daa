#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

struct TreeNode* insert(struct TreeNode *root, int data);
struct TreeNode* deleteNode(struct TreeNode *root, int data);
struct TreeNode* search(struct TreeNode *root, int data);
struct TreeNode* findMin(struct TreeNode *root);
void inorder(struct TreeNode *root);

int main() {
    struct TreeNode *root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu: \n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Search an element\n");
        printf("4. Inorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Enter the element to search: ");
                scanf("%d", &data);
                struct TreeNode *result = search(root, data);
                if (result != NULL)
                    printf("Element %d found in the tree.\n", data);
                else
                    printf("Element %d not found in the tree.\n", data);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

struct TreeNode* insert(struct TreeNode *root, int data) {
    if (root == NULL) {
        struct TreeNode *newNode = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
        newNode->data = data;
        return newNode;
    }
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

struct TreeNode* deleteNode(struct TreeNode *root, int data) {
    if (root == NULL) return NULL;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

struct TreeNode* findMin(struct TreeNode *root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct TreeNode* search(struct TreeNode *root, int data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
    return search(root->right, data);
}

void inorder(struct TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
