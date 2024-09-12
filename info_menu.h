
#ifndef INFO_MENU_H
#include <ncurses.h>
#include "cell.h"







class info_menu {
public:
    info_menu(WINDOW* i);



    void show_info(const std::string& info, int y);




    void clean();



    void display_cell_info(std::shared_ptr<Cell> cells);

    WINDOW *getInfoWindow() const;


private:
    WINDOW* info_window;


};
#define INFO_MENU_H

#endif //INFO_MENU_H
