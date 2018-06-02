typedef int SElemType;
typedef int Status; 
typedef struct Node {
    SElemType data;
    struct Node *next;
}Node,*NodePtr;

typedef struct LStack {
    NodePtr top;
    int count;
}LStack,*LStackPtr;

#define  OK 0
#define  ERROR  1
#define  FALSE 0
#define  TRUE  1

Status LSInit(LStackPtr);
int LSLength(LStackPtr);
Status LSDisplay(LStackPtr);
Status Push(LStackPtr, SElemType );
Status Pop(LStackPtr, SElemType *);
Status LSDestroy(LStackPtr);
