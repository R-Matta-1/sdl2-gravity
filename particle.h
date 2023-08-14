#include<vector>
#include <iostream>
#include<SDL.h>
#include<cmath>
//IN THE UPDATE COMAND, UPDATE BOTH THE X, Y AND THE RECT THEy are not conECTED

#define pixelsize 7


#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

double distance(double x1, double y1, double x2, double y2) {
	return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

class particle
{
public:
	
	SDL_Color color;
	
	std::vector<particle*> neighbors;
	SDL_Rect rect;
	int X;
	int Y;
	double Xm =0;
double Ym =0 ;

	particle( SDL_Color rgba, uint16_t locateX, uint16_t LocateY);
	void draw(SDL_Renderer* r);

	void action(int mouseX, int mouseY, int Gconst);
	
	~particle() {
		
	}
	
};

particle::particle( SDL_Color rgba, uint16_t locateX, uint16_t LocateY)
{
	
	color = rgba;
	color.r -= rand() % 255;
	color.g -= rand() % 255;
	color.b -= rand() % 255;
	X = locateX;
	Y = LocateY;

	rect = { locateX,LocateY,pixelsize,pixelsize };
};

void particle::draw(SDL_Renderer* r) {

	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(r, &rect);

};


 void particle::action(int mouseX, int mouseY,int Gconst) {
	 for (size_t i = 0; i < neighbors.size(); i++)
	 {
		 int NX = neighbors[i]->X;
		 int NY = neighbors[i]->Y;
		 if (X!=NX && Y != NY)
		 {

		 if (distance(X, Y, NX, NY) <= pixelsize * 2 ) {
			 Ym = -1*(NY - Y);
			 Xm = -1*(NX - X);
		 }
		 }
		
	 }
	 double gravDist = distance(X, Y, mouseX, mouseY)+0.0001;
	 Ym += (mouseY - Y) / (gravDist * Gconst);
	 Xm += (mouseX - X) / (gravDist * Gconst);
	 
	 if (X<=1)
	 {
		 X = 2;
		 Xm *= -1;
	 } else
	 if (X >= WINDOWWIDTH)
	 {
		 X = WINDOWWIDTH;
		 Xm *= -1;
	 } 
	 if (Y <= 1)
	 {
		 Y = 2;
		 Ym *= -1;
	 }
	 else
		 if (Y >= WINDOWHEIGHT)
		 {
			 Y = WINDOWHEIGHT;
			 Ym *= -1;
		 }
	 Y += Ym;
	 X += Xm;
	 rect.x = X;
	 rect.y = Y;
}
 

