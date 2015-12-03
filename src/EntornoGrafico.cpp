#include "EntornoGrafico.h"

EntornoGrafico::EntornoGrafico()
{
    init();

    for (int i = KEY_PRESS_SURFACE_DEFAULT; i <  KEY_PRESS_SURFACE_TOTAL; i++)
    {
        keyPressSurfaces[i] = NULL;
    }
}

EntornoGrafico::~EntornoGrafico()
{
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
	    if (keyPressSurfaces[ i ] != NULL)
            SDL_FreeSurface( keyPressSurfaces[ i ] );
	}

	SDL_DestroyWindow( window );

	IMG_Quit();
	SDL_Quit();
}

void EntornoGrafico::init()
{
    try
    {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            throw ERR_SDL_INIT;

        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
            throw ERR_SDL_INIT;

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            throw ERR_SDL_INIT;

        screenSurface = SDL_GetWindowSurface( window );

    }
    catch ( int e)
    {
        cout << "Error "<< e << "SDL_Error: " << SDL_GetError() <<"\n";

        exit (e);

    }

}

void EntornoGrafico::loadSurfaces()
{
    string name_files[] = {"/press.bmp", "/up.bmp", "/down.bmp", "/left.bmp", "/right.bmp" };

    for (int i = KEY_PRESS_SURFACE_DEFAULT; i <  KEY_PRESS_SURFACE_TOTAL; i++)
    {
        keyPressSurfaces[i] = loadSurface( IMAGES_DIR + name_files[i] );
    }
    //JRM Probar un png
    keyPressSurfaces[0] = loadSurface( "/home/jrojo/Projects/C/06_extension_libraries_and_loading_other_image_formats/loaded.png");
}

SDL_Surface *EntornoGrafico::loadSurface( string path )


{
    try
    {
        SDL_Surface* loadedSurface;

        if (path.find( ".png") != string::npos)
        {
            loadedSurface = IMG_Load( path.c_str() );

            if( loadedSurface == NULL )
            {
                cout <<"Unable to load image " << path << "SDL_image Error "<< IMG_GetError()  <<"\n";
                throw  ERR_SDL_LOAD_BMP;
            }
        }
        else
        {
            loadedSurface = SDL_LoadBMP( path.c_str() );
            if ( loadedSurface == NULL )
            {
                cout << "Error en SDL_LoadBMP " + path + "\n";
                throw  ERR_SDL_LOAD_BMP;
            }
        }
        SDL_Surface* optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
        if ( optimizedSurface == NULL )
        {
            cout << "Error en SDL_Convert Surface\n";
            throw  ERR_SDL_LOAD_BMP;
        }
        SDL_FreeSurface( loadedSurface );

        return optimizedSurface;

    }
    catch ( int e)
    {
        cout << "Error "<< e << "SDL_Error: " << SDL_GetError() <<"\n";

        exit (e);

    }

}


void EntornoGrafico::showImage()
{
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    SDL_BlitScaled( currentSurface, NULL, screenSurface, &stretchRect );
    SDL_UpdateWindowSurface( window );

}


void EntornoGrafico::loopUser()
{
    bool quit = false;
    SDL_Event e;

    loadSurfaces();
    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    showImage();


    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                    break;

                case SDLK_DOWN:
                    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                    break;

                case SDLK_LEFT:
                    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                    break;

                case SDLK_RIGHT:
                    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                    break;

                default:
                    currentSurface = keyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                    break;
                }
                showImage();
            }
        }
    }
}
