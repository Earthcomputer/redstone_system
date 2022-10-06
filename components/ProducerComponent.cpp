//
// Created by Earthcomputer on 10/12/18.
//

#include "ProducerComponent.h"

bool ProducerComponent::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    return field_40 || trackingInfo->entry0.mComponent->getBaseType() != TYPE_POWERED_BLOCK;
}

bool ProducerComponent::evaluate(CircuitSystem *system, const BlockPos *pos) {
    mStrength = field_3C;
    return false;
}
