//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H
#define REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H

#include "CapacitorComponent.h"
#include "../Facing.h"

class RedstoneTorchCapacitor : public CapacitorComponent {
private:
    RedstoneTorchCapacitor *mNextInQueue; // off = 0x48
    int mSelfPowerCount; // off = 0x50
    bool field_54;
    bool mHalfPulse; // off = 0x55
    bool field_56;
    bool field_57;
    bool field_58;
    bool field_59;
    bool field_5A;
public:
    RedstoneTorchCapacitor() {
        mNextInQueue = nullptr;
        mSelfPowerCount = 0;
        field_5A = false;
        field_58 = false;
        mHalfPulse = false;
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
    ComponentType getInstanceType() const override {
        return TYPE_REDSTONE_TORCH;
    }

    // VTABLE #12
    bool removeSource(const BlockPos *pos, const BaseCircuitComponent *component) override {
        bool result = BaseCircuitComponent::removeSource(pos, component);
        if (mNextInQueue == component && mNextInQueue) {
            mNextInQueue = mNextInQueue->mNextInQueue;
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
        field_56 = field_59;
        if (mNextInQueue && _canIncrementSelfPower()) {
            mSelfPowerCount++;
        }
        return field_56;
    }

    // VTABLE #17
    void cacheValues(CircuitSystem *system, const BlockPos *pos) override;

    // VTABLE #18
    void updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) override;

    // VTABLE #20
    bool isHalfPulse() override {
        return mHalfPulse;
    }

    // VTABLE #24
    Facing::Facing getPoweroutDirection() override {
        return Facing::UP;
    }

    void setSelfPowerCount(int selfPowerCount) {
        mSelfPowerCount = selfPowerCount;
    }

    void setNextInQueue(RedstoneTorchCapacitor *torch) {
        mNextInQueue = torch;
    }

private:
    bool _canIncrementSelfPower() {
        return !field_5A && mSelfPowerCount <= 32;
    }

    int FindStrongestStrength(const BlockPos *pos, CircuitSystem *system, bool *a4);
};

#endif //REDSTONE_SYSTEM_RESTONETORCHCAPACITOR_H
