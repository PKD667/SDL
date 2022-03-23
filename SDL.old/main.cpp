#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>

int WIDTH = 800;
int HEIGHT = 600;


SDL_Point r(SDL_Point p );
int sq (int o);




class atom {       
  public:             
    SDL_FPoint* point ;  
	float xvel;
	float yvel; 
	atom()
	{
	xvel = (float(rand() % 1000 + 1) / (1000 + (float(rand() % 1000 + 1 ) / 1000))) ;
	yvel = (float(rand() % 1000 + 1) / (1000 + (float(rand() % 1000 + 1 ) / 1000))) ;
	}
	void Updating() 
	{
		
        (*point).x += xvel;
		(*point).y += yvel;
	}
	void Borders()
	{
		if (point->x > WIDTH ) xvel = -xvel;
		if (point->x < 0 ) xvel = -xvel;
		if (point->y > HEIGHT ) yvel = -yvel;
		if (point->y < 0 ) yvel = -yvel;

	}
	void Colisions (std::vector<SDL_FPoint> *points,int num)
	{
		for (int i = 0; i < points->size();i++)
		{
			if(i != num)
			{
				if ((*points)[i].x == point->x && (*points)[i].y == point->y)
				{
					xvel = -xvel * 0.8;
					yvel = -yvel * 0.8;
				}
			}
		}
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
	std::vector<SDL_FPoint> points;

    for (int i = 0; i < 1000   ; i++)
	{
		atom atom_obj;
		SDL_FPoint point_obj {200,200};

		points.push_back(point_obj);
		atoms.push_back(atom_obj);
	}
	for (int i = 0; i < points.size(); i++)
	{
		atoms[i].point = &points[i];
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
		
		for (int i = 0; i < atoms.size(); i++)
		{
        	atoms[i].Updating();
			atoms[i].Borders();
			atoms[i].Colisions(&points,i);
			//std::cout << points[i].x << " : " << points[i].y << " > " << &points[i] << std::endl; //Debug
		}
        // Rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
		SDL_RenderDrawPointsF(renderer,&points[0] ,points.size());	
		
		
		//Updating window
        SDL_RenderPresent(renderer); 
		
		
		// calculates  fps
		frames ++;
		fps = frames / float(SDL_GetTicks() / 1000.0);
		SDL_SetWindowTitle(window,std::to_string(fps).c_str());
		
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

