typedef int LElemType;
typedef int Status; 

typedef struct Node {
    LElemType data;
    struct Node *prior;
    struct Node *next;
}Node,*NodePtr;

typedef struct DLList{
    NodePtr head;
    NodePtr rear;
}DLList,*DLListPtr;

#define  OK 0
#define  ERROR  1

NodePtr CreatNode(void);
Status DLLInit(DLListPtr);
int DLLLength(DLListPtr);
Status DLLDisplay(DLListPtr);
Status DLLInsert(DLListPtr, int, LElemType );
Status NodeDelete(DLListPtr, int);
Status DLLDestroy(DLListPtr);
DLListPtr DLLUnion(DLListPtr,DLListPtr);
