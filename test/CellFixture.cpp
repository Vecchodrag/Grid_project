#include "gtest/gtest.h"
#include "../cell.h"
#include "ncurses.h"
#include "../subject.h"
#include "vector"

class CellSuite : public ::testing::Test {
protected:
    void SetUp() override{
        w=newwin(102,26,51,13);
        i= newwin(55 / 2, 40, 55 / 4, 0);
        c=new Cell(1,1,1,1,w,"C",i);
         s=new Cell(2,2,2,2,w,"S",i);
         o=new Cell(3,3,3,3,w,"O",i);
        c->insert_subject(s);
        c->insert_observer(o);

    }
    Cell* c= nullptr;
    Cell* s= nullptr;
    Cell* o= nullptr;
    WINDOW*w=nullptr;
    WINDOW*i=nullptr;


};

TEST_F(CellSuite,constructor){
    ASSERT_EQ(c->getXGraphicPos(),1);
    ASSERT_EQ(c->getYGraphicPos(),1);
    ASSERT_EQ(c->getXPos(),1);
    ASSERT_EQ(c->getYPos(),1);
    ASSERT_FALSE(c->isSelected());
    ASSERT_FALSE(c->isHighlighted());
    ASSERT_EQ(c->getCurrentOperation(),4);
    ASSERT_EQ(c->getContent(),"C");
}

TEST_F(CellSuite,test_erase_all_subjects){
    c->erase_all_subjects();
    ASSERT_EQ(c->how_many_subjects(),0);

}
