#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum class BrickEnum { BLUE = 0, GREEN, GREY, PURPLE, RED, YELLOW };

#define BRICK_HALF_WIDTH 32
#define BRICK_HALF_HEIGHT 16

class Brick
{
public:
	BrickEnum typeID;
	float x, y;
};

void LoadMap(std::string fileName, std::vector<Brick *> &brickList)
{
	//clear the current brickList
	for (auto B : brickList) delete B;
	brickList.clear();

	//open file
	std::ifstream myfile;
	myfile.open(fileName);

	if (myfile.is_open())
	{
		//read in # of bricks
		int brickNum = 0;
		myfile >> brickNum;

		//read in each brick
		for (; brickNum > 0; --brickNum)
		{
			//make a brick
			Brick *B = new Brick();
			int t = 0;
			myfile >> t;
			B->typeID = (BrickEnum)t;
			myfile >> B->x;
			myfile >> B->y;
			brickList.push_back(B);
		}

		myfile.close();
	}
}

void SaveMap(std::string fileName, std::vector<Brick *> &brickList)
{
	//open file
	std::ofstream myfile;
	myfile.open(fileName, std::ios::trunc); //truncate old file

	if (myfile.is_open())
	{
		//write out # of bricks
		myfile << brickList.size() << std::endl;
		//write out each brick
		for (auto B : brickList)
		{
			myfile << (int)B->typeID << " " << B->x << " " << B->y << std::endl;
		}

		myfile.close();
	}
}
