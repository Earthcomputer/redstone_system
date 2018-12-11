//
// Created by Earthcomputer on 10/12/18.
//

#include "ComparatorCapacitor.h"

ComparatorCapacitor::ComparatorCapacitor() {
    field_44 = -1;
    field_48 = -1;
    field_4C = -1;
    field_50 = 0;
    field_54 = false;
    field_58 = 0;
    field_5C = 0;
    field_60 = 0;
    field_68 = new CircuitComponentList;
}

bool ComparatorCapacitor::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    bool baseRemoved = BaseCircuitComponent::removeSource(pos, component);
    bool comparatorRemoved = field_68->removeSource(pos, component);
    return baseRemoved || comparatorRemoved;
}

bool ComparatorCapacitor::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                    bool *a5) {
    if (trackingInfo->field_0.field_14 != Facing::DOWN && trackingInfo->field_0.field_14 != Facing::UP) {
        if (trackingInfo->field_0.field_14 != getDirection()) {
            bool connected;
            if (trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()]) {
                connected = true;
            } else {
                ComponentType componentType = trackingInfo->field_40.field_0->getInstanceType();
                connected = componentType == TYPE_TRANSPORTER || componentType == TYPE_REPEATER || componentType == TYPE_COMPARATOR;
            }
            if (connected) {
                if (trackingInfo->field_40.field_18 != TYPE_POWERED_BLOCK || trackingInfo->field_40.field_0->hasDirectPower()) {
                    trackPowerSourceDuplicates(trackingInfo, *a4, *a5);
                }
            }
        }
    }
    return false;
}

bool ComparatorCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                          bool *a4) {
    return trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[getDirection()];
}

bool ComparatorCapacitor::evaluate(CircuitSystem *system, const BlockPos *pos) {
    field_50 = field_34;
    if (field_54) {
        field_34 = std::max(GetRearStrength() - GetSideStrength(), 0);
    } else {
        field_34 = GetRearStrength();
        if (GetSideStrength() > field_34) {
            field_34 = 0;
        }
    }
    field_34 = std::min(field_34, 15);
    return field_50 != field_34;
}

void ComparatorCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    if (!field_60)
        return;

    field_58 = 0;
    field_5C = 0;

    for (auto &item : *field_8) {
        if (item.field_19) {
            int v18 = item.field_0->getStrength() - item.field_8;
            v18 = std::max(v18, 0);
            if (v18 > field_58)
                field_58 = v18;
        }
    }

    for (auto &item : *field_68) {
        int v12 = item.field_0->getStrength() - item.field_8;
        v12 = std::max(v12, 0);
        if (v12 > field_5C)
            field_5C = v12;
    }
}

void ComparatorCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    for (auto it = field_8->begin(); it != field_8->end();) {
        if (it->field_0->canStopPower()) {
            it = field_8->erase(it);
        } else {
            if (it->field_0->getDirection() == Facing::OPPOSITE_FACING[getDirection()]) {
                ++it;
            } else {
                BlockPos tmp = it->field_C;
                field_68->add(it->field_0, it->field_8, &tmp);
                it = field_8->erase(it);
            }
        }
    }
}

