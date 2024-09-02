//
// Created by edoardo on 30/08/24.
//
#include "cell.h"


void Cell::erase_all_subjects() {

        for(int i=how_many_subjects()-1;i>=0;i--){
            subjects[i]->erase_specific_observer(this->get_position());
            erase_last_subject();
        }

}

void Cell::erase_all_observers() {

        observers.clear();

}

void Cell::notify() {

    for(auto observer:observers){
        observer->update();
    }
}

void Cell::update() {

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

            break;
    }


}

void Cell::list_subjects_contents() {
    for(auto subject: subjects) {
        printw(subject->get_subject_content().c_str());
        refresh();
    }
}

void Cell::summatory() {
    float sum=0;
    for(auto subject: subjects){
        sum+=atof(subject->get_subject_content().c_str());
    }
    std::string sum_string=std::to_string(sum);
    if(sum>100000000){
        clean();
        mvwprintw(info_window,1,1,"the result is to big to display.");
        mvwprintw(info_window,2,1,"Press a key to continue: ");
        wrefresh(info_window);

        getch();



        erase_all_subjects();
        setCurrentOperation(4);
        sum=0;
    }
    insert_number(sum);
}

void Cell::clean() {
    int ymax=55;
    for(int i=1;i<ymax/2-1;i++)
        mvwprintw(info_window,i,1,"                                      ");
}

void Cell::mean() {
    float sum=0;
    int i=0;
    for(auto subject: subjects){
        sum+=atof(subject->get_subject_content().c_str());
        i++;
    }
    insert_number(sum/i);
}

void Cell::insert_number(float num) {
    content=std::to_string(num);
    content.erase(8,content.length()-8);
    if(content[8]=='.')
        content[8]=' ';

    for(int i=content.length();i<9;i++)
        content=content+' ';
    notify();
}

void Cell::get_max() {
    float max=atof(subjects[0]->get_subject_content().c_str());
    for( auto subject: subjects){
        if(atof(subject->get_subject_content().c_str())>max)
            max=atof(subject->get_subject_content().c_str());
    }
    insert_number(max);
}

void Cell::get_min() {
    float min=atof(subjects[0]->get_subject_content().c_str());

    for(auto subject: subjects){
        if(atof(subject->get_subject_content().c_str())<min)
            min=atof(subject->get_subject_content().c_str());
    }

    insert_number(min);
}

int Cell::how_many_subjects() {
    int num_subjects=0;
    for(auto subject:subjects)
        num_subjects++;
    return num_subjects;
}

int Cell::how_many_observers() {
    int num_observers=0;
    for(auto observer:observers)
        num_observers++;
    return num_observers;
}

int Cell::get_position() const {
    int position= y_pos*10+x_pos;
    position-=11;
    return position;
}

void Cell::erase_specific_observer(const int obs_grid_pos) {

    for(auto itr=observers.begin();itr<observers.end();itr++){
        if((*itr)->get_observer_position()==obs_grid_pos){

            observers.erase(itr,itr+1);
            }
    }
}

void Cell::display_subjects(attr_t att_subject) {
    std::string content;
    for(auto subject: subjects) {
        wattron(window,att_subject);
        content=subject->get_subject_content();
        for(int i=content.length();i<9;i++)
            content=content+' ';
        mvwprintw(window,subject->get_subject_graphic_posY(),subject->get_subject_graphic_posX(),content.c_str());


        wattroff(window,att_subject);


    }
}

void Cell::display_observers(attr_t att_observer) {
    std::string content;
    for(auto observer: observers) {
        wattron(window,att_observer);
        content=observer->get_observer_content();
        for(int i=content.length();i<9;i++)
            content=content+' ';
        mvwprintw(window,observer->get_observer_graphic_posY(),observer->get_observer_graphic_posX(),content.c_str());


        wattroff(window,att_observer);


    }
}

bool Cell::is_reachable(int current_position) {
    bool reachable=true;
    for(auto observer: observers) {
        if(observer->get_observer_position()==current_position)
            reachable=false;
    }
    return reachable;
}






