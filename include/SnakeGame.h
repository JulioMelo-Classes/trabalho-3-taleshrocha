#ifndef SnakeGame_h
#define SnakeGame_h
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep
#include "Level.h"
#include "Player.h"
#include "Snake.h"

class SnakeGame{
public:
    //@brief descreve os possíveis estados do jogo, fique à vontade para adicionar outros se necessário
    enum GameStates{
        RUNNING, //<! quando o jogo está executando o estado é RUNNING
        GAME_OVER, //<! quando o jogo deve terminar o estado é GAME_OVER
        VICTORY, //<! quando o jogo deve terminar o estado é GAME_OVER
        WAITING_USER //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
    };

private:
    //<! atributos adicione outros se quiser
    int frameCount; //<! contador de frames, usado apenas como exemplo
    std::string choice; //<! usado na função process_actions para guardar a escolha do usuário
    GameStates state; //<! guarda o estado do jogo
    std::string levelPath;
    std::string mode; // Just a aux
    bool tail;
    std::vector<std::shared_ptr<Level>> levels; //<! Store all the level's references in the game
    std::vector<std::shared_ptr<Player>> players; //<! Store all the snake's references in the game
    std::vector<std::shared_ptr<Snake>> snakes; //<! Store all the player's references in the game
    std::pair<int, int> move; // Just a aux
    std::shared_ptr<Snake> snake; //<! The snake in with we are using
    std::shared_ptr<Player> player; //<! The player in with we are using
    std::shared_ptr<Level> level; //<! The level in with we are using

public:
    //@brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
    explicit SnakeGame(char *arg1, char *arg2);

    std::shared_ptr<std::vector<std::string>> get_maze();

    //@brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
    void loop();

private:
    //@brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
    void initialize_game();

    //@brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    void update();

    //@brief processa as entradas do jogador
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    void process_actions();

    //@brief testa o estado do jogo e desenha a tela correspondente
    void render();

    //@brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
    void game_over();
};

#endif //SnakeGame_h
