//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_POWEREDBLOCKCOMPONENT_H
#define REDSTONE_SYSTEM_POWEREDBLOCKCOMPONENT_H

#include "BaseCircuitComponent.h"

// Seems to be e.g. stone powered by a repeater. Not a redstone block.
class PoweredBlockComponent : public BaseCircuitComponent {
private:
    bool field_3B;
    bool field_3C;
public:
    PoweredBlockComponent() {
        field_3B = false;
        field_3C = true;
        field_21 = false;
    }

    // VTABLE #1
    ~PoweredBlockComponent() override {
        // TODO: impl
    }

    // VTABLE #2
    int getStrength() override;

    // VTABLE #7
    bool canConsumePower() override {
        return true;
    }

    // VTABLE #10
    long getBaseType() const override {
        return TYPE_POWERED_BLOCK;
    }

    // VTABLE #11
    long getInstanceType() const override {
        return TYPE_POWERED_BLOCK;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override {
        return false;
    }

    // VTABLE #22
    bool hasChildrenSource() override {
        return true;
    }
};

#endif //REDSTONE_SYSTEM_POWEREDBLOCKCOMPONENT_H
