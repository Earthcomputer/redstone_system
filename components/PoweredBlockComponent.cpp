//
// Created by Earthcomputer on 10/12/18.
//

#include "PoweredBlockComponent.h"
#include "ProducerComponent.h"
#include "CapacitorComponent.h"

int PoweredBlockComponent::getStrength() {
    int maxStrength = 0;
    for (size_t i = 0; i < mDependencies->size(); i++) {
        CircuitComponentList::Item item = mDependencies->at(i);
        int strength = item.mComponent->getStrength() - item.field_8;
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

    ComponentType componentType = trackingInfo->entry2.mComponentType;

    if (mAllowPowerUp)
        return false;

    mPromotedToProducer = false;

    if (componentType == TYPE_CONSUMER || componentType == TYPE_POWERED_BLOCK) {
        *a5 = false;
        return false;
    }

    switch (componentType) {
        case TYPE_PRODUCER: {
            auto *producer = dynamic_cast<ProducerComponent *>(trackingInfo->entry2.mComponent);
            bool powered = producer->doesAllowAttachments() && trackingInfo->entry0.mDirection == producer->getDirection();
            *a5 = powered;
            mPromotedToProducer = powered;
            break;
        }
        case TYPE_CAPACITOR: {
            auto *capacitor = dynamic_cast<CapacitorComponent *>(trackingInfo->entry2.mComponent);
            bool powered = trackingInfo->entry0.mDirection == capacitor->getPoweroutDirection();
            *a5 = powered;
            mPromotedToProducer = powered;
            if (!mPromotedToProducer && capacitor->getInstanceType() == TYPE_REDSTONE_TORCH) {
                return false;
            }
            break;
        }
        case TYPE_TRANSPORTER: {
            *a5 |= trackingInfo->entry2.mDirection == trackingInfo->entry0.mDirection
                    && trackingInfo->entry2.mPos.y == trackingInfo->entry0.mPos.y;
            *a5 |= trackingInfo->entry0.mDirection == Facing::DOWN;
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
    if (trackingInfo->entry0.mComponentType == TYPE_TRANSPORTER)
        return mPromotedToProducer;
    else
        return trackingInfo->entry0.mComponentType != TYPE_POWERED_BLOCK;
}

