# ITC-Lab-Final-Assignment
ITC Lab Assignement

ITC Grand Assignment: Pacman Game

How To Play:

Objective:

To win this game, you will have to eat all the food placed inside map or grid
without being eaten by enemies/ghosts


Start Screen:

- On start screen, you will have 3 difficulty levels to choose from.

- Each difficulty level differs from one another by the number of enemies it provides.

- Input difficulty level code i.e. 1, 2, 3. There are only three levels at the moment:
	1. Beginner
	2. Moderate
	3. Expert


Gameplay:

- You are spawned at somewhere below center of map.

- You can use W, A, S, D or UP, DOWN, LEFT, RIGHT to navigate throught the map.

- Pacman will move indefinitely on pressing arrows keys once and will stop on
  the condition that if it either hits a wall/enemy or a space key is pressed.

- If eaten by enemy/ghost, you will be prompted with the message of
  "Sorry, you lost the game"
  "Press N to exit"
  On pressing N, the console window will close and on pressing any other key
  other than 'N', you will be brougth back to menu screen.

- Eat all the food by navigating with arrow keys and avoiding enemies/ghosts
  in order to win the game.


Key Components:

- The core working of game lies on the following functions:
    a) inputLevel
    b) initialize
    c) draw
    d) update

	a) inputLevel
		This function is used for prompting input menu and asking for input.
	
	b) initialize
		This function is responsible for reseting score, pacman/enemy position
		and placing food in grid.

	c) draw
		This function is used to draw 2D map array with pacman and enemy

	d) update
		This function is used for asking input from user and updating user
		coordinates. Enemy coordinates are also updated by this function.

- Main function utilizes all the above function in co-ordination with each other
  inside a forever while loop
