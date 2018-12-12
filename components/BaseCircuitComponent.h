//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_BASECIRCUITCOMPONENT_H
#define REDSTONE_SYSTEM_BASECIRCUITCOMPONENT_H

#include "ComponentType.h"
#include "../BlockPos.h"
#include "../CircuitComponentList.h"
#include "../CircuitTrackingInfo.h"
#include "../CircuitSceneGraph.h"
#include "../CircuitSystem.h"
#include "../Facing.h"

class BaseCircuitComponent {
public:
    CircuitComponentList *mDependencies; // off = 0x8
    bool field_20;
    bool field_21;
    bool field_22;
    BlockPos field_24;
    bool field_30;
    int mStrength; // off = 0x34
    Facing::Facing mDirection; // off = 0x38
    bool mAllowPowerUp; // off = 0x39
    bool field_3A;
public:
    BaseCircuitComponent();

    // VTABLE #1
    virtual ~BaseCircuitComponent();

    // VTABLE #2
    virtual int getStrength() {
        return mStrength;
    }

    // VTABLE #3
    virtual Facing::Facing getDirection() {
        return mDirection;
    }

    // VTABLE #4
    virtual void setStrength(int strength) {
        mStrength = strength;
    }

    // VTABLE #5
    virtual void setDirection(Facing::Facing dir) {
        mDirection = dir;
    }

    // VTABLE #6
    virtual bool consumePowerAnyDirection() {
        return false;
    }

    // VTABLE #7
    virtual bool canConsumePower() {
        return false;
    }

    // VTABLE #8
    virtual bool canStopPower() {
        return false;
    }

    // VTABLE #9
    virtual void setStopPower(bool stopPower) {
    }

    // VTABLE #10
    virtual ComponentType getBaseType() const {
        return TYPE_BASE;
    }

    // VTABLE #11
    virtual ComponentType getInstanceType() const {
        return TYPE_BASE;
    }

    // VTABLE #12
    virtual bool removeSource(const BlockPos *pos, const BaseCircuitComponent *component);

    // VTABLE #13
    virtual bool addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) {
        return false;
    }

    // VTABLE #14
    virtual bool allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
        return true;
    }

    // VTABLE #15
    virtual void checkLock() {
    }

    // VTABLE #16
    virtual bool evaluate(CircuitSystem *system, const BlockPos *pos) {
        return false;
    }

    // VTABLE #17
    virtual void cacheValues(CircuitSystem *system, const BlockPos *pos) {
    }

    // VTABLE #18
    virtual void updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    }

    // VTABLE #19
    virtual bool allowIndirect() {
        return false;
    }

    // VTABLE #20
    virtual bool isHalfPulse() {
        return false;
    }

    // VTABLE #21
    virtual bool hasSource(BaseCircuitComponent *component);

    // VTABLE #22
    virtual bool hasChildrenSource() {
        return false;
    }

    // VTABLE #23
    virtual bool isSecondaryPowered() {
        return false;
    }

    void setAllowPowerUp(bool allowPowerUp) {
        mAllowPowerUp = allowPowerUp;
    }

    bool canAllowPowerUp() {
        return mAllowPowerUp;
    }

    bool canAllowPowerDown() {
        // TODO: impl
    }

    bool trackPowerSource(const CircuitTrackingInfo *trackingInfo, int a3, bool a4, bool a5) {
        // TODO: impl
    }

    void trackPowerSourceDuplicates(const CircuitTrackingInfo *trackingInfo, int a3, bool a4) {
        // TODO: impl
    }

    bool hasDirectPower() {
        // TODO: impl
    }
};

#endif //REDSTONE_SYSTEM_BASECIRCUITCOMPONENT_H
