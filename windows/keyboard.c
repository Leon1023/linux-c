#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>


#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char*);
void print_menu(WINDOW*menu_win, int highlight);

int main(void)
{ 
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();    //clear screen
    curs_set(0);//hiden curser
    noecho();   //not print to screen
    cbreak();   /*禁用行缓冲，直接传递所有输入 */

    startx = (80-WIDTH) / 2;
    starty = (24-HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win,TRUE);
    mvprintw(0, 0,"Use arrow keys to go up and down, Press enter to select a choice.");
    refresh();

    print_menu(menu_win,highlight);
        wgetch(menu_win);
    while(1){ 
        c = wgetch(menu_win);
        switch(c){ 
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case '\n':    //if userpress enter
                choice = highlight;
                break;
            default:
                mvprintw(24, 0, "Charcter pressed is = %3d. Hopefully it can be printed as %c",c,c);
                refresh();
                break;
        }
        print_menu(menu_win,highlight);
        if(choice != 0) /*用户必须要做一个选择*/
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n",choice,choices[choice-1]);
   // clrtoeol();
    refresh();
    //enter tty mode
    def_prog_mode();
    endwin();
    system("$PREFIX/bin/echo 'hello leon'");
    sleep(2);
    //return to curses mode
    reset_prog_mode();
    refresh();
    // show ACS
    clear();    //clear screen
    printw("Upper left corner "); addch(ACS_ULCORNER); printw("\n");
printw("Lower left corner "); addch(ACS_LLCORNER); printw("\n");
printw("Lower right corner "); addch(ACS_LRCORNER); printw("\n");
printw("Tee pointing right "); addch(ACS_LTEE); printw("\n");
printw("Tee pointing left "); addch(ACS_RTEE); printw("\n");
printw("Tee pointing up "); addch(ACS_BTEE); printw("\n");
printw("Tee pointing down "); addch(ACS_TTEE); printw("\n");
printw("Horizontal line "); addch(ACS_HLINE); printw("\n");
printw("Vertical line "); addch(ACS_VLINE); printw("\n");
printw("LargePlus or cross over "); addch(ACS_PLUS); printw("\n");
printw("Scan Line 1 "); addch(ACS_S1); printw("\n");
printw("Scan Line 3 "); addch(ACS_S3); printw("\n");
printw("Scan Line 7 "); addch(ACS_S7); printw("\n");
printw("Scan Line 9 "); addch(ACS_S9); printw("\n");
printw("Diamond "); addch(ACS_DIAMOND); printw("\n");
printw("Checker board (stipple) "); addch(ACS_CKBOARD); printw("\n");
printw("DegreeSymbol "); addch(ACS_DEGREE); printw("\n");
printw("Plus/MinusSymbol "); addch(ACS_PLMINUS); printw("\n");
printw("Bullet "); addch(ACS_BULLET); printw("\n");
printw("Arrow Pointing Left "); addch(ACS_LARROW); printw("\n");
printw("Arrow Pointing Right "); addch(ACS_RARROW); printw("\n");
printw("Arrow Pointing Down "); addch(ACS_DARROW); printw("\n");
printw("Arrow Pointing Up "); addch(ACS_UARROW); printw("\n");
printw("Board of squares "); addch(ACS_BOARD); printw("\n");
printw("LanternSymbol "); addch(ACS_LANTERN); printw("\n");
printw("Solid Square Block "); addch(ACS_BLOCK); printw("\n");
printw("Less/Equal sign "); addch(ACS_LEQUAL); printw("\n");
printw("Greater/Equalsign "); addch(ACS_GEQUAL); printw("\n");
printw("Pi "); addch(ACS_PI); printw("\n");
printw("Not equal "); addch(ACS_NEQUAL); printw("\n");
printw("UK pound sign "); addch(ACS_STERLING); printw("\n");
refresh();


    wgetch(menu_win);
    endwin();
    return 0;
}

void print_menu(WINDOW* menu_win, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i){
        if(highlight == i + 1){ /* 使选择的字符串高亮显示 */
            wattron(menu_win,A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win,A_REVERSE);
        }else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
