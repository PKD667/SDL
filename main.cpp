#include <SDL2/SDL.h>   
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>   
#include <string>
#include <vector>
#include <iostream>
#include <time.h>

template<typename T>
constexpr T WIDTH{ 800 };

template<typename T>
constexpr T HEIGHT{ 600 };

template<typename T>
constexpr T TOTAL_POINTS{ 5000 };

struct  Δ {
    float i, j;
};
struct force {
    Δ v;
    SDL_Point application;
};


class thing {
    public:
        SDL_FRect rect {0,0,50,50};
        Δ vel {0,0};
        Δ acceleration {0,0};
        float ρ = 1; 
        float mass = ρ * (rect.h * rect.w);
        thing ()
        {

        }
	    void Updating() 
	    {	
            vel.i += acceleration.i;
            vel.j += acceleration.j;
            rect.x += vel.i;
		    rect.y += vel.j;
            acceleration.i = 0;
            acceleration.j = 0;
            //std::cout << " [U] -> " << " x : " << rect.x << "  y : " << rect.y << std::endl;

	    }
        void Force(force F)
        {
          
          acceleration.i +=  F.v.i / ( mass) ;
          acceleration.j += F.v.j / ( mass) ;
          std::cout <<  rect.y << " " << rect.x << "\n └─> " << acceleration.i << " " << acceleration.j << std::endl;
        };
	    void Borders()
	    {
		    if (rect.x + rect.w > WIDTH<int> ) 
            {
                vel.i = -vel.i * 0.8;
                Updating();
            }
		    if (rect.x <= 0 )  
            {
                vel.i = -vel.i * 0.8;
                Updating();
            }
		    if (rect.y + rect.h > HEIGHT<int> )
            {
                vel.j = -vel.j * 0.8;
                Updating();
            } 
		    if (rect.y <= 0 )
            {
                vel.j = -vel.j * 0.8;
                Updating();
            } 
            
	    }

};
// F / m = A
int main(int argc, char* argv[])
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

     SDL_Window* pWindow{ nullptr };
    SDL_Renderer* pRenderer{ nullptr };

     if (SDL_CreateWindowAndRenderer(WIDTH<unsigned int>, HEIGHT<unsigned int>, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_NONE);

    SDL_Event events;
    bool isOpen{ true };
    SDL_Rect CollRect{};

    std::vector<thing> things; //vector of things to be rendered
    for (int i = 0; i < 2; i++) {
        std::srand(time(nullptr) + i);
        thing thing_object ;

        thing_object.rect.x = float(std::rand() % (WIDTH<int> - int(thing_object.rect.w)));
        thing_object.rect.y = float(std::rand() % (HEIGHT<int> - int(thing_object.rect.h))) ;
        thing_object.vel.i = 1;
        thing_object.vel.j = 1;

        // Add hte object to the vector
        things.push_back(thing_object);
        std::cout << things[i].rect.x << " " << things[i].rect.y << " - " << things[i].vel.i << " " << things[i].vel.j << std::endl;
        
    }
    

     while (isOpen)
    {
         while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = false;
                break;
            }
        }
        for (int i = 0; i < things.size(); i++)
        {
            
            things[i].Updating();
            things[i].Borders();

            for (int j = i + 1; j < things.size() ; j++)
            {

                SDL_Rect int_rect_i = {int(things[i].rect.x),int(things[i].rect.y),int(things[i].rect.w),int(things[i].rect.h)};
                SDL_Rect int_rect_j = {int(things[j].rect.x),int(things[j].rect.y),int(things[j].rect.w),int(things[j].rect.h)};
                if (SDL_IntersectRect(&int_rect_i, &int_rect_j,&CollRect))
                {
                    things[i].Force({{(things[j].mass * things[j].vel.i),(things[j].mass * things[j].vel.j)},0});
                    things[j].Force({{(things[i].mass * things[i].vel.i),(things[i].mass * things[i].vel.j)},0});
                    things[i].Updating();
                    things[j].Updating();
                }
            }

        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); 
        SDL_RenderClear(pRenderer);  

        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255); 
        for (int i = 0; i < things.size(); i++) {
            //std::cout << things[i].rect.x << " " << things[i].rect.y << " - " << things[i].vel.i << " " << things[i].vel.j << std::endl;
            SDL_RenderFillRectF(pRenderer, &things[i].rect);
        }
        SDL_RenderPresent(pRenderer);  

        SDL_Delay(10);
    }



    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}
