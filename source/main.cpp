#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Get full screen resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Doggo Shelter", sf::Style::Fullscreen);

    sf::Font font;
    if (!font.loadFromFile("assets/Jersey15-Regular.ttf")) {
        std::cerr << "Couldn't load font\n";
        return -1;
    }

    const int menuSize = 2;
    sf::Text title("Doggo Shelter", font, 70);
    sf::Text menu[menuSize];
    std::string options[menuSize] = { "NEW GAME", "EXIT" };
    int selectedIndex = 0;

    // Center the title
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(desktop.width / 2.0f, 100);
    title.setFillColor(sf::Color::White);

    // Setup menu options
    for (int i = 0; i < menuSize; ++i) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(48);
        sf::FloatRect bounds = menu[i].getLocalBounds();
        menu[i].setOrigin(bounds.width / 2, bounds.height / 2);
        menu[i].setPosition(desktop.width / 2.0f, 250 + i * 80);
        menu[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Highlight if mouse is over
        for (int i = 0; i < menuSize; ++i) {
            if (menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                selectedIndex = i;
            }
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Up) {
                    selectedIndex = (selectedIndex - 1 + menuSize) % menuSize;
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedIndex = (selectedIndex + 1) % menuSize;
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) {
                        std::cout << "New Game\n";
                    } else if (selectedIndex == 1) {
                        window.close();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < menuSize; ++i) {
                    if (menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        if (i == 0) {
                            std::cout << "New Game (clicked)\n";
                            // gameplay here
                        } else if (i == 1) {
                            window.close();
                        }
                    }
                }
            }
        }

        // Update colors
        for (int i = 0; i < menuSize; ++i) {
            menu[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        for (const auto& item : menu)
            window.draw(item);
        window.display();
    }

    return 0;
}
