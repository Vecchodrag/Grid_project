//
// Created by edoardo on 26/08/24.
//

#include <ncurses.h>
#ifndef INFO_MENU_H
class info_menu {
public:
    info_menu() {
        int ymax=getmaxy(stdscr);
        info_window=newwin(ymax/2,40,ymax/4,0);
        box(info_window,0,0);

        mvwprintw(info_window,0,17," Info ");
        wrefresh(info_window);
        refresh();
    }

    void show_info(std::string info) {
        clean();
        int i=0,k=1;
        std::string sub_info;
        while(i<info.size()) {
            sub_info=info.substr(i,38);

            mvwprintw(info_window,k,1,sub_info.c_str());
            k++;

            i+=38;


        }

        wrefresh(info_window);
    }

    void clean() {
        int ymax=getmaxy(stdscr);
        for(int i=1;i<ymax/2-1;i++)
            mvwprintw(info_window,i,1,"                                      ");
    }
private:
    WINDOW* info_window;

};
#define INFO_MENU_H

#endif //INFO_MENU_H
