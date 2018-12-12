//
// Created by Earthcomputer on 10/12/18.
//

#include "PoweredBlockComponent.h"
#include "ProducerComponent.h"
#include "CapacitorComponent.h"

int PoweredBlockComponent::getStrength() {
    int maxStrength = 0;
    for (size_t i = 0; i < field_8->size(); i++) {
        CircuitComponentList::Item item = field_8->at(i);
        int strength = item.field_0->getStrength() - item.field_8;
        if (strength < 0)
            strength = 0;
        if (maxStrength < strength)
            maxStrength = strength;
    }
    return maxStrength;
}

bool PoweredBlockComponent::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                      bool *a5) {
    if (!field_3C)
        return false;

    ComponentType componentType = trackingInfo->field_40.field_18;

    if (field_39)
        return false;

    field_3B = false;

    if (componentType == TYPE_CONSUMER || componentType == TYPE_POWERED_BLOCK) {
        *a5 = false;
        return false;
    }

    switch (componentType) {
        case TYPE_PRODUCER: {
            auto *producer = dynamic_cast<ProducerComponent *>(trackingInfo->field_40.field_0);
            bool powered = producer->doesAllowAttachments() && trackingInfo->field_0.field_14 == producer->getDirection();
            *a5 = powered;
            field_3B = powered;
            break;
        }
        case TYPE_CAPACITOR: {
            auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->field_40.field_0);
            bool powered = trackingInfo->field_0.field_14 == capacitor->getPoweroutDirection();
            *a5 = powered;
            field_3B = powered;
            if (!field_3B && capacitor->getInstanceType() == TYPE_REDSTONE_TORCH) {
                return false;
            }
            break;
        }
        case TYPE_TRANSPORTER: {
            *a5 |= trackingInfo->field_40.field_14 == trackingInfo->field_0.field_14
                    && trackingInfo->field_40.field_8.y == trackingInfo->field_0.field_8.y;
            *a5 |= trackingInfo->field_0.field_14 == Facing::DOWN;
            break;
        }
        default: {
            break;
        }
    }
    return trackPowerSource(trackingInfo, *a4, *a5, false);
}

bool PoweredBlockComponent::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                            bool *a4) {
    if (trackingInfo->field_0.field_18 == TYPE_TRANSPORTER)
        return field_3B;
    else
        return trackingInfo->field_0.field_18 != TYPE_POWERED_BLOCK;
}

