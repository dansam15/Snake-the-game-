#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>

#include "snake.h"

void Checker::refresh() 
{
	std::cout<<"POINTS: "<<points<<std::endl;
	for (unsigned int i = 0; i < HEIGTH; i++)
	{
		for (unsigned int j = 0; j < WIDTH; j++)
			std::cout<<gameSpace[i][j];	
		std::cout<<std::endl;
	}
};

void Border::create() 
{
	for (unsigned int i = 0; i < HEIGTH; i++)
		for (unsigned int j = 0; j < WIDTH; j++)
			GameObject::gameSpace[i][j] = ((i == 0) | (j == 0) | (i == HEIGTH-1) | (j == WIDTH-1))? BORDER_SYMB: SPACE_SYMB;
}

void Snake::create()
{
	part head{(unsigned int)rand()%HEIGTH, (unsigned int)rand()%WIDTH, (unsigned int)rand()%MAX_DIR, SNAKE_SYMB};
	body.push_back(head);
}

void Snake::print()
{
	for (auto it:body)
		gameSpace[it.x][it.y] = it.symbol;				
}

void Snake::check_collisions()
{	
	if ((gameSpace[body.at(0).x][body.at(0).y] == BORDER_SYMB) |\
		(gameSpace[body.at(0).x][body.at(0).y] == SNAKE_SYMB))
	{
		std::cout<<"GAME OVER\n";
		exit(0);
	}			
	else
	if (gameSpace[body.at(0).x][body.at(0).y] == FOOD_SYMB)
	{
		points++;
		is_food_exist = false;		
		body.push_back(part_new);
	}
	return;
}
	
void Snake::turn(const unsigned int direction)
{	
	part_new = body.back();
	gameSpace[part_new.x][part_new.y] = SPACE_SYMB;
	
	switch (direction)
	{
		case UP_TURN:
		{
			if (body.at(0).direction != DOWN_TURN)
				body.at(0).direction = UP_TURN;
			break;
		};
		
		case DOWN_TURN:
		{
			if (body.at(0).direction != UP_TURN)
				body.at(0).direction = DOWN_TURN;
			break;
		};
		
		case LEFT_TURN:
		{	
			if (body.at(0).direction != RIGHT_TURN)
				body.at(0).direction = LEFT_TURN;
			break;
		}
		
		case RIGHT_TURN:
		{		
			if (body.at(0).direction != LEFT_TURN)
				body.at(0).direction = RIGHT_TURN;
			break;		
		}
		
		default : break;
	}

	for (auto &it:body)
	{
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
	print();
	for (unsigned int i = body.size() - 1; i >= 1; i--)
		body.at(i).direction = body.at(i-1).direction;
}

void Food::create()
{ 
	if (is_food_exist == true)
		return;
			
	unsigned int x_rand{(unsigned int)rand()%HEIGTH},
				 y_rand{(unsigned int)rand()%WIDTH};

	if (GameObject::gameSpace[x_rand][y_rand] == SPACE_SYMB)
	{
		GameObject::gameSpace[x_rand][y_rand] = FOOD_SYMB;	
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
		int key;
		if (_kbhit())
			key = _getch();

		switch (key)
		{
			case KEY_UP:
			{
				snake.turn(UP_TURN);
				break;
			}
			case KEY_DOWN:
			{
				snake.turn(DOWN_TURN);
				break;
			}
			case KEY_LEFT:
			{
				snake.turn(LEFT_TURN);
				break;
			}
			case KEY_RIGHT:
			{
				snake.turn(RIGHT_TURN);
				break;
			}			
			default:	
				break;
		}
			
		food.create();
		system("cls");
		checker.refresh();
		Sleep(SLEEP_TIME);	
	}
	return 0;
}