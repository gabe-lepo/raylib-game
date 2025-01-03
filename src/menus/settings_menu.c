#include "settings_menu.h"
#include "shared_menu_actions.h"
#include "logging/log.h"

// Actions
void SetVsync(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_VSYNC_HINT} flag");
    SetWindowState(FLAG_VSYNC_HINT);
}
void SetFullscreen(void)
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
void SetResizeable(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_WINDOW_RESIZABLE} flag");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}
void SetBorderless(void)
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
void SetMSAA(void)
{
    LogMessage(LOG_INFO, "SETTINGS: {FLAG_MSAA_4X_HINT} flag");
    SetWindowState(FLAG_MSAA_4X_HINT);
}

// Objects
static MenuItem settingsMenuItems[] = {
    {"V-Sync", SetVsync},
    {"Fullscreen", SetFullscreen},
    {"Resizeable Window", SetResizeable},
    {"Borderless Window", SetBorderless},
    {"4X MSAA", SetMSAA},
    {"Back", BackUpMenu},
};

static Menu settingsMenu = {
    "Settings",
    settingsMenuItems,
    sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]),
    0,
    BLACK,
};

// Getter func
Menu *GetSettingsMenu(void)
{
    return &settingsMenu;
}