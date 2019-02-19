#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {W1,W2,W3,W4,W5,W6,W7} Wrong_num;
    
int prtman(Wrong_num WN)
{
    switch(WN){
        case W1:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\n");
          printf(" |\n");
          printf(" |\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W2:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" | |\n");
          printf(" |\n");
          printf(" |\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W3:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\\|\n");
          printf(" |\n");
          printf(" |\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W4:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\\|/\n");
          printf(" |\n");
          printf(" |\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W5:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\\|/\n");
          printf(" | |\n");
          printf(" |\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W6:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\\|/\n");
          printf(" | |\n");
          printf(" |/\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        case W7:
          printf(" _____\n");
          printf(" | |\n");
          printf(" | O\n");
          printf(" |\\|/\n");
          printf(" | |\n");
          printf(" |/ \\\n");
          printf(" |\n");
          printf("_|__\n");
          break;
        default:
          printf("error:something wrong in prtman\n");
          return 1;
    }
return 0;
}

char read_char(void)
{
    char c=0;
    c = toupper(getc(stdin));
    while(getc(stdin) != '\n')
        ;
    return c;
}

int  main()
{
    for(int i=0;i<7;i++){
        prtman(i);
        putchar('\n');
        putchar('\n');
        putchar('\n');
    }
    return 0;
}


