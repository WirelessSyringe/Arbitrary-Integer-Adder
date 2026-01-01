#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

node_t * create_node(int n) {
    node_t * node = (node_t *)malloc(sizeof(node_t));
    node->val = n;
    node->next = NULL;
    return node;
}

void append(node_t * head, int val) {
    node_t * current = head;
    if (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(val);
}

void prepend(node_t ** head, int val) {
    node_t * node = (node_t *)malloc(sizeof(node_t));
    node->val = val;
    node->next = *head;
    *head = node;
}

node_t * read_to_list(void) {
    node_t * head = NULL;
    char c;
    printf("Enter any integer: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c < '0' || c > '9') continue;
        node_t * node = create_node(c - '0');
        node->next = head;
        head = node;
    }
    return head;
}

node_t * add(node_t * a, node_t * b) {
    node_t * result = NULL;
    node_t * tail = NULL;
    int carry = 0;
    while (a || b || carry) {
        int sum = carry;
        if (a) { sum += a->val; a = a->next; };
        if (b) { sum += b->val; b = b->next; };
        carry = sum / 10;
        node_t * new_node = create_node(sum % 10);
        if (!result) {
            result = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return result;
}

void print(node_t * head) {
    if (!head) return;
    print(head->next);
    printf("%d", head->val);
}

void free_list(node_t * head) {
    while(head) {
        node_t * temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char ** argv) {
    node_t * a = read_to_list();
    node_t * b = read_to_list();
    node_t * sum = add(a, b);
    printf("Sum: ");
    print(sum);
    printf("\n");
    free_list(a);
    free_list(b);
    free_list(sum);
    return 0;
}
