/*

This program implements the following functionalities of a linked list.

1. Insert a node into the linked list
2. Delete a node in the linked list
3. reverse linked list using iterative method
4. reverse linked list using recursive method
5. display a list
6. Merging two linked lists without using extra space.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
typedef struct node_ {
        int val;
        struct node_ *next;
}node;

node* allocate_new_node(int num) {
        node *new_node = (node*) malloc(sizeof(node));
        memset(new_node, 0, sizeof(node));
        new_node->next = NULL;
        new_node->val = num;
        return new_node;
}

int add(int num, node **head) {
        node *node1 = NULL, *temp = NULL;
        if (head == NULL ) {
                return -1;
        }
        node1 = allocate_new_node(num);
        if (*head == NULL) {
                *head = node1;
        } else {
                temp = *head;
                while (temp->next != NULL) temp = temp->next;
                temp->next = node1;
        }
        return SUCCESS;
}

void display_list(node *head) {
        node *temp = NULL;
        printf("\n List is: \n");
        if (head) {
                temp = head;
                while (temp != NULL) {
                        printf(" %d --> ", temp->val);
                        temp = temp->next;
                }
                printf("NULL\n");
        }
}

int del(int num, node **head) {

        node *temp = *head, *prev = NULL;

        if ( num == temp->val) {
                *head = (*head)->next;
                free(temp);
                return 0;
        } else {
                prev = temp;
                while (temp->next != NULL) {
                        temp = temp->next;
                        if (temp->val == num) {
                                prev->next = temp->next;
                                free(temp);
                        }
                        prev = temp;
                }
        }
}

int reverse_list(node **head) {
        node *p, *q, *r;
        p = *head;
        q = p->next;
        p->next = NULL;
        while (q != NULL) {
                r = q->next;
                q->next = p;
                p = q;
                q = r;
        }
        *head = p;
        display_list(*head);
}

node* reverse_recursive(node *root, node **head) {
        if (root->next != NULL) {
                reverse_recursive(root->next, head);
                root->next->next = root;
                return root;
        } else {
                *head = root;
        }
}

node* merge_list(node* head1, node* head2) {

        node *temp=NULL, *temp1= NULL, *temp2=NULL, *res = NULL;

        if(head1 == NULL && head2 ==NULL) {
                printf("BOTH THE LISTS ARE EMPTY");
                return NULL;
        }
        if (head1 == NULL) {
                res = head1;
                return res;
        }
        if (head2 == NULL) {
                res = head2;
                return res;
        }

        temp1 = head1;
        temp2 = head2;

        if (temp1->val <= temp2->val) {
                res = temp1;
                temp1 = temp1->next;
        } else if (temp2->val < temp1->val) {
                res = temp2;
                temp2 = temp2->next;
        }
        temp = res;

        while (temp1 && temp2) {
                if (temp1->val <= temp2->val) {
                        temp->next = temp1;
                        temp1 = temp1->next;
                } else if (temp2->val < temp1->val) {
                        temp->next = temp2;
                        temp2 = temp2->next;
                }
                temp = temp->next;
        }

        while(temp1) {
                temp->next = temp1;
                temp1 = temp1->next;
                temp = temp->next;
        }
        while(temp2) {
                temp->next = temp2;
                temp2 = temp2->next;
                temp = temp->next;
        }
        return res;
}

void sort_linkedlist(node *head) {

    int n=0, i=0, j=0, t =0;
    node* temp=NULL;
    //count no. of nodes
    for (temp = head; temp!= NULL; temp=temp->next)
        i++;
    n = i;

    //now do bubble sort
    for ( i =0; i<n; i++) {
        temp =head;
        for(j=0; j<n-i-1; j++) {
            if (temp->val > temp->next->val) {
                t = temp->val;
                temp->val = temp->next->val;
                temp->next->val = t;
            }
            temp = temp->next;
        }
    }
}


int main() {
        node *head = NULL, *temp = NULL, *head2=NULL, *result = NULL;

        add(1,&head);
        add(3,&head);
        add(6,&head);
        add(9,&head);

        display_list(head);
        reverse_list(&head);
        temp = reverse_recursive(head, &head);
        temp->next = NULL;
        display_list(head);
		
        add(2, &head2);
        add(4, &head2);
        add(5, &head2);
        add(9, &head2);
        display_list(head2);
        result = merge_list(head, head2); /// MERGE linked lists
        display_list(result);
        
        //sorted linked list
        reverse_list(&result);
    	printf("\n display list before sorting: ");
   		display_list(result);
    	sort_linkedlist(result);
    	printf("\n display list after sorting: ");
	    display_list(result);


        del(2, &head);
        display_list(head);
        del(1, &head);
        display_list(head);
        add(5, &head);
        display_list(head);
        del(5, &head);
        display_list(head);
        reverse_list(&head);

}
