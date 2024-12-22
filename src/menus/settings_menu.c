#include "settings_menu.h"

// Actions
void backUpMenu(void)
{
    // TODO
}

// Objects
static MenuItem settingsMenuItems[] = {
    {"Back", backUpMenu},
};

static Menu settingsMenu = {
    "Box Man",
    settingsMenuItems,
    sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]),
    0,
    0,
    BLACK,
};

// Getter func
Menu *getSettingsMenu(void)
{
    return &settingsMenu;
}