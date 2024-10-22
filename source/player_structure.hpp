#ifndef PLAYER_STRUCTURE_H
#define PLAYER_STRUCTURE_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <vector>
#include <ctime>

#include <libght.hpp>

class Player {
public:
    // libhl.dll + 0x00048184 + 0x40C, 0x18, 0x78, 0x64
    struct PlayerStructureA {
        char padding_1[0x0054];
        uint32_t HorizontalPos; // 0x0054
        uint32_t VerticalPos;   // 0x0058

        char padding_2[0x00A0];
        uint32_t Health;        // 0x00FC
        uint32_t MaxHealth;     // 0x0100

        char padidng_3[0x01FC];
        uint32_t FlaskCharges;  // 0x0300

        char padding_4[0x0034];
        uint32_t Cells;         // 0x0338
    };

    // libhl.dll + 0x00048184 + 0x624, 0x8, 0x18, 0x5C
    struct PlayerStructureB {
        char padding_1[0x002C];
        uint32_t Money;
    };

    PlayerStructureA* GetPlayerStructureA();
    PlayerStructureB* GetPlayerStructureB();

    std::pair<uint32_t, uint32_t> GetPosition();
    void SetPosition(const std::pair<uint32_t, uint32_t>& position);

    uint32_t GetHorizontalPosition();
    void SetHorizontalPosition(const uint32_t& horizontal_position);

    uint32_t GetVerticalPosition();
    void SetVerticalPosition(const uint32_t& vertical_position);

    uint32_t GetHealth();
    void SetHealth(const uint32_t& health);

    uint32_t GetMaxHealth();
    void SetMaxHealth(const uint32_t& max_health);

    uint32_t GetFlaskCharges();
    void SetFlaskCharges(const uint32_t& flask_charges);

    uint32_t GetCells();
    void SetCells(const uint32_t& cells);

    uint32_t GetMoney();
    void SetMoney(const uint32_t& money);

    Player();
    ~Player();
};

extern std::ostream& operator<<(std::ostream& stream, Player& player);

#endif // PLAYER_STRUCTURE_H

