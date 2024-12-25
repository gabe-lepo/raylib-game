#include "settings_menu.h"
#include "shared_menu_actions.h"
#include "logging/log.h"

// Actions
void setVsync(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_VSYNC_HINT} flag");
    SetWindowState(FLAG_VSYNC_HINT);
}
void setFullscreen(void)
{
    ToggleFullscreen();

    if (IsWindowState(FLAG_FULLSCREEN_MODE))
    {
        LogMessage(LOG_INFO, "SETTINGS: Fullscreen on");
    }
    else
    {
        LogMessage(LOG_INFO, "SETTINGS: Fullscreen off");
    }
}
void setResizeable(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_WINDOW_RESIZABLE} flag");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}
void setBorderless(void)
{
    ToggleBorderlessWindowed();

    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
    {
        LogMessage(LOG_INFO, "SETTINGS: Borderless window on");
    }
    else
    {
        LogMessage(LOG_INFO, "SETTINGS: Borderless window off");
    }
}
void setMSAA(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_MSAA_4X_HINT} flag");
    SetWindowState(FLAG_MSAA_4X_HINT);
}

// Objects
static MenuItem settingsMenuItems[] = {
    {"V-Sync", setVsync},
    {"Fullscreen", setFullscreen},
    {"Resizeable Window", setResizeable},
    {"Borderless Window", setBorderless},
    {"4X MSAA", setMSAA},
    {"Back", backUpMenu},
};

static Menu settingsMenu = {
    "Settings",
    settingsMenuItems,
    sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *getSettingsMenu(void)
{
    return &settingsMenu;
}