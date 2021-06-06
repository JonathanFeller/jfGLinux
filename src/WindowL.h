#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string>

#include "Render.h"

class WindowL
{
private:
    Display *m_display;
    Window m_window;
    GC m_gc;
    int m_height;
    int m_width;

    XImage *m_xImage;
    Render &m_render;

public:
    WindowL(Render &render, std::string title, int left, int top, int width, int height);
    ~WindowL();

    void SwapBuffers(int offsetX = 0, int offsetY = 0);
    void Clear();
    int msgLoop();

    Display *getDisplay();
    Window getWindow();
    GC getGC();

    int getHeight();
    int getWidth();
};