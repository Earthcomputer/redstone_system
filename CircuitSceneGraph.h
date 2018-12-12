//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
#define REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H

#include "BlockPos.h"
#include "components/ComponentType.h"

class BaseCircuitComponent;

class CircuitSceneGraph {
public:
    BaseCircuitComponent *getBaseComponent(const BlockPos *pos) {
        // TODO: impl
    }
    BaseCircuitComponent *getComponent(const BlockPos *pos, ComponentType type) {
        // TODO: impl
    }
};

#endif //REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
