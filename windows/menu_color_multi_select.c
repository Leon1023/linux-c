#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define CTRLD 4

char *choices[]={
    "Choice 1    ",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Exit"
};

int main()
{
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices, i;
    ITEM *cur_item;

    /*initial curses*/
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);

    /*initial menu's items*/
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices+1,sizeof(ITEM *));
    for(i=0; i<n_choices; ++i)
        my_items[i] = new_item(choices[i],choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    //unenable some item
    item_opts_off(my_items[3],O_SELECTABLE);
    item_opts_off(my_items[6],O_SELECTABLE);

    /*link items to menu*/
    my_menu = new_menu((ITEM **)my_items);

    //set color for menu
    set_menu_fore(my_menu,COLOR_PAIR(1)|A_REVERSE);//set color for selected item
    set_menu_back(my_menu,COLOR_PAIR(2));//set color for unselected item
    set_menu_grey(my_menu,COLOR_PAIR(3));//set color for hiden item

//    /*set the multi_select menu*/
    menu_opts_off(my_menu,O_ONEVALUE);

    /*set the prompt notes*/
    mvprintw(LINES - 3, 0, "Use <SPACE> to select or unselect an item.");
    mvprintw(LINES - 2, 0, "<ENTER> to see presently selected items(F1 to Exit.)");
    post_menu(my_menu);
    refresh();
    int j=0;        /*count the num of lines which illustrated choices last time*/

    while((c = getch())!=KEY_F(1)){
        switch(c){
            case KEY_DOWN:
                menu_driver(my_menu,REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu,REQ_UP_ITEM);
                break;
            case ' ':
                menu_driver(my_menu,REQ_TOGGLE_ITEM);
                break;
            case 10:{                       /*The ASCII num of Enter key*/
                char temp[200];
                ITEM **items;
                items = menu_items(my_menu);
                temp[0] = '\0';
                //clear the last illustrated choices
                while(j){
                    move(10+j,0);
                    clrtoeol();
                    j--;
                }

                for(i=0; i<item_count(my_menu); i++)
                    if(item_value(items[i])==TRUE){
                        strcat(temp,item_name(items[i]));
                        strcat(temp,"\n");
                        j++;
                    }
                mvprintw(10,0,temp);
                refresh();
                }
                break;
        }
    }
    for(int j=0; j<n_choices; j++)
        free_item(my_items[j]);
    free_menu(my_menu);
    endwin();
}

