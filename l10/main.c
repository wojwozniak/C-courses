#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct elem {
    int val;
    struct elem *next;
 } elem;

 elem *utworz(int wart) {
     elem *fin = malloc(sizeof(elem));
     fin->val = wart;
     fin->next = NULL;
     return fin;
 };

 // Task 1
 void attach_elem(elem *node, int wart) {
     if(node->next == NULL) {
        node->next = utworz(wart);
        return;
     }
    attach_elem(node->next, wart);
 }

 //Task 2
 void delete_last(elem *node, elem *parent) {
     if(node->next == NULL) {
        free(node);
        parent->next = NULL;
        return;
     }
    delete_last(node->next, node);
 }

 //Task 3
 void connect_lists(elem *first, elem *second) {
     if(first->next == NULL) {
        first->next = second;
        return;
     }
     connect_lists(first->next, second);
 }

 //Task 4 (call with NULL as 3rd argument)
 void delete_val(elem *root, int val, elem *parent) {
    if(root->val == val) {
        if(parent == NULL) {
            root = root->next;
            if(root->next == NULL) {
                return;
            } else {
                delete_val(root->next, val, NULL);
            }
        } else {
            parent->next = root->next;
            free(root);
            if(parent->next == NULL) {
                return;
            } else {
                delete_val(parent->next, val, parent);
            }
        }
    } else {
        if(root->next == NULL) {
            return;
        }
        delete_val(root->next, val, root);
    }
 }

 //Task 5
 void add_to_front(elem *root, int val) {
     elem *rootptr = root;
     root = utworz(val);
     root->next = rootptr;
 }

 void delete_from_front(elem *root) {
     elem *trash = root;
     root = root->next;
     free(trash);
 }

 //Task 6
 void print_rec(elem *root) {
     if(root->next != NULL) {
        print_rec(root->next);
     }
     printf("%d\n", root->val);
     return;
 }

 void print_rev_list(elem *root) {
     if(root == NULL) {
        return;
     } else if (root->next != NULL) {
         print_rec(root->next);
     }
     printf("%d\n", root->val);
 }

 //Task 7
 elem *reverse_list(elem *root) {
     if(root == NULL || root->next == NULL) {
        return root;
     }
     elem *pom = reverse_list(root->next);
     root->next->next = root;
     root->next = NULL;
     return pom;
 }

 //Task 8
void divide_list(elem *root, elem *negatives, elem *parent) {
    if(root == NULL) {
        return;
    }
    if(root->val >= 0) {
        divide_list(root->next, negatives, root);
    } else {
        parent->next = root->next;
        if(negatives == NULL) {
            negatives = root;
            negatives->next = NULL;
        } else {
            negatives->next = root;
            negatives->next->next = NULL;

        }
        divide_list(parent->next, negatives->next, parent);
    }
}

//Task 10
void sort_rec(elem *first, elem *second, elem *firstparent) {
    if(second == NULL) {
        return;
    }
    if(first == NULL) {
        first = second;
        return;
    }
    if(second->val >= first->val) {
        printf("aa");
        sort_rec(first->next, second, first);
    }
    if (second->val < first->val && firstparent == NULL) {
        printf("bb");
        elem *helper = first;
        elem *secondnext = second->next;
        second->next = NULL;
        first = second;
        first->next = helper;
        sort_rec(first, secondnext, NULL);
    } else {
        elem *helper = second->next;
        firstparent->next = second;
        second->next = first;
        sort_rec(first, second->next, first);
    }
    printf("xx %d   %d\n", first->val, second->val);
}

// Chcemy zawsze obydwa mie� zapisane pod first, dlatego te sprawdzenia
void connect_sorted(elem *first, elem *second) {
    if(second == NULL || first == NULL) {
            if(second == NULL && first ==  NULL || first !=NULL) {
                return;
            }
            first = second;
            free(second);
            return;
    }
    if(first->val > second->val) {
        int help = first->val;
        first->val = second->val;
        second->val = first->val;
    }
    sort_rec(first->next, second, NULL);
}



int main() {
    elem *aaa = utworz(15);
    attach_elem(aaa, 16);
    attach_elem(aaa, 17);
    attach_elem(aaa, 19);
    attach_elem(aaa, 21);
    attach_elem(aaa, 23);
    print_rev_list(aaa);
    elem *bbb = utworz(1);
    attach_elem(bbb, 12);
    attach_elem(bbb, 18);
    attach_elem(bbb, 21);
    attach_elem(bbb, 22);
    attach_elem(bbb, 140);
    print_rev_list(bbb);
    printf("\n\n");
    connect_sorted(aaa,bbb);
    print_rev_list(aaa);
    return 0;
}
