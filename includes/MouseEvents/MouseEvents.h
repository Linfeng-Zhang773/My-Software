#ifndef MOSUEEVENTS_H
#define MOUSEEVENTS_H
#include <SFML/Graphics.hpp>
template <class T>
class MouseEvents
{

public:
    // returns true if the mouse clicks on the object
    static bool mouseClicked(T& object, sf::RenderWindow& window);

    // returns true if the mouse clicks anywhere in the window
    static bool mouseClicked(sf::RenderWindow& window, sf::Event event);

    // // returns true if the mouse has been double clicked
    // static bool mouseDoubleClicked();

    // // returns true if the mouse has been triple clicked
    // static bool mouseTripleClicked();

    // returns if the object has been clicked and the mouse has dragged over the object
    static bool draggedOver(T& object, sf::RenderWindow& window, sf::Event event);

    // returns true if the mouse is hovered over the object
    static bool hovered(T& object, sf::RenderWindow& window);

private:
    // this is what I used to determine if a double click or triple click occurred
    // you don't have to use this if you don't want to
    static sf::Clock clock;
    static int clicks;
    static void countClicks(sf::Event event);
};

template <typename T>
void MouseEvents<T>::countClicks(sf::Event event)
{
    MouseEvents<T>::clicks++;
}
template <typename T>
bool MouseEvents<T>::mouseClicked(T& object, sf::RenderWindow& window)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return false;
    }

    sf::Vector2i mouseCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y});

    sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

    float mouseX = realCoords.x;
    float mouseY = realCoords.y;

    int objX = object.getBox().getPosition().x;
    int objY = object.getBox().getPosition().y;

    int Width = object.getBox().getPosition().x + object.getBox().getGlobalBounds().width;
    int Height = object.getBox().getPosition().y + object.getBox().getGlobalBounds().height;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseX < Width && mouseX > objX && mouseY < Height && mouseY > objY)
    {
        return true;
    }
    return false;
}

template <typename T>
// returns true if the mouse clicks anywhere in the window
bool MouseEvents<T>::mouseClicked(sf::RenderWindow& window, sf::Event event)
{
    if (!(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
    {
        return false;
    }
    sf::Vector2i mouseCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y});

    sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

    float mouseX = realCoords.x;
    float mouseY = realCoords.y;
    if (mouseX < 0 || mouseX > 720)
    {
        return false;
    }
    if (mouseY < 0 || mouseY > 420)
    {
        return false;
    }
    return true;
}

// template <typename T>
// // returns true if the mouse has been double clicked
// bool MouseEvents<T>::mouseDoubleClicked()
// {

// }

// template <typename T>
// // returns true if the mouse has been triple clicked
// bool MouseEvents<T>::mouseTripleClicked()
// {

// }

template <typename T>
bool MouseEvents<T>::draggedOver(T& object, sf::RenderWindow& window, sf::Event event)
{
    static bool isDragging = false;
    static sf::Vector2i lastMousePosition;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            // Left mouse button pressed
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect objectBounds = object.getGlobalBounds();

            if (objectBounds.contains(static_cast<sf::Vector2f>(mousePosition)))
            {
                isDragging = true;
                lastMousePosition = mousePosition;
            }
        }
    }

    if (event.type == sf::Event::MouseMoved && isDragging)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2i offset = mousePosition - lastMousePosition;
        lastMousePosition = mousePosition;

        sf::Vector2f newPosition = object.getPosition() + static_cast<sf::Vector2f>(offset);

        // Update the object's position
        object.setPosition(newPosition);

        return true;
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        isDragging = false;
    }

    return false;
}
template <typename T>
// returns true if the mouse is hovered over the object
bool MouseEvents<T>::hovered(T& object, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return false;
    }

    sf::Vector2i mouseCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y});

    sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

    float mouseX = realCoords.x;
    float mouseY = realCoords.y;

    int objX = object.getBox().getPosition().x;
    int objY = object.getBox().getPosition().y;

    int Width = object.getBox().getPosition().x + object.getBox().getGlobalBounds().width;
    int Height = object.getBox().getPosition().y + object.getBox().getGlobalBounds().height;

    if (mouseX < Width && mouseX > objX && mouseY < Height && mouseY > objY)
    {
        return true;
    }
    return false;
}

#endif