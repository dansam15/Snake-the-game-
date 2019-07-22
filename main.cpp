#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <vector>

#define SLEEP_TIME 1
enum game_variables{HEIGTH = 20, WIDTH = 20 };
enum control_keys{KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77};//simplest way
enum directions_to_move{UP_TURN=0, DOWN_TURN=1, LEFT_TURN=2, RIGHT_TURN=3};//snake's head direction
const int MAX_DIR = 4;//max number of directions

class GameObject;
class Snake;
class Border;
class Food;
class Checker;

class GameObject
{
public:
	virtual void create() = 0;
	virtual ~GameObject(){}
	
protected:
	static char gameSpace[HEIGTH][WIDTH];
	static bool is_food_exist;
	static unsigned int points;
};
char GameObject::gameSpace[HEIGTH][WIDTH] = {{' '}};
bool GameObject::is_food_exist = false;
unsigned int GameObject::points = 0;

class Snake: public GameObject
{
public:
	Snake(){create();}
	void create();
	
	void print();
	void move();
	void check_collisions();

	void turn_up();
	void turn_down();
	void turn_left();
	void turn_rigth();
	
private:
	struct part
	{
		unsigned int x, y;
		unsigned int direction;
		char symbol;
	} part_new;
	std::vector<part> body;
};


class Food: public GameObject
{
public:
	Food()
	{		
		create();	
		is_food_exist = true;
	}
	inline void create();
};

class Border: public GameObject
{
public:
	void create();
	Border() { create(); }
};

class Checker: public GameObject
{
public:
	void create(){};
	void refresh();
	Checker() {refresh();};
};

void Checker::refresh()
{
	std::cout<<"POINTS: "<<points<<std::endl;
	for (unsigned int i = 0; i < HEIGTH; i++)
	{
		for (unsigned int j = 0; j < WIDTH; j++)
			std::cout<<GameObject::gameSpace[i][j];	
		std::cout<<std::endl;
	}
};

void Border::create()
{
	for (unsigned int i = 0; i < HEIGTH; i++)
		for (unsigned int j = 0; j < WIDTH; j++)
			GameObject::gameSpace[i][j] = ((i == 0) | (j == 0) | (i == HEIGTH-1) | (j == WIDTH-1))? '#': ' ';
}

void Snake::create()
{
	part head{(unsigned int)rand()%HEIGTH, (unsigned int)rand()%WIDTH, (unsigned int)rand()%MAX_DIR, 'o'};
	body.push_back(head);
	part_new = head;
}

void Snake::print()
{
	for (auto it:body)
		GameObject::gameSpace[it.x][it.y] = it.symbol;				
}

void Snake::move()
{	
	part_new = body.back();
	for (auto &it:body)
	{
		gameSpace[it.x][it.y] = ' ';
		switch (it.direction)
		{
			case RIGHT_TURN:
			{
				it.y++;
				break;
			}
			
			case LEFT_TURN:
			{
				it.y--;	
				break;
			}
			
			case UP_TURN:
			{
				it.x--;
				break;
			}
			
			case DOWN_TURN:
			{
				it.x++;
				break;
			}
			
			default:
			{
				std::cout<<"WRONG DIRECTION\n";
				exit(0); //TODO: exception
			}	
		}	
	}
	check_collisions();	
	auto body_tmp = body;
	for (unsigned int i = 1; i < body.size(); i++)
		body.at(i).direction = body_tmp.at(i-1).direction;
	print();
}

void Snake::check_collisions()
{
	if ((gameSpace[body.at(0).x][body.at(0).y] == '#') | (gameSpace[body.at(1).x][body.at(1).y] == 'o'))
	{
		std::cout<<"GAME OVER\n";
		exit(0);
	}
	else
	if (gameSpace[body.at(0).x][body.at(0).y] == '*')
	{
		points++;
		is_food_exist = false;
		
		part_new.direction = body.back().direction;
		body.push_back(part_new);
	}
	return;
}

void Snake::turn_up()
{
	if (body.at(0).direction != DOWN_TURN)
		body.at(0).direction = UP_TURN;
}


void Snake::turn_down()
{
	if (body.at(0).direction != UP_TURN)
		body.at(0).direction = DOWN_TURN;
}

void Snake::turn_rigth()
{ 
	if (body.at(0).direction != LEFT_TURN)
		body.at(0).direction = RIGHT_TURN;
}

void Snake::turn_left()
{
	if (body.at(0).direction != RIGHT_TURN)
		body.at(0).direction = LEFT_TURN;
}

void Food::create()
{ 
	if (is_food_exist == true)
		return;
			
	unsigned int x_rand{(unsigned int)rand()%HEIGTH},
				 y_rand{(unsigned int)rand()%WIDTH};

	if (GameObject::gameSpace[x_rand][y_rand] == ' ')
	{
		GameObject::gameSpace[x_rand][y_rand] = '*';	
		is_food_exist = true; 
	}
	else
		Food::create();
	return;		
};

int main()
{		
	Border border;
	Snake snake;
	Checker checker;
	Food food;
	
	while (true)
	{			
		int key = 0;
		if (_kbhit())
			key = _getch();
		switch (key)
		{
			case KEY_UP:
			{
				snake.turn_up();
				break;
			}
			case KEY_DOWN:
			{
				snake.turn_down();
				break;
			}
			case KEY_LEFT:
			{
				snake.turn_left();
				break;
			}
			case KEY_RIGHT:
			{
				snake.turn_rigth();
				break;
			}			
			default:	
				break;
		}
		snake.move();
		food.create();
		system("cls");
		checker.refresh();
		Sleep(SLEEP_TIME);
	}
	return 0;
}