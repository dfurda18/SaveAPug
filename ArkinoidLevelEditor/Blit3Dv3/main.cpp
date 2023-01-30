/*
	Simple example of an Arkinoid level editor
*/
#include "Blit3D.h"

Blit3D *blit3D = NULL;

//memory leak detection
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Brick.h"

//GLOBAL DATA

std::vector<Sprite *> spriteList;
int editBrick = 0; //brick we are currently editing with

//bricks for a level
std::vector<Brick *> brickList;

AngelcodeFont *caviar57font = NULL;

glm::vec2 cursor;

void Init()
{
	
	//load a sprite off of a spritesheet
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_blue_rectangle_glossy.png"));
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_green_rectangle_glossy.png"));
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_grey_rectangle_glossy.png"));
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_purple_rectangle_glossy.png"));
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_red_rectangle_glossy.png"));
	spriteList.push_back(blit3D->MakeSprite(0, 0, 64, 32, "Media\\element_yellow_rectangle_glossy.png"));

	//load an Angelcode binary32 font file
	caviar57font = blit3D->MakeAngelcodeFontFromBinary32("Media\\CaviarDreams57.bin");
}

void DeInit(void)
{
	for (auto B : brickList) delete B;
	brickList.clear();

	// DO NOT delete the font!
	//If we need to delete a font at runtime, call DeleteFont().

	//any sprites/fonts still allocated are freed automatically by the Blit3D object when we destroy it
}

void Update(double seconds)
{
}

void Draw(void)
{
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);	//clear colour: r,g,b,a 	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw stuff here
	for (auto &B : brickList)
	{
		spriteList[(int)B->typeID]->Blit(B->x, B->y);
	}

	
	//quantize cursor
	float x = ((int)cursor.x / BRICK_HALF_WIDTH) * BRICK_HALF_WIDTH;
	float y = ((int)cursor.y / BRICK_HALF_HEIGHT) * BRICK_HALF_HEIGHT;
	//draw cursor
	spriteList[editBrick]->Blit(x, y);
	
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
void DoInput(int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		blit3D->Quit(); //start the shutdown sequence

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		//save!
		SaveMap("level.txt", brickList);
	}

	if (key == GLFW_KEY_L && action == GLFW_RELEASE)
	{
		//load!
		LoadMap("level.txt", brickList);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::BLUE;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::GREEN;
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::GREY;
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::PURPLE;
	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::RED;
	if (key == GLFW_KEY_6 && action == GLFW_PRESS)
		editBrick = (int)BrickEnum::YELLOW;
}

void DoCursor(double x, double y)
{
	//demonstrates how to convert the raw cursor coords passed from the OS
	//into Blit3D screenspace coords
	cursor.x = x * (blit3D->screenWidth / blit3D->trueScreenWidth);
	cursor.y = (blit3D->trueScreenHeight - y) * (blit3D->screenHeight / blit3D->trueScreenHeight);
}

void DoMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		//quantize cursor
		float x = ((int)cursor.x / BRICK_HALF_WIDTH) * BRICK_HALF_WIDTH;
		float y = ((int)cursor.y / BRICK_HALF_HEIGHT) * BRICK_HALF_HEIGHT;

		//remove any brick under us
		for (int b = brickList.size() - 1; b >= 0; --b)
		{
			if (x == brickList[b]->x && y == brickList[b]->y)
			{
				delete brickList[b];
				brickList.erase(brickList.begin() + b);
			}
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//quantize cursor
		float x = ((int)cursor.x / BRICK_HALF_WIDTH) * BRICK_HALF_WIDTH;
		float y = ((int)cursor.y / BRICK_HALF_HEIGHT) * BRICK_HALF_HEIGHT;

		//remove any brick under us
		for (int b = brickList.size() - 1; b >= 0; --b)
		{
			if (x == brickList[b]->x && y == brickList[b]->y)
			{
				delete brickList[b];
				brickList.erase(brickList.begin() + b);
			}
		}

		//add new brick
		Brick *b = new Brick;
		b->x = x;
		b->y = y;
		b->typeID = (BrickEnum)editBrick;
		brickList.push_back(b);
	}
	
}

int main(int argc, char *argv[])
{
	//memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	blit3D = new Blit3D(Blit3DWindowModel::BORDERLESSFULLSCREEN_1080P, 640, 400);

	//set our callback funcs
	blit3D->SetInit(Init);
	blit3D->SetDeInit(DeInit);
	blit3D->SetUpdate(Update);
	blit3D->SetDraw(Draw);
	blit3D->SetDoInput(DoInput);
	blit3D->SetDoCursor(DoCursor);
	blit3D->SetDoMouseButton(DoMouseButton);

	//Run() blocks until the window is closed
	blit3D->Run(Blit3DThreadModel::SINGLETHREADED);
	if (blit3D) delete blit3D;
}