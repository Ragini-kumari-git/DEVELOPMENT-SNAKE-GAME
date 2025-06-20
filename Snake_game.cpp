#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace sf;
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int BLOCK_SIZE = 20;

struct Point {
    int x, y;
};

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Snake Game");
    window.setFramerateLimit(10);

    // Initialize snake and food
    vector<Point> snake;
    snake.push_back({WIDTH / 2, HEIGHT / 2});
    Point food = {rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE};

    // Initialize direction
    int dx = 1, dy = 0;

    // Game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Change direction
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up && dy != 1) {
                    dx = 0; dy = -1;
                } else if (event.key.code == Keyboard::Down && dy != -1) {
                    dx = 0; dy = 1;
                } else if (event.key.code == Keyboard::Left && dx != 1) {
                    dx = -1; dy = 0;
                } else if (event.key.code == Keyboard::Right && dx != -1) {
                    dx = 1; dy = 0;
                }
            }
        }

        // Move snake
        Point newHead = {snake[0].x + dx * BLOCK_SIZE, snake[0].y + dy * BLOCK_SIZE};
        snake.insert(snake.begin(), newHead);

        // Check collision with food
        if (snake[0].x == food.x && snake[0].y == food.y) {
            food = {rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE};
        } else {
            snake.pop_back();
        }

        // Check collision with wall or self
        if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
            window.close();
        }
        for (int i = 1; i < snake.size(); i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                window.close();
            }
        }

        // Draw everything
        window.clear();
        for (Point point : snake) {
            RectangleShape rect(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rect.setFillColor(Color::Green);
            rect.setPosition(point.x, point.y);
            window.draw(rect);
        }
        RectangleShape foodRect(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        foodRect.setFillColor(Color::Red);
        foodRect.setPosition(food.x, food.y);
        window.draw(foodRect);
        window.display();
    }

    return 0;
}
