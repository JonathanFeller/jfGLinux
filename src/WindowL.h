#pragma once
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <limits.h>
#define MAX_FILE_PATH PATH_MAX

#include "Render.h"

class WindowL
{
private:
    Display *m_display;
    Window m_window;
    GC m_gc;
    int m_height;
    int m_width;

    Atom m_wm_delete_window;

    XImage *m_xImage;
    Render &m_render;

    bool pressedKeys[65536]{false};
    bool m_cursor_visible{true};

    POINT m_mouse_displacement;

protected:
    Cursor MakeBlankCursor();
    
public:
    WindowL(Render &render, std::string title, int left, int top, int width, int height);
    ~WindowL();

    static std::string buildFilePath(std::string path);

    void SwapBuffers(int offsetX = 0, int offsetY = 0);
    void Clear();
    int msgLoop();

    RECT getWindowRect();
    Display *getDisplay();
    Window getWindow();
    GC getGC();

    int getHeight();
    int getWidth();
    bool hasFocus();

    bool getKeyHeld(char keyCode);

    void CursorVisible(bool visible);
    void ResetCursorPos();

    POINT getCursorAbsPos();
    POINT getCursorPosFromCenter();
    bool cursorDisplacement(POINT& displacement);
};