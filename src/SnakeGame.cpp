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

        if (levelFile.peek() == std::ifstream::traits_type::eof()){
            cout << "ERROR: The file is empty!" << endl;
            state = GAME_OVER;
        }

        else{
            while(getline(levelFile, line)){ // Gets all the file's lines line per line
                if(lineCount == 0){ // Gets all the maze's parameters
                    while((pos = line.find(delimiter)) != std::string::npos){
                        token = line.substr(0, pos); //Break the string into tokens
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
                if(line.empty()){
                    levels.push_back(make_shared<Level>(maze, mazeHeight, mazeWidth, foodQuantity, spawn));
                    maze.clear(); // Clears the previous level
                    lineCount = 0;
                }
                else{
                    lineCount++;
                }
            }
            levels.push_back(make_shared<Level>(maze, mazeHeight, mazeWidth, foodQuantity, spawn));

            snakes.push_back(make_shared<Snake>(5, spawn, tail));
            snakes.push_back(make_shared<Snake>(5, spawn, tail));
            players.push_back(make_shared<Player>()); // Creates and stores a player

            level = levels[0];
            player = players[0];
            snake = snakes[0];
            snakeLog = snakes[1];
            state = WAITING_USER;

            // TODO: thats ugly!
            vector<pair<int, int>> validPositions;
            string choice;
            auto maze_ = level->get_maze();

            cout << "Random Start? [y/n]" << endl;
            cin >> choice;

            if(choice == "y"){
                for(int x = 0; x < (int) level->get_maze_height(); x++){  // For the lines
                    for(int y = 0; y < (int) level->get_maze_width(); y++){ // For the columns
                        if((*maze_)[x][y] != '#'){
                            validPositions.push_back(make_pair(x, y));
                        }
                    }
                }
                spawn = validPositions[rand() % validPositions.size()];
                snake->move(spawn, false);
                snakeLog->move(spawn, false);
            }

            player->find_solution(level, snakeLog); // Finds the first solution
            level->wellcome();
            level->render(snake);
            cout << "Game speed [0-9]: ";
        }
    }
    else{
        cout << "ERROR: Unable to open the mazes file!" << endl;
        state = GAME_OVER;
    }
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
        if(nextPos.first == -1 and nextPos.second == -1){
            snake->hit();
            if(snake->get_life() == 0)
                game_over();
            else
                ouch();
        }

        if((*maze)[nextPos.first][nextPos.second] != '$')
            snake->move(nextPos, false);
        else{
            //state = WAITING_USER; //TODO change to always set the speed
            snake->move(nextPos, snake->has_tail());

            // Copies the snake into snakeLog to synchronize
            bodyLog->clear();
            for(int i = 0; i < (int) body->size(); i++)
                bodyLog->push_back(make_pair((*body)[i].first, (*body)[i].second));

            if(level->put_food(snake))
                victory();

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
        clearScreen();
        // The status bar
        cout << "Lifes: " << snake->get_life() << " | Food left: " << level->get_foodLeft() << endl;

        level->render(snake);
        break;
    case WAITING_USER:
        cout << "New game speed [0-9]: ";
        break;
    default: break;
    }
}

void SnakeGame::ouch(){
    cout << "OUCH!" << endl;
    wait(500);
    cout << "YOU HIT THE WALL!" << endl;
    wait(1000);

    snake->reset_body(level->get_spawn());
    snakeLog->reset_body(level->get_spawn());
    level->put_food(snake, 0);

    player->reset();
    player->find_solution(level, snakeLog);
    nextPos = player->next_move();
}

void SnakeGame::game_over(){
    string choice;

    cout << "GAME-OVER!" << endl;
    wait(1000);
    cout << "Try Again? [y/n]" << endl;
    cin >> choice;
    if(choice == "y"){
        state = WAITING_USER;
        level->reset();
        level = levels[0];
        //TODO make a reset snake
        snake = make_shared<Snake>(5, level->get_spawn(), tail);
        snakeLog = make_shared<Snake>(5, level->get_spawn(), tail);
        player->reset();
        player->find_solution(level, snakeLog);
        nextPos = player->next_move();
        clearScreen();
        level->wellcome();
        level->render(snake);
    }
    else
        state = GAME_OVER;
}

void SnakeGame::victory(){
    string choice;

    cout << "VICTORY!" << endl;
    wait(1000);
    auto it = find(levels.begin(), levels.end(), level);
    if(it == levels.end()-1){
        cout << "You Won The Game!" << endl;
        wait(500);
        cout << "Loop? [y/n]" << endl;
        cin >> choice;
        if(choice == "y"){
            state = WAITING_USER;
            level->reset();
            level = levels[0];
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
    else{
        cout << "Next Level? [y/n]" << endl;
        cin >> choice;
        if(choice == "y"){
            state = WAITING_USER;
            level->reset();
            it++;
            level = (*it);
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
}

void SnakeGame::loop(){
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait((1000/(gameSpeed+1)));
    }
}
