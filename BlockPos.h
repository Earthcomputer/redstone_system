//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_BLOCKPOS_H
#define REDSTONE_SYSTEM_BLOCKPOS_H

#include <functional>

class BlockPos {
public:
    int x, y, z;
public:
    BlockPos() : x(0), y(0), z(0) {}
    BlockPos(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    explicit BlockPos(BlockPos *other) {
        this->x = other->x;
        this->y = other->y;
        this->z = other->z;
    }
    bool operator==(const BlockPos &other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator!=(const BlockPos &other) const noexcept {
        return !(*this == other);
    }
    BlockPos operator+(const BlockPos &pos) const noexcept {
        return {x + pos.x, y + pos.y, z + pos.z};
    }
    BlockPos operator-(const BlockPos &pos) const noexcept {
        return {x - pos.x, y - pos.y, z - pos.z};
    }
    BlockPos & operator=(const BlockPos &pos) noexcept = default;
};
namespace std {
    template<>
    struct hash<BlockPos> {
        size_t operator()(BlockPos const &pos) const noexcept {
            return static_cast<size_t>(pos.z + 981131 * pos.y + 8976890 * pos.x);
        }
    };
}

#endif //REDSTONE_SYSTEM_BLOCKPOS_H
