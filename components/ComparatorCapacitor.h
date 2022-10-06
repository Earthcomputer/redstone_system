//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_COMPARATORCAPACITOR_H
#define REDSTONE_SYSTEM_COMPARATORCAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class ComparatorCapacitor : public CapacitorComponent {
private:
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    bool mSubtractMode; // off = 0x54
    int mCachedRearStrength; // off = 0x58
    int mCachedSideStrength; // off = 0x5C
    int field_60;
    CircuitComponentList *mSideDependencies; // off = 0x64
public:
    ComparatorCapacitor();

    // VTABLE #1
    ~ComparatorCapacitor() override {
        delete mSideDependencies;
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
        return TYPE_COMPARATOR;
    }

    // VTABLE #12
    bool removeSource(const BlockPos *pos, const BaseCircuitComponent *component) override;

    // VTABLE #13
    bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) override;

    // VTABLE #14
    bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) override;

    // VTABLE #17
    bool evaluate(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #18
    void cacheValues(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #19
    void updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) override;

    // VTABLE #24
    Facing::Facing getPoweroutDirection() override {
        return Facing::OPPOSITE_FACING[getDirection()];
    }

private:
    int GetRearStrength() {
        if (field_44 == -1)
            return mCachedRearStrength;
        else
            return field_44;
    }

    int GetSideStrength() {
        if (field_48 == -1)
            return mCachedSideStrength;
        else
            return std::max(field_48, field_4C);
    }
};

#endif //REDSTONE_SYSTEM_COMPARATORCAPACITOR_H
