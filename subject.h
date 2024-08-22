//
// Created by edoardo on 20/08/24.
//

#include "observer.h"

#ifndef GRID_TEST_SUBJECT_H

class subject{
public:
    virtual void erase_last_observer()=0;
    virtual void insert_observer(observer* observer)=0;
    virtual void notify()=0;
    virtual int get_subject_content()=0;
    virtual int get_subject_position()=0;

};
#define GRID_TEST_SUBJECT_H

#endif //GRID_TEST_SUBJECT_H
