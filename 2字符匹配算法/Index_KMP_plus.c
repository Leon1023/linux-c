typedef char* String;
//字符串放在字符型数组中，数组下标为0的空间存储字符串的长度，由于是char型，所以
//字符串最大长度为255
void get_next_plus(String T, int *next_plus)
{
    int i,j;
    i = 1;
    j = 0;
    next_plus[0] = 0;
    next_plus[1] = 0;
    while(i<T[0]){ //T[0] is the lengh of T string.
        if(j==0||T[i]==T[j]){ //T[i] is the surfix
            i++;              //T[j] is the prefix
            j++;
            if(T[i]!=T[j])   //
                next_plus[i] = j;
            else
                next_plus[i] = next_plus[j];
        }
        else
            j = next_plus[j];      //reset j
    }
}

//return the position of the string T in string S after the char which with the
//position of pos.if T not in S,then return 0;
int Index_KMP(String S, String T, int pos)
{
    int i = pos;//i is the string S's index
    int j = 1;  //j is the string T's index
    int next[255];//the max len of string is 255
    get_next_plus(T, next_plus);
    while(i<=S[0] && j<=T[0]){
        if(j==0 || S[i]==T[j]){
            i++;
            j++;
        }else
            j = next_plus[j];//if not match,then reset j
    }
    if(j>T[0])
        return i-T[0];
    else 
        return 0;
}
