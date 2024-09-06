//
// Created by edoardo on 06/09/24.
//
#include "gtest/gtest.h"
#include "../info_menu.h"
#include "ncurses.h"
#include "../cell.h"
class info_menuSuite : public ::testing::Test {
protected:
    void SetUp() override{
        w= newwin(55 / 2, 40, 55 / 4, 0);

        i=new info_menu(w);

    }
    info_menu* i=nullptr;
    WINDOW *w= nullptr;



};

TEST_F(info_menuSuite,test_display_cell_info){
    Cell*c=new Cell(1,1,1,1, nullptr,"1",i->getInfoWindow());
    i->display_cell_info(c);

}