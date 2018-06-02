typedef int LElemType;
typedef int Status; 

typedef struct Node {
    LElemType data;
    struct Node *next;
}Node,*NodePtr;

typedef struct SRLList{
    NodePtr head;
    NodePtr rear;
}SRLList,*SRLListPtr;

#define  OK 0
#define  ERROR  1

NodePtr CreatNode(void);
Status SRLLInit(SRLListPtr);
int SRLLLength(SRLListPtr);
Status SRLLDisplay(SRLListPtr);
Status SRLLInsert(SRLListPtr, int, LElemType );
Status NodeDelete(SRLListPtr, int);
Status SRLLDestroy(SRLListPtr);
SRLListPtr SRLLUnion(SRLListPtr,SRLListPtr);
