//
// Created by edoardo on 30/08/24.
//
#include "Menu_option.h"

Menu_option::Menu_option(): pos(0) {
    int Xmax = 204;
    menu_window = newwin(7, (Xmax / 2) - 1, 2, Xmax / 4);
    box(menu_window, 0, 0);
    refresh();
    wrefresh(menu_window);

    for (int i = 0; i < 5; i++) {
        int length=options[i].length();
        for (int j = 0; j < (Xmax/2)-3-length; j++) {
            options[i]=options[i]+' ';
        }
        mvwprintw(menu_window, i + 1, 1, options[i].c_str());
    }
    keypad(menu_window,true);
    mvwprintw(menu_window,0,42," Options ");
    wrefresh(menu_window);
}

void Menu_option::move(int choise) {
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
    display_menu(pos,A_REVERSE);
}

void Menu_option::display_menu(int highlight, attr_t attr)const {
    for(int i=0;i<5;i++){
        if(i==highlight)
            wattron(menu_window,attr);
        mvwprintw(menu_window, i + 1, 1, options[i].c_str());
        wattroff(menu_window,attr);
    }
    wrefresh(menu_window);
    refresh();
}


