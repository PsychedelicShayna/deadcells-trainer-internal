#ifndef VMNOCLIP_HPP
#define VMNOCLIP_HPP

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>

#include "player_structure.hpp"

class VMNoclip {
protected:
    Player playerStruct;

    uint32_t lockedVerticalPosition;
    uint32_t lockedHorizontalPosition;

public:
    void SyncToPlayerPosition();
    void NoclipTick();
    VMNoclip();
};

#endif // VMNOCLIP_HPP
