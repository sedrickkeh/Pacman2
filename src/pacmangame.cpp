#include "pacmangame.h"

#include <QMessageBox>
#include <QApplication>

const QString PacmanGame::map_dir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman";
const QString PacmanGame::map_path =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman/mapmaker.txt";

PacmanGame::PacmanGame(Mode mode, int highscore, char m) :
    mode(mode),
    pacman(nullptr),
    ghost1(nullptr),
    ghost2(nullptr),
    ghost3(nullptr),
    ghost4(nullptr),
    current_score(0),
    level(1),
    mapmaker_mode(false)
{
    game_window = new GameWindow(nullptr, this);
    for (int k = 0; k < 31; ++k)
        for (int l = 0; l < 28; ++l)
            board[k][l] = nullptr;

    //set correct mode according to user choice
    if (m == 'M') mapmaker_mode = true;
    else mapmaker_mode = false;

    //load a given mode with given highscore
    load_map(highscore);
    update_map();

    //start timer for movement and countdown
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh_frame()));
    timer -> start(20);

    //display different messages to explain gameplay
    if(mode == Mode::CLASSIC) QMessageBox::information(nullptr, "Welcome!", "This is classic mode. You can use keys WASD to move around.");
    if(mode == Mode::REVERSE) QMessageBox::information(nullptr, "Welcome!", "This is reverse mode. In this mode, you can chase ghosts until the timer runs out.");
}

PacmanGame::~PacmanGame(){}

void PacmanGame::startGraphicUI()
{
    game_window->show();
}

GameWindow* PacmanGame::get_game_window() const
{
    return game_window;
}

Pacman* PacmanGame::get_pacman() const
{
    return pacman;
}

Mode PacmanGame::get_mode() const
{
    return mode;
}

bool PacmanGame::is_mapmaker_mode() const
{
    return mapmaker_mode;
}

void PacmanGame::remove_ghost(int number)
{
    //to remove ghosts in reverse mode
    if(number == 1) {
        delete ghost1;
        ghost1 = nullptr;
    }
    if(number == 2) {
        delete ghost2;
        ghost2 = nullptr;
    }
    if(number == 3) {
        delete ghost3;
        ghost3 = nullptr;
    }
    if(number == 4) {
        delete ghost4;
        ghost4 = nullptr;
    }
}

int PacmanGame::get_score() const
{
    return current_score;
}

void PacmanGame::load_map(int highscore)
{
    //read and load the correct map file, if it exists and initiate map with correct objects
    if (mapmaker_mode) {
        if (!QDir(map_dir).exists()) QDir().mkdir(map_dir);
        if (!QFile(map_path).exists()) {
            mapmaker_mode = false;
            QMessageBox::information(nullptr, "Error", "Map not found. Loading classic map.");

            QFile file(":/resources/maps/pacman_map.txt");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
            int rownum = 30;
            while (!file.atEnd()) {
                QString line = file.readLine();
                for (int k = 0; k < line.size()-1; ++k) {
                    if (line[k] == 'W') board[rownum][k] = new Wall(rownum, k, &board);
                    else if (line[k] == 'V') board[rownum][k] = new Ghostwall(rownum, k, &board);
                    else if (line[k] == 'P') {
                        pacman = new Pacman(this, rownum, k, &board, mode);
                        board[rownum][k] = pacman;
                    }
                    else if (line[k] == 'G') {
                        if (ghost1 == nullptr) {
                            ghost1 = new Ghost(1, rownum, k, &board, 20, nullptr, mode, Movement::CHASE);
                            board[rownum][k] = ghost1;
                        }
                        else if (ghost2 == nullptr) {
                            ghost2 = new Ghost(2, rownum, k, &board, 40, nullptr, mode, Movement::AMBUSH);
                            board[rownum][k] = ghost2;
                        }
                        else if (ghost3 == nullptr) {
                            ghost3 = new Ghost(3, rownum, k, &board, 60, nullptr, mode, Movement::RANDOM);
                            board[rownum][k] = ghost3;
                        }
                        else if (ghost4 == nullptr) {
                            ghost4 = new Ghost(4, rownum, k, &board, 80, nullptr, mode, Movement::RANDOM);
                            board[rownum][k] = ghost4;
                        }
                    }
                    else if (line[k] == 'F') {
                        if (mode == Mode::CLASSIC)
                            board[rownum][k] = new Food(rownum, k, &board);
                        else if (mode == Mode::REVERSE)
                            board[rownum][k] = nullptr;
                    }
                    else if (line[k] == 'U') {
                        if (mode == Mode::CLASSIC)
                            board[rownum][k] = new Superpower(rownum, k, &board);
                        else if (mode == Mode::REVERSE)
                            board[rownum][k] = nullptr;
                    }
                }
                --rownum;
            }
            //initialize pacman variable of the ghosts, needed to chase pacman
            ghost1->set_pacman(pacman);
            ghost2->set_pacman(pacman);
            ghost3->set_pacman(pacman);
            ghost4->set_pacman(pacman);

            game_window->set_lcd(0, highscore);
        }
        else {
            QFile file(map_path);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
            QMessageBox::information(nullptr, "Welcome!", "Feel free to play your custom map. Your scores will NOT be saved while playing this mode.");
            int rownum = 30;
            while (!file.atEnd()) {
                QString line = file.readLine();
                for (int k = 0; k < line.size()-1; ++k) {
                    if (line[k] == 'W') board[rownum][k] = new Wall(rownum, k, &board);
                    else if (line[k] == 'V') board[rownum][k] = new Ghostwall(rownum, k, &board);
                    else if (line[k] == 'P') {
                        pacman = new Pacman(this, rownum, k, &board, mode);
                        board[rownum][k] = pacman;
                    }
                    else if (line[k] == 'G') {
                        if (ghost1 == nullptr) {
                            ghost1 = new Ghost(1, rownum, k, &board, 20, nullptr, mode, Movement::CHASE);
                            board[rownum][k] = ghost1;
                        }
                        else if (ghost2 == nullptr) {
                            ghost2 = new Ghost(2, rownum, k, &board, 40, nullptr, mode, Movement::AMBUSH);
                            board[rownum][k] = ghost2;
                        }
                        else if (ghost3 == nullptr) {
                            ghost3 = new Ghost(3, rownum, k, &board, 60, nullptr, mode, Movement::RANDOM);
                            board[rownum][k] = ghost3;
                        }
                        else if (ghost4 == nullptr) {
                            ghost4 = new Ghost(4, rownum, k, &board, 80, nullptr, mode, Movement::RANDOM);
                            board[rownum][k] = ghost4;
                        }
                    }
                    else if (line[k] == 'F') {
                        if (mode == Mode::CLASSIC)
                            board[rownum][k] = new Food(rownum, k, &board);
                        else if (mode == Mode::REVERSE)
                            board[rownum][k] = nullptr;
                    }
                    else if (line[k] == 'U') {
                        if (mode == Mode::CLASSIC)
                            board[rownum][k] = new Superpower(rownum, k, &board);
                        else if (mode == Mode::REVERSE)
                            board[rownum][k] = nullptr;
                    }
                }
                --rownum;
            }
            ghost1->set_pacman(pacman);
            ghost2->set_pacman(pacman);
            ghost3->set_pacman(pacman);
            ghost4->set_pacman(pacman);

            game_window->set_lcd(0, highscore);
        }
    }
    else {
        QFile file(":/resources/maps/pacman_map.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        int rownum = 30;
        while (!file.atEnd()) {
            QString line = file.readLine();
            for (int k = 0; k < line.size()-1; ++k) {
                if (line[k] == 'W') board[rownum][k] = new Wall(rownum, k, &board);
                else if (line[k] == 'V') board[rownum][k] = new Ghostwall(rownum, k, &board);
                else if (line[k] == 'P') {
                    pacman = new Pacman(this, rownum, k, &board, mode);
                    board[rownum][k] = pacman;
                }
                else if (line[k] == 'G') {
                    if (ghost1 == nullptr) {
                        ghost1 = new Ghost(1, rownum, k, &board, 20, nullptr, mode, Movement::CHASE);
                        board[rownum][k] = ghost1;
                    }
                    else if (ghost2 == nullptr) {
                        ghost2 = new Ghost(2, rownum, k, &board, 40, nullptr, mode, Movement::AMBUSH);
                        board[rownum][k] = ghost2;
                    }
                    else if (ghost3 == nullptr) {
                        ghost3 = new Ghost(3, rownum, k, &board, 60, nullptr, mode, Movement::RANDOM);
                        board[rownum][k] = ghost3;
                    }
                    else if (ghost4 == nullptr) {
                        ghost4 = new Ghost(4, rownum, k, &board, 80, nullptr, mode, Movement::RANDOM);
                        board[rownum][k] = ghost4;
                    }
                }
                else if (line[k] == 'F') {
                    if (mode == Mode::CLASSIC)
                        board[rownum][k] = new Food(rownum, k, &board);
                    else if (mode == Mode::REVERSE)
                        board[rownum][k] = nullptr;
                }
                else if (line[k] == 'U') {
                    if (mode == Mode::CLASSIC)
                        board[rownum][k] = new Superpower(rownum, k, &board);
                    else if (mode == Mode::REVERSE)
                        board[rownum][k] = nullptr;
                }
            }
            --rownum;
        }
        //initialize pacman variable of the ghosts, needed to chase pacman
        ghost1->set_pacman(pacman);
        ghost2->set_pacman(pacman);
        ghost3->set_pacman(pacman);
        ghost4->set_pacman(pacman);

        game_window->set_lcd(0, highscore);
    }
}

void PacmanGame::update_map()
{
    for (int k = 0; k < 31; ++k) {
        for (int l = 0; l < 28; ++l) {
            if (board[k][l] != nullptr)
                init_block(k, l, board[k][l]->getImage());
            else
                init_block(k, l, 'S');
        }
    }
}

void PacmanGame::init_block(int row, int col, char c)
{
    game_window->set_square(row, col, c);
}

void PacmanGame::move_pacman(int r, int c)
{
    //move pacman in the direction he wants to move
    Dir dir = pacman->get_direction();

    if (dir == Dir::DOWN) pacman->move(r-1, c);
    else if (dir == Dir::UP) pacman->move(r+1, c);
    else if (dir == Dir::LEFT) pacman->move(r, c-1);
    else if (dir == Dir::RIGHT) pacman->move(r, c+1);
    else if (dir == Dir::NONE) pacman->move(r, c);

    //update superpower status
    pacman->update_superpower();
    if (pacman->just_eaten_superpower()) gain_power();
    else if (pacman->just_lost_superpower()) lose_power();

    //double the score of the ghosts per ghost eaten in classic mode
    if(mode == Mode::CLASSIC) update_ghost_scores();

}

void PacmanGame::move_ghost(int r, int c, Ghost* g)
{
    //ensures ghost stays in box for set amount of time
    if (g->get_time_in_box() > 0) {
        g->reduce_time_in_box();
        return;
    }

    //get next move of the ghost based on the algorithms of ghost
    Dir direction = g->get_next_move();

    if (direction == Dir::DOWN) {
        g->move(r-1, c);
        g->set_direction(Dir::DOWN);
    }
    else if (direction == Dir::UP) {
        g->move(r+1,c);
        g->set_direction(Dir::UP);
    }
    else if (direction == Dir::RIGHT) {
        g->move(r, c+1);
        g->set_direction(Dir::RIGHT);
    }
    else if (direction == Dir::LEFT) {
        g->move(r,c-1);
        g->set_direction(Dir::LEFT);
    }
}

void PacmanGame::gain_power()
{
    //change status of pieces when superpower was eaten
    ghost1->set_eatmode(true);
    ghost2->set_eatmode(true);
    ghost3->set_eatmode(true);
    ghost4->set_eatmode(true);
    pacman->set_gain();
}

void PacmanGame::lose_power()
{
    //change status of pieces when superpower was eaten
    ghost1->set_eatmode(false);
    ghost1->reset_points();
    ghost2->set_eatmode(false);
    ghost2->reset_points();
    ghost3->set_eatmode(false);
    ghost3->reset_points();
    ghost4->set_eatmode(false);
    ghost4->reset_points();
    pacman->set_lose();
}

void PacmanGame::update_ghost_scores()
{
    //double scores of ghosts when pacman successfully eats a ghost
    if (pacman->get_has_eaten_ghost()) {
        ghost1->update_points();
        ghost2->update_points();
        ghost3->update_points();
        ghost4->update_points();
        pacman->not_eat_ghost();
    }
}

void PacmanGame::reset_ghosts()
{
    //move the ghosts back and reset status when pacman loses a life
    ghost1->move(17, 15);
    ghost1->move(15, 15);
    ghost1->move(17, 12);
    ghost1->move(15, 12);
    ghost1->set_eatmode(false);
    ghost1->set_time_in_box(20);

    ghost2->move(17, 15);
    ghost2->move(15, 15);
    ghost2->move(17, 12);
    ghost2->move(15, 12);
    ghost2->set_eatmode(false);
    ghost2->set_time_in_box(40);

    ghost3->move(17, 15);
    ghost3->move(15, 15);
    ghost3->move(17, 12);
    ghost3->move(15, 12);
    ghost3->set_eatmode(false);
    ghost3->set_time_in_box(60);

    ghost4->move(17, 15);
    ghost4->move(15, 15);
    ghost4->move(17, 12);
    ghost4->move(15, 12);
    ghost4->set_eatmode(false);
    ghost4->set_time_in_box(80);
}

void PacmanGame::update_score()
{
    //add score if it is positive
    if (pacman->get_points_to_add() == -1) {
        pacman->not_eat_piece();
        return;
    }
    else {
        current_score += pacman->get_points_to_add();
        game_window->set_lcd(1, current_score);
        pacman->not_eat_piece();
    }
}

void PacmanGame::update_lives()
{
    game_window->set_lives();
}

void PacmanGame::complete_level()
{
    //show message and get final score when level is completed
    if (is_level_finished() == false) return;
    else {
        current_score += pacman->get_lives() * 1000;
        QMessageBox::information(nullptr, "Congratulations!", "Level complete");
        game_window->close();
        if (timer != nullptr) timer->stop();
    }
}

bool PacmanGame::is_level_finished()
{
    //level finished in classic, which is when all the food is gone
    if(mode == Mode::CLASSIC) {
        for (int k = 0; k < 31; ++k) {
            for (int l = 0; l < 28; ++l) {
                if (board[k][l] != nullptr && (board[k][l] -> getImage() == 'F' || board[k][l] -> getImage() == 'S')) return false;
            }
        }

        if (ghost1->get_prev() != nullptr && (ghost1->get_prev()->getImage() == 'F' || ghost1->get_prev()->getImage() == 'S')) return false;
        if (ghost2->get_prev() != nullptr && (ghost2->get_prev()->getImage() == 'F' || ghost2->get_prev()->getImage() == 'S')) return false;
        if (ghost3->get_prev() != nullptr && (ghost3->get_prev()->getImage() == 'F' || ghost3->get_prev()->getImage() == 'S')) return false;
        if (ghost4->get_prev() != nullptr && (ghost4->get_prev()->getImage() == 'F' || ghost4->get_prev()->getImage() == 'S')) return false;

        return true;
    }

    //level finished in reverse, which is when all the ghosts have been eaten
    else if (mode == Mode::REVERSE) {
        if(ghost1 != nullptr) return false;
        if(ghost2 != nullptr) return false;
        if(ghost3 != nullptr) return false;
        if(ghost4 != nullptr) return false;
        return true;
    }

    return false;
}

void PacmanGame::game_over()
{
    //if no more lives or time, depending on the mode, then show game over message
    if ((mode == Mode::CLASSIC && pacman->get_lives() == 0) || (mode == Mode::REVERSE && pacman->get_superpower() <= 0)){
        QMessageBox::information(nullptr, "Game over!", "Game over!");
        game_window->close();
        timer->stop();
    }
}

void PacmanGame::update_timer()
{
    game_window->set_timer(pacman->get_superpower());
}

void PacmanGame::refresh_frame()
{
    //move the pieces
    if(ghost1 != nullptr) move_ghost(ghost1->getRow(), ghost1->getCol(), ghost1);
    if(ghost2 != nullptr) move_ghost(ghost2->getRow(), ghost2->getCol(), ghost2);
    if(ghost3 != nullptr) move_ghost(ghost3->getRow(), ghost3->getCol(), ghost3);
    if(ghost4 != nullptr) move_ghost(ghost4->getRow(), ghost4->getCol(), ghost4);
    move_pacman(pacman->getRow(), pacman->getCol());

    //update status variables
    update_score();
    update_lives();
    update_timer();

    //reset the ghosts and superpower timer when pacman encounters ghost
    if (pacman->get_has_encountered_ghost()) {
        reset_ghosts();
        pacman->set_superpower(0);
    }

    //update map and check end game statuses
    update_map();
    complete_level();
    game_over();
}
