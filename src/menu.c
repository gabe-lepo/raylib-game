#include "menu.h"

const char *startMenuItems[] = {
    "Start",
    "Load Game",
    "Settings",
    "Close Game",
};

const char *pauseMenuItems[] = {
    "Resume",
    "Save",
    "Load",
    "Settings",
    "Exit",
};

const char *settingsMenuItems[] = {
    "Back",
};

// Menu titles
const char startTitle[] = "Box Man";
const char pauseTitle[] = "Pause";
const char settingsTitle[] = "Settings";

// Is the menu active?
static int startMenuActive;
static int pauseMenuActive;
static int settingsMenuActive;

// Menu item selection iterator
int selectedStartMenuItem;
int selectedPauseMenuItem;
int selectedSettingsMenuItem;

// Basic lengths of menus for selection wrapping
int lengthStartMenuItems;
int lengthPauseMenuItems;
int lengthSettingsMenuItems;

// Last menu active for Back function
static int lastMenuActive;

void ResetMenuSelections(void)
{
   selectedStartMenuItem = 0;
   selectedPauseMenuItem = 0;
   selectedSettingsMenuItem = 0;
}

void InitMenus(void)
{
   startMenuActive = 1;
   lastMenuActive = START_MENU;
   pauseMenuActive = 0;
   settingsMenuActive = 0;

   ResetMenuSelections();

   lengthStartMenuItems = sizeof(startMenuItems) / sizeof(startMenuItems[0]);
   lengthPauseMenuItems = sizeof(pauseMenuItems) / sizeof(pauseMenuItems[0]);
   lengthSettingsMenuItems = sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]);
}

void ToggleMenu(int menu)
{
   if (menu == START_MENU)
   {
      if (startMenuActive)
      {
         startMenuActive = 0;
         lastMenuActive = START_MENU;
      }
      else
      {
         startMenuActive = 1;
      }
   }
   else if (menu == PAUSE_MENU)
   {
      if (pauseMenuActive)
      {
         pauseMenuActive = 0;
         lastMenuActive = PAUSE_MENU;
      }
      else
      {
         pauseMenuActive = 1;
      }
   }
   else if (menu == SETTINGS_MENU)
   {
      if (settingsMenuActive)
      {
         settingsMenuActive = 0;
      }
      else
      {
         settingsMenuActive = 1;
      }
   }
   else
   {
      LogMessage(LOG_WARNING, "Invalid menu type.");
   }
}

void UpdateStartMenu(void)
{
   // Item selection
   if (IsKeyPressed(KEY_DOWN))
   {
      selectedStartMenuItem++;
      if (selectedStartMenuItem > lengthStartMenuItems - 1)
      {
         selectedStartMenuItem = 0;
      }
   }

   if (IsKeyPressed(KEY_UP))
   {
      selectedStartMenuItem--;
      if (selectedStartMenuItem < 0)
      {
         selectedStartMenuItem = lengthStartMenuItems - 1;
      }
   }

   // Selection handling
   if (IsKeyPressed(KEY_ENTER))
   {
      if (selectedStartMenuItem == 0)
      {
         // New game
         ToggleMenu(START_MENU);
      }
      else if (selectedStartMenuItem == 1)
      {
         // Load Game
      }
      else if (selectedStartMenuItem == 2)
      {
         // Settings
         ToggleMenu(START_MENU);
         ToggleMenu(SETTINGS_MENU);
      }
      else if (selectedStartMenuItem == 3)
      {
         // Close game
      }
   }
}

void UpdatePauseMenu(void)
{
   // Item selection
   if (IsKeyPressed(KEY_DOWN))
   {
      selectedPauseMenuItem++;
      if (selectedPauseMenuItem > lengthPauseMenuItems - 1)
      {
         selectedPauseMenuItem = 0;
      }
   }

   if (IsKeyPressed(KEY_UP))
   {
      selectedPauseMenuItem--;
      if (selectedPauseMenuItem < 0)
      {
         selectedPauseMenuItem = lengthPauseMenuItems - 1;
      }
   }

   // Selection handling
   if (IsKeyPressed(KEY_ENTER))
   {
      if (selectedPauseMenuItem == 0)
      {
         // Resume
         ToggleMenu(PAUSE_MENU);
      }
      else if (selectedPauseMenuItem == 1)
      {
         // Save
      }
      else if (selectedPauseMenuItem == 2)
      {
         // Load
      }
      else if (selectedPauseMenuItem == 3)
      {
         // Settings
         ToggleMenu(PAUSE_MENU);
         ToggleMenu(SETTINGS_MENU);
      }
      else if (selectedPauseMenuItem == 4)
      {
         // Exit to main menu
         ToggleMenu(PAUSE_MENU);
         ResetMenuSelections();
         ToggleMenu(START_MENU);
      }
   }
}

void UpdateSettingsMenu(void)
{
   // Item selection
   if (IsKeyPressed(KEY_DOWN))
   {
      selectedSettingsMenuItem++;
      if (selectedSettingsMenuItem > lengthSettingsMenuItems - 1)
      {
         selectedSettingsMenuItem = 0;
      }
   }

   if (IsKeyPressed(KEY_UP))
   {
      selectedSettingsMenuItem--;
      if (selectedSettingsMenuItem < 0)
      {
         selectedSettingsMenuItem = lengthSettingsMenuItems - 1;
      }
   }

   // Selection handling
   if (IsKeyPressed(KEY_ENTER))
   {
      if (selectedSettingsMenuItem == 0)
      {
         ToggleMenu(SETTINGS_MENU);

         if (lastMenuActive == START_MENU)
         {
            ToggleMenu(START_MENU);
         }
         if (lastMenuActive == PAUSE_MENU)
         {
            ToggleMenu(PAUSE_MENU);
         }
      }
   }
}

void DrawMenus(void)
{
   if (startMenuActive)
   {
      // Background
      DrawRectangle(
          0,
          0,
          SCREEN_WIDTH,
          SCREEN_HEIGHT,
          BLACK);

      // Starting positions
      int menuItemPosY = SCREEN_HEIGHT / 2 - 60;
      int menuItemPosX = SCREEN_WIDTH / 2 - MeasureText(startTitle, 40) / 2;

      // Title
      DrawText(startTitle, menuItemPosX, menuItemPosY, 40, RAYWHITE);
      menuItemPosY += 60;

      // settings
      for (int i = 0; i < lengthStartMenuItems; i++)
      {
         DrawText(startMenuItems[i], SCREEN_WIDTH / 2 - MeasureText(startMenuItems[i], 20) / 2, menuItemPosY, 20, (selectedStartMenuItem == i) ? YELLOW : WHITE);
         menuItemPosY += 40;
      }
   }

   if (pauseMenuActive)
   {
      // Background
      DrawRectangle(
          0,
          0,
          SCREEN_WIDTH,
          SCREEN_HEIGHT,
          BLACK);

      // Starting positions
      int menuItemPosY = SCREEN_HEIGHT / 2 - 60;
      int menuItemPosX = SCREEN_WIDTH / 2 - MeasureText(pauseTitle, 40) / 2;

      // Title
      DrawText(pauseTitle, menuItemPosX, menuItemPosY, 40, RAYWHITE);
      menuItemPosY += 60;

      // settings
      for (int i = 0; i < lengthPauseMenuItems; i++)
      {
         DrawText(pauseMenuItems[i], SCREEN_WIDTH / 2 - MeasureText(pauseMenuItems[i], 20) / 2, menuItemPosY, 20, (selectedPauseMenuItem == i) ? YELLOW : WHITE);
         menuItemPosY += 40;
      }
   }

   if (settingsMenuActive)
   {
      // Background
      DrawRectangle(
          0,
          0,
          SCREEN_WIDTH,
          SCREEN_HEIGHT,
          BLACK);

      // Starting positions
      int menuItemPosY = SCREEN_HEIGHT / 2 - 60;
      int menuItemPosX = SCREEN_WIDTH / 2 - MeasureText(settingsTitle, 40) / 2;

      // Title
      DrawText(settingsTitle, menuItemPosX, menuItemPosY, 40, RAYWHITE);
      menuItemPosY += 60;

      // settings
      for (int i = 0; i < lengthSettingsMenuItems; i++)
      {
         DrawText(settingsMenuItems[i], SCREEN_WIDTH / 2 - MeasureText(settingsMenuItems[i], 20) / 2, menuItemPosY, 20, (selectedSettingsMenuItem == i) ? YELLOW : WHITE);
         menuItemPosY += 40;
      }
   }
}

int isMenuActive(int menu)
{
   if (menu == START_MENU)
   {
      return startMenuActive;
   }
   else if (menu == PAUSE_MENU)
   {
      return pauseMenuActive;
   }
   else if (menu == SETTINGS_MENU)
   {
      return settingsMenuActive;
   }
   else
   {
      LogMessage(LOG_WARNING, "Invalid menu type.");
      return -1;
   }
}