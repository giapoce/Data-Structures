#include <cstdlib>
#include <iostream>
#include <conio2.h>

using namespace std;
void DrawBox ( char cChar, int nTopX, int nTopY, int nWidth, int nHeight);

void DrawBox ( char cChar, int nTopX, int nTopY, int nWidth, int nHeight)
{
    
    int x,y;
    
    for ( y = nTopY; y < nTopY + nHeight; y++) {

        gotoxy ( nTopX, y );
        putch( cChar );

        gotoxy ( nTopX + nWidth, y );
        putch( cChar );
    }

    for ( x = nTopX; x < nTopX + nWidth; x++) {

        gotoxy ( x, nTopY );
        putch( cChar );

        gotoxy ( x, nTopY + nHeight );
        putch( cChar );
        
    }
}


int main() {

    return 0;
}
