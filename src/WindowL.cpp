#include "WindowL.h"
#include <iostream>

WindowL::WindowL(Render &render, std::string title, int left, int top, int width, int height) : m_render(render)
{
    m_display = XOpenDisplay(NULL);
    int screen_num = DefaultScreen(m_display);
    Visual *visual = DefaultVisual(m_display, screen_num);

    m_xImage = XCreateImage(m_display, visual, DefaultDepth(m_display, screen_num), ZPixmap, 0, reinterpret_cast<char *>(m_render.getData()), width, height, 32, 0);
    Window root = RootWindow(m_display, screen_num);
    m_window = XCreateSimpleWindow(m_display, root, left, top, width, height, 1, 0, 0);
    XSetStandardProperties(m_display, m_window, title.c_str(), "jfGL", None, NULL, 0, NULL);
    XSelectInput(m_display, m_window, ExposureMask | KeyPressMask | KeyReleaseMask | MotionNotify);
    XGrabPointer(m_display, m_window, True, PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    m_gc = XCreateGC(m_display, m_window, 0, 0);
    XMapWindow(m_display, m_window);
    m_wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &m_wm_delete_window, 1);

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

RECT WindowL::getWindowRect()
{
    RECT rect{};
    Window child;
    XWindowAttributes xwa;
    int screen = DefaultScreen(m_display);
    Window root_window = RootWindow(m_display, screen);
    XTranslateCoordinates(m_display, m_window, root_window, 0, 0, &rect.left, &rect.top, &child);
    XGetWindowAttributes(m_display, m_window, &xwa);
    return rect;
}

void WindowL::SwapBuffers(int offsetX, int offsetY)
{
    XPutImage(m_display, m_window, m_gc, m_xImage, 0, 0, offsetX, offsetY, m_width, m_height);
}

int WindowL::msgLoop()
{
    XEvent xEvent;
    XCheckTypedWindowEvent(m_display, m_window, ClientMessage, &xEvent);
    if (xEvent.type == ClientMessage)
    {
        if ((Atom)xEvent.xclient.data.l[0] == m_wm_delete_window)
        {
            // TODO: Break if you want to exit
            return 0;
        }
    }

    while (XCheckWindowEvent(m_display, m_window, KeyPress | KeyRelease | MotionNotify, &xEvent))
    {
        auto keycode = xEvent.xkey.keycode;
        auto state = xEvent.xkey.state;
        KeySym keySym = XkbKeycodeToKeysym(m_display, keycode, 0, 0);
        int keyPress = keySym & 0xFF;
        if (keySym == XK_Escape)
            return 0;
        switch (xEvent.type)
        {
        case KeyRelease:
            pressedKeys[keyPress] = false;
            break;
        case KeyPress:
            pressedKeys[keyPress] = true;
            break;
        }
    }
    return 1;
}

bool WindowL::getKeyHeld(char keyCode)
{
    return pressedKeys[keyCode];
}

bool WindowL::hasFocus()
{
    Window focused;
    int revert_to;
    XGetInputFocus(m_display, &focused, &revert_to);
    return m_window == focused;
}

std::string WindowL::buildFilePath(std::string path)
{
    char pathBuffer[MAX_FILE_PATH];
    getcwd(pathBuffer, MAX_FILE_PATH);
    pathBuffer[strlen(pathBuffer)] = '/';
    strcat(pathBuffer, path.c_str());
    return std::string(pathBuffer);
}

void WindowL::ResetCursorPos()
{
    POINT absPos = getCursorAbsPos();
    if (absPos.x > getWidth() - 1 || absPos.y > getHeight() - 1 || absPos.x < 1 || absPos.y < 1)
    {
        XWarpPointer(m_display, None, m_window, 0, 0, 0, 0, getWidth() / 2, getHeight() / 2);
        m_mouse_displacement += (POINT{getWidth() / 2, getHeight() / 2} - absPos);
    }
}

bool WindowL::cursorDisplacement(POINT &displacementRef)
{
    POINT displacement = getCursorAbsPos();
    displacementRef = displacement - m_mouse_displacement;
    m_mouse_displacement = displacement;
    return displacementRef;
}

POINT WindowL::getCursorAbsPos()
{
    POINT point{};
    Window r, c;
    int rx, ry;
    unsigned int m;
    XQueryPointer(m_display, m_window, &r, &c, &rx, &ry, &point.x, &point.y, &m);
    return point;
}

POINT WindowL::getCursorPosFromCenter()
{
    POINT cursor{getCursorAbsPos()};
    POINT halfSize{getWidth() / 2, getHeight() / 2};
    return cursor - halfSize;
}

void WindowL::CursorVisible(bool visible)
{
    XDefineCursor(m_display, m_window, visible ? None : MakeBlankCursor());
    m_cursor_visible = visible;
}

Cursor WindowL::MakeBlankCursor()
{
    static char data[1] = {0};
    Cursor cursor;
    Pixmap blank;
    XColor dummy;

    int screen = DefaultScreen(m_display);
    Window root_window = RootWindow(m_display, screen);
    blank = XCreateBitmapFromData(m_display, root_window, data, 1, 1);
    cursor = XCreatePixmapCursor(m_display, blank, blank, &dummy, &dummy, 0, 0);
    XFreePixmap(m_display, blank);

    return cursor;
}