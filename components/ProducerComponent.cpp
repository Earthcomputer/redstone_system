//
// Created by joseph on 10/12/18.
//

#include "ProducerComponent.h"

void ProducerComponent::setStrength(int strength) {
    field_3C = strength;
    // TODO: more code
}

bool ProducerComponent::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    return field_40; // TODO: || something to do with the trackingInfo
}

bool ProducerComponent::evaluate(CircuitSystem *system, const BlockPos *pos) {
    // TODO: impl
}
