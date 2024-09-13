//
// Created by edoardo on 25/07/24.
//



#ifndef GRID_TEST_CELL_H
#include <memory>
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

    [[nodiscard]] int getYGraphicPos() const {
        return y_graphic_pos;
    }

    [[nodiscard]] int getXGraphicPos() const {
        return x_graphic_pos;
    }

    [[nodiscard]] const std::string &getContent() const {
        return content;
    }

    void setContent(const std::string &c) {
        Cell::content = c;
    }

    [[nodiscard]] int getXPos() const;
    [[nodiscard]] bool isHighlighted() const {
        return highlighted;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<subject>> &getSubjects() const;
    void setHighlighted(bool h) {
        Cell::highlighted = h;
    }

    void insert_subject(std::shared_ptr<subject> subject) override{
        subjects.push_back(subject);
    }

    void insert_observer(std::shared_ptr<observer> observer)override{
        observers.push_back(observer);
    }

    void erase_last_subject()override{
        subjects.pop_back();
    }

    void erase_last_observer() override{
        observers.pop_back();
    }

    void erase_all_subjects();
    void notify() override;
    [[nodiscard]] bool isSelected() const {
        return selected;
    }

    void setSelected(bool s) {
        Cell::selected = s;
    }

    void update()override;
    [[nodiscard]] std::string get_subject_content()const override{
        return this->content;
    }

    [[nodiscard]] int get_subject_position()const override{
        return get_position();
    }

    [[nodiscard]] int get_observer_position()const override{
        return get_position();
    }

    void summation();
    void clean();
    void mean();
    void insert_number(float num);
    void get_max();
    void get_min();
    [[nodiscard]] int getCurrentOperation() const {
        return current_operation;
    }

    void setCurrentOperation(int currentOperation) {
        current_operation = currentOperation;
    }

    [[nodiscard]] int how_many_subjects()const;
    [[nodiscard]] int how_many_observers() const;
    [[nodiscard]] int get_last_subject_position()const {
        return subjects[how_many_subjects()-1]->get_subject_position();
    }

    [[nodiscard]] int get_position () const;
    void erase_specific_observer(int obs_grid_pos) override;
     [[nodiscard]] int get_subject_graphic_posY() const override {
        return y_graphic_pos;
    }

    [[nodiscard]] int get_subject_graphic_posX()const override {
        return x_graphic_pos;
    }

    void display_subjects(attr_t att_subject) const;
    [[nodiscard]] int get_observer_graphic_posY()const override {
        return y_graphic_pos;
    }

    [[nodiscard]] int get_observer_graphic_posX() const override {
        return x_graphic_pos;
    }


    [[nodiscard]] std::string get_observer_content()const override {
        return this->content;
    }

    void display_observers(attr_t att_observer) const;
    [[nodiscard]] bool is_reachable(int current_position)const;
    [[nodiscard]] int x_pos1() const {
        return x_pos;
    }

    [[nodiscard]] int y_pos1() const {
        return y_pos;
    }

    ~Cell() override;
    [[nodiscard]] int getYPos() const;
    [[nodiscard]] const std::vector<std::shared_ptr<observer>> &getObservers() const;

private:
    int x_pos,y_pos,x_graphic_pos,y_graphic_pos;
    WINDOW * window;
    std::string content;
    bool highlighted;
    std::vector<std::shared_ptr<subject>> subjects;
    std::vector<std::shared_ptr<observer>> observers;
    int current_operation;
    bool selected;
    WINDOW* info_window;









};
#define GRID_TEST_CELL_H

#endif //GRID_TEST_CELL_H
