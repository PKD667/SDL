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

class thing {
    public:
        SDL_FRect rect ;
        float xvel;
	    float yvel; 
        thing ()
        {

        }
	    void Updating() 
	    {	
            rect.x += xvel;
		    rect.y += yvel;
            std::cout << " [U] -> " << " x : " << rect.x << "  y : " << rect.y << std::endl;

	    }
	    void Borders()
	    {
		    if (rect.x + rect.w > WIDTH<int> ) 
            {
                xvel = -xvel * 0.8;
                Updating();
            }
		    if (rect.x <= 0 ) 
            {
                xvel = -xvel * 0.8;
                Updating();
            }
		    if (rect.y + rect.h > HEIGHT<int> )
            {
                yvel = -yvel * 0.8;
                Updating();
            } 
		    if (rect.y <= 0 )
            {
                yvel = -yvel * 0.8;
                Updating();
            } 
            
	    }
};
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
    for (int i = 0; i < 10;i++) {
        std::srand(time(nullptr) + i);
        thing thing_object ;
        thing_object.rect.x = float(std::rand() % (WIDTH<int> - int(thing_object.rect.w)));
        thing_object.rect.y = float(std::rand() % (HEIGHT<int> - int(thing_object.rect.h))) ;
        thing_object.xvel = 1;
        thing_object.yvel = 1;
        things.push_back(thing_object);
        
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
            
            for (int j = i + 1; j < things.size(); j++)
            {
                SDL_Rect int_rect_i = {static_cast<int>(things[i].rect.x),static_cast<int>(things[i].rect.y),static_cast<int>(things[i].rect.w),static_cast<int>(things[i].rect.h)};
                SDL_Rect int_rect_j = {static_cast<int>(things[j].rect.x),static_cast<int>(things[j].rect.y),static_cast<int>(things[j].rect.w),static_cast<int>(things[j].rect.h)};
                if (SDL_HasIntersection(&int_rect_i, &int_rect_j))
                {
                    things[i].xvel = -things[i].xvel * 0.8;
                    things[j].xvel = -things[j].xvel * 0.8;
                    things[i].yvel = -things[i].yvel * 0.8;
                    things[j].yvel = -things[j].yvel * 0.8;
                    things[i].Updating();
                    things[j].Updating();


                }
                
            }
            


        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); 
        SDL_RenderClear(pRenderer);  

        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255); 
        for (int i = 0; i < things.size(); i++) {
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
