//
// Created by edoardo on 25/07/24.
//


#ifndef GRID_TEST_GRID_H
#define GRID_TEST_GRID_H

#include <cstring>
#include "vector"
#include "cell.h"
#include "ncurses.h"
#include "memory"
#include "Menu_option.h"
#include "info_menu.h"


class Grid{
public:
    explicit Grid(WINDOW* win);
    void build_grid();




    void move(int trigger,attr_t attribute);

    void display(attr_t attr);


    void chose(int trigger,attr_t attr,int selected_position);

    bool check_if_last_cell(int selected_position);



private:
    std::vector<Cell*>cells;
    int num_columns, num_rows, current_position;
    WINDOW* window;
    Menu_option* menu_options;
    info_menu* info_menu_;


};



#endif //GRID_TEST_GRID_H
