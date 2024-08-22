//
// Created by edoardo on 25/07/24.
//

#ifndef GRID_TEST_CELL_H
#include "string"
#include "ncurses.h"
#include "observer.h"
#include "subject.h"
class Cell: public observer,public subject{
public:
    Cell(int X_pos,int Y_pos,int X_graphic_pos, int Y_graphic_pos,WINDOW* win, std::string cont): x_pos(X_pos),x_graphic_pos(X_graphic_pos),y_pos(Y_pos),y_graphic_pos(Y_graphic_pos),content(cont),window(win),highlighted(
            false),selected(false){}

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


    bool isHighlighted() const {
        return highlighted;
    }

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

    void erase_all_subjects(){
        for(auto subject:subjects){
            erase_last_subject();
        }
    }

    void erase_all_observers(){
        for(auto observer:observers){
            erase_last_observer();
        }
    }
    void notify() override{
        for(auto observer:observers){
            observer->update();
        }
    }

    bool isSelected() const {
        return selected;
    }

    void setSelected(bool s) {
        Cell::selected = s;
    }

    void update()override{
        switch (current_operation) {
            case 0:
                get_max();
                break;
            case 1:
                get_min();
                break;
            case 2:
                mean();
                break;
            case 3:
                summatory();
                break;

            default:
                std::cout<<"something went wrong"<<std::endl;
                break;
        }
    }

    int get_subject_content()override{
        return stoi(this->content);

    }
    int get_subject_position()override{
        int result=this->y_pos*10+this->x_pos;
        result-=11;

        return result;
    }

    void summatory(){
        int sum=0;
        for(auto subject: subjects){
            sum+=subject->get_subject_content();
        }
        content=std::to_string(sum);
        notify();
    }

    void mean(){
        int sum=0,i=0;
        for(auto subject: subjects){
            sum+=subject->get_subject_content();
            i++;
        }
        content=std::to_string(sum/i);
        notify();

    }

    void insert_number(int num){
        content=std::to_string(num);
        erase_all_subjects();
        notify();
    }

    void get_max(){
        int max=subjects[0]->get_subject_content();
        for(auto subject: subjects){
            if(subject->get_subject_content()>max)
                max=subject->get_subject_content();
        }
        content=std::to_string(max);
        notify();
    }
    void get_min(){
        int min=subjects[0]->get_subject_content();
        for(auto subject: subjects){
            if(subject->get_subject_content()<min)
                min=subject->get_subject_content();
        }
        content=std::to_string(min);
        notify();
    }

    int getCurrentOperation() const {
        return current_operation;
    }

    void setCurrentOperation(int currentOperation) {
        current_operation = currentOperation;
    }

    int how_many_subjects(){
        int num_subjects=0;
        for(auto subject:subjects)
            num_subjects++;
        return num_subjects;


    }
    int get_last_subject_position(){
        return subjects[how_many_subjects()-1]->get_subject_position();
    }

    int get_position(){
        int position= y_pos*13+x_pos;
        return position;
    }




private:
    int x_pos,y_pos,x_graphic_pos,y_graphic_pos;
    WINDOW * window;
    std::string content;
    bool highlighted;
    std::vector<subject*> subjects;
    std::vector<observer*> observers;
    int current_operation;
    bool selected;
public:




};
#define GRID_TEST_CELL_H

#endif //GRID_TEST_CELL_H
