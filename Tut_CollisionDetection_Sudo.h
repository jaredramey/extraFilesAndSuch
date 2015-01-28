//Function prototype to be worked off of
bool CircleCircle(vec2 a_center1, float a_radius1, vec2 a_center2, float a_radius2);

//Function Fleshed out
//Function is supposed to take in the center and radius of two circles and tell if they've collided
//My assumption is that Vec2 is a class that contains an X and a Y
bool CircleCircle(vec2 a_center1, float a_radius1, vec2 a_center2, float a_radius2)
{
	//Code from slides
	/*float distance = (circle1.pos - circle2.pos).Magnitude();
	if(distance < circle1.radius + circle2.radius)
		return true; //collision!
	else
		return false; //no collision*/
		
	//My Code
					   //Getter for X1      Getter for X2
	float calculateX = (a_center1.posX() - a_center2.posX());
					   //Getter for Y1      Getter for Y2
	float calculateY = (a_center1.posY() - a_center2.posY());
					//Turn Calculations into a distance
	float distance = (calculateX + calculateY);
					//Check if they collide
	if((a_radius1 + a_radius2) <= distance)
	{
		return true;
	}
	
	else
	return false;
}

//Function Prototype to work off of
bool AABB(vec2 a_min1, vec2 a_max1, vec2 a_min2, vec2 a_max2);

//Function Fleshed out
//Function is supposed to take in the Min point and Max point two boxes and then return if they are collided
//My assumption again is that Vec2 is a class that contains an X and a Y 
bool AABB(vec2 a_min1, vec2 a_max1, vec2 a_min2, vec2 a_max2)
{
	//Code from slides
	/*
	if(box1.min.x > box2.max.x || box2.min.x > box1.max.x)
	return false; //no collision
	if(box1.min.y > box2.max.y || box2.min.y > box1.max.y)
	return false; //no collision
	return true; //if none of the above, then a collision has occurred
	*/
	
	if(a_min1.x > a_max2.x || a_min2.x > max1.x)
	{
		return false; //No collision
	}
	
	if(a_min1.y > a_max2.y || a_min2.y > max1.y)
	{
		return false; //No collision
	}
	
	else
	return true;
}