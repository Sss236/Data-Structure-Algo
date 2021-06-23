//enter your name here Yaqian Yang
//enter your email here yang.yaqi@northeastern.edu

#include<stdio.h>
#include<stdlib.h>
typedef struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
    int height;
} avl_node;

/* creating a new node*/
avl_node* NewNode(int data)
{
    avl_node* temp = (avl_node*)malloc(sizeof(avl_node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

/* calculating maximum of 2 numbers*/
int max(int a,int b)
{
     if(a>b)
         return a;
 else return b;
}

/* finding the height of the node*/
int height(avl_node* node)
{
    if(node==NULL)
        return 0;

     return node->height;
}

/* finding the balance factor of the node*/
int Balance(avl_node* node)
{
    if(node==NULL)
        return 0;

     return height(node->left) - height(node->right);//height of Left subtree-height of right subtree.
}

/* function to perform the left rotation of the node and updating the height of left and right subtree*/
avl_node* LeftRotate(avl_node* z)
{
    avl_node* y = z->right;
    avl_node* temp = y->left;

    y->left = z;
    z->right = temp;

    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}

/*--- function to perform the Right rotation and updating the height of left and right subtree--*/
avl_node* RightRotate(avl_node *z)
{
    avl_node* y = z->left;
    avl_node* temp = y->right;

    y->right = z;
    z->left = temp;
/*update the height after right rotation*/
    z->height = max(height(z->left),height(z->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}

/*---------------- function to display the preorder traversal of AVL tree------------*/
void preorder(avl_node *temp)
    {
    
    if(temp!=NULL)
    {
    printf("%d\n",temp->data);
    preorder(temp->left);
    preorder(temp->right);
        free(temp);
    }
    }

/* ----------------function to insert a node*---------------------------*/
/* Insert a node like a Binary search tree, then convert it into a AVL tree using four cases*/
avl_node* Insert(avl_node* root,int data)
{
    
    //INSERT YOUR CODE HERE
    if (root == NULL)
        return(NewNode(data));
 
    if (data < root->data)
        root->left  = Insert(root->left, data);
    else if (data > root->data)
        root->right = Insert(root->right, data);
    else 
        return root;
 
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = Balance(root);
 
    if (balance > 1 && data < root->left->data)
        return RightRotate(root);

    if (balance < -1 && data > root->right->data)
        return LeftRotate(root);

    if (balance > 1 && data > root->left->data)
    {
        root->left =  LeftRotate(root->left);
        return RightRotate(root);
    }
 
    if (balance < -1 && data < root->right->data)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
 
    return root;
}



/*------------------main program-------------------------------*/
    int main()
{
    avl_node *root=NULL;
    int n,x,i;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    printf("Enter the tree data\n");
    root=NULL;
    for(i=0;i<n;i++)
    {
        scanf("%d", &x);
        root= Insert(root,x);
    }
    printf("The output is:\n");
    preorder(root);
    
}
