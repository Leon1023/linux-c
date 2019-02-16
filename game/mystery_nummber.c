#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

typedef enum {EASY,MIDDLE,HARD}level;
typedef enum {MP,MM}mode;

//函数set_disp_mode用于控制是否开启输入回显功能
//如果option为0，则关闭回显，为1则打开回显
int set_disp_mode(int fd,int option)
{
   int err;
   struct termios term;
   if(tcgetattr(fd,&term)==-1){
     perror("Cannot get the attribution of the terminal");
     return 1;
   }
   if(option)
        term.c_lflag|=ECHOFLAGS;
   else
        term.c_lflag &=~ECHOFLAGS;
   err=tcsetattr(fd,TCSAFLUSH,&term);
   if(err==-1 && err==EINTR){
        perror("Cannot set the attribution of the terminal");
        return 1;
   }
   return 0;
}
//函数get_num用于获得用户输入的数字，并将其存储在指定的字符数组中
int get_num_array(char* num_array, int size)
{
    int c;
    int n = 0;
  
    scanf("%*[^\n]");
    getc(stdin);
 //  printf("Please Input password:");
   do{
      c=getc(stdin);
      if (c != '\n'|c!='\r'){
         num_array[n++] = c;
      }
   }while(c != '\n' && c !='\r' && n < (size - 1));
   num_array[n] = '\0';
   return n;
}



int get_mode( mode* ptr_md )
{
    scanf("%*[^\n]");  //get and abandon the chars in the old line
    getc(stdin);     //get the last char of '\n' in the old line

    printf("请选择模式：(a)人机对战\t\t(b)人人对战\n");
    switch (fgetc(stdin)){
        case 'a':
            printf("您选择了人机对战模式！\n");
            *ptr_md = MP;
            break;
        case 'b':
            printf("您选择了人人对战模式！\n");
            *ptr_md = MM;
            break;
        default :
            printf("Waring of mode:您的输入有误!\n\n");
            return 1;
    }
    return 0;
}


int get_level(level *ptr_lv)
{
    scanf("%*[^\n]");  //get and abandon the chars in the old line
    getc(stdin);     //get the last char of '\n' in the old line

    printf("请选择级别：(a)简单\t(b)中等\t(c)困难\n");
    switch (fgetc(stdin)){
        case 'a':
            printf("您选择了[简单]级别！\n");
            *ptr_lv = EASY;
            break;
        case 'b':
            printf("您选择了[中等]级别！\n");
            *ptr_lv = MIDDLE;
            break;
        case 'c':
            printf("您选择了[困难]级别！\n");
            *ptr_lv = HARD;
            break;
        default:
            printf("Waring of level:您的输入有误!\n");
            return 1;
    }
    return 0;
}

long get_mystery_num( mode md, level lv)
{
    long min=0,max,mystery_num;
    char num_array[5]={0};
    if(md == MP){   //man VS PC
        switch(lv){
            case EASY:
                max = 100;
                break;
            case MIDDLE:
                max = 1000;
                break;
            case HARD:
                max = 10000;
                break;
            default :
                fprintf(stderr,"error:wrong level input!");
                exit(EXIT_FAILURE);
        }
        srand(time(NULL));
        mystery_num = ((rand()%(max-min+1))+min);
    }
    else if(md == MM){  //man VS man
        switch(lv){
            case EASY:
                printf("请输入你让他猜的神秘数字[0 - 100]:");
                do{
                    set_disp_mode(STDIN_FILENO,0);
                    get_num_array(num_array, sizeof(num_array));
                    set_disp_mode(STDIN_FILENO,1);
                    if(0 == sscanf(num_array,"%ld",&mystery_num)){
                        printf("请输入[0-100]范围内的数！\n");
                        scanf("%*[^\n]");
                        getc(stdin);
                        continue;
                   }
                    scanf("%*[^\n]");
                    getc(stdin);
                    if( (0 <= mystery_num) && (100 >= mystery_num) )
                        break;
                    else{
                        printf("请输入[0-100]范围内的数！\n");
                        continue;
                    }
                }while(1);
                break;
            case MIDDLE:
                printf("请输入你让他猜的神秘数字[0 - 1000]:");
                do{
                    set_disp_mode(STDIN_FILENO,0);
                    get_num_array(num_array, sizeof(num_array));
                    set_disp_mode(STDIN_FILENO,1);
                    if(0 == sscanf(num_array,"%ld",&mystery_num)){
                        printf("请输入[0-1000]范围内的数！\n");
                        scanf("%*[^\n]");
                        getc(stdin);
                        continue;
                   }
                    scanf("%*[^\n]");
                    getc(stdin);
                    if( (0 <= mystery_num) && (1000 >= mystery_num) )
                        break;
                    else{
                        printf("请输入[0-1000]范围内的数！\n");
                        continue;
                    }
                }while(1);
                break;
            case HARD:
                printf("请输入你让他猜的神秘数字[0 - 10000]:");
                do{
                    set_disp_mode(STDIN_FILENO,0);
                    get_num_array(num_array, sizeof(num_array));
                    set_disp_mode(STDIN_FILENO,1);
                    if(0 == sscanf(num_array,"%ld",&mystery_num)){
                        printf("请输入[0-10000]范围内的数！\n");
                        scanf("%*[^\n]");
                        getc(stdin);
                        continue;
                   }
                    scanf("%*[^\n]");
                    getc(stdin);
                    if( (0 <= mystery_num) && (10000 >= mystery_num) )
                        break;
                    else{
                        printf("请输入[0-10000]范围内的数！\n");
                        continue;
                    }
                }while(1);
                break;
            default :
                fprintf(stderr,"error:wrong level input!");
                exit(EXIT_FAILURE);
        }
    }else{
        fprintf(stderr,"error:wrong mode input!");
        exit(EXIT_FAILURE);
    }

    return mystery_num;
}


int main(void)
{
    long mystery_num,your_num=0;
    mode md;
    level lv;
    char st;
    do{
        unsigned int count=0;
        scanf("%*[^\n]");  //get and abandon the chars in the old line
        getc(stdin);     //get the last char of '\n' in the old line

        printf("\t\t欢迎来到Leon的猜数迷游戏！\n");
        printf("\t(a)进入游戏\t(b)退出游戏\n");

        st = getc(stdin);

        if(('b' != st) && ('a' != st)){
            printf("您的输入有误，请重新输入！\n");
            continue;
        }

        if('b' == st){
            printf("Bye-bye!");
            return 0;
        }

        printf("\t\t您已进入游戏！\n");
        //slect the Mode
        do{
            if(1 == get_mode( &md )){ //when user have a invalid input
                 getc(stdin);      //abandon the last '\n' of the old line
                 continue;
            }
            break;
        }while(1);

        //slect the Level
        do{
            if(1 == get_level( &lv )){ //when user have a invalid input
                 continue;
            }
            break;
        }while(1);

        //get the mystery nummber 
        mystery_num = get_mystery_num(md,lv);

        //compare the user's nummber with mystery nummber
        do{
            printf("Enter your nummber:");
            count++;
            if(0==scanf("%ld",&your_num)){
                printf("请正确输入您的数字！\(简单[0-100] 中等[0-1000] 困难[0-10000]\)\n");
                scanf("%*[^\n]");
                getc(stdin);
                continue;
            }
            if(your_num < mystery_num)
                printf("你猜的太小了！\n");
            else if(your_num > mystery_num)
                printf("你猜的太大了！\n");
            else{
                printf("恭喜你用了%d步猜对啦！\n",count);
                break;
            }
        }while(1);

        getc(stdin);//abandon the last '\n' of the old line
    }while(1);

    return 0;
}

