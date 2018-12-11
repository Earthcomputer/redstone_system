//
// Created by Earthcomputer on 10/12/18.
//

#include "PistonConsumer.h"

bool PistonConsumer::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4, bool *a5) {
    if (field_3F != trackingInfo->field_0.field_14) {
        ComponentType componentType = trackingInfo->field_40.field_18;
        if (componentType == TYPE_CAPACITOR) {
            if (trackingInfo->field_0.field_14 == trackingInfo->field_40.field_0->getDirection())
                return false;
        } else if (componentType == TYPE_POWERED_BLOCK && !*a5) {
            return false;
        }
        trackPowerSource(trackingInfo, *a4, *a5, trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()]);
    }
    return false;
}
