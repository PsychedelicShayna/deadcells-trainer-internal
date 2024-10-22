#include "vmnoclip.hpp"

void VMNoclip::SyncToPlayerPosition() {
    lockedVerticalPosition = playerStruct.GetVerticalPosition();
    lockedHorizontalPosition = playerStruct.GetHorizontalPosition();
}

void VMNoclip::NoclipTick() {
    // W
    if(GetAsyncKeyState(0x57) & 0x8000) {
        lockedVerticalPosition -= 1;
    }

    // S
    if(GetAsyncKeyState(0x53) & 0x8000) {
        lockedVerticalPosition += 1;
    }

    // A
    if(GetAsyncKeyState(0x41) & 0x8000) {
        lockedHorizontalPosition -= 1;
    }

    //  D
    if(GetAsyncKeyState(0x44) & 0x8000) {
        lockedHorizontalPosition += 1;
    }

    playerStruct.SetVerticalPosition(lockedVerticalPosition);
    playerStruct.SetHorizontalPosition(lockedHorizontalPosition);
}

VMNoclip::VMNoclip()
    :
      lockedHorizontalPosition { 0 },
      lockedVerticalPosition   { 0 }
{

}
