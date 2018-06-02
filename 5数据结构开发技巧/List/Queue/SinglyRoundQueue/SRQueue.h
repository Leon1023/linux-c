#define QSize 5
#define OK 0
#define ERROR 1

typedef int Status;
typedef int QElemType;
typedef struct SRQueue{
    QElemType data[QSize];
    int front;
    int rear;
}SRQueue,*SRQueuePtr;

Status InitSRQueue(SRQueuePtr);
int SRQLength(SRQueue);
Status InSRQueue(SRQueuePtr, QElemType);
Status OutSRQueue(SRQueuePtr, QElemType *);
Status SRQDisplay(SRQueue);
