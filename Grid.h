//
// Created by edoardo on 25/07/24.
//
#ifndef GRID_TEST_GRID_H
#define GRID_TEST_GRID_H

#include <cstring>
#include "vector"
#include "cell.h"
#include "ncurses.h"
#include "memory.h"
#include "Menu_option.h"
#include "info_menu.h"


class Grid{
public:
    explicit Grid(WINDOW* win);
    void build_grid() ;
    void move(int trigger,attr_t attribute);
    void display(attr_t attr)const;
    void chose(int trigger,attr_t attr,int selected_position);
    [[nodiscard]] bool check_if_last_cell(int selected_position)const;
    [[nodiscard]] int get_current_position() const {
        return current_position;
    }

    void set_current_position(int position) {
            current_position = position;
    }
    [[nodiscard]] const std::vector<std::shared_ptr<Cell>> &get_cells() const;
    void elaborate_input(char shield[50], int p);
    void display_selected(attr_t selected_menu_item,int p,attr_t att_observer)const;
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void chose_up(int selected_position);
    void chose_down(int selected_position);
    void chose_left(int selected_position);
    void chose_right(int selected_position);
    ~Grid();

private:
    std::vector<std::shared_ptr<Cell>>cells;
    int num_columns, num_rows, current_position;
    WINDOW* window;
    std::unique_ptr<Menu_option> menu_options;
    std::unique_ptr<info_menu> info_menu_;


};



#endif //GRID_TEST_GRID_H
