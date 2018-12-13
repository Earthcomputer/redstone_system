//
// Created by Earthcomputer on 10/12/18.
//

#include "ComparatorCapacitor.h"

ComparatorCapacitor::ComparatorCapacitor() {
    field_44 = -1;
    field_48 = -1;
    field_4C = -1;
    field_50 = 0;
    mSubtractMode = false;
    mCachedRearStrength = 0;
    mCachedSideStrength = 0;
    field_60 = 0;
    mSideDependencies = new CircuitComponentList;
}

bool ComparatorCapacitor::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    bool baseRemoved = BaseCircuitComponent::removeSource(pos, component);
    bool comparatorRemoved = mSideDependencies->removeSource(pos, component);
    return baseRemoved || comparatorRemoved;
}

bool ComparatorCapacitor::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                    bool *a5) {
    if (trackingInfo->entry0.mDirection != Facing::DOWN && trackingInfo->entry0.mDirection != Facing::UP) {
        if (trackingInfo->entry0.mDirection != getDirection()) {
            bool connected;
            if (trackingInfo->entry0.mDirection == Facing::OPPOSITE_FACING[getDirection()]) {
                connected = true;
            } else {
                ComponentType componentType = trackingInfo->entry2.mComponent->getInstanceType();
                connected = componentType == TYPE_TRANSPORTER || componentType == TYPE_REPEATER || componentType == TYPE_COMPARATOR;
            }
            if (connected) {
                if (trackingInfo->entry2.mComponentType != TYPE_POWERED_BLOCK || trackingInfo->entry2.mComponent->hasDirectPower()) {
                    trackPowerSourceDuplicates(trackingInfo, *a4, *a5);
                }
            }
        }
    }
    return false;
}

bool ComparatorCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                          bool *a4) {
    return trackingInfo->entry0.mDirection == Facing::OPPOSITE_FACING[getDirection()];
}

bool ComparatorCapacitor::evaluate(CircuitSystem *system, const BlockPos *pos) {
    field_50 = mStrength;
    if (mSubtractMode) {
        mStrength = std::max(GetRearStrength() - GetSideStrength(), 0);
    } else {
        mStrength = GetRearStrength();
        if (GetSideStrength() > mStrength) {
            mStrength = 0;
        }
    }
    mStrength = std::min(mStrength, 15);
    return field_50 != mStrength;
}

void ComparatorCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    if (!field_60)
        return;

    mCachedRearStrength = 0;
    mCachedSideStrength = 0;

    for (auto &item : *mDependencies) {
        if (item.field_19) {
            int strength = item.mComponent->getStrength() - item.field_8;
            strength = std::max(strength, 0);
            if (strength > mCachedRearStrength)
                mCachedRearStrength = strength;
        }
    }

    for (auto &item : *mSideDependencies) {
        int strength = item.mComponent->getStrength() - item.field_8;
        strength = std::max(strength, 0);
        if (strength > mCachedSideStrength)
            mCachedSideStrength = strength;
    }
}

void ComparatorCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    for (auto it = mDependencies->begin(); it != mDependencies->end();) {
        if (it->mComponent->canStopPower()) {
            it = mDependencies->erase(it);
        } else {
            if (it->mComponent->getDirection() == Facing::OPPOSITE_FACING[getDirection()]) {
                ++it;
            } else {
                BlockPos tmp = it->mPos;
                mSideDependencies->add(it->mComponent, it->field_8, &tmp);
                it = mDependencies->erase(it);
            }
        }
    }
}

