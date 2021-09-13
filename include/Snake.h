#ifndef SNAKE_H_
#define SNAKE_H_
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Snake{
private:
  //<! Attributes
  int initialLife;                       //<! The snake's default life. Setted when creating the snake.
  int life;                              //<! The snakes fluid life. Changes when the snake hits the wall.
  std::vector<std::pair<int, int>> body; //<! The snake's head and body. The head is the first element.
  bool tail;                             //<! If this snake grows the tail when it eats food.

public:
  /* @brief The class constructor.
   * @param int _life: The snake's default life.
   * @param std::pair<int, int> spawn: The snake's spawn point. The first head position.
   * @param bool _tail: If the snake is going to grow its tail. The game mode. */
  explicit Snake(int _life, std::pair<int, int> spawn, bool _tail);

  /* @brief Gets the life attribute value.
   * @return A integer containing the life attribute value. */
  int get_life();

  /* @brief To see if the snake is going to grow its tail when it eats.
   * @return True if the snake is going to grow its tail. False otherwise. */
  bool has_tail();

  /* @brief Moves the snake to the desired point.
   * @param std::pair<int, int> position: The coordinates of the point in the maze.
   * @param bool food: True and the snakes grows its tail when it moves. False otherwise. */
  void move(std::pair<int, int> position, bool food);

  /* @brief Clears the snake body vector and resets the snake position to the level's spawn point.
   * @param std::pair<int, int> spawn: The level's spawn point. */
  void reset_body(std::pair<int, int> spawn);

  /* @brief Gets a point the snake's body vector attribute.
   * @return A pointer to the body attribute vector. */
  std::vector<std::pair<int, int>>* get_body();

  // @brief Lowers the snake's life by one point.
  void hit();
};

#endif // SNAKE_H_
