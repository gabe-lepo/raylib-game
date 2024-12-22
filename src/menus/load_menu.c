#include "load_menu.h"
#include "shared_menu_actions.h"

// Actions
void tempLoad(void)
{
    // TODO
}

// Objects
static MenuItem loadMenuItems[] = {
    {"Some settings", tempLoad},
    {"Back", backUpMenu},
};

static Menu loadMenu = {
    "Box Man",
    loadMenuItems,
    sizeof(loadMenuItems) / sizeof(loadMenuItems[0]),
    0,
    0,
    BLACK,
};

// Getter func
Menu *getLoadMenu(void)
{
    return &loadMenu;
}