#define OK 0
#define ERROR 1

typedef int Status;
typedef int QElemType;

typedef struct LQNode{
    QElemType data;
    struct LQNode *next;
}LQNode,*LQNodePtr;

typedef struct LQueue{
    LQNodePtr front;
    LQNodePtr rear;
}LQueue,*LQueuePtr;


Status InitLQueue(LQueuePtr);
Status InLQueue(LQueuePtr, QElemType);
Status OutLQueue(LQueuePtr, QElemType *);
