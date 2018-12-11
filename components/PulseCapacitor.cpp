//
// Created by Earthcomputer on 10/12/18.
//

#include "PulseCapacitor.h"

bool PulseCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    return trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()];
}

