#pragma once
class Vector
{
private:
	float x;
	float y;

public:
	Vector();
	~Vector();

	void SetPos(float X, float Y);

	void LERP(Vector &end, float t);
	void CubBezier(Vector &p_Two, Vector &p_Three, float t);

	float getX();
	float getY();
};

