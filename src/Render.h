class Bitmap
{
public:
    char *m_data;
    int m_width;
    int m_height;

    Bitmap(long width, long height);
    ~Bitmap();

    void Clear();

    void setPixel(int x, int y, char r, char g, char b);
};

class Render : public Bitmap
{
public:
    Render(long width, long height);
};
