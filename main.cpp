#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int BLOCK_SIZE = 50;
const int BLOCK_COUNT_X = 10;
const int BLOCK_COUNT_y = 10;
const float WALL_THICKNESS = BLOCK_SIZE * 0.02;

const int SCREEN_WIDTH = (BLOCK_COUNT_X-1)*WALL_THICKNESS + BLOCK_COUNT_X*BLOCK_SIZE;
const int SCREEN_HEIGHT = (BLOCK_COUNT_y-1)*WALL_THICKNESS + BLOCK_COUNT_y*BLOCK_SIZE;

const std::string TITLE = "MAZE"; 

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        window.display();
    }

    return 0;
}