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







}