#include <windows.h>
#include <iostream>
#include <stdlib.h>

int invertScreen()
{
    HDC desktop; // vars to store stuff
    HWND desktopHandle;
    RECT screenSize;
    screenSize.left = 0;
    screenSize.top = 0;
    screenSize.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);  // width of screen 1 (i think)
    screenSize.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN); // height of screen 1 (again i think)
    desktopHandle = GetDesktopWindow();                       // gets the screen handle
    desktop = GetDC(desktopHandle);                           // gets the device context aka the pixels of the screen
    InvertRect(desktop, &screenSize);                         // inverts the screen
    return ReleaseDC(desktopHandle, desktop);                 // returns 1 if releasing the dc worked
}
int main(int argc, char **argv)
{
    const char defaultKey = 'Y';
    char key;
    if (argc > 1)
        key = *argv[1];
    if (argc == 1)                                                                                                                                                                                                                                                                                // command name
        std::cout << "You have chosen no key for inverting the screen.\nIt will default to '" << defaultKey << "'.\nTo pass a different key, run this program in the command prompt\nand add a letter after it.\ne.g. 'InvertScreen.exe H' for the 'H' key to invert your screen." << std::flush; // std::flush so we can clear  the console later
    else if (argc > 1)
        std::cout << "You have chosen '" << key << "' as your invert screen key.\nNow when you press '" << key << "', the screen will invert.\nIf it is already inverted, this will revert it back to the original colours.\nIf the key doesn't work, it may be an invalid key." << std::flush; // "invalid key" aka key that doesnt work with GetKeyState
    int keyDownY = 0;
    int keyEverPressed = 0;
    while (true)
    {
        if (key != 0)
        {
            if ((GetKeyState(key) & 0x8000) && keyDownY != 1) // the actual key press part i found on stack overflow only part i yoinked
            {
                keyDownY = 1;
                invertScreen();
                if (keyEverPressed == 0)
                {
                    keyEverPressed = 1;
                    system("CLS"); // clears the terminal
                }
            }
            else if (!(GetKeyState(key) & 0x8000))
            {
                keyDownY = 0;
            }
        }
        else
        {
            if ((GetKeyState('Y') & 0x8000) && keyDownY != 1)
            {
                keyDownY = 1;
                invertScreen();
                if (keyEverPressed == 0)
                {
                    keyEverPressed = 1;
                    system("CLS"); // clears the terminal
                }
            }
            else if (!(GetKeyState('Y') & 0x8000))
            {
                keyDownY = 0;
            }
        }
    }
}
