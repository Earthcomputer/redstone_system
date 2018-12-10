//
// Created by joseph on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_BASERAILTRANSPORTER_H
#define REDSTONE_SYSTEM_BASERAILTRANSPORTER_H

#include "BaseCircuitComponent.h"

class BaseRailTransporter : public BaseCircuitComponent {
private:
    bool field_3C;
public:
    BaseRailTransporter() {
        field_3C = false;
    }

    // VTABLE #1
    ~BaseRailTransporter() override {
        // TODO: impl
    }

    // VTABLE #10
    long getBaseType() override {
        return TYPE_RAIL_TRANSPORTER;
    }

    // VTABLE #11
    long getInstanceType() override {
        return TYPE_RAIL_TRANSPORTER;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;
};

#endif //REDSTONE_SYSTEM_BASERAILTRANSPORTER_H
