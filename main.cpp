#include <iostream>
#include<SDL.h>

#include <vector>
#include"particle.h"
#include"qtree.h"

#define pixelsize 7
#define pixelTwo 14
#define SANDCOLOR { 255, 255, 255,255 }
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480
using namespace std;

	//gives the creator some space
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

		int round(int start, int multiple) {
			return (int)((int)start / multiple) * multiple;
		}
	void reset(int r,  int g, int b, int a) {
	
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderClear(renderer);
}
	bool moveValid(int Xchange, int Ychange)
	{
		return ( Xchange  < WINDOWWIDTH - (pixelsize * 2)
			&&  Xchange  >(pixelsize * 2)
			&& Ychange  < WINDOWHEIGHT - (pixelsize * 2)
			&&  Ychange  >(pixelsize * 2));
	}
	//holds our particles

	
int main(int argc, char* args[]) {

	cout << "hello, this is my fist project on sdl2, is was made primarily to show a quadtree and practice c++\n use the 1-5 keys to controll the gravity, have fun!\n\n\n\n\n now it could be alot better and i could refine it but i would rather move on and work on other things ";
	//initalize and uze that space
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOWWIDTH, WINDOWHEIGHT, 0, &window, &renderer);

	int gravConst = 10;
	bool running = true;

	int mouseX = 1;
	int mouseY = 1;
	bool mouseDown = false;


	SDL_Event event;
	vector<particle> particles;
		qtree world(0, 0, WINDOWWIDTH, WINDOWHEIGHT);
		particles.push_back(particle( SANDCOLOR, 50, 75));

		Uint32 start_time, frame_time;
		int particlesSize;
	while (running)
	{
		start_time = SDL_GetTicks();

		reset(0, 0, 0, 255);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN) {
				
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
				break;
				case SDLK_1:
					gravConst = 1;
					break;
				case SDLK_2:
					gravConst = 10;

					break;
				case SDLK_3:
					gravConst = 50;

					break;
				case SDLK_4:
					gravConst = 100;

					break;
				case SDLK_5:
					gravConst = 500;

					break;
				default:
				break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					 mouseX = event.button.x;
					 mouseY = event.button.y;
					 mouseDown = true;
					// Handle left mouse button click at (mouseX, mouseY)
				}
			 }
			if (event.type == SDL_MOUSEMOTION) {
				
				 mouseX = event.button.x;
					mouseY = event.button.y;
				
					// Handle left mouse button click at (mouseX, mouseY)
				
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				mouseDown = false;
			}
		}
		
		 particlesSize = particles.size();
		
		 for (auto& p : particles) {
			world.place(p);
			
		};
		if (mouseDown){
		
				if (moveValid(mouseX, mouseY)&&world.find(round(mouseX ,pixelsize) - 3,mouseY - 3, 5, 5).size()==0)
				{
			particles.emplace_back(particle( SANDCOLOR, mouseX+ rand() % 30 -15, mouseY + rand() % 30 - 15));
				}
			
		}
	for (size_t i = 0; i < particlesSize; i++)
		{
			particles[i].neighbors = world.find(particles[i].X - pixelsize, particles[i].Y - pixelsize, pixelTwo, pixelTwo);
		};
	

		//clears renderer with the color we just set
		//draws our guy 
		//////////////////////////////////////////////////////////////////////
	
	for (size_t i = 0; i < particlesSize; i++)
	{
		 particles[i].action(mouseX,mouseY,gravConst ); 
		particles[i].draw(renderer);
	};
		
	//world.draw(renderer);
	
		////////////////////////////////////////////////////////////////////////
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
		world.reset();
		frame_time = SDL_GetTicks() - start_time;
	/*
		if (frame_time % 5 <= 0 )
		{
	
			cout << " ( " << particles.size()  << ", " << frame_time << ")" << "\n";
		}
		*/
	}
	return 0;
}


