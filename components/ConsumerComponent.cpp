//
// Created by Earthcomputer on 10/12/18.
//

#include "ConsumerComponent.h"
#include "ProducerComponent.h"
#include "../Facing.h"
#include "CapacitorComponent.h"

bool ConsumerComponent::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                  bool *a5) {
    bool v15 = *a5;
    *a5 = false;
    field_3D = false;

    long componentType = trackingInfo->entry2.mComponentType;
    if (componentType == TYPE_POWERED_BLOCK && !v15)
        return false;

    if (field_3C) {
        switch (componentType) {
            case TYPE_PRODUCER: {
                auto *producer = dynamic_cast<ProducerComponent *>(trackingInfo->entry2.mComponent);
                bool attached = producer->doesAllowAttachments()
                        && trackingInfo->entry0.mDirection == producer->getDirection();
                *a5 = attached;
                field_3D = attached;
                break;
            }
            case TYPE_CAPACITOR: {
                *a5 = trackingInfo->entry0.mDirection == Facing::UP;
                Facing::Facing v13 = trackingInfo->entry2.mComponent->getDirection();
                if (v13 != Facing::NONE) {
                    auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->entry2.mComponent);
                    if (capacitor->getPoweroutDirection() != Facing::NONE) {
                        v13 = capacitor->getPoweroutDirection();
                    }
                    bool attached = trackingInfo->entry0.mDirection == v13;
                    *a5 = attached;
                    field_3D = attached;
                }
                if (trackingInfo->entry0.mDirection == trackingInfo->entry2.mComponent->getDirection())
                    return false;
                break;
            }
            case TYPE_TRANSPORTER: {
                *a5 = true;
                break;
            }
            default: {
                break;
            }
        }
    }

    bool result = false;
    if (trackPowerSource(trackingInfo, *a4, *a5, componentType == TYPE_CONSUMER))
        result = *a5;
    return result;
}

bool ConsumerComponent::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    long componentType = trackingInfo->entry0.mComponentType;
    if (componentType != TYPE_CAPACITOR) {
        if (componentType == TYPE_TRANSPORTER && field_3C) {
            return field_3D;
        } else {
            return trackingInfo->field_84;
        }
    }

    auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->entry0.mComponent);
    Facing::Facing dir = capacitor->getPoweroutDirection();
    if (dir == Facing::NONE) {
        if (trackingInfo->entry0.mDirection != Facing::UP) {
            return false;
        } else {
            return trackingInfo->field_84;
        }
    }
    if (trackingInfo->entry0.mDirection == dir) {
        return trackingInfo->field_84;
    } else {
        return false;
    }
}

bool ConsumerComponent::evaluate(CircuitSystem *system, const BlockPos *pos) {
    mSecondaryPowered = false;

    int v11 = 0;
    for (auto &it : *mDependencies) {
        int v6 = it.mComponent->getStrength() - it.field_8;
        if (it.mComponent->isHalfPulse() && !field_3E) {
            v6 = 15 - it.field_8;
        }
        if (v6 < 0) {
            v6 = 0;
        }
        if (v11 < v6) {
            mSecondaryPowered = it.field_1C == 1;
            v11 = v6;
        }
    }

    bool v3 = mStrength != v11;
    mStrength = v11;
    return v3 || field_21;
}

