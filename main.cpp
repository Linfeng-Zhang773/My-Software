#include "includes/Application/Application.h"
#include "includes/DropdownMenu/DropdownMenu.h"
#include <SFML/Graphics.hpp>

int main()
{

    DropdownMenu menu;
    Application::addComponent(menu);
    // menu.setBoxPosition({100, 50}); // be able to change position

    menu.addItem("Apple");
    menu.addItem("Banana");
    menu.addItem("Car");
    menu.addItem("Dog");
    menu.addItem("Elf");
    // menu.changeSize({300, 30}); // be able to resize
    Application::run();

    return 0;
}