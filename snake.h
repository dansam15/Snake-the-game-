class GameObject;
class Snake;
class Border;
class Food;
class Checker;

enum game_variables {HEIGTH = 20, WIDTH = 20 };
enum control_keys {KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77};//simplest way
enum directions_to_move {UP_TURN = 0, DOWN_TURN = 1, LEFT_TURN = 2, RIGHT_TURN = 3};//snake's head direction
enum symbols_to_display {SPACE_SYMB = ' ', SNAKE_SYMB ='o', BORDER_SYMB = '#', FOOD_SYMB = '*'};

const int MAX_DIR = 4,//max number of directions
	      SLEEP_TIME = 1;
		  
class GameObject
{
public:
	virtual void create() = 0;
	virtual ~GameObject(){};
	
protected:
	static char gameSpace[HEIGTH][WIDTH];
	static bool is_food_exist;
	static unsigned int points;
};

char GameObject::gameSpace[HEIGTH][WIDTH] = {{SPACE_SYMB}};
bool GameObject::is_food_exist = false;
unsigned int GameObject::points = 0;

class Snake: public GameObject
{
public:
	Snake(){create();};
	virtual void create() override;
	void print();
	void check_collisions();
	void turn(const unsigned int direction);
	
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
	};
	virtual void create() override;
};

class Border: public GameObject
{
public:
	virtual void create() override;
	Border() {create();};
};

class Checker: public GameObject
{
public:
	virtual void create() override {};
	void refresh();
	Checker() {refresh();};
};
