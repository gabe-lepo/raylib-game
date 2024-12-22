#include "settings_menu.h"
#include "shared_menu_actions.h"

// Actions
void tempSettings(void)
{
    // TODO
}

// Objects
static MenuItem settingsMenuItems[] = {
    {"Some settings", tempSettings},
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