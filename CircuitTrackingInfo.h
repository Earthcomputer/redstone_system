//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CIRCUITTRACKINGINFO_H
#define REDSTONE_SYSTEM_CIRCUITTRACKINGINFO_H

class BaseCircuitComponent;

#include "BlockPos.h"
#include "Facing.h"
#include "components/ComponentType.h"

class CircuitTrackingInfo {
public:
    struct Entry {
        BaseCircuitComponent *field_0;
        BlockPos field_8;
        Facing::Facing field_14;
        ComponentType field_18;
    };

    Entry field_0;
    Entry field_20;
    Entry field_40;
    Entry field_60;
    unsigned int field_80;
    bool field_84;
    int field_88;

    CircuitTrackingInfo(BaseCircuitComponent *component, BlockPos *pos, unsigned int a4);
};

#endif //REDSTONE_SYSTEM_CIRCUITTRACKINGINFO_H
