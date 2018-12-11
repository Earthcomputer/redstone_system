//
// Created by Earthcomputer on 10/12/18.
//

#include "TransporterComponent.h"
#include "RepeaterCapacitor.h"
#include "PulseCapacitor.h"
#include "PoweredBlockComponent.h"
#include "ConsumerComponent.h"


bool sub_1F61EE0(CircuitSceneGraph *graph, const BlockPos *pos, Facing::Facing facing, bool a4) {
    ComponentType baseType = TYPE_NULL;
    BaseCircuitComponent *component = graph->getBaseComponent(pos);
    if (component) {
        baseType = component->getBaseType();
        if (component->getInstanceType() == TYPE_REPEATER) {
            auto *repeater = dynamic_cast<RepeaterCapacitor *>(component);
            Facing::Facing poweroutDir = repeater->getPoweroutDirection();
            return (poweroutDir == facing || facing == Facing::OPPOSITE_FACING[poweroutDir]) && a4;
        }
        if (component->getInstanceType() == TYPE_PULSE_CAPACITOR) {
            auto *pulseCapacitor = dynamic_cast<PulseCapacitor *>(component);
            return facing == Facing::OPPOSITE_FACING[pulseCapacitor->getPoweroutDirection()] && a4;
        }
    }

    if (baseType == TYPE_TRANSPORTER)
        return true;

    return (baseType == TYPE_PRODUCER || baseType == TYPE_CAPACITOR || baseType == TYPE_PISTON) && a4;
}

bool sub_1F61B00(CircuitSceneGraph *graph, const BlockPos *pos) {
    BlockPos above = *pos + Facing::DIRECTION[Facing::UP];
    BaseCircuitComponent *component = graph->getBaseComponent(&above);
    return component && component->canAllowPowerUp();
}

bool sub_1F61B80(CircuitSceneGraph *graph, const BlockPos *pos) {
    BlockPos below = *pos + Facing::DIRECTION[Facing::DOWN];
    BaseCircuitComponent *component = graph->getBaseComponent(&below);
    return component && component->canAllowPowerDown();
}

bool sub_1F61760(CircuitSceneGraph *graph, const BlockPos *pos, Facing::Facing facing) {
    BlockPos off = *pos + Facing::DIRECTION[facing];
    BlockPos offAbove = off + Facing::DIRECTION[Facing::UP];
    BlockPos offBelow = off + Facing::DIRECTION[Facing::DOWN];

    bool v6 = sub_1F61EE0(graph, &offBelow, facing, false);
    if (v6 && sub_1F61B00(graph, &offBelow))
        v6 = false;
    bool v5 = sub_1F61EE0(graph, &offAbove, facing, false);
    if (v5 && sub_1F61B00(graph, pos))
        v5 = false;

    return sub_1F61EE0(graph, &off, facing, true) || v5 || v6;
}

bool sub_1F618B0(CircuitSceneGraph *graph, const BlockPos *a2, const BlockPos *a3) {
    int v7 = 0;
    int v8 = 0;
    int v9 = 0;
    if (sub_1F61760(graph, a2, Facing::NORTH)) {
        if (a3->z != 0)
            v8++;
        v9++;
    }
    if (sub_1F61760(graph, a2, Facing::SOUTH)) {
        if (a3->z != 0)
            v8++;
        v9++;
    }
    if (sub_1F61760(graph, a2, Facing::EAST)) {
        if (a3->x != 0)
            v7++;
        v9++;
    }
    if (sub_1F61760(graph, a2, Facing::WEST)) {
        if (a3->x != 0)
            v7++;
        v9++;
    }

    return v9 == 1 && (v8 == 1 || v7 == 1);

}

bool sub_1F61A30(const CircuitTrackingInfo *trackingInfo) {
    switch (trackingInfo->field_60.field_18) {
        case TYPE_POWERED_BLOCK: {
            return dynamic_cast<PoweredBlockComponent *>(trackingInfo->field_60.field_0)->isPromotedToProducer();
        }
        case TYPE_CONSUMER: {
            return dynamic_cast<ConsumerComponent *>(trackingInfo->field_60.field_0)->isPromotedToProducer();
        }
        case TYPE_PRODUCER: {
            return true;
        }
        default: {
            return trackingInfo->field_60.field_0->getInstanceType() == TYPE_REDSTONE_TORCH;
        }
    }
}

bool TransporterComponent::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                     bool *a5) {
    ComponentType componentType = trackingInfo->field_40.field_18;
    if (componentType != TYPE_POWERED_BLOCK && componentType != TYPE_TRANSPORTER && componentType != TYPE_CONSUMER) {
        if (trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[trackingInfo->field_0.field_0->getDirection()]) {
            trackPowerSource(trackingInfo, *a4, *a5, false);
        }
    }
    return false;
}

bool TransporterComponent::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                           bool *a4) {
    if (trackingInfo->field_0.field_14 == Facing::UP) {
        return false;
    }
    if (trackingInfo->field_0.field_14 == Facing::DOWN) {
        return true;
    }
    if (trackingInfo->field_0.field_0->consumePowerAnyDirection()) {
        return true;
    }

    ComponentType componentType = trackingInfo->field_0.field_18;
    if (componentType == TYPE_TRANSPORTER) {
        BlockPos pos = trackingInfo->field_0.field_8 - trackingInfo->field_40.field_8;
        if (pos.y >= 0) {
            if (pos.y > 0 && sub_1F61B00(graph, &trackingInfo->field_40.field_8)) {
                return false;
            }
        } else {
            if (sub_1F61B00(graph, &trackingInfo->field_0.field_8)) {
                return false;
            }
            if (sub_1F61B80(graph, &trackingInfo->field_40.field_8)) {
                return false;
            }
        }
        return true;
    }

    BlockPos pos = trackingInfo->field_60.field_8 - trackingInfo->field_0.field_8;
    const BlockPos *v15 = &trackingInfo->field_40.field_8;
    if (pos.z == -2 || pos.z == 2) {
        bool v14 = !sub_1F61760(graph, v15, Facing::EAST)
                   && !sub_1F61760(graph, v15, Facing::WEST);
        return v14;
    } else if (pos.x == -2 || pos.x == 2) {
        bool v14 = !sub_1F61760(graph, v15, Facing::NORTH)
                   && !sub_1F61760(graph, v15, Facing::SOUTH);
        return v14;
    } else {
        if ((pos.y == 1 || pos.y == -1) && (pos.x != 0 || pos.z != 0)) {
            BlockPos tmp = trackingInfo->field_40.field_8 - trackingInfo->field_0.field_8;
            *a4 = sub_1F618B0(graph, v15, &tmp);
            return *a4;
        }
        if ((trackingInfo->field_0.field_18 == TYPE_POWERED_BLOCK ||
             trackingInfo->field_0.field_18 == TYPE_CONSUMER)
            && pos.y == 0 && pos.x != 0 && pos.z != 0) {
            BlockPos tmp = trackingInfo->field_40.field_8 - trackingInfo->field_0.field_8;
            *a4 = sub_1F618B0(graph, v15, &tmp);
            return *a4;
        }
        if (sub_1F61A30(trackingInfo)) {
            bool v14 = !sub_1F61760(graph, v15, Facing::NORTH)
                       && !sub_1F61760(graph, v15, Facing::SOUTH)
                       && !sub_1F61760(graph, v15, Facing::EAST)
                       && !sub_1F61760(graph, v15, Facing::WEST);
            if (v14) {
                *a4 = true;
            }
            return v14;
        }
    }

    return true;
}

bool TransporterComponent::evaluate(CircuitSystem *system, const BlockPos *pos) {
    bool ret = field_34 != field_3C;
    field_34 = field_3C;
    return ret;
}

void TransporterComponent::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    int v10 = 0;
    for (auto &item : *field_8) {
        int v6 = item.field_0->getStrength() - item.field_8;
        if (v6 < 0)
            v6 = 0;
        if (v10 < v6)
            v10 = v6;
    }
    field_3C = v10;
}

