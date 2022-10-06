//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_TRANSPORTERCOMPONENT_H
#define REDSTONE_SYSTEM_TRANSPORTERCOMPONENT_H

#include "BaseCircuitComponent.h"

class TransporterComponent : public BaseCircuitComponent {
private:
    int field_3C;
public:
    TransporterComponent() {
        field_3C = 0;
    }

    // VTABLE #1
    ~TransporterComponent() override {
        // TODO: impl
    }

    // VTABLE #7
    bool canConsumePower() override {
        return true;
    }

    // VTABLE #10
    ComponentType getBaseType() const override {
        return TYPE_TRANSPORTER;
    }

    // VTABLE #11
    ComponentType getInstanceType() const override {
        return TYPE_TRANSPORTER;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #17
    void cacheValues(CircuitSystem *system, const BlockPos *pos) override;
};

#endif //REDSTONE_SYSTEM_TRANSPORTERCOMPONENT_H
