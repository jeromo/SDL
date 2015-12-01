#include "EntornoGrafico.h"

EntornoGrafico::EntornoGrafico()
{
    init();
}

EntornoGrafico::~EntornoGrafico()
{
    SDL_FreeSurface( pHelloWorld );
    pHelloWorld = NULL;

    SDL_DestroyWindow( pWindow );
    pWindow = NULL;

    SDL_Quit();
}

void EntornoGrafico::init()
{
    try
    {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            throw ERR_SDL_INIT;

        pWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( pWindow == NULL )
            throw ERR_SDL_CREATE_WIONDOW;

        pScreenSurface = SDL_GetWindowSurface( pWindow );

    }
    catch ( int e)
    {
        cout << "Error "<< e << "SDL_Error: " << SDL_GetError() <<"\n";

        exit (e);

    }

}

bool EntornoGrafico::loadMedia()
{
    int success = true;
    pHelloWorld = SDL_LoadBMP( "/home/jrojo/Projects/C/02_getting_an_image_on_the_screen/hello_world.bmp" );
    if( pHelloWorld == NULL )
    {
        cout << "Unable to load image /home/jrojo/Projects/C/02_getting_an_image_on_the_screen/hello_world.bmp " << SDL_GetError() <<"\n";
        success = false;
    }

    return success;
}

void EntornoGrafico::showImage()
{
    SDL_BlitSurface( pHelloWorld, NULL, pScreenSurface, NULL );
    SDL_UpdateWindowSurface( pWindow );

    SDL_Delay( 2000 );
}
