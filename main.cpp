#include "Player.h"
#include "Skeleton.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 1920,1080 }), "RPG Game", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    sf::Clock clock;

    Player player;
    Skeleton skeleton;

    player.Initialize();
    skeleton.Initialize();
    player.Load();
    skeleton.Load();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            player.HandleEvent(event, skeleton,window,clock);
        }
        skeleton.Update();
        player.Update(skeleton,window);
        window.clear();
        skeleton.Draw(window);
        player.Draw(window,clock);
        window.display();
    }

    return 0;
}