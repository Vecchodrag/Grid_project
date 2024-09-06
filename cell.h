//
// Created by edoardo on 25/07/24.
//


#include <memory>
#ifndef GRID_TEST_CELL_H

#include "string"
#include "ncurses.h"
#include "observer.h"
#include "subject.h"
#include "vector"
#include "memory.h"



class Cell final : public observer,public subject{
public:
    Cell(int X_pos,int Y_pos,int X_graphic_pos, int Y_graphic_pos,WINDOW* win, std::string cont,WINDOW* i): x_pos(X_pos),x_graphic_pos(X_graphic_pos),y_pos(Y_pos),y_graphic_pos(Y_graphic_pos),content(cont),window(win),highlighted(

            false),selected(false),current_operation(4),info_window((i)){}

    int getYGraphicPos() const {
        return y_graphic_pos;
    }

    int getXGraphicPos() const {
        return x_graphic_pos;
    }


    const std::string &getContent() const {
        return content;
    }

    void setContent(const std::string &c) {
        Cell::content = c;
    }

    int getXPos() const;

    bool isHighlighted() const {
        return highlighted;
    }

    const std::vector<subject *> &getSubjects() const;

    void setHighlighted(bool h) {
        Cell::highlighted = h;
    }

    void insert_subject(subject* subject) override{
        subjects.push_back(subject);
    }
    void insert_observer(observer* observer)override{
        observers.push_back(observer);
    }

    void erase_last_subject()override{
        subjects.pop_back();
    }
    void erase_last_observer() override{
        observers.pop_back();
    }

    void erase_all_subjects();

    void erase_all_observers();
    void notify() override;

    bool isSelected() const {
        return selected;
    }

    void setSelected(bool s) {
        Cell::selected = s;
    }

    void update()override;

    std::string get_subject_content()override{
        return this->content;

    }
    int get_subject_position()override{
        return get_position();
    }
    int get_observer_position()override{
        return get_position();
    }

    void list_subjects_contents();




    void summatory();




    void clean();



    void mean();




    void insert_number(float num);


    void get_max();


    void get_min();




    int getCurrentOperation() const {
        return current_operation;
    }

    void setCurrentOperation(int currentOperation) {
        current_operation = currentOperation;
    }

    int how_many_subjects();




    int how_many_observers();





    int get_last_subject_position(){
        return subjects[how_many_subjects()-1]->get_subject_position();
    }

    int get_position () const;



    void erase_specific_observer(int obs_grid_pos) override;



     int get_subject_graphic_posY() override {
        return y_graphic_pos;
    }
    int get_subject_graphic_posX()override {
        return x_graphic_pos;
    }
    void display_subjects(attr_t att_subject);




    int get_observer_graphic_posY() override {
        return y_graphic_pos;
    }

    int get_observer_graphic_posX()override {
        return x_graphic_pos;
    }

    std::string get_observer_content() override {
        return this->content;
    }


    void display_observers(attr_t att_observer);





    bool is_reachable(int current_position);



    [[nodiscard]] int x_pos1() const {
        return x_pos;
    }

    [[nodiscard]] int y_pos1() const {
        return y_pos;
    }

    ~Cell() override;

    int getYPos() const;

    const std::vector<observer *> &getObservers() const;

private:
    int x_pos,y_pos,x_graphic_pos,y_graphic_pos;
    WINDOW * window;
    std::string content;
    bool highlighted;
    std::vector<subject*> subjects;
    std::vector<observer*> observers;
    int current_operation;
    bool selected;
    WINDOW* info_window;









};
#define GRID_TEST_CELL_H

#endif //GRID_TEST_CELL_H
