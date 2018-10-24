/* C++ implementation of a binary search tree */

# include <iostream>
# include <cstdlib>
using namespace std;

/* Structure of the tree nodes */
struct node{
    int value;
    struct node *left;
    struct node *right;
};

/* Initialize root node */ 
struct node *root;

/* Declare the binary tree class */
class binTree{
    public:
        void insert(node *, node *);
        void find(int, node **, node **);
        void del(int);
        void case_a(node *, node *);
        void case_b(node *, node *);
        void case_c(node *, node *);
        void preorder(node *);
        void inorder(node *);
        void postorder(node *);
        void display(node *, int);
        binTree(){
            root = NULL;
        }
};

/* Main contains a menu */
int main(){
    int choice;
    int num;
    binTree bst;
    node *temp;
    /* Menu loop */
    while(1){
        cout<<"--------------------------"<<endl;
        cout<<"| Binary Tree Operations |"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<"1. Insert Element"<<endl;
        cout<<"2. Delete Element"<<endl;
        cout<<"3. Preorder Traversal"<<endl;
        cout<<"4. Inorder Traversal"<<endl;
        cout<<"5. Postorder Traversal"<<endl;
        cout<<"6. Display"<<endl;
        cout<<"7. Quit"<<endl;
        cout<<"What would you like to do?"<<endl;
        cout<<"Choice: ";
        cin>>choice;
        
        /* Use input to determine action */
        switch(choice){
            case 1:
                temp = new node;
                cout<<"Enter the value to be inserted: ";
                cin>>temp->value;
                bst.insert(root, temp);
                break;
            case 2:
                if(root == NULL){
                    cout<<"Tree is already empty, nothing to delete!"<<endl;
                    continue;
                }
                cout<<"Enter the number to be deleted: ";
                cin>>num;
                bst.del(num);
                break;
            case 3:
                cout<<"Performing Preorder Traversal..."<<endl;
                bst.preorder(root);
                cout<<endl;
                break;
            case 4:
                cout<<"Performing Inorder Traversal..."<<endl;
                bst.inorder(root);
                cout<<endl;
                break;
            case 5:
                cout<<"Performing Postorder Traversal..."<<endl;
                bst.postorder(root);
                cout<<endl;
                break;
            case 6:
                cout<<"Displaying Tree..."<<endl;
                bst.display(root, 1);
                cout<<endl;
                break;
            case 7:
                exit(1);
            default: 
                cout<<"\nPlease choose from one of the options listed.\n"<<endl;
        }
    }
}

/* Find element within the tree */
void binTree::find(int val, node **par, node **loc){
    node *ptr;
    node *ptrsave;
    /* No tree to search */
    if(root == NULL){
        *loc = NULL;
        *par = NULL;
        return;
    /* Root is the value we're looking for, no parent */
    }if(val == root->value){
        *loc = root;
        *par = NULL;
        return;
    /* Search tree going left or right as appropriate 
     * while keeping track of parent node */
    }if(val < root->value)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while(ptr != NULL){
        if(val == ptr->value){
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if(val < ptr->value)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    /* Value not found, location null, report would be parent */
    *loc = NULL;
    *par = ptrsave;
}

/* Insert element into tree */
void binTree::insert(node *tree, node *newNode){
    /* Need to make a root node */
    if(root == NULL){
        root = new node;
        root->value = newNode->value;
        root->left = NULL;
        root->right = NULL;
        cout<<"Root node created!"<<endl;
        return;
    /* New value is already in the BST */
    }if(tree->value == newNode->value){
        cout<<"Element already in list!"<<endl;
        return;
    /* New value is less than current value in the tree */
    }if(tree->value > newNode->value){
        if(tree->left != NULL){
            insert(tree->left, newNode);
        }else{
            tree->left = newNode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            cout<<"Added new node to the left."<<endl;
            return;
        }
    /* New value is greater than current value in the tree */
    }else{
        if(tree->right != NULL){
            insert(tree->right, newNode);
        }else{
            tree->right = newNode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            cout<<"Added new node to the right."<<endl;
            return;
        }
    }
}

void binTree::del(int val){
    node *parent;
    node *location;
    if(root == NULL){
        cout<<"Cannot delete from an empty tree."<<endl;
        return;
    }
    find(val, &parent, &location);
    if(location == NULL){
        cout<<"Value not present in tree."<<endl;
        return;
    }if(location->left == NULL && location->right == NULL)
        case_a(parent, location);
    if(location->left == NULL && location->right != NULL)
        case_b(parent, location);
    if(location->left != NULL && location->right == NULL)
        case_b(parent, location);
    if(location->left != NULL && location->right != NULL)
        case_c(parent, location);
    free(location);
}

/* Case A for delete function (Both children are null) */
void binTree::case_a(node *par, node *loc){
    /* if parent is null than we are looking at the root node, 
     * since it has no parent and no children we can empty the tree */
    if(par == NULL){
        root = NULL;
    }else{
        /* no children, thus we simply remove the node */
        if(loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}

/* Case B for delete function (One child is not null) */
void binTree::case_b(node *par, node *loc){
    node *child;
    /* Child node is either left or right */
    if(loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    /* Removing the root, since there is a child,
     * the child becomes the new root */
    if(par == NULL){
        root = child;
    }else{
        /* Since there is a child,
         * the removed element is replaced with the child */
        if(loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}

/* Case C for delete function (node has two children) */
void binTree::case_c(node *par, node *loc){
    node *ptr;
    node *ptrsave;
    node *suc;
    node *parsuc;
    /* Succesor will be the smallest element on the right side */
    ptrsave = loc;
    ptr = loc->right;
    while(ptr->left != NULL){
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    /* Succesor has no children, case a */
    if(suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    /* Succesor has a child (namely a right child), case b */
    else
        case_b(parsuc, suc);
    /* We're examining the root, replace with succesor */
    if(par == NULL){
        root = suc;
    }else{
        /* Replace removed element with the succesor */
        if(loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    /* give succesor the removed element's children */
    suc->left = loc->left;
    suc->right = loc->right;
}

/* Perform a preorder traversal */
void binTree::preorder(node *ptr){
    if(root == NULL){
        cout<<"The tree is empty."<<endl;
        return;
    }if(ptr != NULL){
        cout<<ptr->value<<"  ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

/* Perform an inorder traversal */
void binTree::inorder(node *ptr){
    if(root == NULL){
        cout<<"The tree is empty."<<endl;
        return;
    }if(ptr != NULL){
        inorder(ptr->left);
        cout<<ptr->value<<"  ";
        inorder(ptr->right);
    }
}

/* Perform a postorder traversal */
void binTree::postorder(node *ptr){
    if(root == NULL){
        cout<<"The tree is empty."<<endl;
        return;
    }if(ptr != NULL){
        postorder(ptr->left);
        postorder(ptr->right);
        cout<<ptr->value<<"  ";
    }
}

/* Visual representation of the current tree */
void binTree::display(node *ptr, int level){
    int i;
    if(ptr != NULL){
        /* Start from the right most child of the tree */
        display(ptr->right, level+1);
        cout<<endl;
        /* Special identifier for the root node */
        if(ptr == root)
            cout<<"Root->:  ";
        else{
            /* Pad spaces to indicate the 
             * various levels of the tree */
            for(i = 0; i < level; i++)
                cout<<"       ";
        }
        /* print the value and move to the left child */
        cout<<ptr->value;
        display(ptr->left, level+1);
    }
}