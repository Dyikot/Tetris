#include "Menu.h"

int Menu::CalculateButtonYPosition(const int order)
{
    return DefaultButtonYPosition + order * ButtonSpacing;
}
