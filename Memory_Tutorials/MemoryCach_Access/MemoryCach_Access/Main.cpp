const int NUMBER_ENTITIES = 300;

class Point3D
{
	float x;
	float y;
	float z;
};

class Entity
{
	Point3D *position;
	Point3D *size;
	char *name;
	float health;
	float value;

public:
	Entity()
	{
		position = new Point3D;
		size = new Point3D;
	}

	~Entity()
	{
		delete (position);
		delete (size);
	}

	void update()
	{
		//game related stuff goes here!
	}
};

void main()
{
	//create an array of pointers to our entities
	Entity *entityList[NUMBER_ENTITIES];

	//instantiate all our entities when the game starts
	for (int count = 0; count < NUMBER_ENTITIES; count++)
	{
		Entity *newEntity = new Entity;
		entityList[count] = newEntity;
	}

	//game related stuff goes here!
	for (int count = 0; count < NUMBER_ENTITIES; count++)
	{
		entityList[count]->update();
	}

	//delete all our entities when the game is over
	for (int count = 0; count < NUMBER_ENTITIES; count++)
	{
		delete(entityList[count]);
	}
}