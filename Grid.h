//
// Created by edoardo on 25/07/24.
//


#ifndef GRID_TEST_GRID_H
#define GRID_TEST_GRID_H
#include "vector"
#include "cell.h"
#include "ncurses.h"
#include "memory"
#include "Menu_option.h"

class Grid{
public:
    explicit Grid(WINDOW* win):window(win),current_position(0){
        int Ymax,Xmax;
        num_columns=num_rows=1;
        getmaxyx(stdscr,Ymax,Xmax);
        for(int i=2;i<(Ymax/2)-1;i+=2){
            for(int j=1;j<(Xmax/2)-2;j++){
                mvwprintw(window,i,j,"-");;
                wrefresh(window);
            }
            num_rows++;

        }

        for(int j=10;j<(Xmax/2)-2;j+=10){
            for(int i=1;i<(Ymax/2)-1;i++){
                if(!(i%2))
                    mvwprintw(window,i,j,"+");
                else
                    mvwprintw(window,i,j,"|");;
                wrefresh(window);
            }
            num_columns++;
        }
        int Ypos=1;

        for(int i=1;i<(Ymax/2)-1;i+=2){
            int Xpos=1;
            for(int j=1;j<(Xmax/2)-2;j+=10){
                Cell* cell= new Cell(Xpos,Ypos,j,i,win,std::to_string((Ypos-1)*num_columns+Xpos));
                for(int k=cell->getContent().length();k<9;k++)
                    cell->setContent(cell->getContent()+' ');
                cells.push_back(cell);
                Xpos++;
                mvwprintw(win,i,j,cell->getContent().c_str());

            }
            Ypos++;

        }

    menu_options= new Menu_option;


    }

    void move(int trigger,attr_t attribute){
        init_pair(1,COLOR_CYAN,COLOR_BLACK);
        init_pair(2,COLOR_WHITE,COLOR_BLACK);
        attr_t menu= COLOR_PAIR(1)|A_REVERSE;
        attr_t grid= COLOR_PAIR(2)|A_REVERSE;

        keypad(window,true);
        display(attribute);
        switch(trigger){
            case KEY_RIGHT:
                if(current_position<num_columns*num_rows-1) {
                    cells[current_position]->setHighlighted(false);
                    current_position++;
                }
                break;



            case KEY_LEFT:
                if(current_position>0) {
                    cells[current_position]->setHighlighted(false);
                    current_position--;

                }
                break;



            case KEY_UP:
                if (current_position-num_columns>-1) {
                    cells[current_position]->setHighlighted(false);
                    current_position -= num_columns;
                }
                break;


            case KEY_DOWN:
                if(current_position+num_columns<num_columns*num_rows){
                    cells[current_position]->setHighlighted(false);
                    current_position+=num_columns;
                }
                break;

            case 10:
                int choise;
                while((choise= wgetch(window))!='x'){
                    if(choise==10){
                        cells[current_position]->setCurrentOperation(menu_options->getPos());
                        int c;
                        int x_cell_selected=cells[current_position]->getXGraphicPos(),y_cell_selected=cells[current_position]->getYGraphicPos(),p=current_position;
                        std::string selected_cell_content=cells[current_position]->getContent();
                        do{
                            if(cells[p]->getCurrentOperation()==4){
                                char input[10];

                                    wgetstr(window, input);

                                cells[current_position]->setContent(input);
                                for(int i=cells[current_position]->getContent().length();i<9;i++)
                                    cells[current_position]->setContent(cells[current_position]->getContent()+' ');
                                display(grid);
                                std::cout<<cells[current_position]->getContent()<<std::endl;
                                break;

                                //temporary solution, check input in ncourses
                                

                            }

                            chose(c,menu,p);
                            wattron(window,grid);
                            mvwprintw(window,y_cell_selected,x_cell_selected,selected_cell_content.c_str());
                            wattroff(window,grid);

                        }while((c=wgetch(window))!='x');
                        cells[current_position]->setHighlighted(false);
                        current_position=p;
                        cells[current_position]->setHighlighted(true);
                        display(grid);
                        if(cells[p]->getCurrentOperation()==4){
                            break;
                        }
                    }
                    menu_options->move(choise);
                    menu_options->display_menu(menu_options->getPos());

                }

            default:
                break;

        }
        cells[current_position]->setHighlighted(true);
        display(attribute);




    }
    void display(attr_t attr){


        for(auto cell:cells){
            if(cell->isHighlighted())
                wattron(window,attr);
            mvwprintw(window,cell->getYGraphicPos(),cell->getXGraphicPos(),cell->getContent().c_str());
            wattroff(window,attr);

        }
        wrefresh(window);
        refresh();


    }

    void chose(int trigger,attr_t attr,int selected_position){
        switch(trigger) {
            case KEY_RIGHT:
                if (current_position < num_columns * num_rows - 1) {
                    cells[current_position]->setHighlighted(false);
                    current_position++;
                    if(current_position==selected_position){
                        cells[current_position]->setHighlighted(false);
                        current_position++;

                    }
                }
                break;


            case KEY_LEFT:
                if (current_position > 0) {
                    cells[current_position]->setHighlighted(false);
                    current_position--;
                    if(current_position==selected_position){
                        cells[current_position]->setHighlighted(false);
                        current_position--;

                    }

                }
                break;


            case KEY_UP:
                if (current_position - num_columns > 0) {
                    cells[current_position]->setHighlighted(false);
                    current_position -= num_columns;
                    if(current_position==selected_position){
                        cells[current_position]->setHighlighted(false);
                        current_position -= num_columns;

                    }
                }
                break;


            case KEY_DOWN:
                if (current_position + num_columns < num_columns * num_rows - 1) {
                    cells[current_position]->setHighlighted(false);
                    current_position += num_columns;
                    if(current_position==selected_position){
                        cells[current_position]->setHighlighted(false);
                        current_position += num_columns;

                    }

                }
                break;
            case 10:








                //select the content in singular cell vector

                break;
            default:
                break;


        }

        cells[current_position]->setHighlighted(true);
        display(attr);

    }

private:
    std::vector<Cell*>cells;
    int num_columns, num_rows, current_position;
    WINDOW* window;
    Menu_option* menu_options;

};


#endif //GRID_TEST_GRID_H
