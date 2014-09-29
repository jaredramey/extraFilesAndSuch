#pragma once
class Bullet
{
public:
	struct Bullets
	{
		unsigned int BulletTexture;

	};

	Bullet();
	~Bullet();

	float x;
	float y;

	float width;
	float height;

	unsigned int bulletTextureID;

	float velocityX;
	float velocityY;

	void Update(float delta);
	void Draw();
	void InitializeBullet(float a_x, float a_y, float a_velocityX, float a_velocityY, unsigned int a_textureID);
	void TextureID(unsigned int a_textureID);

	bool isActive;
};

