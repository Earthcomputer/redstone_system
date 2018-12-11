//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CONSUMERCOMPONENT_H
#define REDSTONE_SYSTEM_CONSUMERCOMPONENT_H

#include "BaseCircuitComponent.h"

class ConsumerComponent : public BaseCircuitComponent {
private:
    bool field_3B;
    bool field_3C;
    bool field_3D;
    bool field_3E;
public:
    ConsumerComponent() {
        field_3B = false;
        field_3C = false;
        field_3D = false;
        field_3E = false;
    }

    // VTABLE #1
    ~ConsumerComponent() override {
        // TODO: impl
    }

    // VTABLE #7
    bool canConsumePower() override {
        return true;
    }

    // VTABLE #10
    long getBaseType() const override {
        return TYPE_CONSUMER;
    }

    // VTABLE #11
    long getInstanceType() const override {
        return TYPE_CONSUMER;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #23
    bool isSecondaryPowered() override {
        return field_3B;
    }
};

#endif //REDSTONE_SYSTEM_CONSUMERCOMPONENT_H
