#include <stdio.h>
#include <stdlib.h>

// Define the structure of a tree node
struct Node {
    int key;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Find the minimum value node in a subtree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root; // Base case: if tree is empty

    // Traverse the tree to find the node to delete
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            // Node with only right child or no child
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Node with only left child
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);

        // Copy the inorder successor's value to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Insert a new node into the BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return createNode(key); // Base case: create a new node

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

// Inorder traversal of the BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Driver program
int main() {
    struct Node* root = NULL;
    int choice, key;

    printf("Binary Search Tree Operations:\n");
    printf("1. Insert a node\n");
    printf("2. Delete a node\n");
    printf("3. Display the BST (inorder traversal)\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 3:
                printf("Inorder traversal of the BST: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
