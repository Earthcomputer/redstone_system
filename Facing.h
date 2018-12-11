//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_FACING_H
#define REDSTONE_SYSTEM_FACING_H

#include "BlockPos.h"

namespace Facing {
    enum Facing {
        DOWN, UP, NORTH, SOUTH, WEST, EAST, NONE // TODO: assuming same as Java edition
    };
    const Facing OPPOSITE_FACING[7] = {UP, DOWN, SOUTH, NORTH, EAST, WEST, NONE};
    const BlockPos DIRECTION[7] = {{0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}, {0, 0, 0}};
}

#endif //REDSTONE_SYSTEM_FACING_H
