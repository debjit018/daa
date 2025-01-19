
1. Create a BST and Delete an Element

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = delete(root->left, key);
    else if (key > root->key) root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int n, key, delKey;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Enter element to delete: ");
    scanf("%d", &delKey);
    root = delete(root, delKey);

    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");
    return 0;
}
2. Breadth-First Search (BFS)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Graph {
    int vertices;
    int adj[MAX][MAX];
} Graph;

void bfs(Graph* graph, int start) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = true;

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adj[vertex][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }
}

int main() {
    Graph graph;
    printf("Enter number of vertices: ");
    scanf("%d", &graph.vertices);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < graph.vertices; i++) {
        for (int j = 0; j < graph.vertices; j++) {
            scanf("%d", &graph.adj[i][j]);
        }
    }

    int start;
    printf("Enter start vertex: ");
    scanf("%d", &start);

    printf("BFS Traversal: ");
    bfs(&graph, start);
    printf("\n");
    return 0;
}
3. Depth-First Search (DFS)

#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void dfs(int graph[MAX][MAX], int visited[MAX], int v, int vertices) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < vertices; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(graph, visited, i, vertices);
        }
    }
}

int main() {
    int graph[MAX][MAX], visited[MAX] = {0}, vertices;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int start;
    printf("Enter start vertex: ");
    scanf("%d", &start);

    printf("DFS Traversal: ");
    dfs(graph, visited, start, vertices);
    printf("\n");
    return 0;
}
4. Matrix Chain Multiplication
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to perform Matrix Chain Multiplication
int matrixChainOrder(int p[], int n) {
    // m[i][j] stores the minimum number of scalar multiplications
    int m[n][n];

    // Base case: Single matrix, no multiplication needed
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // Chain length varies from 2 to n-1
    for (int length = 2; length < n; length++) {
        for (int i = 1; i < n - length + 1; i++) {
            int j = i + length - 1;
            m[i][j] = INT_MAX;

            // Try every possible position to split the chain
            for (int k = i; k < j; k++) {
                // Calculate number of multiplications
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    // Return the minimum number of multiplications needed for the entire chain
    return m[1][n - 1];
}

int main() {
    int n;  // Number of matrices
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int *p = (int *)calloc(n + 1, sizeof(int));
    printf("Enter the dimensions of matrices (e.g., for A1 (10x20), enter 10 20):\n");
    for (int i = 0; i < n; i++) {
        printf("Enter dimension %d: ", i + 1);
        scanf("%d", &p[i]);
    }

    // Compute the minimum number of multiplications
    int result = matrixChainOrder(p, n + 1);
    printf("Minimum number of multiplications is: %d\n", result);

    free(p);
    return 0;
}

5. AVL Tree Insertion and Deletion
#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int data;
    struct AVLNode *left, *right;
    int height;
};

int getHeight(struct AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(struct AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

struct AVLNode* createNode(int data) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct AVLNode* rotateRight(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

struct AVLNode* rotateLeft(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

struct AVLNode* insert(struct AVLNode* node, int data) {
    if (!node) return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rotateRight(node);
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

struct AVLNode* findMin(struct AVLNode* node) {
    while (node->left) node = node->left;
    return node;
}

struct AVLNode* deleteNode(struct AVLNode* root, int data) {
    if (!root) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (!root->left || !root->right) {
            struct AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        struct AVLNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorderTraversal(struct AVLNode* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct AVLNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Inorder Traversal\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
6. Red-Black Tree (Creation and Deletion)
#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct RBNode {
    int data;
    enum Color color;
    struct RBNode *left, *right, *parent;
};

struct RBNode* createNode(int data) {
    struct RBNode* node = (struct RBNode*)calloc(1, sizeof(struct RBNode));
    node->data = data;
    node->color = RED;
    return node;
}

void rotateLeft(struct RBNode** root, struct RBNode* x) {
    struct RBNode* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rotateRight(struct RBNode** root, struct RBNode* x) {
    struct RBNode* y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void fixViolation(struct RBNode** root, struct RBNode* newNode) {
    struct RBNode *parent = NULL, *grandparent = NULL;

    while ((newNode != *root) && (newNode->color != BLACK) &&
           (newNode->parent->color == RED)) {
        parent = newNode->parent;
        grandparent = newNode->parent->parent;

        if (parent == grandparent->left) {
            struct RBNode* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->right) {
                    rotateLeft(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateRight(root, grandparent);
                enum Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                newNode = parent;
            }
        } else {
            struct RBNode* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    rotateRight(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rotateLeft(root, grandparent);
                enum Color tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                newNode = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

struct RBNode* insertNode(struct RBNode* root, struct RBNode* newNode) {
    if (root == NULL)
        return newNode;

    if (newNode->data < root->data) {
        root->left = insertNode(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->data > root->data) {
        root->right = insertNode(root->right, newNode);
        root->right->parent = root;
    }

    return root;
}

void insert(struct RBNode** root, int data) {
    struct RBNode* newNode = createNode(data);
    *root = insertNode(*root, newNode);
    fixViolation(root, newNode);
}

struct RBNode* deleteNode(struct RBNode* root, int data) {
    // Placeholder for Red-Black Tree deletion (requires extensive handling).
    printf("Red-Black Tree deletion logic not implemented yet.\n");
    return root;
}

void inorderTraversal(struct RBNode* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d(%s) ", root->data, (root->color == RED) ? "R" : "B");
        inorderTraversal(root->right);
    }
}

int main() {
    struct RBNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Inorder Traversal\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

7. Heap Sort in Ascending and Descending Order

#include <stdio.h>
void heapify(int arr[], int n, int i, int ascending) {
    int largest = i; // For max-heap
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (ascending) { // Ascending order requires max-heap
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
    } else { // Descending order requires min-heap
        if (left < n && arr[left] < arr[largest])
            largest = left;
        if (right < n && arr[right] < arr[largest])
            largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, ascending);
    }
}

void heapSort(int arr[], int n, int ascending) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, ascending);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, ascending);
    }
}

int main() {
    int n, ascending;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter 1 for Ascending order, 0 for Descending order: ");
    scanf("%d", &ascending);

    heapSort(arr, n, ascending);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

8. Prim's Algorithm

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int findMinVertex(int key[], bool mstSet[], int n) {
    int min = INT_MAX, minIndex;

    for (int i = 0; i < n; i++)
        if (!mstSet[i] && key[i] < min) {
            min = key[i];
            minIndex = i;
        }
    return minIndex;
}

void primMST(int graph[MAX][MAX], int n) {
    int parent[n], key[n];
    bool mstSet[n];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinVertex(key, mstSet, n);
        mstSet[u] = true;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

int main() {
    int n, graph[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, n);

    return 0;
}

10. Strassen's Matrix Multiplication

#include <stdio.h>
#include <stdlib.h>

void addMatrices(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void subtractMatrices(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            result[i][j] = a[i][j] - b[i][j];
}

void strassenMultiply(int a[2][2], int b[2][2], int c[2][2]) {
    int p1, p2, p3, p4, p5, p6, p7;

    p1 = a[0][0] * (b[0][1] - b[1][1]);
    p2 = (a[0][0] + a[0][1]) * b[1][1];
    p3 = (a[1][0] + a[1][1]) * b[0][0];
    p4 = a[1][1] * (b[1][0] - b[0][0]);
    p5 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
    p6 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
    p7 = (a[0][0] - a[1][0]) * (b[0][0] + b[0][1]);

    c[0][0] = p5 + p4 - p2 + p6;
    c[0][1] = p1 + p2;
    c[1][0] = p3 + p4;
    c[1][1] = p5 + p1 - p3 - p7;
}

int main() {
    int a[2][2], b[2][2], c[2][2];

    printf("Enter the elements of first 2x2 matrix (row-wise):\n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            scanf("%d", &a[i][j]);

    printf("Enter the elements of second 2x2 matrix (row-wise):\n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            scanf("%d", &b[i][j]);

    strassenMultiply(a, b, c);

    printf("Resultant matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }

    return 0;
}

11. Create a Unique Binary Tree from Preorder and Inorder Traversals

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == value)
            return i;
    return -1;
}

struct Node* buildTree(int inorder[], int preorder[], int start, int end, int* preorderIndex) {
    if (start > end)
        return NULL;

    struct Node* node = createNode(preorder[*preorderIndex]);
    (*preorderIndex)++;

    if (start == end)
        return node;

    int inorderIndex = search(inorder, start, end, node->data);
    node->left = buildTree(inorder, preorder, start, inorderIndex - 1, preorderIndex);
    node->right = buildTree(inorder, preorder, inorderIndex + 1, end, preorderIndex);

    return node;
}

void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    int inorder[n], preorder[n];
    printf("Enter inorder traversal: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    printf("Enter preorder traversal: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &preorder[i]);

    int preorderIndex = 0;
    struct Node* root = buildTree(inorder, preorder, 0, n - 1, &preorderIndex);

    printf("Inorder traversal of the constructed tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

12. Merge Sort

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

13. BST Inorder Traversal

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (!root)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int n, value;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the values: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

14. Dijkstra's Algorithm

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int findMinDistance(int dist[], bool visited[], int n) {
    int min = INT_MAX, minIndex;
    for (int i = 0; i < n; i++)
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    return minIndex;
}

void dijkstra(int graph[MAX][MAX], int n, int start) {
    int dist[MAX];
    bool visited[MAX] = {false};

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinDistance(dist, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t%d\n", i, dist[i]);
}

int main() {
    int n, graph[MAX][MAX], start;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter the starting vertex: ");
    scanf("%d", &start);

    dijkstra(graph, n, start);

    return 0;
}
