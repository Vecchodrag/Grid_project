//
// Created by edoardo on 30/08/24.
//
#include "info_menu.h"
#include "memory.h"

info_menu::info_menu(WINDOW *i) {
    info_window=i;


    mvwprintw(info_window,0,17," Info ");
    wrefresh(info_window);
    refresh();
}

void info_menu::show_info(std::string info, int y) {
    int i=0,k=y;
    std::string sub_info;
    while(i<info.size()) {
        sub_info=info.substr(i,38);

        mvwprintw(info_window,k,1,sub_info.c_str());
        k++;

        i+=38;


    }

    wrefresh(info_window);
}

void info_menu::clean() {
    int ymax=55;
    for(int i=1;i<ymax/2-1;i++)
        mvwprintw(info_window,i,1,"                                      ");
}

void info_menu::display_cell_info(Cell* cell) {
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_BLUE,COLOR_BLACK);
    clean();
    mvwprintw(info_window,1,1," position= %d:%d",cell->y_pos1(),cell->x_pos1());
    mvwprintw(info_window,2,1," content= %s",cell->getContent().c_str());

    switch (cell->getCurrentOperation()) {
        case 0:
            mvwprintw(info_window,3,1," operation = max");
        break;
        case 1:
            mvwprintw(info_window,3,1," operation = min");
        break;
        case 2:
            mvwprintw(info_window,3,1," operation = mean");
        break;
        case 3:
            mvwprintw(info_window,3,1," operation = summatory");
        break;
        case 4:
            mvwprintw(info_window,3,1," operation = insert number");
        break;

    }
    mvwprintw(info_window,4,1," number of subjects = %d",cell->how_many_subjects());
    mvwprintw(info_window,5,1," number of observers = %d",cell->how_many_observers());
    wattron(info_window,COLOR_PAIR(5));
    show_info("Subjects are cells that, if modified, can modify other cells content",8);
    wattroff(info_window,COLOR_PAIR(5));
    wattron(info_window,COLOR_PAIR(6));
    show_info("Observers are cells that change       whenever their subjects change",11);

    wattroff(info_window,COLOR_PAIR(6));
    show_info("Use arrow keys to move in the grid.   When you want to select a cell, press enter.                                If you want to exit or go back, press x.",14);

    wrefresh(info_window);

}

WINDOW *info_menu::getInfoWindow() const {
    return info_window;
}
