//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_REPEATERCAPACITOR_H
#define REDSTONE_SYSTEM_REPEATERCAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class RepeaterCapacitor : public CapacitorComponent {
private:
    int field_44[5];
    int field_58;
    bool mOn; // off = 0x5C
    bool field_5D; // TODO: what type should this be? delayPulse() suggests it's not a bool, but alignment suggests it's not an int
    bool field_5E;
    int field_60;
    bool field_64; // TODO: this is compared to field_5D, probably the same type
    bool field_65;
    CircuitComponentList *field_68;
public:
    RepeaterCapacitor();

    // VTABLE #1
    ~RepeaterCapacitor() override {
        delete field_68;
    }

    // VTABLE #2
    int getStrength() override {
        return mOn ? 15 : 0;
    }

    // VTABLE #4
    void setStrength(int strength) override {
        mOn = strength != 0;
        for (int i = 0; i < field_58 + 1; i++) {
            field_44[i] = mOn ? 3 : 2;
        }
        for (int i = field_58 + 1; i <= 4; i++) {
            field_44[i] = 0;
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
    ComponentType getInstanceType() const override {
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
    Facing::Facing getPoweroutDirection() override {
        return Facing::OPPOSITE_FACING[getDirection()];
    }

    void delayPulse(int a2) {
        for (int i = 1; i <= field_58; i++) {
            field_44[i - 1] = field_44[i];
        }
        for (int i = field_58; i < 4; i++) {
            field_44[i] = a2;
        }
    }

    void alternatePulse() {
        if (field_58 > 0) {
            if (field_44[0] == 0 || field_44[0] == 1) {
                int v1 = field_65 ? 3 : 2;
                field_65 = !field_65;
                for (int i = 0; i < field_58 + 1; i++) {
                    field_44[i] = v1;
                }
            }
        }
    }

    void extendPulse() {
        if (field_58 > 0) {
            if (field_44[0] == 2 && field_44[1] == 0) {
                field_44[1] = 2;
            } else if (field_44[0] == 3 && field_44[1] == 1) {
                field_44[1] = 3;
            }
            if (field_44[0] == 0 || field_44[0] == 1) {
                int v5 = 0;
                for (int i = 0; i <= field_58; i++) {
                    if (field_44[i] == field_44[0])
                        v5++;
                }
                int v3;
                if (field_44[0] != 0) {
                    v3 = 3;
                } else {
                    v3 = v5 <= field_58 ? 3 : 2;
                }
                for (int i = 0; i <= field_58; i++) {
                    field_44[i] = v3;
                }
            }
        }
    }
};

#endif //REDSTONE_SYSTEM_REPEATERCAPACITOR_H
