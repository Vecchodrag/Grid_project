//
// Created by edoardo on 30/08/24.
//
#include "Grid.h"

Grid::Grid(WINDOW *win): window(win), current_position(0) {
    int Ymax = 55, Xmax = 204;

    WINDOW *info_window = newwin(Ymax / 2, 40, Ymax / 4, 0);
    box(info_window, 0, 0);


    build_grid();
    int Ypos = 1;

    for (int i = 1; i < (Ymax / 2) - 1; i += 2) {
        int Xpos = 1;
        for (int j = 1; j < (Xmax / 2) - 2; j += 10) {
            Cell* cell =new Cell(Xpos, Ypos, j, i, win, std::to_string(0), info_window);
            for (int k = cell->getContent().length(); k < 9; k++)
                cell->setContent(cell->getContent() + ' ');
            cells.push_back(cell);
            Xpos++;
            mvwprintw(win, i, j, cell->getContent().c_str());
        }
        Ypos++;
    }

    menu_options = new Menu_option;
    info_menu_ = new info_menu(info_window);
}

void Grid::build_grid() {
    int Ymax = 55, Xmax = 204;
    num_columns = num_rows = 1;

    for (int i = 2; i < (Ymax / 2) - 1; i += 2) {
        for (int j = 1; j < (Xmax / 2) - 2; j++) {
            mvwprintw(window, i, j, "-");;
            wrefresh(window);
        }
        num_rows++;
    }

    for (int j = 10; j < (Xmax / 2) - 2; j += 10) {
        for (int i = 1; i < (Ymax / 2) - 1; i++) {
            if (!(i % 2))
                mvwprintw(window, i, j, "+");
            else
                mvwprintw(window, i, j, "|");;
            wrefresh(window);
        }
        num_columns++;
    }
    wrefresh(window);
    int pos = Ymax / 4 + 1;
    std::string number;
    for (int i = 1; i < Ymax / 4 + 1; i++) {
        number = std::to_string(i);
        if (number.length() == 2)
            mvprintw(pos, Xmax / 4 - 3, number.c_str());
        else
            mvprintw(pos, Xmax / 4 - 2, number.c_str());
        pos += 2;
    }
    pos = Xmax / 4 + 5;
    for (int i = 1; i < Xmax / 20 + 1; i++) {
        number = std::to_string(i);
        mvprintw(Ymax / 4 - 1, pos, number.c_str());
        pos += 10;
    }
    refresh();
}

void Grid::move(int trigger, attr_t attribute) {
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_BLUE,COLOR_BLACK);
    attr_t menu = COLOR_PAIR(1) | A_REVERSE;
    attr_t grid = COLOR_PAIR(2) | A_REVERSE;
    attr_t input_attr = COLOR_PAIR(3) | A_REVERSE;
    attr_t selected_menu_item = COLOR_PAIR(4) | A_REVERSE;
    attr_t att_subject = COLOR_PAIR(5) | A_REVERSE;
    attr_t att_obserber = COLOR_PAIR(6) | A_REVERSE;
    keypad(window, true);


    display(attribute);
    switch (trigger) {
        case KEY_RIGHT:
            move_right();
            break;


        case KEY_LEFT:
            move_left();
            break;


        case KEY_UP:
            move_up();
            break;


        case KEY_DOWN:
            move_down();
            break;

        case 10:
            display(selected_menu_item);
            int choise;
            menu_options->display_menu(menu_options->getPos(), input_attr);
            cells[current_position]->display_observers(att_obserber);
            while ((choise = wgetch(window)) != 'x') {
                if (choise == 10) {
                    menu_options->display_menu(menu_options->getPos(), selected_menu_item);
                    cells[current_position]->setCurrentOperation(menu_options->getPos());
                    cells[current_position]->erase_all_subjects();
                    int c;
                    if (cells[current_position]->get_position() != 129)
                        c = KEY_RIGHT;
                    else
                        c = KEY_LEFT;
                    int p = current_position;
                    std::string selected_cell_content = cells[current_position]->getContent();

                    if (cells[p]->getCurrentOperation() == 4) {
                        char shield[50];
                        display(input_attr);
                        keypad(window, false);
                        echo();
                        curs_set(1);
                        mvwgetstr(window, cells[p]->getYGraphicPos(), cells[p]->getXGraphicPos(), shield);
                        elaborate_input(shield, p);
                    } else {
                        do {
                            chose(c, menu, p);
                            display_selected(selected_menu_item, p, att_obserber);
                        } while (!((c = wgetch(window)) == 'x' && cells[p]->how_many_subjects() <= 0) && c != 'e' && !(
                                     check_if_last_cell(p) && c != 'x'));
                        if (c == 'e' || (check_if_last_cell(p) && c != 'x'))
                            chose('e', menu, p);
                    }


                    cells[current_position]->setHighlighted(false);
                    current_position = p;
                    cells[current_position]->setHighlighted(true);
                    display(grid);
                    if (cells[p]->getCurrentOperation() == 4) {
                        break;
                    }


                    if (c == 'e' || !(check_if_last_cell(p) && c != 'x'))
                        break;
                }
                menu_options->move(choise);
                menu_options->display_menu(menu_options->getPos(), input_attr);
            }
            menu_options->display_menu(menu_options->getPos(),A_REVERSE);

        default:
            break;
    }
    cells[current_position]->setHighlighted(true);

    display(grid);
    cells[current_position]->display_subjects(att_subject);
    cells[current_position]->display_observers(att_obserber);
    info_menu_->display_cell_info(cells[current_position]);
}

void Grid::display(attr_t attr) {
    for (auto cell: cells) {
        if (cell->isHighlighted())
            wattron(window, attr);
        mvwprintw(window, cell->getYGraphicPos(), cell->getXGraphicPos(), cell->getContent().c_str());
        wattroff(window, attr);
    }

    wrefresh(window);
    refresh();
}

void Grid::chose(int trigger, attr_t attr, int selected_position) {
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_BLUE,COLOR_BLACK);
    attr_t grid = COLOR_PAIR(2) | A_REVERSE;

    int last;
    bool reachable;
    info_menu_->show_info(
        "Use arrow keys to move in the grid.   When you want to select a cell, press enter.                                If you want to exit or go back, press x. To get the result of the selected  operation, press e. You cannot select observer cells as a subject.",
        14);


    switch (trigger) {
        case KEY_RIGHT:
            chose_right(selected_position,reachable);
            break;

        case KEY_LEFT:
            chose_left(selected_position,reachable);
            break;

        case KEY_UP:
            chose_up(selected_position,reachable);
            break;

        case KEY_DOWN:
            chose_down(selected_position,reachable);
            break;

        case 10:

            cells[selected_position]->insert_subject(cells[current_position]);
            cells[current_position]->insert_observer(cells[selected_position]);
            cells[current_position]->setSelected(true);
            if (!check_if_last_cell(selected_position)) {
                if (current_position != 129)
                    chose(KEY_RIGHT, attr, selected_position);
                else
                    chose(KEY_LEFT, attr, selected_position);
            }


            break;


        case 120:
            last = cells[selected_position]->get_last_subject_position();
            cells[selected_position]->erase_last_subject();
            cells[last]->setSelected(false);
            cells[last]->erase_specific_observer(cells[selected_position]->get_position());


            wrefresh(window);


            break;

        case 101:
            cells[selected_position]->update();
            for (auto cell: cells)
                cell->setSelected(false);
            display(grid);
            cells[selected_position]->notify();


        default:
            break;
    }

    cells[current_position]->setHighlighted(true);
    display(attr);
}

bool Grid::check_if_last_cell(int selected_position) {
    int num_sel_cells = 1;
    for (auto cell: cells) {
        if (cell->isSelected())
            num_sel_cells++;
    }
    num_sel_cells += cells[selected_position]->how_many_observers();
    if (num_sel_cells == 130)
        return true;
    return false;
}

void Grid::elaborate_input(char shield[50], int p) {
    build_grid();
    std::string shield_content = shield;
    for (int i = 0; i < 50; i++)
        shield[i] = '0';


    curs_set(0);
    noecho();
    keypad(window, true);
    bool is_a_number = true;

    for (int i = 0, dot = 0, minus = 0; i < shield_content.length(); i++) {
        if (shield_content[i] == '.')
            dot++;
        if (shield_content[i] == '-')
            minus++;
        if (!isdigit(shield_content[i]) && (
                shield_content[i] != '.' && shield_content[0] != '-') || dot > 1 || minus > 1)
            is_a_number = false;
    }
    if (!is_a_number) {
        info_menu_->clean();
        info_menu_->show_info("that is not a number, press a key to  continue:", 1);
        wrefresh(window);
        getch();
        refresh();
    } else {
        if (shield_content.length() > 8) {
            info_menu_->clean();
            info_menu_->show_info(
                "input is to long: max input length is 8 digits, press a key to continue:", 1);
            build_grid();
            getch();
        } else {
            if (shield_content.length() == 0)
                shield_content = '0';


            cells[current_position]->setContent(shield_content);
            for (int i = cells[current_position]->getContent().length(); i < 9; i++)
                cells[current_position]->
                        setContent(cells[current_position]->getContent() + ' ');
            display(A_REVERSE);

            cells[p]->erase_all_subjects();
            cells[current_position]->notify();
        }
    }
}

void Grid::display_selected(attr_t selected_menu_item, int p, attr_t att_obserber) {
    for (auto itr=cells.begin();itr!=cells.end();itr++) {
        if ((*itr)->isSelected()) {
            wattron(window, selected_menu_item);
            mvwprintw(window, (*itr)->getYGraphicPos(), (*itr)->getXGraphicPos(),
                      (*itr)->getContent().c_str());
            wattroff(window, selected_menu_item);
        }
    }
    wrefresh(window);
    wattron(window, A_REVERSE);
    mvwprintw(window, cells[p]->getYGraphicPos(), cells[p]->getXGraphicPos(), cells[p]->getContent().c_str());
    wattroff(window, A_REVERSE);
    cells[p]->display_observers(att_obserber);
}

void Grid::move_right() {
    if (current_position < num_columns * num_rows - 1) {
        cells[current_position]->setHighlighted(false);
        current_position++;
    }

}

void Grid::move_left() {
    if (current_position > 0) {
        cells[current_position]->setHighlighted(false);
        current_position--;
    }
}

void Grid::move_up() {
    if (current_position - num_columns > -1) {
        cells[current_position]->setHighlighted(false);
        current_position -= num_columns;
    }
}

void Grid::move_down() {
    if (current_position + num_columns < num_columns * num_rows) {
        cells[current_position]->setHighlighted(false);
        current_position += num_columns;
    }
}

void Grid::chose_up(int selected_position,bool reachable) {
    if (current_position - num_columns > -1) {
        cells[current_position]->setHighlighted(false);
        current_position -= num_columns;
        reachable = cells[selected_position]->is_reachable(current_position);
        while ((current_position == selected_position || cells[current_position]->isSelected() || !reachable) &&
               current_position - num_columns > -1) {
            cells[current_position]->setHighlighted(false);
            current_position -= num_columns;
            reachable = cells[selected_position]->is_reachable(current_position);
               }
        if (current_position - num_columns <= 0) {
            while (cells[current_position]->isSelected() || current_position == selected_position || !
                   reachable) {
                cells[current_position]->setHighlighted(false);
                current_position += num_columns;
                reachable = cells[selected_position]->is_reachable(current_position);
                   }
        }
    }
}

void Grid::chose_down(int selected_position,bool reachable) {
    if (current_position + num_columns < num_columns * num_rows) {
        cells[current_position]->setHighlighted(false);
        current_position += num_columns;
        reachable = cells[selected_position]->is_reachable(current_position);
        while ((current_position == selected_position || cells[current_position]->isSelected() || !reachable) &&
               current_position + num_columns < num_columns * num_rows) {
            cells[current_position]->setHighlighted(false);
            current_position += num_columns;
            reachable = cells[selected_position]->is_reachable(current_position);
               }
        if (current_position + num_columns >= num_columns * num_rows) {
            while (cells[current_position]->isSelected() || current_position == selected_position || !
                   reachable) {
                cells[current_position]->setHighlighted(false);
                current_position -= num_columns;
                reachable = cells[selected_position]->is_reachable(current_position);
                   }
        }
    }
}

void Grid::chose_left(int selected_position,bool reachable) {
    if (current_position > 0) {
        cells[current_position]->setHighlighted(false);
        current_position--;
        reachable = cells[selected_position]->is_reachable(current_position);
        while ((current_position == selected_position || cells[current_position]->isSelected() || !reachable) &&
               current_position > 0) {
            cells[current_position]->setHighlighted(false);
            current_position--;
            reachable = cells[selected_position]->is_reachable(current_position);
               }
        if (current_position <= 0) {
            while (cells[current_position]->isSelected() || current_position == selected_position || !
                   reachable) {
                cells[current_position]->setHighlighted(false);
                current_position++;
                reachable = cells[selected_position]->is_reachable(current_position);
                   }
        }
    }
}

void Grid::chose_right(int selected_position,bool reachable) {
    if (current_position < num_columns * num_rows - 1) {
        cells[current_position]->setHighlighted(false);
        current_position++;
        reachable = cells[selected_position]->is_reachable(current_position);
        while ((current_position == selected_position || cells[current_position]->isSelected() || !reachable) &&
               current_position < num_columns * num_rows - 1) {
            cells[current_position]->setHighlighted(false);
            current_position++;
            reachable = cells[selected_position]->is_reachable(current_position);
               }
        if (current_position >= num_columns * num_rows - 1) {
            while (cells[current_position]->isSelected() || current_position == selected_position || !
                   reachable) {
                cells[current_position]->setHighlighted(false);
                current_position--;
                reachable = cells[selected_position]->is_reachable(current_position);
                   }
        }
    }
}
