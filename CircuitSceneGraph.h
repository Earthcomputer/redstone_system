//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
#define REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H

#include <unordered_map>
#include <memory>
#include "BlockPos.h"
#include "components/ComponentType.h"
#include "CircuitComponentList.h"

class BaseCircuitComponent;

class CircuitSceneGraph : public std::unordered_map<BlockPos, std::unique_ptr<BaseCircuitComponent>> {
private:
    class PendingEntry {

    };

    CircuitComponentList *field_38;
    std::unordered_map<BlockPos, CircuitComponentList> field_50;
    std::unordered_map<BlockPos, CircuitComponentList> field_88;
    std::unordered_map<BlockPos, PendingEntry> field_C0;
    std::unordered_map<BlockPos, PendingEntry> field_F8;
    std::unordered_map<BlockPos, std::vector<BlockPos>> field_130;
    std::vector<PendingEntry> field_168;
public:
    CircuitSceneGraph() :
        field_38(),
        field_50(),
        field_88(),
        field_C0(),
        field_F8(),
        field_130(),
        field_168() {
    }

    BaseCircuitComponent *getBaseComponent(const BlockPos *pos) {
        auto it = find(*pos);
        if (it == end())
            return nullptr;
        return it->second.get();
    }
    BaseCircuitComponent *getComponent(const BlockPos *pos, ComponentType type);
};

#endif //REDSTONE_SYSTEM_CIRCUITSCENEGRAPH_H
