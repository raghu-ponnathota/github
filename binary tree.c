//Binary tree implementation
// This has code for insert node, deleting node (all possible cases)
// pre-order, post-order, in-orser, level-order traversal implementation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
        int val;
        struct node_ *left;
        struct node_ *right;
} node;

node* get_new_node(int val) {
        node *node1 = (node*)malloc(sizeof(node));
        node1->val = val;
        node1->left = NULL;
        node1->right = NULL;
        return node1;
}
void insert(node **root, int val) {
        node *temp = NULL, *new_node=NULL, *prev=NULL;

        new_node = get_new_node(val);
        if (*root == NULL) {
                *root = new_node;
                return;
        }
        temp = *root;
        while (temp != NULL) {
                prev = temp;
                if (temp->val > val) {
                        temp = temp->left;
                } else if (temp->val < val) {
                        temp = temp->right;
                }
        }
        if(prev->val > val)
                prev->left = new_node;
        else
                prev->right = new_node;
        return;
}

void pre_order_traverse(node* root) {
        if (root) {
                printf(" %d ", root->val);
                pre_order_traverse(root->left);
                pre_order_traverse(root->right);
        }
}
void in_order_traverse(node* root) {
        if (root) {
                in_order_traverse(root->left);
                printf(" %d ", root->val);
                in_order_traverse(root->right);
        }
}
void post_order_traverse(node* root) {
        if (root) {
                post_order_traverse(root->left);
                post_order_traverse(root->right);
                printf(" %d ", root->val);
        }
}


void level_order_traversal(node *root) {
        int front = -1, rear =-1;
        node q[13];
        node *temp = NULL;

        if (root == NULL) {
                printf(" Tree is empty");
                return;
        }
        temp = root;
        while (temp != NULL) {
                printf(" %d ", temp->val);
                if (temp->left != NULL)
                        memcpy(&q[++rear], temp->left, sizeof(node));
                        //q[++rear] = temp->left;
                if (temp->right != NULL)
                        //q[++rear] = temp->right;
                        memcpy(&q[++rear], temp->right, sizeof(node));
                temp = &q[++front];
                if(front > rear)
                        return;
        }

}
node* inorder_successor(node* root, node** prev) {

        node *temp = NULL;
        *prev = root;
        temp = root->right;
        while (temp->left != NULL) {
                *prev =temp;
                temp = temp->left;
        }
        return temp;
}
void delete(node* root, int val) {

        node *temp = root, *prev = NULL, *succ = NULL, *prev_of_succ = NULL;
        int found = 0;

        while (temp != NULL) {
                if(temp->val == val) {
                        found = 1;
                        printf("value %d found ", val);
                        break;
                }
                prev = temp;
                if(temp->val > val)
                                temp = temp->left;
                else
                                temp = temp->right;
        }
        if (found) {
                if(temp->left == NULL && temp->right == NULL) {
                        if (prev->left == temp)
                                prev->left = NULL;
                        if (prev->right == temp)
                                prev->right = NULL;
                        free(temp);
                        return;
                }
                if (temp->left == NULL || temp->right == NULL) {
                        if (temp->left == NULL)
                                prev->left = temp->right;
                        if (temp->right == NULL)
                                prev->right = temp->left;
                        free(temp);
                        return;
                }
                //find in-order successor
                succ = inorder_successor(temp, &prev_of_succ);
                if (prev->left == temp)
                        prev->left = succ;
                if (prev->right == temp)
                        prev->right = succ;
                succ->left = temp->left;
                prev_of_succ->left = NULL;
                if (temp->right == succ)
                                succ->right = NULL;
                else
                        succ->right = temp->right;
                free (temp);
        } else {
                printf("Node not found ");
        }
        return;
}
int main() {
        int a[] = { 34, 56, 23, 76, 98, 1, 22, 43, 12, 99, 33, 75, 21};
        int n = 12;
        int i=0, choice =0, val = 0;
        node *root = NULL;

        for (i=0; i<n; i++) {
                insert(&root, a[i]);
        }
        printf("\n Pre-order traversal: \n");
        pre_order_traverse(root);

        printf("\n In-order traversal: \n");
        in_order_traverse(root);

        printf("\n Post-order traversal: \n");
        post_order_traverse(root);

        printf("\n level-order traversal: \n");
        level_order_traversal(root);
        while (1) {
                printf("\n 1. Insert");
                printf("\n 2. Delete");
                printf("\n 3. level order");
                scanf("\n %d", &choice);
                switch(choice) {
                        case 1:
                                printf("\n enter val to be added");
                                scanf("%d", &val);
                                insert(&root,val);
                        break;
                        case 2:
                                printf("\n enter val to be deleted");
                                scanf("%d", &val);
                                delete(root,val);
                        break;
                        case 3:
                                level_order_traversal(root);
                        break;
                }
                fflush(stdin);
        }

}