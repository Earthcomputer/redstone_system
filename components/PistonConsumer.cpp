//
// Created by Earthcomputer on 10/12/18.
//

#include "PistonConsumer.h"

bool PistonConsumer::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) {
    if (field_3F != trackingInfo->entry0.mDirection) {
        ComponentType componentType = trackingInfo->entry2.mComponentType;
        if (componentType == TYPE_CAPACITOR) {
            if (trackingInfo->entry0.mDirection == trackingInfo->entry2.mComponent->getDirection())
                return false;
        } else if (componentType == TYPE_POWERED_BLOCK && !*a5) {
            return false;
        }
        trackPowerSource(trackingInfo, *a4, *a5, trackingInfo->entry0.mDirection == Facing::OPPOSITE_FACING[getDirection()]);
    }
    return false;
}
