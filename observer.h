//
// Created by edoardo on 20/08/24.
//

#ifndef GRID_TEST_OBSERVER_H

class subject;
class observer{
public:
    virtual ~observer() = default;
    virtual void update()=0;
    virtual void erase_last_subject()=0;
    virtual void insert_subject(std::shared_ptr<subject> subject)=0;
    [[nodiscard]] virtual int get_observer_position() const=0;
    [[nodiscard]] virtual std::string get_observer_content() const=0;
    [[nodiscard]] virtual int get_observer_graphic_posY() const=0;
    [[nodiscard]] virtual int get_observer_graphic_posX()const=0;
};
#define GRID_TEST_OBSERVER_H

#endif //GRID_TEST_OBSERVER_H
