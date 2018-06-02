typedef int LElemType;
typedef int Status; 
typedef struct Node {
    LElemType data;
    struct Node *next;
}Node,*NodePtr;

#define  OK 0
#define  ERROR  1

NodePtr CreatNode(void);
Status SLLInit(NodePtr);
int SLLLength(NodePtr);
Status SLLDisplay(NodePtr);
Status SLLInsert(NodePtr, int, LElemType );
Status NodeDelete(NodePtr, int);
Status SLLDestroy(NodePtr);
