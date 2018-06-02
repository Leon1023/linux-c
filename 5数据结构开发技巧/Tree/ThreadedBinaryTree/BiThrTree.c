BiThrTree pre;

void InThreading(BiThrTree p)
{
    if(p){
        InThreading(p->LChild);
        if(!p->LChild){
            p->LTag = Thread;
            p->LChild = pre;
        }
        if(!pre->RChild){
            pre->RTag = Thread;
            pre->RChild = p;
        }
        pre = p;
        InThreading(p->RChild);
    }
}



void PreThreading(BiThrTree p)
{
    if(p){
        if(!p->LChild){
            p->LTag = Thread;
            p->LChild = pre;
        }
        if(!pre->RChild){
            pre->RTag = Thread;
            pre->RChild = p;
        }
        pre = p;
        InThreading(p->LChild);
        InThreading(p->RChild);
    }
}



void PostThreading(BiThrTree p)
{
    InThreading(p->LChild);
    InThreading(p->RChild);
    if(p){
        if(!p->LChild){
            p->LTag = Thread;
            p->LChild = pre;
        }
        if(!pre->RChild){
            pre->RTag = Thread;
            pre->RChild = p;
        }
        pre = p;
    }
}


Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->LChild;
    while(p!=T){
        while(p->LTag==Link){
            p = p->LChild;
        }
        printf("%c",p->data);
        while(p->RTag==Thread && p->RChild!=T){
            p = p->RChild;
            printf("%c",p->data);
        }
        p = p->RChild;
    }
    return OK;
}

/*
Status PreOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->LChild;
    while(p!=T){
        printf("%c",p->data);
        while(p->LTag==Link){
            p = p->LChild;
        }
        printf("%c",p->data);
        while(p->RTag==Thread && p->RChild!=T){
            p = p->RChild;
            printf("%c",p->data);
        }
        p = p->RChild;
    }
    return OK;
}
*/

/*
Status PostOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->LChild;
    while(p!=T){
        printf("%c",p->data);
        while(p->LTag==Link){
            p = p->LChild;
        }
        printf("%c",p->data);
        while(p->RTag==Thread && p->RChild!=T){
            p = p->RChild;
            printf("%c",p->data);
        }
        p = p->RChild;
    }
    return OK;
}
*/
