/*

	gcc xwin_i.cpp -o xwin_i -lX11
	gcc xwin_i.cpp -o xwin_i -I /usr/include/X11 -L /usr/X11/lib -lX11
	gcc xwin_i.cpp -o xwin_i -I /sowhere/else -L /who/knows/where -lX11
	gcc xwin_i.cpp -o xwin_i -lX11 -lstdc++

*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
 

#define WIN_WIDTH   640
#define WIN_HEIGHT  480
 

unsigned long GetColor( Display* dis, char* color_name )
{
    Colormap cmap;
    XColor near_color, true_color;
 
    cmap = DefaultColormap( dis, 0 );
    XAllocNamedColor( dis, cmap, color_name, &near_color, &true_color );
    return( near_color.pixel );
}

 

int main( void )
{
    Display* dis;
    Window win;
    XSetWindowAttributes att;
    GC gc;
    XEvent ev;
 
    int t;
 
    dis = XOpenDisplay( NULL );
    win = XCreateSimpleWindow( dis, RootWindow(dis,0), 100, 100, WIN_WIDTH, WIN_HEIGHT, 5, WhitePixel(dis,0), BlackPixel(dis,0) );
 
    att.backing_store = WhenMapped;
    XChangeWindowAttributes( dis, win, CWBackingStore, &att );
 
    XSelectInput( dis, win, ExposureMask );
    XMapWindow( dis, win );
 
    do{
        XNextEvent( dis, &ev);
    }while( ev.type != Expose );
 
    gc = XCreateGC( dis, DefaultRootWindow(dis), 0, 0 );
    XSetFunction( dis, gc, GXxor );
  /* 
    for (int t = 0; t < 100; t++)
    {
           XSetForeground( dis, gc, BlackPixel(dis, 0)^GetColor( dis, "red"));
           XFillArc( dis, win, gc, t*5+80, t*3+40, 80, 40, 0, 360*64);
           XSetForeground( dis, gc, BlackPixel(dis, 0)^GetColor( dis, "red"));
        usleep(10000);
           XFillArc( dis, win, gc, t*5+80, t*3+40, 80, 40, 0, 360*64);
    }
  */

    XSetForeground( dis, gc, BlackPixel(dis, 0)^GetColor( dis, "red"));

    unsigned int x=600, y=55, d=0, xd=1, yd=1, it=0;
    while ( 1 )
    {
	it ++;
	if(it%100000==0)XClearWindow(dis, win);
	//XDrawLine(display, frame_window, graphical_context, 0+x, 200+y, 400-x++, 200-y++);
	for(int i=0;i < 10;i++)
  		for(int j=0; j <10;j++)
   			XDrawPoint(dis, win, gc, x+i, y+j);
	x+=xd;
	y+=yd;
	if(x > WIN_WIDTH -11|| x < 1) xd = -xd;
	if(y > WIN_HEIGHT -11|| y < 1) yd = -yd;

	//XFlush(display);
	usleep(200); 
    }     

    XDestroyWindow( dis , win );
    XCloseDisplay( dis );

    return(0);

}
