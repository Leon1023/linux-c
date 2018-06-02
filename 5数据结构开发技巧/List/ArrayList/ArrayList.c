#include <stdio.h>
#include "ArrayList.h"

/*----------------------------------------------*/
Status AListEmpty(AListPtr AL)
{
    return AL->length==0?TRUE:FALSE;
}
/*----------------------------------------------*/
Status AListClear(AListPtr AL)
{
    AL->length = 0;
    return OK;
}
/*----------------------------------------------*/
Status AListGetElem(AListPtr AL, int i, LElemType *OutLElem)
{
    if(AListEmpty(AL) || i<1 || i>AL->length)
        return ERROR;
    *OutLElem = AL->data[i-1];
    return OK;
}
/*----------------------------------------------*/
int AListLocate(AListPtr AL, LElemType elem)
{
    int location,len,locate_elem;
    len = AL->length;
    locate_elem = elem;
    if(AListEmpty(AL))
        return 0;
    for(location=1;location<=len;location++){
        if(AL->data[location] == locate_elem){
            return location;
        }
    }
    return 0;
}
/*----------------------------------------------*/
Status AListInsert(AListPtr AL, int i, LElemType InLElem)
{
    int k;
    if(AL->length==ALSIZE || i<1 || i>AL->length+1){
        return ERROR;
    }
    if(i<=AL->length){
        for(k=AL->length-1;k>=i-1;k--){
            AL->data[k+1] = AL->data[k];
        }
    }
    AL->data[i-1] = InLElem;
    (AL->length)++; 
    return OK;
}
/*----------------------------------------------*/
Status AListDelete(AListPtr AL, int i, LElemType *OutLElem)
{
    int k;
    if(AL->length ==0 || i<1 || i>AL->length){
        return ERROR;
    }
    *OutLElem = AL->data[i-1];
    for(k=i;k<AL->length;k++){
        AL->data[k-1] = AL->data[k];
    }
    AL->length--;
    return OK;
}
/*----------------------------------------------*/
