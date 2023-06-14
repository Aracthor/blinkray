struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    constexpr Color()
        : r(0)
        , g(0)
        , b(0)
        , a(0)
    {
    }

    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }
};
