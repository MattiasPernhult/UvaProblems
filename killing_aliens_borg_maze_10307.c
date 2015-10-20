#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXV 10000
#define MAXDEGREE 50000

typedef struct queue_element {
  int value;
  struct queue_element *next;
} queue_element;

typedef struct queue {
  struct queue_element *head;
  struct queue_element *tail;
} queue;

typedef struct {
  int source;
  int dest;
  int weight;
} edges_mst;

typedef struct node {
  int data;
  int rank;
  struct node *parent;
} node;

typedef struct graph {
  int edges[MAXV+1][MAXDEGREE]; /* adjacency info */
  int degree[MAXV+1];           /* meningsfulla entries för den givna vertex */
  int nvertices;                /* antal vertices i grafen */
  int nedges;                   /* antal edge i grafen */
} graph;

node* make_set(int data);
void union_nodes(node* n1, node* n2);
node* find_root(node* n);
queue* init_queue();
void enqueue(struct queue *q,  int value);
void dequeue(struct queue *q);
int front(struct queue *q);
int is_empty(struct queue *q);

queue* init_queue() {
  struct queue *q = (queue*) malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void enqueue(struct queue *q, int value) {
  struct queue_element *new_element = (queue_element*) malloc(sizeof(queue_element));
  new_element->value = value;
  new_element->next = NULL;

  /* första elementet */
  if (q->head == NULL) {
    q->head = new_element;
    q->tail = new_element;
  } else {
    q->tail->next = new_element;
    q->tail = new_element;
  }
}

void dequeue(struct queue *q) {
  if (q->head != NULL) {
    queue_element *element = q->head;
    q->head = q->head->next;
    free(element);
  }
}

int front(struct queue *q) {
  if (q->head != NULL) {
    return q->head->value;
  }
  return -666;
}

int is_empty(struct queue *q) {
  return (q->head == NULL ? 1 : 0);
}

graph* init_graph(int nr_vertices) {
  struct graph *g = (graph*) malloc(sizeof(graph));
  g->nvertices = nr_vertices;
  g->nedges = 0;
  int i;
  for (i = 1; i <= MAXV; i++) {
    g->degree[i] = 0;
  }
  return g;
}

void insert_edge(graph *g, int x, int y, int directed) {

  if (g->degree[x] > MAXDEGREE) {
    printf("Warning: insertion(%d,%d) exceeds max degree\n",x,y);
  }

  g->edges[x][g->degree[x]] = y;
  g->degree[x]++;

  if (!directed) {
    insert_edge(g, y, x, 1);
  } else {
    g->nedges++;
  }
}

void print_graph(graph *g) {
  int i, j;
  for (i = 1; i <= g->nvertices; i++) {
    printf("%d: ", i);
    for (j = 0; j < g->degree[i]; j++) {
      printf(" %d", g->edges[i][j]);
    }
    printf("\n");
  }
}

void process_vertex(int v) {

}

void process_edge(int x, int y) {

}

void find_path(int start, int end, int parents[]) {
  if (start == end || end == -1) {
    return;
  } else {
    find_path(start, parents[end], parents);
  }
}

int bfs(graph *g, int start, int target) {
  int processed[MAXV], discovered[MAXV], parent[MAXV];
  int v, i, dist;
  for (i = 1; i <= g->nvertices; i++) {
    processed[i] = discovered[i] = 0;
    parent[i] = -1;
  }

  queue *d = init_queue();
  queue *q = init_queue();
  enqueue(q, start);
  enqueue(d, 0);
  discovered[start] = 1;

  while(!is_empty(q)) {
    v = front(q);
    dist = front(d);
    dequeue(q);
    dequeue(d);
    if (v == target) {
      while(!is_empty(q))
        dequeue(q);
      while(!is_empty(d))
        dequeue(d);
      free(q);
      free(d);
      return dist;
    }
    process_vertex(v);
    processed[v] = 1;
    for (i = 0; i < g->degree[v]; i++) {
      if (g->edges[v][i] > 0) {
        if (!discovered[g->edges[v][i]]) {
          enqueue(q, g->edges[v][i]);
          enqueue(d, dist + 1);
          discovered[g->edges[v][i]] = 1;
          parent[g->edges[v][i]] = v;
        }
        if(!processed[g->edges[v][i]]) {
          process_edge(v, g->edges[v][i]);
        }
      }
    }
  }
  while(!is_empty(q))
    dequeue(q);
  while(!is_empty(d))
    dequeue(d);
  free(q);
  free(d);
  return -1;
}

int sort_edges(const void* a, const void* b) {
  edges_mst* ea = (edges_mst*) a;
  edges_mst* eb = (edges_mst*) b;
  return ea->weight - eb->weight;
}

int main() {
  int nr_test_cases;
  scanf("%d", &nr_test_cases);
  while(nr_test_cases--) {
    int rows, columns;
    scanf("%d%d", &columns, &rows);
    int graph[105][105];
    char line[columns];
    int i, j, s, counter = 1, nr_aliens = 0, nr_vertices = 0, aliens[500];
    for (i = 0; i < rows; i++) {
      fgets(line, columns+1, stdin);
      line[strcspn(line, "\n")] = '\0';
      if (line[0] == '\0') {
        i--;
        continue;
      }
      for (j = 0; j < columns; j++) {
        char c = line[j];
        if (c == 'A' || c == 'S' || c == ' ') {
          if (c == 'A') {
            aliens[nr_aliens] = counter;
            nr_aliens++;
          } else if (c == 'S') {
            s = counter;
          }
          graph[i][j] = counter;
          nr_vertices++;
          counter++;
        } else {
          graph[i][j] = 0;
        }
      }
    }

    struct graph *g = init_graph(nr_vertices);
    int x, y;
    for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++) {
        if (graph[i][j] > 0) {
          if (graph[i-1][j] > 0) {
            x = graph[i-1][j];
            y = graph[i][j];
            insert_edge(g, x, y, 0);
          }
          if (graph[i][j-1] > 0) {
            x = graph[i][j-1];
            y = graph[i][j];
            insert_edge(g, x, y, 0);
          }
          if (graph[i+1][j] > 0) {
            x = graph[i+1][j];
            y = graph[i][j];
            insert_edge(g, x, y, 0);
          }
          if (graph[i][j+1] > 0) {
            x = graph[i][j+1];
            y = graph[i][j];
            insert_edge(g, x, y, 0);
          }
        }
      }
    }

    if (nr_aliens == 1) {
      printf("%d\n", bfs(g, s, aliens[0]));
    } else if (nr_aliens == 0) {
      printf("%d\n", 0);
    } else {
      int nr_actual_nodes = (nr_aliens * (nr_aliens+1)) / 2;
      edges_mst edges[nr_actual_nodes];
      int nr_edges = 0;

      for (i = 0; i <= nr_aliens; i++) {
        for (j = 0; j <= nr_aliens; j++) {
          if (i != j) {
            if (i == 0) {
              edges_mst em;
              em.source = s;
              em.dest = aliens[j-1];
              int res = bfs(g, em.source, em.dest);
              if (res == -1)
                res = 999;
              em.weight = res;
              edges[nr_edges] = em;
              nr_edges++;
            } else if (j >= i + 1) {
              edges_mst em;
              em.source = aliens[i-1];
              em.dest = aliens[j-1];
              int res = bfs(g, em.source, em.dest);
              if (res == -1)
                res = 999;
              em.weight = res;
              edges[nr_edges] = em;
              nr_edges++;
            }
          }
        }
      }

      qsort(edges, nr_actual_nodes, sizeof(edges_mst), sort_edges);
      node* nodes[5000];
      nodes[s] = make_set(s);
      for (i = 0; i < nr_aliens; i++) {
        nodes[aliens[i]] = make_set(aliens[i]);
      }

      int nr_edges_in_mst = 0, mst_total = 0, counter_in_mst = 0;
      while (nr_aliens > nr_edges_in_mst) {
        edges_mst e = edges[counter_in_mst];
        struct node* u = find_root(nodes[e.source]);
        struct node* v = find_root(nodes[e.dest]);
        if (u->data != v->data) {
          mst_total += e.weight;
          union_nodes(u, v);
          nr_edges_in_mst++;
        }
        counter_in_mst++;
      }
      printf("%d\n", mst_total);
      free(nodes[s]);
      for (i = 0; i < nr_aliens; i++) {
        free(nodes[aliens[i]]);
      }
    }
    free(g);
  }
  return(0);
}

node* make_set(int data) {
  node* n = malloc(sizeof(node));
  n->data = data;
  n->parent = NULL;
  n->rank = 0;
  return n;
}

void union_nodes(node* n1, node* n2) {
  if (n1->data > n2->data) {
        n2->parent = n1;
  } else if (n2->data > n1->data) {
      n1->parent = n2;
  } else {
      n2->parent = n1;
      n1->rank++;
  }
}

node* find_root(node* n) {
  node* root = n;
  while(root->parent != NULL) {
    root = root->parent;
  }
  return root;
}
