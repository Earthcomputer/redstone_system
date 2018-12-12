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
        BaseCircuitComponent *mComponent; // off = 0x0
        BlockPos mPos; // off = 0x8
        Facing::Facing mDirection; // off = 0x14
        ComponentType mComponentType; // off = 0x18
    };

    Entry entry0; // off = 0x0
    Entry entry1; // off = 0x20
    Entry entry2; // off = 0x40
    Entry entry3; // off = 0x60
    unsigned int field_80;
    bool field_84;
    int field_88;

    CircuitTrackingInfo(BaseCircuitComponent *component, BlockPos *pos, unsigned int a4);
};

#endif //REDSTONE_SYSTEM_CIRCUITTRACKINGINFO_H
