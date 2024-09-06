//
// Created by edoardo on 26/07/24.
//




#ifndef GRID_TEST_MENU_Hclass
#define GRID_TEST_MENU_Hclass
#include "string"
#include "ncurses.h"
#include "memory"
class Menu_option{
public:
    Menu_option();



    void move(int choise);





    void display_menu(int highlight,attr_t attr);




    int getPos() const {
        return pos;
    }

private:
    std::string options[5]={"Maximus","Minimum","Mean","Summation","Insert number"};
    WINDOW * menu_window;
    int pos;

};


#endif //GRID_TEST_MENU_H
