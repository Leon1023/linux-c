/*
 * 菜单基础知识示例
 */

#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
    "Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
    "Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
    "Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
    "Exit",(char *)NULL
};

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);


int main(void)
{ 
    ITEM **my_items;    //define a ptr to array of item_ptr
    int c;              //receive user's choice
    MENU *my_menu;      //define a ptr to menu
    WINDOW *my_menu_win;
    int n_choices, i;
    ITEM *cur_item;     //a ptr to current item

    /* 初始化 curses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    /* 创建菜单项 */
    n_choices = ARRAY_SIZE(choices);    //number of choices
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *)); // alocate sizes for array of item_ptr
    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]); //creat items and it's describes 

    /* 创建菜单 */
    my_menu = new_menu((ITEM **)my_items);

    /* 设置菜单选项，不显示描述 */
    menu_opts_off(my_menu,O_SHOWDESC);

    /* 创建与菜单相关联的窗口*/
    my_menu_win = newwin(10, 50, 4, 8);
    keypad(my_menu_win,TRUE);

    /* 设置主窗口和子窗口 */
    set_menu_win(my_menu,my_menu_win);  //将主窗口和菜单关联
    set_menu_sub(my_menu,derwin(my_menu_win,6, 48, 3, 2));  //子窗口大小
    set_menu_format(my_menu,5, 3);      //滚动窗口格式为5行3列

    /* 设置字符串的标记为 " * " */
    set_menu_mark(my_menu," * ");

    /* 在主窗口的边界打印边框线和标题 */
    box(my_menu_win,0, 0);
    print_in_middle(my_menu_win,1, 0, 48, "My Menu", COLOR_PAIR(1));
    mvwaddch(my_menu_win,2, 0, ACS_LTEE);
    mvwhline(my_menu_win,2, 1, ACS_HLINE, 48);
    mvwaddch(my_menu_win,2, 49, ACS_RTEE);
    mvprintw(LINES - 2, 0, "F1 to exit");
    refresh();

    /* 递送菜单 */
    post_menu(my_menu);
    wrefresh(my_menu_win);

    /* 主窗口显示用户操作提示 */
    attron(COLOR_PAIR(2));
    mvprintw(LINES - 2, 0, "Use PageUp and PageDown to scoll down or up a page of items");
    mvprintw(LINES - 1, 0, "Arrow Keys to navigate (F1 to Exit)");
    attroff(COLOR_PAIR(2));
    refresh();

    while((c = wgetch(my_menu_win)) != KEY_F(1)){ 
        switch(c){ 
            case KEY_DOWN:
                menu_driver(my_menu,REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu,REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(my_menu,REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(my_menu,REQ_RIGHT_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(my_menu,REQ_SCR_DPAGE);
                break;
            case KEY_PPAGE:
                menu_driver(my_menu,REQ_SCR_UPAGE);
                break;
        }
        wrefresh(my_menu_win);
    }

    /* 取消递送并释放占用的内存 */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i = 0; i <= n_choices; ++i)
        free_item(my_items[i]);
    endwin();
    return 0;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{ 
    int length, x, y;
    float temp;
    if(win == NULL)
        win = stdscr;
    getyx(win, y, x);   //get the curser's location
    if(startx != 0)
        x = startx;
    if(starty != 0)
        y = starty;
    if(width == 0)
        width = 80;
        
    length = strlen(string);
    temp = (width - length)/ 2;
    x = startx + (int)temp;

    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}

/*
 * menu_driver(MENU* , REQ_*)函数可以接受以下导览请求：（就是第二个参数）
 * REQ_LEFT_ITEM            左移一个菜单项
 * REQ_RIGHT_ITEM			右移一个菜单项
 * REQ_UP_ITEM			    上移一个菜单项
 * REQ_DOWN_ITEM			下移一个菜单项
 * REQ_SCR_ULINE			向上滚动一行
 * REQ_SCR_DLINE			向下滚动一行
 * REQ_SCR_DPAGE			下翻一页
 * REQ_SCR_UPAGE			上翻一页
 * REQ_FIRST_ITEM			跳到首项
 * REQ_LAST_ITEM			跳到最末一项
 * REQ_NEXT_ITEM			跳到下一项
 * REQ_PREV_ITEM			跳到上一项
 * REQ_TOGGLE_ITEM			选择/取消选择一项
 * REQ_CLEAR_PATTERN		清空菜单模式缓冲区
 * REQ_BACK_PATTERN			删除菜单模式缓冲区的前面一个字符
 * REQ_NEXT_MATCH			跳到下一个与模式匹配的项
 * REQ_PREV_MATCH			跳到上一个与模式匹配的项
 */
