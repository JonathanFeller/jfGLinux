#pragma once

typedef unsigned char BYTE;

struct RECT
{
	int top;
	int left;
	int bottom;
	int right;
};

struct POINT
{
	int x;
	int y;
	POINT operator-(POINT const &point) { return POINT{x - point.x, y - point.y}; }
	POINT &operator+=(POINT const &point)
	{
		x += point.x;
		y += point.y;
		return *this;
	};
	operator bool() const { return x || y; };
};

typedef struct _BitmapFileHeader_
{
	uint16_t bfType;
	uint32_t bfSize;
	uint32_t bfReserved;
	uint32_t bfOffBits;
}
__attribute__((packed))
BITMAPFILEHEADER;

typedef struct _BitmapInfoHeader_
{
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} BITMAPINFOHEADER;