#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  int rank;
  struct node *parent;
} node;

int hgof = 1;

node* make_set(int data);
void union_nodes(node* n1, node* n2);
node* find_root(node* n);

node* make_set(int data) {
  node* n = malloc(sizeof(node));
  n->data = data;
  n->parent = NULL;
  n->rank = 1;
  return n;
}

void union_nodes(node* n1, node* n2) {

  node* p1 = find_root(n1);
  node* p2 = find_root(n2);

  if (p1->data != p2->data) {
    if (p1->rank > p2->rank) {
      p2->parent = p1;
      p1->rank += p2->rank;
      hgof = (p1->rank >= hgof) ? p1->rank : hgof;
    } else if (p1->rank < p2->rank) {
      p1->parent = p2;
      p2->rank += p1->rank;
      hgof = (p2->rank >= hgof) ? p2->rank : hgof;
    } else {
      if (p1->data < p2->data) {
        p2->parent = p1;
        if (p1->rank == 0) {
          p1->rank++;
        } else {
          p1->rank += p2->rank;
          hgof = (p1->rank >= hgof) ? p1->rank : hgof;
        }
      } else {
        p1->parent = p2;
        if (p2->rank == 0) {
          p2->rank++;
        } else {
          p2->rank += p1->rank;
          hgof = (p2->rank >= hgof) ? p2->rank : hgof;
        }
      }
    }
  }
}

node* find_root(node* n) {
  node* root = n;
  while(root->parent != NULL) {
    root = root->parent;
  }
  // For path compression
  // node* temp;
  // while (n->parent != NULL) {
  //   temp = n->parent;
  //   n->parent = root;
  //   n = temp;
  // }
  return root;
}


int main() {
  int nr_test_cases, nr_pos_input, nr_friends;

  scanf("%d", &nr_test_cases);

  while(nr_test_cases--) {
    hgof = 1;
    scanf("%d%d", &nr_pos_input, &nr_friends);
    node* nodes[nr_pos_input + 1];
    int i;
    for (i = 1; i <= nr_pos_input; i++) {
      nodes[i] = make_set(i);
    }
    while(nr_friends--) {
        int f1, f2;
        scanf("%d%d\n", &f1, &f2);
        union_nodes(nodes[f1], nodes[f2]);
    }
    printf("%d\n", hgof);
  }
  return 0;
}
