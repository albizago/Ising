#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Thread.hpp>
#include "spins.hpp"
#include "math.hpp"
#include <array>
#include <algorithm>
#include <chrono>

int main()
{
    std::cout << "Inserire valore del campo magnetico esterno: ";
    double field{0.};
    std::cin >> field;
    std::string f_str = std::to_string(field);
    std::cout << "Inserire valore della temperatura : ";
    double temp{0.};
    std::cin >> temp;
    while (temp < 0)
    {
        std::cout
            << "Input invalido. Immetti nuovamente la temperatura: ";
        std::cin >> temp;
    }
    std::string t_str = std::to_string(temp);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(980, 780), "Ising Simulator");
    window.setFramerateLimit(50);
    phys::Board system;
    sf::VertexArray slots(sf::Points, 250000);
    std::transform(system.spins().begin(), system.spins().end() - 1, &slots[0], &slots[0], [](phys::Spin sp, sf::Vertex &rec)
                   {
                sf::Vector2f vec(50 + 1.36f * (sp.get_x() - 1), 50 + 1.36f * (sp.get_y() - 1));
                rec.position = vec;
            return rec; });
    sf::Font font;
    if (!font.loadFromFile("Inter-Medium.otf"))
    {
        return 0;
    }
    sf::Text mag_display;
    mag_display.setFillColor(sf::Color::Blue);
    mag_display.setFont(font);
    mag_display.setPosition(65, 15);
    mag_display.setCharacterSize(15);
    auto init = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> step;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        mag_display.setString("System magnetization : " + std::to_string(system.magnetization()) + " | External field: " + f_str + " | Temperature: " + t_str + " | Draw time: " + std::to_string(step.count()));

        window.clear(sf::Color::White);

        std::transform(system.spins().begin(), system.spins().end() - 1, &slots[0], &slots[0], [](phys::Spin sp, sf::Vertex &rec)
                       {
            switch (sp.get_state())
            {
            case 1 :
                rec.color = sf::Color::White;
                break;
            case -1 :
                rec.color = sf::Color::Black;
                break;
            default:
                break;
            }
            return rec; });
        init = std::chrono::steady_clock::now();
        window.draw(slots);
        step = std::chrono::steady_clock::now() - init;
        window.draw(mag_display);
        window.display();
        math::evolution(system, field, temp, 0, 250000);
    }
    return EXIT_SUCCESS;
}