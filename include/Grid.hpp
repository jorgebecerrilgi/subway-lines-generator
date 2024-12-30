#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>
#include "Vector2.hpp"

struct Path
{
    std::vector<Vector2<int> > points;
    SDL_Color color;
};

class Grid
{
public:
    Grid(Vector2<int> origin, int width, int height, int step);
    ~Grid();

    void draw(SDL_Renderer *renderer, const SDL_Color &color);
    int addPath(Path path);
    void removePath(int index);
    void drawPaths(SDL_Renderer *renderer);

private:
    Vector2<int> _origin;
    int _width;
    int _height;
    int _step;
    int _w;
    int _h;
    std::vector<Path> _paths;
};

#endif // GRID_H
