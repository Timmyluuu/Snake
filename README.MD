This game is called SNAKE!

Game Description:
  The game screen displays a snake which is a chain of blocks always in motion and a fruit at a fixed point on the screen. The direction of snake is controlled by "WASD"(W-up, A-left, S-down, D-right). The objective of the snake is to eat the fruit and it makes it grow in length. As the snake eats the fruit, it disappears and another one appears at a random location. The snake can die(or lose life) by eating itself or by hitting the edge of the screen or obstacles.

Control: Use “WASD” to control the movement. 

Development environment: C++ and Xlib

Enhancement: 
 - Power-up: After eating 5 fruits, a special fruit will be generated randomly on the screen. The snake will gain extra life if the snake eats it (Extra life details is in the rule). There will be at most one special fruit on the screen. After the snake eats the special,
a new special fruit will be generated after eating 5 fruits.
 - Obstacle: This game has three level. 
      Level 0: no obstacle.
      Level 1: Easy obstacle.
      Level 2: Complicated obstacle.
      (more level details is in the rule) 
 - Graphics: 
      Snake: A chain of grey blocks with black edges.
      Fruit: A orange block with black edges.
      Special fruit: A red block with black edges.
      Obstacle: A number of brown blocks with orange edges.
      Wall: Black blocks around the screen.

Rule: 
  The snake has 5 extra lives at the beginning of the game in level 0 and level 1. The
 game will be over if the snake has 0 extra life and eats itself or hit the edge or 
obstacle. When the snake has extra lives, if the snake eats itself, the new tail of the 
snake will be the block that the snake eats, and it will lose one extra life. If the snake
 hits the obstacle or the edge of screen, the snake will lose half of its body(i.e length:
 4 -> 2, length: 3 -> 2, length: 1 -> 1) and lose one life, meanwhile the snake will turn 
by itself, it will pick the direction that the next obstacle or wall is further so the 
player has longer time to react. The initial score is 0, eating one fruit will increase 1
 score(special fruit does not count). In level 0 and 1, if the score reaches 20, it will
restart in the next level but the score maintains. In level 2, there is no extra life so 
there is no special fruit. The speed of snake is 1-10 and FPS is support for 25-60. At any
 time, you can press P to pause, when it is pausing, you can press P again to continue 
playing, or press R to restart, or press Q to quit. Other buttons will not work. When the
 game is over, you can press Q to quit or R to restart.
