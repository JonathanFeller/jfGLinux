#include "Render.h"
#include <string.h>

Bitmap::Bitmap(long width, long height)
{
    m_data = new char[width * height * 4];
    m_width = width;
    m_height = height;
};

Bitmap::~Bitmap()
{
    delete[] m_data;
};

void Bitmap::Clear()
{
    memset(m_data, 0, m_width * m_height * 4);
}

void Bitmap::setPixel(int x, int y, char r, char g, char b)
{
    long index = (x * 4) + (y * m_width * 4);
    m_data[index + 0] = b;
    m_data[index + 1] = g;
    m_data[index + 2] = r;
}

Render::Render(long width, long height) : Bitmap(width, height){};