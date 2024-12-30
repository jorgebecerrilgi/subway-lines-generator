#include <iostream>
#include "Grid.hpp"

Grid::Grid(Vector2<int> origin, int width, int height, int step)
    : _origin(origin),
      _width(width),
      _height(height),
      _step(step),
      _w(width / step),
      _h(height / step) {}

Grid::~Grid() {}

void Grid::draw(SDL_Renderer *renderer, const SDL_Color &color)
{
    const int x2 = _origin.x + _width;
    const int y2 = _origin.y + _height;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int x1 = _origin.x; x1 <= x2; x1 += _step)
    {
        SDL_RenderDrawLine(renderer, x1, _origin.y, x1, y2);
    }
    for (int y1 = _origin.y; y1 <= y2; y1 += _step)
    {
        SDL_RenderDrawLine(renderer, _origin.x, y1, x2, y1);
    }
}

int Grid::addPath(Path path)
{
    _paths.push_back(path);
    return _paths.size() - 1;
}

void Grid::removePath(int index)
{
    _paths.erase(_paths.begin() + index);
}

void Grid::drawPaths(SDL_Renderer *renderer)
{
    // Matrix representing the grid.
    // Each position count the number of paths crossing through it.
    std::vector<std::vector<int>> grid(_h, std::vector<int>(_w, 0));

    for (const Path &p : _paths)
    {
        SDL_SetRenderDrawColor(renderer, p.color.r, p.color.g, p.color.b, p.color.a);

        const int pathSize = p.points.size();

        for (int i = 0; i < pathSize - 1; i++)
        {
            const Vector2<int> &curr = p.points[i];
            const Vector2<int> &next = p.points[i + 1];

            const int dx = next.x - curr.x;
            const int dy = next.y - curr.y;

            if (dx == 0)
            {
                for (int y = curr.y; y < next.y; y++)
                {
                    grid[y][curr.x] += 1;

                    const SDL_Rect rect = {_origin.x + curr.x * _step, _origin.y + y * _step, _step, _step};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
            else if (dy == 0)
            {
                for (int x = curr.x; x < next.x; x++)
                {
                    grid[curr.y][x] += 1;

                    const SDL_Rect rect = {_origin.x + x * _step, _origin.y + curr.y * _step, _step, _step};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
            else if (abs(dx) == abs(dy))
            {
                const int stepX = dx / abs(dx);
                const int stepY = dy / abs(dy);

                for (int j = 0; j < abs(dx); j++)
                {
                    const int x = curr.x + (stepX * j);
                    const int y = curr.y + (stepY * j);

                    grid[y][x] += 1;

                    const SDL_Rect rect = {_origin.x + x * _step, _origin.y + y * _step, _step, _step};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
            else
            {
                // Error.
            }
        }

        // Count the last point in the path, which was previously skipped.
        if (pathSize > 1)
        {
            const Vector2<int> last = p.points[pathSize - 1];
            const int x = last.x;
            const int y = last.y;
            
            grid[y][x] += 1;

            const SDL_Rect rect = {_origin.x + x * _step, _origin.y + y * _step, _step, _step};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
    // Print the resulting grid.
    for (const auto &rows : grid)
    {
        for (const int v : rows)
        {
            std::cout << v << " ";
        }

        std::cout << std::endl;
    }
}
