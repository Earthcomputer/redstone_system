//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H
#define REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class RedstoneTorchCapacitor : public CapacitorComponent {
private:
    RedstoneTorchCapacitor *field_48;
    int field_50;
    bool field_54;
    bool field_55;
    bool gap56;
    bool field_57;
    bool field_58;
    bool gap59;
    bool field_5A;
public:
    RedstoneTorchCapacitor() {
        field_48 = nullptr;
        field_50 = 0;
        field_5A = false;
        field_58 = false;
        field_55 = false;
        field_57 = false;
        field_54 = false;
        setAllowPowerUp(true);
    }

    // VTABLE #1
    ~RedstoneTorchCapacitor() override {
        // TODO: impl
    }

    // VTABLE #2
    int getStrength() override {
        return field_54 ? 15 : 0;
    }

    // VTABLE #11
    long getInstanceType() override {
        return TYPE_REDSTONE_TORCH;
    }

    // VTABLE #12
    bool removeSource(const BlockPos *pos, const BaseCircuitComponent *component) override {
        bool result = BaseCircuitComponent::removeSource(pos, component);
        if (field_48 == component && field_48) {
            field_48 = field_48->field_48;
            return true;
        } else {
            return result;
        }
    }

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #16
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override {
        field_54 = field_57;
        gap56 = gap59;
        if (field_48 && _canIncrementSelfPower()) {
            field_50++;
        }
        return gap56;
    }

    // VTABLE #17
    void cacheValues(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #18
    void updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) override;

    // VTABLE #20
    bool isHalfPulse() override {
        return field_55;
    }

    // VTABLE #24
    int getPoweroutDirection() override {
        return Facing::UP;
    }

private:
    bool _canIncrementSelfPower() {
        return !field_5A && field_50 <= 32;
    }
};

#endif //REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H
