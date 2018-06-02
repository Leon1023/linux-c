#define TElemType char
typedef struct BiNode{
    TElemType data;
    struct BiNode *LChild, *RChild;
}BiTNode, *BiTree;

void PreOrderTraverse( BiTree );
void InOrderTraverse( BiTree );
void PostOrderTraverse( BiTree );
void CreatPreOrdBiTree( BiTree * );
void CreatInOrdBiTree( BiTree * );
void CreatPostOrdBiTree( BiTree * );

