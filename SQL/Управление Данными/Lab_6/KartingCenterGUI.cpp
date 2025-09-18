#include <SFML/Graphics.hpp>
#include "DatabaseManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 700), "Karting Center");

    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase("postgres", "your_username", "your_password")) {
        return -1;
    }

    dbManager.createUsersTable();
    dbManager.addInitialUsers();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // TODO: Добавить кнопки для входа и других функций

        window.display();
    }

    return 0;
}