#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

Display *dis;
Window win;
GC gc;

struct point
{
    int x;
    int y;
} dot;

int main()
{
    init();
    char text[255];
    while (True)
    {
        XEvent event;
        KeySym key;
        XNextEvent(dis, &event);
        if (event.type == Expose && event.xexpose.count == 0)
        {
            draw();
        }
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1)
        {
            if (text[0] == 'q')
            {
                close();
            }
            printf("You pressed %c\n", text[0]);
        }
        if (event.type == ButtonPress)
        {
            int x = event.xbutton.x;
            int y = event.xbutton.y;
            XSetForeground(dis, gc, red);
            XDrawLine(dis, win, gc, dot.x, dot.y, x, y);
            XSetForeground(dis, gc, blue);
            strcpy(text, "Hello world");
            XDrawString(dis, win, gc, x, y, text, strlen(text));
        }
    }

    return 0;
}

void init()
{
    dot.x = 100;
    dot.y = 100;
    dis = XOpenDisplay((char *)0);
    black = BlackPixel(dis, screen);
    white = BlackPixel(dis, screen);
    red = RGB(255, 0, 0);
    blue = RGB(0, 0, 255);
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 100, 100, 128, 128, 0, black, white);
    XSetStandardProperties(dis, win, "Testing", "Hi", None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
    gc = XCreateGC(dis, win, 0, 0);
    // XSetBackground(dis, gc, white);
    XMapWindow(dis, win);
}

void SetPixel(uint16_t x, uint16_t y, uint32_t color)
{
    XSetForeground(dis, gc, color);
    XDrawPoint(dis, win, gc, x, y);
}

void close()
{
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

void draw()
{
    XClearWindow(dis, win);

    char bitmap[128 * 128 * 8];
    memset(bitmap, 255, sizeof(bitmap));

    XVisualInfo visTemp;
    int num_visuals = 0;
    auto visualInfo = XGetVisualInfo(dis, 0, &visTemp, &num_visuals);
    XImage *frameBuffer = XCreateImage(dis, visualInfo->visual, 1, XYBitmap, 0, (char *)bitmap, 128, 128, 16, 0);

    Pixmap pixmap = XCreatePixmap(dis, win, 128, 128, 24);
    XPutImage(dis, pixmap, gc, frameBuffer, 0, 0, 0, 0, 128, 128);
    XCopyArea(dis, pixmap, win, gc, 0, 0, 128, 128, 0, 0);
    XFreePixmap(dis, pixmap);
}