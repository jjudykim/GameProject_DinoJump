#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<vector>

using namespace std;

class GameObject
{
private:
	string image;
	COORD loc;

public:
	GameObject(COORD loc, string image);
	string getImage();
	COORD getLoc();
	void setLoc(COORD loc);
};
