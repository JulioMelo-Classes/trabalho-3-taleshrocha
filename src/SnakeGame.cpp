#include "SnakeGame.h"

using namespace std;

void SnakeGame::wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void SnakeGame::clearScreen(){
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

SnakeGame::SnakeGame(char *arg1, char *arg2){
    levelPath = arg1;
    if((string) arg2 == "tail")
        tail = true;
    initialize_game();
}

void SnakeGame::initialize_game(){
    // Temporary values to construct the level
    unsigned int foodQuantity;
    unsigned int mazeHeight;
    unsigned int mazeWidth;
    vector<string> maze;
    pair<int, int> spawn;

    // String treatment related
    size_t pos = 0;
    string line, token;
    string delimiter = " ";
    stringstream ss;

    int lineCount = 0, paramCount = 0;
    ifstream levelFile(levelPath);

    if(levelFile.is_open()){
        while(getline(levelFile, line)){ // Gets all the file's lines
            if(lineCount == 0){ // Gets all the maze's parameters
                while((pos = line.find(delimiter)) != std::string::npos){
                    token = line.substr(0, pos); //Break the string into tokens.
                    if(paramCount == 0){
                        ss << token;
                        ss >> mazeHeight;
                    }
                    else{
                        ss.clear(); // To be able to get new values in that ss
                        ss << token;
                        ss >> mazeWidth;
                    }
                    line.erase(0, pos + delimiter.length()); //Erase the token from the original string.
                    paramCount++;
                }
                ss.clear(); // To be able to get new values in that ss
                ss << line;
                ss >> foodQuantity;
            }
            else{ // Gets the maze
                for(int column = 0; column < (int) line.size(); column++){ // Gets the spawn point and removes the (*) from the map
                    if(line[column] == '*'){
                        spawn = make_pair(lineCount - 1, column);
                        line[column] = ' ';
                    }
                }
                maze.push_back(line);
            }
            lineCount++;
        }
    }
    else{
        //TODO: Make that better. Like return 1
        cout << "ERROR: Unable to open the mazes file!" << endl;
    }

    // TODO make that nice
    levels.push_back(make_shared<Level>(maze, mazeHeight, mazeWidth, foodQuantity, spawn));
    snakes.push_back(make_shared<Snake>(5, spawn, tail));
    snakes.push_back(make_shared<Snake>(5, spawn, tail));
    players.push_back(make_shared<Player>()); // Creates and stores a player

    level = levels[0];
    player = players[0];
    snake = snakes[0];
    snakeLog = snakes[1];
    state = WAITING_USER;
}

void SnakeGame::process_actions(){
    switch(state){
    case RUNNING:
        nextPos = player->next_move();
        break;
    case WAITING_USER: // The game blocks in here. Waits for the user to set a game time
        cin >> gameSpeed; // In the menu screen
        break;
    default: break;
    }
}

void SnakeGame::update(){
    auto maze = level->get_maze();
    auto body = snake->get_body();
    auto bodyLog = snakeLog->get_body();

    switch(state){
    case RUNNING:
        cout << nextPos.first << " " << nextPos.second << endl;
        if(nextPos.first == -1 and nextPos.second == -1)
            game_over();
        else if((*maze)[nextPos.first][nextPos.second] != '$')
            snake->move(nextPos, false);
        else{
            state = WAITING_USER;
            snake->move(nextPos, snake->has_tail());

            // Copies the snake into snakeLog to synchronize
            bodyLog->clear();
            for(int i = 0; i < (int) body->size(); i++)
                bodyLog->push_back(make_pair((*body)[i].first, (*body)[i].second));

            level->put_food();
            player->reset();
            player->find_solution(level, snakeLog);
        }
        break;
    case WAITING_USER:
        if((gameSpeed >= 0 and gameSpeed < 10) or gameSpeed == 99)
            state = RUNNING;
        break;
    default: break;
    }
}

void SnakeGame::render(){
    switch(state){
    case RUNNING:
        //clearScreen();
        // The status bar
        cout << "Lifes: " << snake->get_life() << " | Score: " << snake->get_foodEaten() << " | Food left: " << level->get_foodQuantity() << endl;

        level->render(snake);
        break;
    case WAITING_USER:
        cout << "New game speed [0-9]: ";
        break;
    default: break;
    }
}

void SnakeGame::game_over(){
    string choice;

    cout << "GAME-OVER!" << endl;
    wait(1000);
    cout << "TRY AGAIN? [y/n]" << endl;
    cin >> choice;
    if(choice == "y"){
        state = WAITING_USER;
        snake = make_shared<Snake>(5, level->get_spawn(), tail);
        snakeLog = make_shared<Snake>(5, level->get_spawn(), tail);
        player->reset();
        player->find_solution(level, snakeLog);
        clearScreen();
        level->wellcome();
        level->render(snake);
    }
    else
        state = GAME_OVER;
}

void SnakeGame::loop(){
    player->find_solution(level, snakeLog); // Finds the first solution

    level->wellcome();
    level->render(snake);
    cout << "Game speed [0-9]: ";

    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait((1000/(gameSpeed+1)));
    }
}
