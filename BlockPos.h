//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_BLOCKPOS_H
#define REDSTONE_SYSTEM_BLOCKPOS_H

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
    bool operator==(BlockPos other) {
        return x == other.x && y == other.y && z == other.z;
    }
};
BlockPos operator+(const BlockPos &a, const BlockPos &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
BlockPos operator-(const BlockPos &a, const BlockPos &b) {
    return {b.x - a.x, b.y - a.y, b.z - a.z};
}

#endif //REDSTONE_SYSTEM_BLOCKPOS_H
