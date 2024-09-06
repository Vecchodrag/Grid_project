//
// Created by edoardo on 06/09/24.
//

#include "gtest/gtest.h"
#include "../Menu_option.h"
#include "ncurses.h"
class Menu_optionSuite : public ::testing::Test {
protected:
    void SetUp() override{

        m=new Menu_option();

    }
   Menu_option* m=nullptr;



};

TEST_F(Menu_optionSuite,constructor){
    ASSERT_EQ(m->getPos(),0);
}


TEST_F(Menu_optionSuite,test_move){
    m->move(KEY_DOWN);
    ASSERT_EQ(m->getPos(),1);
    m->move(KEY_UP);
    ASSERT_EQ(m->getPos(),0);
    m->move(KEY_LEFT);
    ASSERT_EQ(m->getPos(),0);


}
