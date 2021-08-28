#include "SnakeGame.h"

using namespace std;

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal */
void clearScreen(){
    //some C++ voodoo here ;D
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
    mode = arg2;
    choice = "";
    frameCount = 0;
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
                        spawn = make_pair(lineCount, column);
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

    //cout << mazeHeight << " " << mazeWidth << " " << foodQuantity << " Spawn:" << spawn.first << " " << spawn.second << endl; //DEBUG
    levels.push_back(make_shared<Level>(maze, mazeHeight, mazeWidth, foodQuantity, spawn));
    players.push_back(make_shared<Player>()); // Creates and stores a player
    state = WAITING_USER;
}

void SnakeGame::process_actions(){
    auto player = players[0];
    switch(state){
    case RUNNING:
        move = player->next_move();
        break;
    case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        //cin>>std::ws>>choice;
        render();
        std::getline(std::cin, choice);
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

void SnakeGame::update(){
    auto level = levels[0];
    auto player = players[0];
    auto maze = level->get_maze();

    switch(state){
    case RUNNING:
        if((*maze)[move.first][move.second] == '$'){
            if(level->eat_food()){
                state = WAITING_USER;
            }
            level->put_food();
            player->find_solution(level);
            move = player->next_move();
        }
        break;
    case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        if(choice.length() == 0){
            //initialize_game(); // TODO: Don't work
            state = RUNNING;
        }
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

void SnakeGame::render(){
    clearScreen();
    auto level = levels[0];
    auto maze = level->get_maze();

    // Render the menu

    switch(state){
    case RUNNING:
        cout << "Lifes: " << 0 << " | Score: " << 0 << " | Food eaten: " << 0 << endl;
        // TODO: Change that to level.drawn_maze(solution); So i dont need to get the maze
        // Drawn the maze in the screen line by line
        //level->put_food();
        for(int line = 0; line < (int) maze->size(); line++){ // For the lines
            for(int column = 0; column < (int) (*maze)[line].size(); column++){ // For the columns
                if(line == move.first and column == move.second){
                    cout << "V";
                }
                else{
                    cout << (*maze)[line][column];
                }
            }
            cout << endl;
        }
        break;
    case WAITING_USER:
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
                                Press enter to begin
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
    case GAME_OVER:
        cout<<"GAME OVER!"<<endl;
        break;
    case VICTORY:
        cout<<"VICTORY"<<endl;
        break;
    }
    frameCount++;
}

void SnakeGame::game_over(){ // TODO: Implement that
}

void SnakeGame::loop(){
    auto level = levels[0];
    auto player = players[0];
    player->find_solution(level);
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(100);// espera 1 segundo entre cada frame
    }
}
