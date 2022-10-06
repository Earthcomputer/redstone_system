//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_PRODUCERCOMPONENT_H
#define REDSTONE_SYSTEM_PRODUCERCOMPONENT_H

#include "BaseCircuitComponent.h"

class ProducerComponent : public BaseCircuitComponent {
protected:
    int field_3C;
    bool field_40;
    bool field_41;
public:
    ProducerComponent() {
        field_3C = 0;
        field_41 = false;
        field_40 = false;
    }

    // VTABLE #1
    ~ProducerComponent() override {
        // TODO: impl
    }

    // VTABLE #4
    void setStrength(int strength) override {
        field_3C = strength;
        if (field_21) {
            mStrength = strength;
        }
    }

    // VTABLE #8
    bool canStopPower() override {
        return field_41;
    }

    // VTABLE #9
    void setStopPower(bool stopPower) override {
        field_41 = stopPower;
    }

    // VTABLE #10
    ComponentType getBaseType() const override {
        return TYPE_PRODUCER;
    }

    // VTABLE #11
    ComponentType getInstanceType() const override {
        return TYPE_PRODUCER;
    }

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

    void allowAttachments(bool allowAttachments) {
        field_40 = allowAttachments;
    }

    bool doesAllowAttachments() {
        return field_40;
    }
};

#endif //REDSTONE_SYSTEM_PRODUCERCOMPONENT_H
