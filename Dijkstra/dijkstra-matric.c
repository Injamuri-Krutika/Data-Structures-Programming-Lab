#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int nodes, edges;
void min_heapify(unsigned int A[][2], unsigned int index, unsigned int n) {
  unsigned int leftChild = 2 * index;
  unsigned int rightChild = 2 * index + 1;
  unsigned int smallest = 0;

  if (leftChild <= n && A[leftChild - 1][0] < A[index - 1][0]) {
    smallest = leftChild;
  } else {
    smallest = index;
  }
  if (rightChild <= n && A[rightChild - 1][0] < A[smallest - 1][0]) {
    smallest = rightChild;
  }
  if (smallest != index) {
    unsigned int temp1 = A[index - 1][0];
    unsigned int temp2 = A[index - 1][1];

    A[index - 1][0] = A[smallest - 1][0];
    A[index - 1][1] = A[smallest - 1][1];
    A[smallest - 1][0] = temp1;
    A[smallest - 1][1] = temp2;

    min_heapify(A, smallest, n);
  }
}

void buildMinHeap(unsigned int A[][2], unsigned int n) {
  for (int i = (n / 2); i > 0; i--) {
    min_heapify(A, i, n);
  }
}

unsigned int extractMinFromHeap(unsigned int A[][2], unsigned int n,
                                unsigned int *node_index) {
  if (n < 1) {
    printf("error: underflow\n");
    return -1;
  }

  unsigned int min = A[0][0];
  unsigned int u = A[0][1];

  if (n > 1) {
    A[0][0] = A[n - 1][0];
    A[0][1] = A[n - 1][1];
    buildMinHeap(A, n - 1);
  }
  *node_index = u;
  return min;
}

void heap_decrease_key(unsigned int heap[][2], unsigned int u,
                       unsigned int weight, unsigned int n) {
  for (int i = 0; i < n; i++) {
    if (heap[i][1] == u) {
      if (weight < heap[i][0]) {
        heap[i][0] = weight;
        unsigned int parent = i / 2;
        while (i > 0 && heap[parent][0] > heap[i][0]) {
          // swap
          unsigned int temp1 = heap[parent][0];
          unsigned int temp2 = heap[parent][1];
          heap[parent][0] = heap[i][0];
          heap[parent][1] = heap[i][1];
          heap[i][0] = temp1;
          heap[i][1] = temp2;
          i = parent;
          parent = i / 2;
        }
      }
      break;
    }
  }
}

void dijkstra(unsigned int adjacencyMatrix[][nodes], unsigned int distance[][2],
              int source, int n) {

  unsigned int heap[n][2];
  unsigned int S[n];

  for (int i = 0; i < n; i++) {
    distance[i][0] = UINT_MAX;
    distance[i][1] = UINT_MAX;
    heap[i][0] = UINT_MAX;
    heap[i][1] = i;
    S[i] = 0;
  }
  distance[source][0] = 0;
  distance[source][1] = 0;
  heap[source][0] = 0;

  unsigned int heap_size = n;

  buildMinHeap(heap, heap_size);

  while (heap_size > 0) {
    unsigned int u = UINT_MAX;
    unsigned int min_val = extractMinFromHeap(heap, heap_size, &u);

    if (u == -1) {
      printf("unexpected case\n");
      break;
    }
    S[u] = 1;
    heap_size--;
    if (min_val == UINT_MAX) {
      break;
    } else {
      for (unsigned int v = 0; v < n; v++) {
        unsigned int w = adjacencyMatrix[u][v];
        if (w != UINT_MAX && S[v] != 1) {
          if (distance[v][0] > distance[u][0] + w) {
            distance[v][0] = distance[u][0] + w;
            distance[v][1] = u;
            heap_decrease_key(heap, v, distance[u][0] + w, n);
          }
        }
      }
    }
  }
}

int main() {
  int testCases, source;
  printf("%s\n", "Enter the number of test cases: ");
  scanf("%d", &testCases);
  for (int i = 0; i < testCases; i++) {
    printf("%s\n", "Enter the number of nodes and the number of edges: ");
    scanf("%d %d", &nodes, &edges);

    unsigned int adjacencyMatrix[nodes][nodes];
    unsigned int shortestDistance[nodes][2];

    memset(adjacencyMatrix, -1, sizeof(adjacencyMatrix));
    memset(shortestDistance, -1, sizeof(shortestDistance));
    printf("%s\n", "Enter the source destination followed by the weight: ");
    for (int i = 0; i < edges; i++) {
      int x, y, r;
      scanf("%d %d %d", &x, &y, &r);
      if (adjacencyMatrix[x - 1][y - 1] > r) {
        adjacencyMatrix[x - 1][y - 1] = r;
      }
    }
    printf("%s\n", "Enter the start vertex: ");
    scanf("%d", &source);
    dijkstra(adjacencyMatrix, shortestDistance, source - 1, nodes);

    for (int i = 0; i < nodes; i++) {
      printf("Node: %d Weight: %d\n", i + 1, shortestDistance[i][0]);
    }
    printf("\n");
  }
  return 0;
}
