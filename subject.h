//
// Created by edoardo on 20/08/24.
//

#include "observer.h"

#ifndef GRID_TEST_SUBJECT_H

class subject{
public:
    virtual ~subject() = default;

    virtual void erase_last_observer()=0;
    virtual void insert_observer(std::shared_ptr<observer>observer)=0;
    virtual void notify()=0;
    virtual std::string get_subject_content()=0;
    virtual int get_subject_position()=0;
    virtual int get_subject_graphic_posY()=0;
    virtual int get_subject_graphic_posX()=0;
    virtual void erase_specific_observer(int obs_grid_pos)=0;



};
#define GRID_TEST_SUBJECT_H

#endif //GRID_TEST_SUBJECT_H
