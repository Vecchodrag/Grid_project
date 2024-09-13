
#ifndef INFO_MENU_H
#include <ncurses.h>
#include "cell.h"
class info_menu {
public:
    explicit info_menu(WINDOW* i);
    void show_info(const std::string& info, int y)const;
    void clean()const;
    void display_cell_info(const std::shared_ptr<Cell>& cells)const;
    [[nodiscard]] WINDOW *getInfoWindow() const;
private:
    WINDOW* info_window;
};
#define INFO_MENU_H

#endif //INFO_MENU_H
