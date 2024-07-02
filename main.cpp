#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<math.h>
const int BLOCK_SIZE = 25;
const int BLOCK_COUNT_X = 10;
const int BLOCK_COUNT_y = 10;
const float WALL_THICKNESS = BLOCK_SIZE * 0.02;

const int SCREEN_WIDTH = (BLOCK_COUNT_X-1)*WALL_THICKNESS + BLOCK_COUNT_X*BLOCK_SIZE;
const int SCREEN_HEIGHT = (BLOCK_COUNT_y-1)*WALL_THICKNESS + BLOCK_COUNT_y*BLOCK_SIZE;

const std::string TITLE = "MAZE"; 

// enum class Wall {
//     CELL_TOP,
//     CELL_LEFT,
//     CELL_BOTTOM,
//     CELL_RIGHT,
// };


class Cell { // Corrected the class name to start with uppercase 'C'
private:
    int x;
    int y;
    int cellWidth;
    bool isLeftWall;
    bool isBottomWall;
public:
    bool isVisited;
    Cell(){
        x = 0;
        y = 0;
        cellWidth = 0;
        isLeftWall = true;
        isBottomWall = true;
        isVisited = false;

    }
    Cell(int x, int y,int width){
        this->x = x;
        this->y = y;
        this->cellWidth = width;
        isLeftWall = true;
        isBottomWall = true;
        isVisited = false;

    }
    void drawCell(sf::RenderWindow& window){
        //leftwall
        if(isVisited){
            sf::RectangleShape cellColor(sf::Vector2f(cellWidth-1,cellWidth-1));
            cellColor.setPosition(sf::Vector2f(x,y));
            cellColor.setFillColor(sf::Color::Blue);
            window.draw(cellColor);
        }
        if(isLeftWall){
            sf::Vertex leftWall[] =
            {
                sf::Vertex(sf::Vector2f(x+cellWidth, y)),
                sf::Vertex(sf::Vector2f(x+cellWidth, y+cellWidth))
            };
            window.draw(leftWall, 2, sf::Lines);
        }
        if(isBottomWall){
            sf::Vertex bottomWall[] =
            {
                sf::Vertex(sf::Vector2f(x, y+cellWidth)),
                sf::Vertex(sf::Vector2f(x+cellWidth, y+cellWidth))
            };
            window.draw(bottomWall, 2, sf::Lines);
        }
        
    }
};
Cell cell[BLOCK_COUNT_X][BLOCK_COUNT_y];
void initGrid(){
     for(int i = 0;i<BLOCK_COUNT_X;i++){

            for(int j = 0;j<BLOCK_COUNT_y;j++){

                cell[i][j]= Cell(i*BLOCK_SIZE,j*BLOCK_SIZE,BLOCK_SIZE);

            }
     }
}
void drawGrid(sf::RenderWindow& window){
    for(int i = 0;i<BLOCK_COUNT_X;i++){

            for(int j = 0;j<BLOCK_COUNT_y;j++){

                cell[i][j].drawCell(window);

            }
        }        
}
    
int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE);
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape rect(sf::Vector2f(100,100));
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(sf::Vector2f(50,50));
    initGrid();
    // Cell cell1(100,100,50);

   
    // cell[1][1].isVisited = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        //     rect.move(-0.1f,0.0f);
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        //     rect.move(0.0f,-0.1f);
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        //     rect.move(0.0f,0.1f);
        // }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        //     rect.move(0.1f,0.0f);
        // }
        // if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //     int mouse_i = static_cast<int>(floor(mousePosition.x/BLOCK_SIZE));
        //     int mouse_j = static_cast<int>(floor(mousePosition.y/BLOCK_SIZE));
        //     // rect.setPosition(sf::Vector2f((float)mousePosition.x,(float)mousePosition.y));
        //     cell[mouse_i][mouse_j].isVisited = true;
        // }
        // if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //     int mouse_i = static_cast<int>(floor(mousePosition.x/BLOCK_SIZE));
        //     int mouse_j = static_cast<int>(floor(mousePosition.y/BLOCK_SIZE));
        //     // rect.setPosition(sf::Vector2f((float)mousePosition.x,(float)mousePosition.y));
        //     cell[mouse_i][mouse_j].isVisited = false;
        // }
        window.clear(sf::Color::Black);
        drawGrid(window);
        window.display();
    }

    return 0;
}