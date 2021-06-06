#include "WindowL.h"

WindowL::WindowL(Render &render, std::string title, int left, int top, int width, int height) : m_render(render)
{
    m_display = XOpenDisplay(NULL);
    int screen_num = DefaultScreen(m_display);
    Visual *visual = DefaultVisual(m_display, screen_num);

    m_xImage = XCreateImage(m_display, visual, DefaultDepth(m_display, screen_num), ZPixmap, 0, m_render.m_data, width, height, 32, 0);
    XID root = RootWindow(m_display, screen_num);
    m_window = XCreateSimpleWindow(m_display, root, left, top, width, height, 1, 0, 0);
    XSetStandardProperties(m_display, m_window, title.c_str(), "jfGL", None, NULL, 0, NULL);
    XSelectInput(m_display, m_window, ExposureMask);
    m_gc = XCreateGC(m_display, m_window, 0, 0);
    XMapWindow(m_display, m_window);

    m_width = width;
    m_height = height;
}

void WindowL::Clear()
{
    XClearWindow(m_display, m_window);
};

WindowL::~WindowL()
{
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
}

Display *WindowL::getDisplay() { return m_display; };
Window WindowL::getWindow() { return m_window; };
GC WindowL::getGC() { return m_gc; };

int WindowL::getHeight()
{
    return m_height;
}

int WindowL::getWidth()
{
    return m_width;
}

void WindowL::SwapBuffers(int offsetX, int offsetY)
{
    XPutImage(m_display, m_window, m_gc, m_xImage, 0, 0, offsetX, offsetY, m_width, m_height);
}