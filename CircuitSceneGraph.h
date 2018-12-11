//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
#define REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H

#include "components/BaseCircuitComponent.h"

class CircuitSceneGraph {
public:
    BaseCircuitComponent *getBaseComponent(const BlockPos *pos);
};

#endif //REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
