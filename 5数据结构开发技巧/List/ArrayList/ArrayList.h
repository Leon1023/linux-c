#define ALSIZE 20
#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0

typedef int LElemType;
typedef int Status;
typedef struct AList{
    LElemType data[ALSIZE];
    int length;
}AList,*AListPtr;

Status AListEmpty(AListPtr);
Status AListClear(AListPtr);
Status AListGetElem(AListPtr, int, LElemType *);
int AListLocate(AListPtr,LElemType);
Status AListInsert(AListPtr,int,LElemType);
Status AListDelete(AListPtr,int,LElemType *);
