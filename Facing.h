//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_FACING_H
#define REDSTONE_SYSTEM_FACING_H

namespace Facing {
    enum Facing {
        DOWN, UP, NORTH, SOUTH, WEST, EAST, NONE // TODO: assuming same as Java edition
    };
    const Facing OPPOSTE_FACING[7] = {UP, DOWN, SOUTH, NORTH, EAST, WEST, NONE};
}

#endif //REDSTONE_SYSTEM_FACING_H
