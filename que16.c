#include <stdio.h>
#include <stdlib.h>

void maxHeapify(int *heap, int n, int index, int k);
void minHeapify(int *heap, int n, int index, int k);
void buildMaxHeap(int *heap, int n, int k);
void printHeap(int *heap, int n);

int main() {
    int n, k, i;
    
    // Input number of elements and value of k
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the value of k (number of children per node): ");
    scanf("%d", &k);

    // Allocate memory for the heap array
    int *heap = (int *)calloc(n, sizeof(int));
    if (heap == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input elements into the heap
    printf("Enter %d elements: \n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &heap[i]);
    }

    // Build the k-ary max heap
    buildMaxHeap(heap, n, k);

    // Print the max heap
    printf("The k-ary max heap is: \n");
    printHeap(heap, n);

    // Free allocated memory
    free(heap);

    return 0;
}

// Function to perform max-heapify operation
void maxHeapify(int *heap, int n, int index, int k) {
    int largest = index;
    int child;

    // Check all k children of the current node
    for (int i = 1; i <= k; i++) {
        child = k * index + i;
        if (child < n && heap[child] > heap[largest]) {
            largest = child;
        }
    }

    // If the largest is not the current node, swap and heapify
    if (largest != index) {
        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, n, largest, k);
    }
}

// Function to perform min-heapify operation
void minHeapify(int *heap, int n, int index, int k) {
    int smallest = index;
    int child;

    // Check all k children of the current node
    for (int i = 1; i <= k; i++) {
        child = k * index + i;
        if (child < n && heap[child] < heap[smallest]) {
            smallest = child;
        }
    }

    // If the smallest is not the current node, swap and heapify
    if (smallest != index) {
        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, n, smallest, k);
    }
}

// Function to build a k-ary max heap
void buildMaxHeap(int *heap, int n, int k) {
    for (int i = (n - 2) / k; i >= 0; i--) {
        maxHeapify(heap, n, i, k);
    }
}

// Function to print the heap
void printHeap(int *heap, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}
