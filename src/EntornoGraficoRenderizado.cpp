#include "EntornoGraficoRenderizado.h"

EntornoGraficoRenderizado::EntornoGraficoRenderizado():EntornoGrafico()
{
    try
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            throw ERR_SDL_INIT;


        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL )
            throw ERR_SDL_INIT;

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    catch ( int e)
    {
        cout << "Error "<< e << "SDL_Error: " << SDL_GetError() <<"\n";

        exit (e);

    }
}

EntornoGraficoRenderizado::~EntornoGraficoRenderizado()
{
    //dtor
}

bool EntornoGraficoRenderizado::loadMedia()
{
	bool success = true;

	string media = IMAGES_DIR;
	media  += "/viewport.png";
	texture = loadTexture( media );
	if( texture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

SDL_Texture* EntornoGraficoRenderizado::loadTexture( string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void EntornoGraficoRenderizado::loopUser()
{
    bool quit = false;
    SDL_Event e;

    loadMedia();

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
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				//Top left corner viewport
				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH / 2;
				topLeftViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( renderer, &topLeftViewport );

				//Render texture to screen
				SDL_RenderCopy( renderer, texture, NULL, NULL );


				//Top right viewport
				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( renderer, &topRightViewport );

				//Render texture to screen
				SDL_RenderCopy( renderer, texture, NULL, NULL );


				//Bottom viewport
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( renderer, &bottomViewport );


				//Render texture to screen
				SDL_RenderCopy( renderer, texture, NULL, NULL );


				//Update screen
				SDL_RenderPresent( renderer );        }

    }

}
