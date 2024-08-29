#include <iostream>
#include "ncurses.h"
#include "Grid.h"
#include "info_menu.h"
#include "Menu_option.h"

int main() {


    initscr();
    noecho();

    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    attr_t menu= COLOR_PAIR(1)|A_REVERSE;
    attr_t grid= COLOR_PAIR(2)|A_REVERSE;
    start_color();

    int Xmax=204,Ymax=55;

    printw(std::to_string(Ymax).c_str());
    printw(std::to_string(Xmax).c_str());
    wresize(stdscr, 55,204);


    WINDOW * window= newwin(Ymax/2,(Xmax/2)-1,Ymax/4,Xmax/4);
    box(window,0,0);
    keypad(window, true);
    refresh();
    wrefresh(window);
    curs_set(0);


    Grid Grid(window);

    int trigger=KEY_LEFT;

    Grid.display(grid);

   do{


       Grid.move(trigger,grid);

    }while((trigger=wgetch(window))!='x');












    endwin();
    return 0;
}
