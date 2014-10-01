#pragma once
class Entity
{
public:
	Entity();

	void SetSize(float a_width, float a_heigth);
	void SetPosition(float a_x, float a_y);
	
	virtual void Update(float delta) = 0;
	virtual void Draw() = 0;

	void SetSpriteID(unsigned int a_spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float a_width);
	void SetHeigth(float a_heigth);

	float GetWidth();
	float GetHeigth();

	void SetX(float a_x);
	void SetY(float a_Y);

	float GetX();
	float GetY();

	~Entity();


protected:
	unsigned int spriteID;

	float width;
	float heigth;

	float x;
	float y;
};

