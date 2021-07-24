#include "Main.h"
#include "../Util/GameUtil.h"
///#include ""

int main() {
    GameUtil* l;
    uint32_t process_id = l->getGameProcessId();
    uintptr_t gameId = l->getGameModule(process_id);
    HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);
    float hitboxWidthVal;
    float hitboxHeightVal;
    std::string prompt;
    bool to_exit = false;

    while (!to_exit) {
        HWND gameWindow = FindWindow(NULL, L"Minecraft");
        if (!gameWindow) {
            system("color 4");
            std::cout << "You must have Minecraft open in order to use this game modification.";
            return -1;
        }
        else {
            std::cout << "Game window found! Scanning pointers...\n";
        }

        uintptr_t __localPlayerBaseAddress = gameId + 0x041457C8;
        uintptr_t __localPlayer = l->findAddressFromPointer(procHandle, __localPlayerBaseAddress, {
                0x8,
                0x20,
                0xC8,
                0x378,
                0x58,
                0x0,
                0x4EC //this offset was used in the actual pointer scan
            });

        std::cout << "Pointers scanned.\n\n\n";
        std::cout << "Enter hitbox width value: ";
        std::cin >> hitboxWidthVal;
        WriteProcessMemory(procHandle, (unsigned int*)__localPlayer, &hitboxWidthVal, sizeof(hitboxWidthVal), nullptr);
        std::cout << "Set entity hitboxes (width) to " << hitboxWidthVal << "!\nYou may now close this window.";
    
        system("cls");//sys-call to flush the terminal
    }
    return 0;
}