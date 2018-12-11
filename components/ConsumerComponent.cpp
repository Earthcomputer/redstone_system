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

    long componentType = trackingInfo->field_40.field_18;
    if (componentType == TYPE_POWERED_BLOCK && !v15)
        return false;

    if (field_3C) {
        switch (componentType) {
            case TYPE_PRODUCER: {
                auto *producer = dynamic_cast<ProducerComponent *>(trackingInfo->field_40.field_0);
                bool attached = producer->doesAllowAttachments()
                        && trackingInfo->field_0.field_14 == producer->getDirection();
                *a5 = attached;
                field_3D = attached;
                break;
            }
            case TYPE_CAPACITOR: {
                *a5 = trackingInfo->field_0.field_14 == Facing::UP;
                signed char v13 = trackingInfo->field_40.field_0->getDirection();
                if (v13 != 6) {
                    auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->field_40.field_0);
                    if (capacitor->getPoweroutDirection() != 6) {
                        v13 = capacitor->getPoweroutDirection();
                    }
                    bool attached = trackingInfo->field_0.field_14 == v13;
                    *a5 = attached;
                    field_3D = attached;
                }
                if (trackingInfo->field_0.field_14 == trackingInfo->field_40.field_0->getDirection())
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
    long componentType = trackingInfo->field_0.field_18;
    if (componentType != TYPE_CAPACITOR) {
        if (componentType == TYPE_TRANSPORTER && field_3C) {
            return field_3D;
        } else {
            return trackingInfo->field_84;
        }
    }

    auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->field_0.field_0);
    signed char dir = capacitor->getPoweroutDirection();
    if (dir == 6) {
        if (trackingInfo->field_0.field_14 != Facing::UP) {
            return false;
        } else {
            return trackingInfo->field_84;
        }
    }
    if (trackingInfo->field_0.field_14 == dir) {
        return trackingInfo->field_84;
    } else {
        return false;
    }
}

bool ConsumerComponent::evaluate(CircuitSystem *system, const BlockPos *pos) {
    field_3B = false;

    int v11 = 0;
    for (auto &it : *field_8) {
        int v6 = it.field_0->getStrength() - it.field_8;
        if (it.field_0->isHalfPulse() && !field_3E) {
            v6 = 15 - it.field_8;
        }
        if (v6 < 0) {
            v6 = 0;
        }
        if (v11 < v6) {
            field_3B = it.field_1C == 1;
            v11 = v6;
        }
    }

    bool v3 = field_34 != v11;
    field_34 = v11;
    return v3 || field_21;
}

