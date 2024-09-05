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
    //g->move(10,A_REVERSE); this requires a further input from the user
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
TEST_F(GridSuite,Test_check_if_last_cell) {
    ASSERT_FALSE(g->check_if_last_cell(0));
    for(int i=1;i<130;i++) {
        g->get_cells()[i]->setSelected(true);
    }
    ASSERT_TRUE(g->check_if_last_cell(0));
}

TEST_F(GridSuite,Test_elaborate_input) {
    char shield[50]="56";
    g->elaborate_input(shield,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),56);
    for(int i=0;i<9;i++)
        shield[i]='9';
    g->elaborate_input(shield,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),56);
    char test[50]="9999999";

    g->elaborate_input(test,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),9999999);

    char words[50]="dfgh";
    g->elaborate_input(words,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),9999999);

    char points[50]="7.8.6";
    g->elaborate_input(points,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),9999999);

    char minus[50]="-8-9-7";
    g->elaborate_input(minus,0);
    ASSERT_EQ(stof(g->get_cells()[0]->getContent()),9999999);

    char correct_n[50]="-8.98";
    g->elaborate_input(correct_n,0);
    ASSERT_EQ(g->get_cells()[0]->getContent(),"-8.98    ");



}

TEST_F(GridSuite,Test_move_right){
    g->move_right();
    ASSERT_EQ(g->get_current_position(),1);
    g->set_current_position(129);
    g->move_right();
    ASSERT_EQ(g->get_current_position(),129);

}



TEST_F(GridSuite,Test_move_left){
    g->move_left();
    ASSERT_EQ(g->get_current_position(),0);
    g->set_current_position(129);
    g->move_left();
    ASSERT_EQ(g->get_current_position(),128);

}
TEST_F(GridSuite,Test_move_up){
    g->move_up();
    ASSERT_EQ(g->get_current_position(),0);
    g->set_current_position(129);
    g->move_up();
    ASSERT_EQ(g->get_current_position(),119);

}
TEST_F(GridSuite,Test_move_down){
    g->move_down();
    ASSERT_EQ(g->get_current_position(),10);
    g->set_current_position(129);
    g->move_down();
    ASSERT_EQ(g->get_current_position(),129);

}
TEST_F(GridSuite,Test_chose_right){
    g->chose_right(1);
    ASSERT_EQ(g->get_current_position(),2);
    g->get_cells()[g->get_current_position()]->insert_observer(g->get_cells()[3]);
    g->chose_right(2);
    ASSERT_EQ(g->get_current_position(),4);
    g->get_cells()[5]->setSelected(true);
    g->chose_right(4);
    ASSERT_EQ(g->get_current_position(),6);
}

TEST_F(GridSuite,Test_chose_left){
    g->chose_left(1);
    ASSERT_EQ(g->get_current_position(),0);
    g->set_current_position(4);
    g->get_cells()[g->get_current_position()]->insert_observer(g->get_cells()[3]);
    g->chose_left(4);
    ASSERT_EQ(g->get_current_position(),2);
    g->get_cells()[1]->setSelected(true);
    g->chose_left(4);
    ASSERT_EQ(g->get_current_position(),0);
}

TEST_F(GridSuite,Test_chose_up){
    g->chose_up(1);
    ASSERT_EQ(g->get_current_position(),0);
    g->set_current_position(50);
    g->get_cells()[g->get_current_position()]->insert_observer(g->get_cells()[40]);
    g->chose_up(50);
    ASSERT_EQ(g->get_current_position(),30);
    g->get_cells()[20]->setSelected(true);
    g->chose_up(30);
    ASSERT_EQ(g->get_current_position(),10);
}

TEST_F(GridSuite,Test_chose_down){
    g->chose_down(0);
    ASSERT_EQ(g->get_current_position(),10);

    g->get_cells()[g->get_current_position()]->insert_observer(g->get_cells()[20]);
    g->chose_down(10);
    ASSERT_EQ(g->get_current_position(),30);
    g->get_cells()[40]->setSelected(true);
    g->chose_down(30);
    ASSERT_EQ(g->get_current_position(),50);
}








