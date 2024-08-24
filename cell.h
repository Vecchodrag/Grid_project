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

        switch (this->current_operation) {
            case 0:
                this->get_max();
                break;
            case 1:
                this->get_min();
                break;
            case 2:
                this->mean();
                break;
            case 3:
                this->summatory();
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
        return get_position();
    }
    int get_observer_position()override{
        return get_position();
    }

    void list_subjects_contents() {
        for(auto subject: subjects) {
            printw(std::to_string(subject->get_subject_content()).c_str());
            refresh();
        }
    }


    void summatory(){
        int sum=0;
        for(auto subject: subjects){
            sum+=subject->get_subject_content();
        }
        insert_number(sum);
    }

    void mean(){
        int sum=0,i=0;
        for(auto subject: subjects){
            sum+=subject->get_subject_content();
            i++;
        }
        insert_number(sum/i);

    }

    void insert_number(int num){
        content=std::to_string(num);

        for(int i=content.length();i<9;i++)
            content=content+' ';
        notify();
    }

    void get_max(){
        int max=subjects[0]->get_subject_content();
        for( auto subject: subjects){
            if(subject->get_subject_content()>max)
                max=subject->get_subject_content();
        }
        insert_number(max);
    }
    void get_min(){

        int min=subjects[0]->get_subject_content();

        for(auto subject: subjects){
            if(subject->get_subject_content()<min)
                min=subject->get_subject_content();
        }

        insert_number(min);
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
    int how_many_observers(){
        int num_observers=0;
        for(auto observer:observers)
            num_observers++;
        return num_observers;


    }

    int get_last_subject_position(){
        return subjects[how_many_subjects()-1]->get_subject_position();
    }

    int get_position () const{
        int position= y_pos*10+x_pos;
        position-=11;
        return position;
    }

    void erase_specific_observer(int obs_grid_pos){
        int observer_pos=0;
        for(auto observer: observers){
            if(observer->get_observer_position()==obs_grid_pos){
                if(observer_pos==how_many_observers()-1){
                    observers.pop_back();
                    return;
                }
                for(int i=observer_pos;i<how_many_observers()-1;i++){
                    observers[observer_pos]=observers[observer_pos+1];
                }
                observers.pop_back();

            }
                observer_pos++;

        }

    }
     int get_subject_graphic_posY() override {
        return y_graphic_pos;
    }
    int get_subject_graphic_posX()override {
        return x_graphic_pos;
    }
    void display_subjects(attr_t att_subject) {
        std::string content;
        for(auto subject: subjects) {
           wattron(window,att_subject);
            content=std::to_string(subject->get_subject_content());
            for(int i=content.length();i<9;i++)
                content=content+' ';
            mvwprintw(window,subject->get_subject_graphic_posY(),subject->get_subject_graphic_posX(),content.c_str());


            wattroff(window,att_subject);


        }


    }
    int get_observer_graphic_posY() override {
        return y_graphic_pos;
    }

    int get_observer_graphic_posX()override {
        return x_graphic_pos;
    }

    int get_observer_content() override {
        return stoi(this->content);
    }


    void display_observers(attr_t att_observer) {
        std::string content;
        for(auto observer: observers) {
            wattron(window,att_observer);
            content=std::to_string(observer->get_observer_content());
            for(int i=content.length();i<9;i++)
                content=content+' ';
            mvwprintw(window,observer->get_observer_graphic_posY(),observer->get_observer_graphic_posX(),content.c_str());


            wattroff(window,att_observer);


        }


    }

    bool is_reachable(int current_position) {
        bool reachable=true;
        for(auto observer: observers) {
            if(observer->get_observer_position()==current_position)
                reachable=false;
        }
        return reachable;
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
