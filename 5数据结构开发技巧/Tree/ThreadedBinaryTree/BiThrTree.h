#define OK 0
#define ERROR 1
#define FALSE 0
#define TRUE 1

typedef enum {Link,Thead} PointerTag;

typedef struct BiThrTree {
    TElemType data;
    struct BiThrTree *LChild,*RChild;
    PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre;

void InThreading(BiThrTree);
void PreThreading(BiThrTree);
void PostThreading(BiThrTree);
Status InOrderTraverse_Thr( BiThrTree )
