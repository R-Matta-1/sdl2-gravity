#include<SDL.h>
#include <vector>


#define SUBTREE_LIMIT 400

using namespace std;
bool intersection(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return !(x1 > x2 + w2 || x1 + w1 < x2 || y1 > y2 + h2 || y1 + h1 < y2);
}



class qtree
{
public:
	qtree(int xx, int yy, int ww, int hh);
		
	int x;
	int y;
	int w;
	int h;
	int Wh;
	int Hh;
	


	qtree* UL = nullptr;
	qtree* UR = nullptr;
	qtree* DL = nullptr;
	qtree* DR = nullptr;

	std::vector<particle> particles;

	SDL_Rect rect;
	std::vector<particle*> find(int xx, int yy, int ww, int hh);
	void reset();
	~qtree();
	void place (particle p);
	void divide();

	void draw(SDL_Renderer* r);
};




qtree::qtree(int xx, int yy, int ww,int hh)
{
	x = xx;
	y = yy;
	w = ww;
	h = hh;
	rect = { x,y,w,h };
		  Wh = w / 2;
		 Hh = h / 2;
	
}

 std::vector<particle*> qtree::find(int xx, int yy, int ww, int hh){

	 std::vector<particle*>awnser;
	  
	 if (UL == 0) {
			for (auto& p : particles) {
				if (intersection(xx, yy, ww, hh, p.X, p.Y, 1, 1)) {
					awnser.push_back(&p);
				}
			}
		}
		else {
		 if (intersection(xx,yy,ww,hh, x, y, Wh,Hh)) {
			 vector<particle*>  ULawnser = UL->find(xx, yy, ww, hh);
			 awnser.insert(awnser.end(), ULawnser.begin(), ULawnser.end());
		 }
		 if (intersection(xx, yy, ww, hh, x + Wh, y, Wh,Hh))
		 {
		 vector<particle*> URawnser = UR->find(xx, yy, ww, hh);
		 awnser.insert(awnser.end(), URawnser.begin(), URawnser.end());
		 }
		 if (intersection(xx, yy, ww, hh, x, y +Hh, Wh,Hh))
		 {
		 vector<particle*> DLawnser = DL->find(xx, yy, ww, hh);
		 awnser.insert(awnser.end(), DLawnser.begin(), DLawnser.end());
		 }
		 if (intersection(xx, yy, ww, hh, x + Wh, y +Hh, Wh,Hh))
		 {
		 vector<particle*> DRawnser = DR->find(xx, yy, ww, hh);
		 awnser.insert(awnser.end(), DRawnser.begin(), DRawnser.end());

		 }


	 }
	 return awnser ;
}

inline void qtree::reset()
{
	
	particles.clear();
	delete UL; UL = nullptr;
	delete UR; UR = nullptr;
	delete DR; DR = nullptr;
	delete DL; DL = nullptr;
	

}

qtree::~qtree()
{
	delete UL;
	delete UR;
	delete DR;
	delete DL;
}

 void qtree::place(particle p)
{
	 if (UL != 0)
	 {
		 int pX = p.X;
		 int pY = p.Y;
		

		 if (pX >= x + Wh  && pY >= y + Hh) {
			 DR->place(p);
		 }
		 else if (pX >= x + Wh  && pY < y + Hh) {
			 UR->place(p);
		 }
		 else if (pX < x + Wh  && pY >= y +Hh) {
			 DL->place(p);
		 }
		 else {
			 UL->place(p);
		 }
	 }

	 else {
		 particles.emplace_back(p);
	 }
	 if (particles.size()>SUBTREE_LIMIT&& w >=20)
	 {
		 divide();
		
	 }
 }

  void qtree::divide()
 {
UL = new qtree(x, y, Wh, Hh); // Create a new child node in the Upper Left quadrant
UR = new qtree(x + Wh, y, Wh, Hh); // Upper Right quadrant
DL = new qtree(x, y + Hh, Wh, Hh); // Lower Left quadrant
DR = new qtree(x + Wh, y + Hh, Wh, Hh); // Lower Right quadrant

int i = particles.size() - 1;
while (i >= 0) {
	particle p = particles[i];
	if (p.X >= x + w / 2) {
		if (p.Y >= y + h / 2) DR->place(p);
		else UR->place(p);
	}
	else {
		if (p.Y >= y + h / 2) DL->place(p);
		else UL->place(p);
	} 
	particles.pop_back();
	i--;
}

 }


  void qtree::draw(SDL_Renderer* r) {

	  if(UL == 0){
		  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

		  SDL_RenderDrawRect(r, &rect);
	  }
	  else
	  {
		  UL->draw(r);
		  UR->draw(r);
		  DL->draw(r);
		  DR->draw(r);
	  }
  }
