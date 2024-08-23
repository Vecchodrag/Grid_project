//
// Created by edoardo on 20/08/24.
//

#ifndef GRID_TEST_OBSERVER_H

class subject;
class observer{
public:
    virtual void update()=0;
    virtual void erase_last_subject()=0;
    virtual void insert_subject(subject* subject)=0;
    virtual int get_observer_position()=0;



};
#define GRID_TEST_OBSERVER_H

#endif //GRID_TEST_OBSERVER_H
