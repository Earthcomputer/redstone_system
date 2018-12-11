//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CAPACITORCOMPONENT_H
#define REDSTONE_SYSTEM_CAPACITORCOMPONENT_H

#include "ProducerComponent.h"

class CapacitorComponent : public ProducerComponent {
public:
    CapacitorComponent() = default;

    // VTABLE #1
    ~CapacitorComponent() override {
        // TODO: impl
    }

    // VTABLE #10
    long getBaseType() const override {
        return TYPE_CAPACITOR;
    }

    // VTABLE #11
    long getInstanceType() const override {
        return TYPE_CAPACITOR;
    }

    // VTABLE #24
    virtual signed char getPoweroutDirection() {
        return 6;
    }
};

#endif //REDSTONE_SYSTEM_CAPACITORCOMPONENT_H
