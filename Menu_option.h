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
    Menu_option(): pos(0) {
        int Xmax = getmaxx(stdscr);
        menu_window = newwin(7, (Xmax / 2) - 1, 0, Xmax / 4);
        box(menu_window, 0, 0);
        refresh();
        wrefresh(menu_window);

        for (int i = 0; i < 5; i++) {
            mvwprintw(menu_window, i + 1, 1, options[i].c_str());
        }
        keypad(menu_window,true);
        wrefresh(menu_window);

    }



    void move(int choise){

        switch (choise) {
            case KEY_DOWN:
                if (pos < 4)
                    pos++;


                break;
            case KEY_UP:
                if (pos > 0)
                    pos--;
                break;

            default:
                break;




        }
        display_menu(pos);

    }

    void display_menu(int highlight){
        for(int i=0;i<5;i++){
            if(i==highlight)
                wattron(menu_window,A_REVERSE);
            mvwprintw(menu_window, i + 1, 1, options[i].c_str());
            wattroff(menu_window,A_REVERSE);

        }
        wrefresh(menu_window);

    }

    int getPos() const {
        return pos;
    }

private:
    std::string options[5]={"max","min","mean","sum","insert_num"};
    WINDOW * menu_window;
    int pos;

};


#endif //GRID_TEST_MENU_H
