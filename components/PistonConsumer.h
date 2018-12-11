//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_PISTONCONSUMER_H
#define REDSTONE_SYSTEM_PISTONCONSUMER_H

#include "ConsumerComponent.h"

class PistonConsumer : public ConsumerComponent {
private:
    int field_3F;
public:
    PistonConsumer() {
        field_3F = 6;
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
    long getInstanceType() const override {
        return TYPE_PISTON;
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;
};

#endif //REDSTONE_SYSTEM_PISTONCONSUMER_H
