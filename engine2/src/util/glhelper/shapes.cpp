#include <GL/gl.h>

/*
 * Draws a solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
 */
void solidCube( double dSize ){
	
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /* PWO: Again, I dared to convert the code to use macros... */
    glBegin( GL_QUADS );
        N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
        N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
        N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
        N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
        N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
        N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
    glEnd();

#   undef V
#   undef N
}

void DrawRectangle2D( double _dX, double _dY, double _dWidth, double _dHeight, bool _bFilled )
{
    if ( _bFilled )
    {
	    glBegin( GL_QUADS );

		    glTexCoord2f( 0.0f, 0.0f );
		    glVertex2d( _dX, _dY + _dHeight );

            glTexCoord2f( 1.0f, 0.0f );
		    glVertex2d( _dX + _dWidth, _dY + _dHeight );

		    glTexCoord2f( 1.0f, 1.0f );
		    glVertex2d( _dX + _dWidth, _dY );

		    glTexCoord2f( 0.0f, 1.0f );
		    glVertex2d( _dX, _dY );

        glEnd( );
    }
    else
    {
	    glBegin( GL_LINE_LOOP );

		    glVertex2d( _dX, _dY + _dHeight );
		    glVertex2d( _dX + _dWidth, _dY + _dHeight );
		    glVertex2d( _dX + _dWidth, _dY );
		    glVertex2d( _dX, _dY );

        glEnd( );
    }
}