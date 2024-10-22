#include "player_structure.hpp"

Player::PlayerStructureA* Player::GetPlayerStructureA() {
    const uintptr_t& followed_pointer {
        Ght::Internal::FollowPointerOffsets(Ght::Internal::GetModuleBaseAddress(L"libhl.dll") + 0x00048184, { 0x40C, 0x18, 0x78, 0x64 })
    };

    if(followed_pointer != NULL) {
        const uintptr_t& last_step { *reinterpret_cast<uintptr_t*>(followed_pointer) };

        if(Ght::Internal::IsMemoryAccessible(last_step)) {
            return reinterpret_cast<PlayerStructureA*>(last_step);
        }
    }

    return nullptr;
}

Player::PlayerStructureB* Player::GetPlayerStructureB() {
    const uintptr_t& followed_pointer {
        Ght::Internal::FollowPointerOffsets(Ght::Internal::GetModuleBaseAddress(L"libhl.dll") + 0x00048184, { 0x624, 0x8, 0x18, 0x5C })
    };

    if(followed_pointer != NULL) {
        const uintptr_t& last_step { *reinterpret_cast<uintptr_t*>(followed_pointer) };

        if(Ght::Internal::IsMemoryAccessible(last_step)) {
            return reinterpret_cast<PlayerStructureB*>(last_step);
        }
    }

    return nullptr;
}

std::pair<uint32_t, uint32_t> Player::GetPosition() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) return std::make_pair(player_struct->HorizontalPos, player_struct->VerticalPos);
    else return std::make_pair(NULL, NULL);
}

void Player::SetPosition(const std::pair<uint32_t, uint32_t>& position) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };

    if(player_struct) {
        player_struct->HorizontalPos = position.first;
        player_struct->VerticalPos = position.second;
    }
}

uint32_t Player::GetHorizontalPosition() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->HorizontalPos : NULL;
}

void Player::SetHorizontalPosition(const uint32_t& horizontal_position) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->HorizontalPos = horizontal_position;
}

uint32_t Player::GetVerticalPosition() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->VerticalPos : NULL;
}

void Player::SetVerticalPosition(const uint32_t& vertical_position) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->VerticalPos = vertical_position;
}

uint32_t Player::GetHealth() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->Health : NULL;
}

void Player::SetHealth(const uint32_t& health) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->Health = health;
}

uint32_t Player::GetMaxHealth() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->MaxHealth : NULL;
}

void Player::SetMaxHealth(const uint32_t& max_health) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->MaxHealth = max_health;
}

uint32_t Player::GetFlaskCharges() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->FlaskCharges : NULL;
}

void Player::SetFlaskCharges(const uint32_t& flask_charges) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->FlaskCharges = flask_charges;
}

uint32_t Player::GetCells() {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    return player_struct ? player_struct->Cells : NULL;
}

void Player::SetCells(const uint32_t& cells) {
    PlayerStructureA* player_struct { GetPlayerStructureA() };
    if(player_struct) player_struct->Cells = cells;
}

uint32_t Player::GetMoney() {
    PlayerStructureB* player_struct { GetPlayerStructureB() };
    return player_struct ? player_struct->Money : NULL;
}

void Player::SetMoney(const uint32_t& money) {
    PlayerStructureB* player_struct { GetPlayerStructureB() };
    if(player_struct) player_struct->Money = money;
}

Player::Player() {

}

Player::~Player() {

}

std::ostream& operator<<(std::ostream& stream, Player& player) {
    auto time_of_print { std::time(nullptr) };
    auto local_time_of_print { *std::localtime(&time_of_print) };

    stream << "Player Structure @ " << std::put_time(&local_time_of_print, "%Y-%m-%dT%H:%M:%S.%z%Z") << "\n";
    stream << std::string(30, '-') << "\n";
    stream << "Position: " << "H" << player.GetHorizontalPosition() << ", V" << player.GetVerticalPosition() << "\n";
    stream << "Health: " << player.GetHealth() << " / " << player.GetMaxHealth() << "\n";
    stream << "Cells: " << player.GetCells() << "\n";
    stream << "Money: " << player.GetMoney() << "\n";
    stream << "Flasks: " << player.GetFlaskCharges() << "\n";
    stream << std::string(30, '-') << "\n\n";

    return stream;
}
