/*
 *we can define some func,and link them to each item.
 *when user selectd a item, it may run the linked  func
 */
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "choice 1",
    "choice 2",
    "choice 3",
    "choice 4",
    "choice 5",
    "choice 6",
    "choice 7",
    "Exit"
};

void func(char *name);
int main()
{
    ITEM ** my_items;
    int c;
    MENU * my_menu;
    int n_choices,i;
    ITEM *cur_item;

    //initial curses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_MAGENTA,COLOR_BLACK);

    //init items
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices+1,sizeof(ITEM *));
    for(i=0; i<n_choices; i++){
        my_items[i] = new_item(choices[i],choices[i]);
        //set userptr
        set_item_userptr(my_items[i],func);
    }
    my_items[n_choices] = (ITEM *)NULL;

    //link items to menu
    my_menu = new_menu((ITEM **)my_items);

    //add note and post menu
    mvprintw(LINES-3,0,"Press <Enter> to see the option selected.");
    mvprintw(LINES-2,0,"Up and Down arrow keys to navige(F1 to Exit)");
    post_menu(my_menu);
    refresh();

    while((c=getch())!=KEY_F(1)){
        switch(c){
            case KEY_DOWN:
                menu_driver(my_menu,REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu,REQ_UP_ITEM);
                break;
            case 10:    //the key of enter
            {   ITEM *cur;
                void (*p)(char *);
                cur = current_item(my_menu);
                p = item_userptr(cur);
                p((char *)item_name(cur));
                pos_menu_cursor(my_menu);
                break;
            }
            break;
        }
    }
    unpost_menu(my_menu);
    for(i=0; i<n_choices; i++)
        free_item(my_items[i]);
    free_menu(my_menu);
    endwin();
}

void func(char *name)
{
    move(10,0);
    clrtoeol();
    mvprintw(10,0,"Item selected is :%s",name);
}



