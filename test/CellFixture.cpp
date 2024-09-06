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
        c=new Cell(1,1,1,1,w,"0",i);
         s=new Cell(2,2,2,2,w,"2",i);
         o=new Cell(3,3,3,3,w,"3",i);
        c->insert_subject(s);
        s->insert_observer(c);
        c->insert_observer(o);
        o->insert_subject(c);



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
    ASSERT_EQ(c->getContent(),"0");
}

TEST_F(CellSuite,test_erase_all_subjects){
    c->erase_all_subjects();
    ASSERT_EQ(c->how_many_subjects(),0);

}

TEST_F(CellSuite,test_notify){
    c->setCurrentOperation(1);
    c->getSubjects()[0]->notify();
    ASSERT_EQ(c->getContent(),"2.000000 ");


}

TEST_F(CellSuite, test_update){
    c->setCurrentOperation(3);
    c->update();
    ASSERT_EQ(c->getContent(),"2.000000 ");
    Cell* h=new Cell(4,4,2,2,w,"3",i);
    c->insert_subject(h);
    h->insert_observer(c);
    c->update();
    ASSERT_EQ(c->getContent(),"5.000000 ");

    delete h;


}

TEST_F(CellSuite,test_summatory){
    c->summation();
    ASSERT_EQ(c->getContent(),"2.000000 ");
    Cell* h=new Cell(4,4,2,2,w,"9999999",i);
    c->insert_subject(h);
    h->insert_observer(c);
    c->summation();
    ASSERT_EQ(c->getContent(),"0.000000 ");
    ASSERT_EQ(c->getCurrentOperation(),4);

    delete h;


}

TEST_F(CellSuite,test_mean){
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    c->insert_subject(h);
    h->insert_observer(c);
    c->mean();
    ASSERT_EQ(c->getContent(),"3.000000 ");

}

TEST_F(CellSuite,test_max){
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    c->insert_subject(h);
    h->insert_observer(c);
    c->get_max();
    ASSERT_EQ(c->getContent(),"4.000000 ");

}

TEST_F(CellSuite,test_min){
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    c->insert_subject(h);
    h->insert_observer(c);
    c->get_min();
    ASSERT_EQ(c->getContent(),"2.000000 ");
    delete h;

}

TEST_F(CellSuite,test_insert_num){
    c->insert_number(6.78);
    ASSERT_EQ(c->getContent(),"6.780000 ");
    c->insert_number(-6.7);
    ASSERT_EQ(c->getContent(),"-6.70000 ");
}

TEST_F(CellSuite,test_how_many_observers){
    ASSERT_EQ(c->how_many_observers(),1);
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    c->insert_observer(h);
    h->insert_subject(c);
    ASSERT_EQ(c->how_many_observers(),2);
    delete h;

}

TEST_F(CellSuite,test_how_many_subjects){
    ASSERT_EQ(c->how_many_subjects(),1);
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    c->insert_subject(h);
    h->insert_observer(c);
    ASSERT_EQ(c->how_many_subjects(),2);
    delete h;

}

TEST_F(CellSuite,test_get_position){
    ASSERT_EQ(c->get_position(),0);
    Cell* h=new Cell(4,4,2,2,w,"4",i);
    ASSERT_EQ(h->get_position(),33);
    delete h;

}

TEST_F(CellSuite, test_erase_specific_observer){
    c->erase_specific_observer(22);
    ASSERT_EQ(c->how_many_observers(),0);
}

TEST_F(CellSuite,test_is_reachable){
    ASSERT_FALSE(c->is_reachable(22));
    ASSERT_TRUE(c->is_reachable(1));
}