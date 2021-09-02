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
    choice = "";
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
        render(); // Shows the menu TODO is redering two times
        cin >> gameSpeed; // In the menu screen
        break;
    case VICTORY:
        victory();
        break;
    default: break;
    }
}

void SnakeGame::update(){
    int x;
    auto maze = level->get_maze();
    auto body = snake->get_body();
    auto bodyLog = snakeLog->get_body();

    switch(state){
    case RUNNING:
        if((*maze)[nextPos.first][nextPos.second] != '$'){
            snake->move(nextPos, false);
        }
        else{
            snake->move(nextPos, snake->has_tail());

            bodyLog->clear();
            for(int i = 0; i < body->size(); i++){
                bodyLog->push_back(make_pair((*body)[i].first, (*body)[i].second));
            }

            //snakeLog->move(nextPos, snakeLog->has_tail());
            cin >> gameSpeed;
            level->put_food();
            player->find_solution(level, snakeLog);
        }
        break;
    case WAITING_USER:
        if(gameSpeed > 0)
            state = RUNNING;
        break;
    default: break;
    }
}

void SnakeGame::render(){
    //clearScreen();
    auto maze = level->get_maze();
    auto body = snake->get_body();
    auto bodyLog = snakeLog->get_body();
    bool print;

    switch(state){
    case RUNNING:

        //cout << "----SNAKE----" << endl;
        //for(int i = 0; i < (int) body->size(); i++)
        //    cout << "body["<< i <<"]: " << (*body)[i].first << " | " << (*body)[i].second << endl;
        //cout << "-------------" << endl;

        //cout << "----SNAKELOG----" << endl;
        //for(int i = 0; i < (int) bodyLog->size(); i++)
        //    cout << "bodyLog["<< i << "]: " << (*bodyLog)[i].first << " | " << (*bodyLog)[i].second << endl;
        //cout << "----------------" << endl;

        // The status bar
        cout << "Lifes: " << snake->get_life() << " | Score: " << snake->get_foodEaten() << " | Food left: " << level->get_foodQuantity() << endl;

        // Drawn the maze in the screen line by line
        level->render(snake);

        //for(int line = 0; line < (int) maze->size(); line++){ // For the lines
        //    for(int column = 0; column < (int) (*maze)[line].size(); column++){ // For the columns
        //        for(int i = 0; i < (int) body->size(); i++){
        //            if(line == ((*body)[i]).first and column == ((*body)[i]).second){
        //                if(i == 0)
        //                    cout << "V";
        //                else
        //                    cout << "O";
        //                print = true;
        //            }
        //        }
        //        if(!print){
        //            cout << (*maze)[line][column];
        //        }
        //        print = false;
        //    }
        //    cout << endl;
        //}
        break;
    case WAITING_USER:
        // Render the menu
        cout << R"(
           ____________              ____________              ____________
         /  _________   \          /  _________   \          /  _________   \
        |  |  _____  |  |  _____  |  |  _____  |  |  _____  |  |  _____  |  |        _
        |  | |   __| |  | |   | | |  | |  _  | |  | |__   | |  | |   __| |  |       ( )
        |  | |__   | |  | | | | | |  | |     | |  | |   __| |  | |   __| |  |      (   )
        |  | |_____| |  | |_|___| |  | |__|__| |  | |_____| |  | |_____| |  |      /  /
       ($  $)        \   \________/  /         \   \________/  /         \  \_____/  /
        \__/          \_____________/           \_____________/           \_________/

                              a SNAke traped in a maZE
                                Set a speed to begin
        )";
        cout << endl;

        for(int line = 0; line < (int) maze->size(); line++){ // For the lines
            for(int column = 0; column < (int) (*maze)[line].size(); column++){ // For the columns
                if(line == (level->get_spawn()).first and column == (level->get_spawn()).second){
                    cout << "*";
                }
                else{
                    cout << (*maze)[line][column];
                }
            }
            cout << endl;
        }
        break;
    default: break;
    }
}

void SnakeGame::game_over(){
    cout << "GAME-OVER!" << endl;
    cout << "CONTINUE? [y/n]" << endl;
    cin >> choice;
    if(choice == "y"){
        initialize_game(); // TODO: fix that
        state = RUNNING;
    }
    else
        state = GAME_OVER;
}

void SnakeGame::victory(){
    cout << "VICTORY!" << endl;
    cout << "CONTINUE? [y/n]" << endl;
    cin >> choice;
    if(choice == "y"){
        initialize_game(); // TODO: fix that
        state = RUNNING;
    }
    else
        state = GAME_OVER;
}

void SnakeGame::loop(){
    player->find_solution(level, snakeLog); // Finds the first solution

    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(gameSpeed);
    }
}
