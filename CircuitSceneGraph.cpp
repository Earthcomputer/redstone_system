//
// Created by Earthcomputer on 13/12/18.
//

#include "components/BaseCircuitComponent.h"
#include "CircuitSceneGraph.h"

BaseCircuitComponent* CircuitSceneGraph::getComponent(const BlockPos *pos, ComponentType type) {
    auto it = find(*pos);
    if (it == end())
        return nullptr;

    BaseCircuitComponent *component = it->second.get();
    if (component->getBaseType() == type || component->getInstanceType() == type)
        return component;
    else
        return nullptr;
}
