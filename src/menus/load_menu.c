#include "load_menu.h"
#include "shared_menu_actions.h"

// Actions
void TempLoad(void)
{
    // TODO
}

// Objects
static MenuItem loadMenuItems[] = {
    {"Some load options", TempLoad},
    {"Back", BackUpMenu},
};

static Menu loadMenu = {
    "Load Game",
    loadMenuItems,
    sizeof(loadMenuItems) / sizeof(loadMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *GetLoadMenu(void)
{
    return &loadMenu;
}