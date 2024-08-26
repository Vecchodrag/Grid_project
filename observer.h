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
    virtual std::string get_observer_content()=0;
    virtual int get_observer_graphic_posY()=0;
    virtual int get_observer_graphic_posX()=0;



};
#define GRID_TEST_OBSERVER_H

#endif //GRID_TEST_OBSERVER_H
