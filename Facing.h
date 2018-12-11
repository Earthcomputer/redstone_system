//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_FACING_H
#define REDSTONE_SYSTEM_FACING_H

namespace Facing {
    enum Facing {
        DOWN, UP
    };
    const signed char OPPOSTE_FACING[7] = {UP, DOWN, 3, 2, 5, 4, 6};
}

#endif //REDSTONE_SYSTEM_FACING_H
