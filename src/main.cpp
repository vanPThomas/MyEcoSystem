#include "UIManager.h"
#include "Environment.h"
#include <iostream>

int main()
{
    Environment world(1000, 1000);
    UIManager ui(world);
    
    while(ui.render()) {}
    return 0;
}