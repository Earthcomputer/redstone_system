//
// Created by joseph on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_REPEATERCAPACITOR_H
#define REDSTONE_SYSTEM_REPEATERCAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class RepeaterCapacitor : public CapacitorComponent {
private:
    int field_58;
    bool field_5C;
    bool field_5D;
    bool field_5E;
    int field_60;
    bool field_64;
    bool field_65;
    CircuitComponentList *field_68;
    int gap4_64[5];
public:
    RepeaterCapacitor();

    // VTABLE #1
    ~RepeaterCapacitor() override;

    // VTABLE #2
    int getStrength() override {
        return field_5C ? 15 : 0;
    }

    // VTABLE #4
    void setStrength(int strength) override {
        field_5C = strength != 0;
        for (int i = 0; i < field_58 + 1; i++) {
            gap4_64[i] = field_5C ? 3 : 2;
        }
        for (int i = field_58 + 1; i <= 4; i++) {
            gap4_64[i] = 0;
        }
    }

    // VTABLE #6
    bool consumePowerAnyDirection() override {
        return true;
    }

    // VTABLE #7
    bool canConsumePower() override {
        return true;
    }

    // VTABLE #11
    long getInstanceType() override {
        return TYPE_REPEATER;
    }

    // VTABLE #12
    bool removeSource(const BlockPos *pos, const BaseCircuitComponent *component) override;

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #15
    void checkLock() override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #17
    void cacheValues(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #18
    void updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) override;

    // VTABLE #24
    int getPoweroutDirection() override {
        return Facing::OPPOSTE_FACING[getDirection()];
    }
};

#endif //REDSTONE_SYSTEM_REPEATERCAPACITOR_H
