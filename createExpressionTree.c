#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
 //Write your code here
    int index=0, numVal=0, multiplyer = 1;
    BTNode *cNode;
    Stack stack;
    stack.head = NULL;
    stack.size = 0;


    //Count length of prefix
    while(1)
    {
        if(prefix[index] == NULL)
            break;
        index++;
    }
    index--;

    //Prefix to infix to Node
    while(1)
    {
        if(index == -1)
            break;

        numVal = 0;
        if(prefix[index] == ' ');
        else if(prefix[index] >= '0' && prefix[index]<='9')
        {
            while(1)
            {
                numVal = numVal + (prefix[index] - '0')*multiplyer;
                if(index-1==-1 || prefix[index-1]==' '|| prefix[index-1]<'0' || prefix[index-1]>'9')
                {
                    break;
                }
                multiplyer *= 10;
                index--;
            }
            cNode = malloc(sizeof(BTNode));
            cNode->item = numVal+48;
            cNode->left = NULL;
            cNode->right = NULL;
            push(&stack,cNode);
            numVal = 0;

            multiplyer = 1;
        }
        else
        {
            cNode = malloc(sizeof(BTNode));
            cNode->item = prefix[index];
            cNode->left = peek(stack);
            pop(&stack);
            cNode->right = peek(stack);
            pop(&stack);
            push(&stack,cNode);
        }

        index--;
    }
    *root = peek(stack);
}

void printTree(BTNode *node){
    if(node == NULL)
        return;
    //Write your code here
    printTree(node->left);
    if(node->item > 48)
        printf("%d ",node->item - 48);
    else
        printf("%c ",node->item);
    printTree(node->right);
}


void printTreePostfix(BTNode *node){
   //Write your code here
    BTNode *cNode;
    Stack stack, stack2;
    stack.head = NULL;
    stack.size = 0;
    stack2.head = NULL;
    stack2.size = 0;
    push(&stack,node);

    //Non-recursive postorder travel
    while(1)
    {
        if(isEmptyStack(stack))
            break;

        cNode = peek(stack);
        pop(&stack);
        push(&stack2,cNode);

        //Push Left and Right Nodes
        if(cNode->left != NULL)
            push(&stack,cNode->left);
        if(cNode->right != NULL)
            push(&stack, cNode->right);
    }

    while(1)
    {
        if(isEmptyStack(stack2))
            break;

        if(peek(stack2)->item > 48)
            printf("%d ",peek(stack2)->item-48);
        else
            printf("%c ",peek(stack2)->item);

        pop(&stack2);
    }
}

double computeTree(BTNode *node){
   //Write your code here
    double left_val, right_val, val;

    if(node->item > 48)
        return node->item-48;

    left_val=computeTree(node->left);
    right_val=computeTree(node->right);

    if(node->item == '+')
        val = left_val + right_val ;

    else if(node->item == '-')
        val = left_val  - right_val;

    else if(node->item == '/')
        val = left_val / right_val;

    else if(node->item == '*')
        val = left_val * right_val;

    return val;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}