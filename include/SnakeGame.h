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
    //@brief All the possible game states
    enum GameStates{
        RUNNING, //<! When the game is executing
        GAME_OVER, //<! When the game finishes
        WAITING_USER //<! When waiting for the user input
    };

private:
    //<! Attributes
    GameStates state;            //<! keeps the game state
    std::string levelPath;       //<! Is the path to the maze file
    std::pair<int, int> nextPos; //<! used in Player::next_move. Keeps the next snake's position
    int gameSpeed;               //<! Sets the speed. The smaller, the faster
    bool tail = false;           //<! If the game mode is with tail

    // Vectors
    std::vector<std::shared_ptr<Level>> levels;   //<! Store all the level's references in the game
    std::vector<std::shared_ptr<Player>> players; //<! Store all the snake's references in the game
    std::vector<std::shared_ptr<Snake>> snakes;   //<! Store all the player's references in the game

    // References
    std::shared_ptr<Snake> snake;    //<! The snake used to render
    std::shared_ptr<Snake> snakeLog; //<! The snake used in to find the solutions
    std::shared_ptr<Player> player;  //<! The player in with we are using
    std::shared_ptr<Level> level;    //<! The level in with we are using

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

    /**
     * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
     * @param ms a quantidade de segundos que o programa deve esperar */
    void wait(int ms);
    /**
     * @brief função auxiliar para limpar o terminal */
    void clearScreen();
};

#endif //SnakeGame_h
