// edited by: Toby Winegarner
// last updated: 7/13/2020

//all props go to one lone coder for the starter code and videos
//his license below
//



//
/*
OneLoneCoder.com - Command Line Game Engine
"Who needs a frame buffer?" - @Javidx9
The Original & Best :P
One Lone Coder License
~~~~~~~~~~~~~~~~~~~~~~
- This software is Copyright (C) 2018 Javidx9
- This is free software
- This software comes with absolutely no warranty
- The copyright holder is not liable or responsible for anything
  this software does or does not
- You use this software at your own risk
- You can distribute this software
- You can modify this software
- Redistribution of this software or a derivative of this software
  must attribute the Copyright holder named above, in a manner
  visible to the end user
License
~~~~~~~
One Lone Coder Console Game Engine  Copyright (C) 2018  Javidx9
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; See license for details.
Original works located at:
	https://www.github.com/onelonecoder
	https://www.onelonecoder.com
	https://www.youtube.com/javidx9
GNU GPLv3
	https://github.com/OneLoneCoder/videos/blob/master/LICENSE
From Javidx9 :)
~~~~~~~~~~~~~~~
Hello! Ultimately I don't care what you use this for. It's intended to be
educational, and perhaps to the oddly minded - a little bit of fun.
Please hack this, change it and use it in any way you see fit. You acknowledge
that I am not responsible for anything bad that happens as a result of
your actions. However this code is protected by GNU GPLv3, see the license in the
github repo. This means you must attribute me if you use it. You can view this
license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
Cheers!*/


#include <iostream>
#include "pch.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
//need this to get the windows console size and frame
#include "olcConsoleGameEngine.h"
using namespace std;

class _UltimateFPS : public olcConsoleGameEngine
{
public:
	_UltimateFPS()
	{
		m_sAppName = L"Ultimate First Person Shooter";	//creats the console title name
	}
	virtual bool OnUserCreate()
	{

		//creating the games map


		map += L"################################";//0
		map += L"#..............##............###";//1
		map += L"########.#########.......#######";//2
		map += L"#......#.#.....##....####......#";//3
		map += L"#...#.....#....#...............#";//4
		map += L"#...#.....###..#...............#";//5
		map += L"#...#...#......#...............#";//6
		map += L"###..#......##.#......###......#";//7
		map += L"#............#.#......###......#";//8
		map += L"#..#..###....#.#...............#";//9
		map += L"#..#..####....#................#";//10
		map += L"#........##############..#######";//11
		map += L"#######..#.....#......#..#.....#";//12
		map += L"#........###...#......#..#.....#";//13
		map += L"#..####........#......#....#...#";//14
		map += L"############.##......#....#....#";//15
		map += L"############.#.......#....######";//0
		map += L"#..............##..............#";//1
		map += L"###......##...###..............#";//2
		map += L"#......#.#.....#...............#";//3
		map += L"#...#.....#....#...............#";//4
		map += L"#...#.....###..##......##......#";//5
		map += L"#...#...#......#...............#";//6
		map += L"###..#......##.#.......##......#";//7
		map += L"#............#.#...............#";//8
		map += L"#..#..###....#.##......##......#";//9
		map += L"#..#..####....##...............#";//10
		map += L"#........#######.......##......#";//11
		map += L"#######..#.....#.......##......#";//12
		map += L"#........###...#...............#";//13
		map += L"#..####........#...............#";//14
		map += L"################################";//15

		//spriteWall = 

		return true;
	}
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//controls
		//handle rotation and movment
		if (m_keys[L'A'].bHeld) //changes angle when pressed in console
		{
			fPlayerA -= (fSpeed * 1.1f) * fElapsedTime;
		}
		if (m_keys[L'D'].bHeld) //changes angle when pressed in console
		{
			fPlayerA += (fSpeed * 1.1f) * fElapsedTime;
		}
		if (m_keys[L'W'].bHeld) //changes angle when pressed in console
		{
			fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
			//test colide with wall
			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
				fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
			}

		}
		if (m_keys[L'S'].bHeld) //changes angle when pressed in console
		{
			fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
			//test colide with wall
			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
			{
				fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
				fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
			}
		}


		//loop for the sudo view
		for (int x = 0; x < ScreenWidth(); x++)
		{
			//for each colum, cal the projected ray angle in world space
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fFOV;

			//track the distance from player to wall
			float fDistanceToWall = 0;
			bool bHitWall = false; //if ray has hit a wall
			bool bBoundary = false; // the boundray of each cell wall

			//unit vector for a ray in player space
			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);
			//looking for wall or out of range flag
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				//each ray tracking to the wall
				fDistanceToWall += 0.1f;
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
				//test if out of bounds
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;
					fDistanceToWall = fDepth;	//save the distance to the wall
				}
				else
				{
					//ray is inbounds so test if block in view is hit
					if (map[nTestY * nMapWidth + nTestX] == '#')
					{
						bHitWall = true;   //if ray hit a wall
						//store distance , dot in a vector
						vector<pair<float, float>> p;

						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{
								float vy = (float)nTestY + ty - fPlayerY;//find the corners in realtion the the charater
								float vx = (float)nTestX + tx - fPlayerX;
								float d = sqrt(vx*vx + vy * vy);//distance
								float dot = (fEyeX * vx / d) + (fEyeY*vy / d);//dot product
								p.push_back(make_pair(d, dot));//make a pair and push to vector p

							}
						//sort pairs from closest to farthest
						sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first; }); //lamda sort
						//the angle of forgivness in find ing the two closest angles
						float fBound = 0.01f;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;

					}
				}
			}

			//cal the distance to ceiling and floor
			int nCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)fDistanceToWall);
			int nFloor = ScreenHeight() - nCeiling;

			//unicode for a blocks shade
			short nShade = ' ';


			if (fDistanceToWall <= fDepth / 4.0f)		nShade = 0x2588;//close to wall
			else if (fDistanceToWall < fDepth / 3.0f)	nShade = 0x2593;
			else if (fDistanceToWall < fDepth / 2.0f)	nShade = 0x2592;
			else if (fDistanceToWall < fDepth)			nShade = 0x2591;
			else										nShade = ' ';//too far

			//if boundary is found
			if (bBoundary)
				nShade = ' ';


			//draw the ceiling 
			for (int y = 0; y < ScreenHeight(); y++)
			{
				//check ceiling and draw
				if (y <= nCeiling)
					Draw(x, y, L' ');
				else if (y > nCeiling && y <= nFloor)
					Draw(x, y, nShade);
				else
				{
					//shade the floor for perspective
					float b = 1.0f - (((float)y - ScreenHeight() / 2.0f) / ((float)ScreenHeight() / 2.0f));
					if (b < 0.25)			nShade = '#';
					else if (b < 0.5)		nShade = 'x';
					else if (b < 0.75)		nShade = '.';
					else if (b < 0.9)		nShade = '-';
					else					nShade = ' ';
					Draw(x, y, nShade);	//checks the screen and "recolors the screen"

				}

			}

		}
		//display states
		//display map
		for (int nx = 0; nx < nMapWidth; nx++)
			for (int ny = 0; ny < nMapWidth; ny++)
			{
				Draw(nx + 1, ny + 1, map[ny * nMapWidth + nx]);//note map is offset for neat ness
			}
		//player marker
		Draw(1 + (int)fPlayerX, 1 + (int)fPlayerY, L'P');

		return true;
	}

private:
	
	//player postions in the space and the start location
	float fPlayerX = 1.0f;	//x cord
	float fPlayerY = 1.0f;	//y cord
	float fPlayerA = 0.0f;	//the view angle

	//note 16x16
	wstring map;
	//players map to infer location
	int nMapHeight = 32;
	int nMapWidth = 32;

	//feild of view var
	float fFOV = 3.14159 / 4.0;
	float fDepth = 16.0f;
	//speed mod
	float fSpeed = 2.0f;
};



int main()
{

	_UltimateFPS game;
	game.ConstructConsole(240, 180, 4, 4);
	game.Start();
	

		

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
