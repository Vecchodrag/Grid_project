//
// Created by edoardo on 26/08/24.
//

#include <ncurses.h>
#ifndef INFO_MENU_H
class info_menu {
public:
    info_menu() {
        int ymax=getmaxy(stdscr);
        WINDOW* info_window=newwin(ymax/2,40,ymax/4,0);
        box(info_window,0,0);

        mvwprintw(info_window,0,17," Info ");
        wrefresh(info_window);
        refresh();
    }
private:

};
#define INFO_MENU_H

#endif //INFO_MENU_H
