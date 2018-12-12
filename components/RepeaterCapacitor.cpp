//
// Created by Earthcomputer on 10/12/18.
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
    field_68 = new CircuitComponentList;
    for (int i = 0; i < 4; i++)
        field_44[i] = 2;
}

bool RepeaterCapacitor::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    bool baseRemoved = BaseCircuitComponent::removeSource(pos, component);
    bool repeaterRemoved = field_68->removeSource(pos, component);
    return baseRemoved || repeaterRemoved;
}

bool RepeaterCapacitor::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                  bool *a5) {
    bool sameDir = trackingInfo->field_0.field_14 == getDirection();
    bool oppositeDir = trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()];
    if ((trackingInfo->field_40.field_18 != TYPE_POWERED_BLOCK || (trackingInfo->field_40.field_0->hasDirectPower() && *a5)) && !sameDir) {
        ComponentType componentType = trackingInfo->field_40.field_0->getInstanceType();
        if (oppositeDir || componentType == TYPE_REPEATER || componentType == TYPE_COMPARATOR)
            trackPowerSource(trackingInfo, *a4, *a5, oppositeDir);
    }
    return false;
}

bool RepeaterCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, bool *a4) {
    return trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()];
}

void RepeaterCapacitor::checkLock() {
    field_5E = false;
    for (auto &item : *field_68) {
        int v10 = item.field_0->getStrength() - item.field_8;
        v10 = std::max(v10, 0);
        if (v10 > 0) {
            field_5E = true;
            for (int i = 1; i < 4; i++) {
                field_44[i] = field_44[0];
            }
            return;
        }
    }
}

bool RepeaterCapacitor::evaluate(CircuitSystem *system, const BlockPos *pos) {
    bool oldVal = field_5C;
    if (!field_5E) {
        delayPulse(field_5D);
        if (field_58 > 0) {
            if (field_60 > field_58 && !(field_64 && field_60 == 2)) {
                alternatePulse();
            } else {
                extendPulse();
            }
        }
        field_5C = field_44[0] == 1 || field_44[0] == 3;
    }
    return oldVal != field_5C;
}

void RepeaterCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    field_5D = false;
    for (auto &item : *field_8) {
        int v9 = item.field_0->getStrength() - item.field_8;
        v9 = std::max(v9, 0);
        if (v9 > 0) {
            field_5D = true;
            break;
        }
    }

    if (!field_5E) {
        if (field_64 == field_5D) {
            field_60 = 0;
        } else {
            field_60++;
            if (field_60 == 1) {
                field_65 = !field_64;
            }
            field_64 = !field_64;
        }
    }
}

void RepeaterCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    for (auto it = field_8->begin(); it != field_8->end();) {
        if (it->field_1C == 1) {
            ++it;
        } else {
            BlockPos tmp = it->field_C;
            field_68->add(it->field_0, it->field_8, &tmp);
            it = field_8->erase(it);
        }
    }
}
