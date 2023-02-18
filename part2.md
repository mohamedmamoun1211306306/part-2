
                    Alien vs. Zombie Game


Introduction:

    YouTube video 
part1
https://www.youtube.com/watch?v=WWBrU7tgLWA

part2
https://youtu.be/NJ4G6K23uHw

   This code is a C++ program for a text-based game called Alien vs Zombies. The game is set in a virtual world where an alien is being attacked by zombies. The objective of the game is for the alien to survive as many turns as possible while being attacked by zombies. The game has default settings but the user can choose to change the game settings such as the number of rows and columns in the virtual world, the number of zombies, and other settings. The game has multiple functions that handle different tasks such as creating the board, displaying the board, displaying the status of the alien and zombies, and handling user inputs. The code uses arrays, structures, loops, and various C++ libraries such as iostream, vector, and climits to create a seamless gaming experience.

 The game consists of a board where the alien is placed in the center of the board and the zombies are placed randomly on the board. The player (the alien) can move in four directions (up, down, left, and right) and can pick up health pods, power-ups, and arrows to attack the zombies. The player wins if they reach one of the board's borders and the game is over if the player's life reaches zero.




     User’s manual   
Welcome to the Alien Survival Game User's Manual

In this game, you will control an alien as it tries to survive in a dangerous world filled with zombies. Your goal is to survive for as long as possible by gathering resources, avoiding obstacles, and battling the zombies.

1. Game Settings:

At the start of the game, you will be prompted to select the game settings. The default settings are as follows:
Board Rows: 5
Board Columns: 9
Zombie Count: 1

However, you have the option to change these settings by entering 'y' when prompted. If you choose to change the settings, you will be asked to enter the number of rows and columns for the board. These numbers must be odd numbers. You will also be asked to enter the number of zombies that will be on the board. The number of zombies must be a positive integer.

2. Controls:

The game will display a board with your alien 'A' in the centre. You can use the following commands to control the alien:
up- move the alien up.
left - move the alien left.
down - move the alien down.
right - move the alien right.

You can also use the following commands during the game:
p - pick up an object
arrow- use an arrow (if you have one)
quit - quit the game.


3. Objects on the Board:

Throughout the game, you will encounter various objects on the board. These objects include:
^, v, <, > - obstacles
h - health pod
p - escape pod
r - arrow

4. Obstacles:

The ^, v, <, and > symbols represent obstacles that you must avoid. If the alien moves into one of these symbols, it will lose 1 life.

5. Health Pod:

The 'h' symbol represents a health pod. If the alien moves into it, it will regain 1 life.

 6. Escape Pod:

The 'p' symbol represents an escape pod. If the alien moves into it, it will escape the current level and move on to the next level.

 7. Arrow:

The 'arrow' symbol represents an arrow. If the alien picks it up, it will gain an arrow. The alien can use the arrow by typing ‘arrow' during the game. The arrow will destroy all zombies within a certain range.



8. Zombies:

Throughout the game, you will encounter zombies represented by the letter 'Z'. The zombies will move towards the alien and attack if they are within range. If the alien is attacked by a zombie, it will lose 1 life.

 9. Display Board:

The game will display the board after each move. The board will show the position of the alien, the objects on the board, and the zombies. The alien's status, including its current life and arrows, will be displayed at the bottom of the board.

10. Saving the Game 

To save the current game progress, press "save" and enter the name of the file you want to save to.


11. Loading a Saved Game

To load a saved game, enter the name of the file you want to load when prompted at the start of the game.

12. Quit Game:

You can quit the game at any time by entering 'quit' during the game.

Enjoy the game!

     Minimum Requirements to done in part 1


1. Game settings: 

Allow the user to choose the game settings such as the board size and number of zombies.

2. Board creation: 

Create the board game with the given settings and initialize it with appropriate elements.

3. Alien game:
 Implement the alien's game play such as movement, health, arrows, encounters with zombies and escape pods.

4. Zombie movement:

 Implement the movement of zombies on the board game and their attack on the alien.

5. User input: 

Accept user commands to control the alien's movement and actions.

6. Display board:

 Display the board game and status of the alien and zombies on the board.

7. End game:

 Check the conditions for ending the game such as the death of the alien or all zombies being killed.

 8. Error handling:   

Implement error handling to handle invalid user inputs and exceptional situations.

 9. Code documentation: 

Add appropriate comments and documentation to the code to make it easy to understand and maintain.

     Minimum Requirements to done in part 2
1. saveGame function should save the state of the game to a file in a format that can be later read by the loadGame function.

2. The loadGame function should be able to read the file created by the saveGame function and restore the state of the game to the saved state.

3.  Both functions should be able to handle and report any errors that may occur while processing the input or output. 
4. encArrow:

 takes in a character representing the direction the alien wants to move in and a reference to an Alien object. It updates the Alien object's attack and direction attributes and prints out a message indicating the change in direction.


5. encHealth:

 takes in a reference to an Alien object. It checks if the Alien's life is less than or equal to 100, and if so, increases it by 20. It then prints out a message indicating the encounter with a health pack and the increase in life.

6. checkWin:

 takes in a reference to a vector of Zombie objects. It checks if all the Zombie objects in the vector have a life attribute of 0. If so, it returns true indicating the player has won. Otherwise, it returns false indicating the game should continue.
 
7. encPod:

 takes in a reference to an Alien object and a reference to a vector of Zombie objects. It finds the Zombie object in the vector with the minimum distance to the Alien object and decreases its life attribute by the Alien object's attack attribute. It then prints out a message indicating the damage done to the Zombie object. If the Zombie object's life attribute is less than or equal to 0, it is considered defeated and its attack, life, and range attributes are set to 0. If all the Zombie objects in the vector have been defeated, the player has won and a message indicating so is printed.
 Additional Features 

1. Mohamed Mamoun:  create the board of the game and objects and places of the aliens and zombies display the board. Initialize board, setboardsetting, setgamesetting, getboard, getrandomobject, initializeframe, saveGame, ChangeArrowDirection, loadGame


2. Alharthi Hamzah Hamed: initialize player , check next spot, encarrow, enhealth, aliengame, input command, display status, zombies game,encArrow ,checkWin ,encPod.

       Problems Encountered and Solutions.
1.	When call a late function inside early function that’s be error. The solution of this problem function prototype.
2.	In temprow and tempcol when we put 0, the 0 %2=0 and that replace 0 to 1
3.	When we write boardrows=(boardrows*2) and boardcolumns=(boardcolumns*2) the code do not find a place to print a frame. Solution boardrows=(boardrows*2)+1 boardcolumns=(boardcolumns*2)+1.

