#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
        int val;
        struct node_ *left;
        struct node_ *right;
        int height;
} node;

node* get_new_node(int val) {
        node *node1 = (node*)malloc(sizeof(node));
        node1->val = val;
        node1->left = NULL;
        node1->right = NULL;
        node1->height = 1;
        return node1;
}
int max(int a, int b) {
        return (a>b? a:b);
}
int height_tree(node* root) {
        if (root == NULL)
                return 0;
        return root->height;
}
int balance(node* root) {
        if (root == NULL)
                return 0;
        return (height_tree(root->left) - height_tree(root->right));
}

node* left_rotation(node *x) {
        node* y = x->right;
        node* T2 = y->left;

                //perform rotation
        y->left = x;
        x->right = T2;
        //adjust heights
        x->height = max(height_tree(x->left), height_tree(x->right)) +1;
        y->height = max(height_tree(y->left), height_tree(y->right)) +1;

        return y;
}

node* right_rotation(node *x) {
        node *y = x->left;
        node *T2 = y->right;

        //rotation
        y->right = x;
        x->left = T2;

        //adjust heights;
        x->height = max(height_tree(x->left), height_tree(x->right)) +1;
        y->height = max(height_tree(y->left), height_tree(y->right)) +1;

        return y;
}
node* inorder_successor(node* root, node** prev) {

        node *temp = NULL;
        if(prev != NULL)
                *prev = root;
        temp = root->right;
        while (temp->left != NULL) {
                *prev =temp;
                temp = temp->left;
        }
        return temp;
}
node* avl_insert(node *root, int val) {
        node *temp = NULL, *new_node=NULL, *prev=NULL;
        int bal = 0;

        if (root == NULL) {
                return (get_new_node(val));
        }

        if (root->val > val) {
                root->left = avl_insert(root->left, val);
        }
        if (root->val < val) {
                root->right = avl_insert(root->right, val);
        }

        root->height = max(height_tree(root->left), height_tree(root->right)) + 1;

        bal = balance(root);
        if (bal > 1 && val < root->left->val) {
                return right_rotation(root);
        }
        if(bal > 1 && val > root->left->val) {
                root->left = left_rotation(root->left);
                return right_rotation(root);
        }
        if (bal < -1 && val > root->right->val) {
                return left_rotation(root);
        }
        if(bal < -1 && val < root->right->val) {
                root->right = right_rotation(root->right);
                return left_rotation(root);
        }
        return root;

}
node* avl_delete(node *root, int val) {
        node *temp = NULL, *new_node=NULL, *succ=NULL;
        int bal = 0;

        if (root == NULL) {
                return NULL;
        }

        if (root->val > val) {
                root->left = avl_delete(root->left, val);
        } else if (root->val < val) {
                root->right = avl_delete(root->right, val);
        } else {
                //element found. now delete it and balance it.
                if(root->left == NULL ||  root->right == NULL) {
                        temp = root->left ? root->left: root->right;
                        if (temp == NULL) {
                                temp = root = NULL;
                        } else {
                                *root = *temp;
                                free(temp);
                        }
                } else {
                        //node has two child.
                        succ = inorder_successor(root, NULL);
                        root->val = succ->val;
                        root->right = avl_delete(root->right, succ->val);
                }
        }
        if (root == NULL)
                return root;

        root->height = max(height_tree(root->left), height_tree(root->right)) + 1;

        bal = balance(root);
        if (bal > 1 && val < root->left->val) {
                return right_rotation(root);
        }
        if(bal > 1 && val > root->left->val) {
                root->left = left_rotation(root->left);
                return right_rotation(root);
        }
        if (bal < -1 && val > root->right->val) {
                return left_rotation(root);
        }
        if(bal < -1 && val < root->right->val) {
                root->right = right_rotation(root->right);
                return left_rotation(root);
        }
        return root;

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
int getHeight(node* root) {
    int lh=0, rh=0, maxheight=0;
    // Write your code here
    if (root == NULL)
        return -1;
    lh = getHeight(root->left);
    rh = getHeight(root->right);
    if (lh>rh) return (lh+1);
    else return rh+1;
}
int main() {
        //int a[] = { 34, 56, 23, 76, 98, 1, 22, 43, 12, 99, 33, 75, 21};
        int a[]= {10,20,30,40,50,60,70,80,90,100,110,120};
        int n = 12;
        int i=0, choice =0, val = 0;
        node *root = NULL;

        for (i=0; i<n; i++) {
                root = avl_insert(root, a[i]);
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
                printf("\n 4. EXIT");
                scanf("\n %d", &choice);
                switch(choice) {
                        case 1:
                                printf("\n enter val to be added");
                                scanf("%d", &val);
                                root = avl_insert(root,val);
                        break;
                        case 2:
                                printf("\n enter val to be deleted");
                                scanf("%d", &val);
                                avl_delete(root,val);
                        break;
                        case 3:
                                level_order_traversal(root);
                        break;
                        case 4:
                                exit(0);
                                break;
                }
                fflush(stdin);
        }

}
