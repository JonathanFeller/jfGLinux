#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

int main(int argc, char **argv)
{
    Display *display = XOpenDisplay(NULL);
    int screen_num = DefaultScreen(display);
    Window root = RootWindow(display, screen_num);
    Visual *visual = DefaultVisual(display, screen_num);

    char *data = new char[512 * 512 * 4];
    XImage *img = XCreateImage(display, visual, DefaultDepth(display, screen_num), ZPixmap, 0, data, 512, 512, 32, 0);

    Window win = XCreateSimpleWindow(display, root, 50, 50, 512, 512, 1, 0, 0);
    XSetStandardProperties(display, win, "Testing", "Hi", None, NULL, 0, NULL);
    XSelectInput(display, win, ExposureMask);
    GC gc = XCreateGC(display, win, 0, 0);
    XMapWindow(display, win);

    XEvent event;
    while (true)
    {
        int count = 512 * 512;
        for (int i = 0; i < count; ++i)
            ((int32_t *)data)[i] = 0x000000FF | 0x00000F00;

        XPutImage(display, win, gc, img, 0, 0, 0, 0, 512, 512);
        XSetForeground(display, gc, WhitePixel(display, screen_num));
        char strBuffer[64];
        sprintf(strBuffer, "Testing one two three");
        XClearWindow(display, win);
        XDrawString(display, win, gc, 10, 10, strBuffer, strlen(strBuffer));

        // TODO: Why does this prevent the window from being redrawn?
        // XNextEvent(display, &event);
        // if (event.type == Expose)
        // {
        // }
    }

    delete[] data;

    XDestroyWindow(display, win);
    XCloseDisplay(display);

    return 0;
}