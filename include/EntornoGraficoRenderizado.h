#ifndef ENTORNOGRAFICORENDERIZADO_H
#define ENTORNOGRAFICORENDERIZADO_H

#include <EntornoGrafico.h>
#define IMAGES_DIR "/home/jrojo/Projects/C/09_the_viewport"

class EntornoGraficoRenderizado : public EntornoGrafico
{
    public:
        EntornoGraficoRenderizado();
        virtual ~EntornoGraficoRenderizado();
        void loopUser();
    protected:
    private:
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture = NULL;

        bool loadMedia();
        SDL_Texture* loadTexture( string path );

};

#endif // ENTORNOGRAFICORENDERIZADO_H
