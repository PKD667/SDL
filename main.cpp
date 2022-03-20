#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

int WIDTH = 800;
int HEIGHT = 600;

void write (std::string file , std::string texte);
void ComputePoints(std::vector<SDL_Point> *points);
SDL_Point r(SDL_Point p );
int sq (int o);

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> r_10(1,10); 



class atom {       
  public:             
    SDL_FPoint point {200,200};  
	float xvel;
	float yvel; 
	void Updating() 
	{
		
    	point.x += xvel;
		point.y += yvel;
	}
	void Borders()
	{
		if (point.x > WIDTH ) point.x = 0;
		if (point.x < 0 ) point.x = WIDTH;
		if (point.y > HEIGHT ) point.y = 0;
		if (point.y < 0 ) point.y = HEIGHT;

	}


	    
};

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
	SDL_Window* window{ nullptr };     
    SDL_Renderer* renderer{ nullptr };
    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit();         
        return EXIT_FAILURE;
    }
    SDL_Event event;
    bool close = false;
	// creates a renderer to render our images
    srand (time(NULL));
    float fps = 0;
	int frames = 0;
    std::vector<atom> atoms;

    for (int i = 0; i < 4   ; i++)
	{
		atom atom_obj;
		atom_obj.xvel = float(r_10(rng) / 10);
		atom_obj.yvel = float(r_10(rng) / 10);
		atoms.push_back(atom_obj);

	}
	// animation loop
	while (!close) 
	{
				// Events management
		
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{

				case SDL_QUIT:
					// handling of close button
					close = 1;
					break;
			}
		}
		// computing
		for (int i = 0; i < 100 ; i++)
		{
        	atoms[i].Updating();
			atoms[i].Borders();
		}
        
        // Rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		for(int i = 0; i < atoms.size();i++)
		{
			SDL_RenderDrawPointF(renderer,atoms[i].point.x , atoms[i].point.y);	
		}
		
		

		//Updating window
        SDL_RenderPresent(renderer); 
		
		
		
		// calculates  fps
		frames ++;
		fps = frames / float(SDL_GetTicks() / 1000.0);
		SDL_SetWindowTitle(window,std::to_string(fps).c_str());
        SDL_Delay(fps / 15);
	}


	// destroy renderer
	SDL_DestroyRenderer(renderer);

	// destroy window
	SDL_DestroyWindow(window);

	// close SDL
	SDL_Quit();

	return 0;
}

int sq (int o)
{
	return o*o;
}

