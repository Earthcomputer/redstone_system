//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_BASERAILTRANSPORTER_H
#define REDSTONE_SYSTEM_BASERAILTRANSPORTER_H

#include "BaseCircuitComponent.h"

class BaseRailTransporter : public BaseCircuitComponent {
private:
    bool mRailType; // off = 0x3C
public:
    BaseRailTransporter() {
        mRailType = false;
    }

    // VTABLE #1
    ~BaseRailTransporter() override {
        // TODO: impl
    }

    // VTABLE #10
    ComponentType getBaseType() const override {
        return TYPE_RAIL_TRANSPORTER;
    }

    // VTABLE #11
    ComponentType getInstanceType() const override {
        return TYPE_RAIL_TRANSPORTER;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

private:
    bool sub_1F60A40(const CircuitTrackingInfo *trackingInfo, int a3, int a4);
};

#endif //REDSTONE_SYSTEM_BASERAILTRANSPORTER_H
