#include "confirm_menu.h"
#include "shared_menu_actions.h"

void yes(void) {}
void no(void) {}

static MenuItem confirmMenuItems[] = {
    {"Yes", yes},
    {"No", no},
};

static Menu confirmMenu = {
    "Settings",
    confirmMenuItems,
    sizeof(confirmMenuItems) / sizeof(confirmMenuItems[0]),
    0,
    BLACK,
};

Menu *GetConfirmMenu(void)
{
    return &confirmMenu;
}