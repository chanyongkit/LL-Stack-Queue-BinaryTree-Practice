#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
    Stack stack;
    stack.head = NULL;
    stack.size = 0;
    char op;
    enum ExpType eType;
    int index=0, numVal=0;
    LinkedList tempLL;
    tempLL.head = NULL;
    tempLL.size = 0;
    ListNode *lNode;


    while(1)
    {
        if(infix[index] == '\0')
            break;

        numVal = 0;
        if(infix[index] >= '0' && infix[index]<='9')
        {
            while(1)
            {
                numVal = (numVal*10) + (infix[index] - '0');
                if(infix[index+1]=='\0' || infix[index-1]==' ' || infix[index+1]<'0' || infix[index+1]>'9')
                    break;
                index++;
            }
            insertNode(&tempLL, numVal, OPERAND);
            numVal = 0;
        }
        else
        {
            if(infix[index]!=' ')
                insertNode(&tempLL, infix[index], OPT);
        }

        index++;
    }

    lNode=tempLL.head;
    while(1)
    {
        if(lNode == NULL)
            break;

        if(lNode->type == OPERAND)
        {
            insertNode(inExpLL,lNode->item,OPERAND);
        }
        else
        {
            op = lNode->item;
            if(op == ')')
            {
                push(&stack, op);
            }

            else if(op =='(')
            {
                while(peek(stack)!=')')
                {
                  insertNode(inExpLL,peek(stack),OPT);
                  pop(&stack);
                }

                if(!isEmptyStack(stack))
                    pop(&stack);
            }
            else
            {
                while(1)
                {
                    if(isEmptyStack(stack))
                        break;
                    if(peek(stack)== ')')
                        break;



                    if(lNode->item == '*' || lNode->item == '/')
                        break;
                    else
                    {
                        if(peek(stack)== '+' || peek(stack)== '-')
                        {
                            break;
                        }
                            insertNode(inExpLL,peek(stack),OPT);
                            pop(&stack);
                    }
                }
                push(&stack,op);
            }
        }
        lNode= lNode->next;
    }
    while(1)
    {
        if(isEmptyStack(stack))
            break;

        insertNode(inExpLL,peek(stack),OPT);
        pop(&stack);
    }
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
