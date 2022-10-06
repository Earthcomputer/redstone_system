//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_PISTONCONSUMER_H
#define REDSTONE_SYSTEM_PISTONCONSUMER_H

#include "ConsumerComponent.h"

class PistonConsumer : public ConsumerComponent {
private:
    Facing::Facing field_3F;
public:
    PistonConsumer() {
        field_3F = Facing::NONE;
    }

    // VTABLE #1
    ~PistonConsumer() override {
        // TODO: impl
    }

    // VTABLE #6
    bool consumePowerAnyDirection() override {
        return true;
    }

    // VTABLE #11
    ComponentType getInstanceType() const override {
        return TYPE_PISTON;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override {
        return true;
    }

    void setBlockPowerFace(Facing::Facing face) {
        if (face == Facing::DOWN) {
            field_3F = Facing::UP;
        } else if (face == Facing::UP) {
            field_3F = Facing::DOWN;
        } else {
            field_3F = face;
        }
    }
};

#endif //REDSTONE_SYSTEM_PISTONCONSUMER_H
