//
// Created by edoardo on 31/08/24.
//
#include "gtest/gtest.h"
#include "../Grid.h"
#include "ncurses.h"

class GridSuite : public ::testing::Test {
protected:
     void SetUp() override{
        w=newwin(102,26,51,13);
        g=new Grid(w);

    }
    Grid* g=nullptr;
    WINDOW*w=nullptr;


};
TEST_F(GridSuite,Test_move) {
    g->move(KEY_RIGHT,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),1);
    g->move(KEY_LEFT,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),0);
    g->move(KEY_LEFT,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),0);
    g->move(KEY_UP,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),0);
    g->move(KEY_DOWN,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),10);
    g->move(KEY_UP,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),0);
    g->set_current_position(129);
    g->move(KEY_RIGHT,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),129);
    g->move(KEY_DOWN,A_REVERSE);
    ASSERT_EQ(g->get_current_position(),129);
    ASSERT_TRUE(g->get_cells()[129]->isHighlighted());
    ASSERT_FALSE(g->get_cells()[67]->isHighlighted());
    char s[50]="50";

    g->elaborate_input(s,129);
    ASSERT_EQ(stoi(g->get_cells()[129]->getContent()),50);
    //g->move(10,A_REVERSE); this requires to a further input by the user
}
TEST_F(GridSuite,Test_chose) {
    g->chose(KEY_LEFT,A_REVERSE,0);
    ASSERT_EQ(g->get_current_position(),0);
    g->chose(KEY_RIGHT,A_REVERSE,0);
    ASSERT_EQ(g->get_current_position(),1);
    g->chose(KEY_LEFT,A_REVERSE,0);
    ASSERT_EQ(g->get_current_position(),1);
    g->chose(10,A_REVERSE,0);

    g->chose(101,A_REVERSE,0);
    g->chose(KEY_LEFT,A_REVERSE,1);

    ASSERT_EQ(g->get_current_position(),2);

    g->chose(KEY_LEFT,A_REVERSE,1);
    ASSERT_EQ(g->get_current_position(),2);
    g->chose(KEY_RIGHT,A_REVERSE,1);
    ASSERT_EQ(g->get_current_position(),3);

    g->chose(KEY_RIGHT,A_REVERSE,3);
    g->chose(10,A_REVERSE,3);
    g->chose(10,A_REVERSE,3);
    g->chose(10,A_REVERSE,3);
    g->chose(120,A_REVERSE,3);
    g->chose(101,A_REVERSE,3);
    ASSERT_EQ(g->get_current_position(),7);
    ASSERT_EQ(g->get_cells()[3]->how_many_subjects(),2);


}