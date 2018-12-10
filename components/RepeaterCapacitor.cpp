//
// Created by joseph on 10/12/18.
//

#include "RepeaterCapacitor.h"

RepeaterCapacitor::RepeaterCapacitor() {
    field_58 = 0;
    field_5C = false;
    field_5D = false;
    field_5E = true;
    field_60 = 0;
    field_64 = false;
    field_65 = false;
    // field_68
    for (int i = 0; i < 4; i++)
        gap4_64[i] = 2;
}

RepeaterCapacitor::~RepeaterCapacitor() {
    // TODO: impl
}

bool RepeaterCapacitor::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    // TODO: impl
}

bool RepeaterCapacitor::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                  bool *a5) {
    // TODO: impl
}

bool RepeaterCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    // TODO: impl
}

void RepeaterCapacitor::checkLock() {
    // TODO: impl
}

bool RepeaterCapacitor::evaluate(CircuitSystem *system, const BlockPos *pos) {
    // TODO: impl
}

void RepeaterCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    // TODO: impl
}

void RepeaterCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    // TODO: impl
}
