#include"GameObject.h"

GameObject::GameObject(COORD loc, string image)
{
	this->image = image;
	this->loc = loc;
}

string GameObject::getImage()
{
	return image;
}
COORD GameObject::getLoc()
{
	return loc;
}
void GameObject::setLoc(COORD loc)
{
	this->loc = loc;
}