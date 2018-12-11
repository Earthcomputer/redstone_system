//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_PULSECAPACITOR_H
#define REDSTONE_SYSTEM_PULSECAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class PulseCapacitor : public CapacitorComponent {
private:
    bool field_42;
    bool field_43;
public:
    PulseCapacitor() {
        field_42 = false;
        field_43 = false;
    }

    // VTABLE #1
    ~PulseCapacitor() override {
        // TODO: impl
    }

    // VTABLE #2
    int getStrength() override {
        return field_34;
    }

    // VTABLE #4
    void setStrength(int strength) override {
        field_3C = strength;
        field_43 = strength != 0;
    }

    // VTABLE #6
    bool consumePowerAnyDirection() override {
        return false;
    }

    // VTABLE #7
    bool canConsumePower() override {
        return false;
    }

    // VTABLE #11
    ComponentType getInstanceType() const override {
        return TYPE_PULSE_CAPACITOR;
    }

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override {
        ProducerComponent::evaluate(system, pos);
        field_42 = field_43;
        field_43 = false;
        field_3C = 0;
        return field_42;
    }

    // VTABLE #24
    Facing::Facing getPoweroutDirection() override {
        return Facing::OPPOSITE_FACING[getDirection()];
    }
};

#endif //REDSTONE_SYSTEM_PULSECAPACITOR_H
