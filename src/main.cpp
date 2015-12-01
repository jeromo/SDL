
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "EntornoGrafico.h"





int main( int argc, char* args[] )
{
    EntornoGrafico x;

    if( !x.loadMedia() )
    {
		cout << "Failed to load media!\n" ;
	}
	else
	{
	    x.showImage();
	}


	return 0;
}
