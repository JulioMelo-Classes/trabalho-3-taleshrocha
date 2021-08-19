#include "SnakeGame.h"

#include <iostream>
#include <fstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(char *arg){
    levelPath = arg;
    choice = "";
    frameCount = 0;
    initialize_game();
}

void SnakeGame::initialize_game(){
    int lineCount = 0, i = 0;
    size_t pos = 0;
    string line, token;
    string delimiter = " ";
    ifstream levelFile(levelPath);
    //TODO: make_shared<mensagem> (id, username, message);
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(lineCount > 0){ //ignora a primeira linha já que ela contem informações que não são uteis para esse exemplo
                maze.push_back(line);
            }
            //else{
            //    while((pos = line.find(delimiter)) != std::string::npos){
            //        token = line.substr(0, pos); //Break the string into tokens.
            //        //switch(i){
            //        //    case 0: stringstream ss(token); ss >> level.lines; break;
            //        //    case 1: stringstream ss(token); ss >> level.colluns; break;
            //        //    case 2: stringstream ss(token); ss >> level.foods; break;
            //        //}
            //        i++;
            //    }
            //}
            lineCount++;
        }
    }
    else{
        //TODO: Make that better. Like return 1
        cout << "ERROR: Unable to open the mazes file!" << endl;
    }
    state = RUNNING;
}



void SnakeGame::process_actions(){
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch(state){
    case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
        cin>>std::ws>>choice;
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

void SnakeGame::update(){
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    switch(state){
    case RUNNING:
        if(frameCount>0 && frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
            state = WAITING_USER;
        break;
    case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
        if(choice == "n"){
            state = GAME_OVER;
            game_over();
        }
        else{
            //pode fazer alguma coisa antes de fazer isso aqui
            state = RUNNING;
        }
        break;
    default:
        //nada pra fazer aqui
        break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
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

//TODO kill that
int x = 6;
int y = 1;
void SnakeGame::render(){
    clearScreen();
    switch(state){
    case RUNNING:
        //desenha todas as linhas do labirinto
        for(int line = 0; line < (int) maze.size(); line++){
            for(int column = 0; column < (int) maze[line].size(); column++){
                if(line == x and column == y){
                    cout << "V";
                    // Just playing
                    //TODO kill that
                    x--;
                    y++;
                }
                else{
                    cout << maze[line][column];
                }
            }
            cout << endl;
        }
        break;
    case WAITING_USER:
        cout<<"Você quer continuar com o jogo? (s/n)"<<endl;
        break;
    case GAME_OVER:
        cout<<"O jogo terminou!"<<endl;
        break;
    }
    frameCount++;
}

void SnakeGame::game_over(){
}

void SnakeGame::loop(){
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(1000);// espera 1 segundo entre cada frame
    }
}
