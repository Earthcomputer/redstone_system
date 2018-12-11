//
// Created by Earthcomputer on 10/12/18.
//

#include "BaseRailTransporter.h"
#include "../Facing.h"

bool BaseRailTransporter::sub_1F60A40(const CircuitTrackingInfo *trackingInfo, int a3, int a4) {
    for (auto &it : *field_8) {
        if (it.field_C == trackingInfo->field_20.field_8) {
            return false;
        }
    }

    CircuitComponentList::Item item;
    item.field_8 = a3 - 1 < 0 ? 0 : a3 - 1;
    item.field_C = trackingInfo->field_20.field_8;
    item.field_18 = trackingInfo->field_0.field_14;
    item.field_19 = true;
    item.field_0 = trackingInfo->field_20.field_0;
    item.field_1C = a4 - 1 < 0 ? 0 : a4 - 1;
    field_8->push_back(&item);
    return true;
}

bool BaseRailTransporter::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                    bool *a5) {
    if (!*a5)
        return false;

    const BaseCircuitComponent *component = trackingInfo->field_40.field_0;
    auto oldSize = field_8->size();
    int v13 = 0;
    bool v19 = *a5;
    *a5 = true;
    switch (component->getInstanceType()) {
        case TYPE_RAIL_TRANSPORTER: {
            CircuitTrackingInfo trackingInfo1 = *trackingInfo;
            for (auto &item : *component->field_8) {
                if (item.field_1C - 1 > 0) {
                    BlockPos pos = item.field_C; // TODO: wat
                    int v18 = item.field_1C;
                    sub_1F60A40(&trackingInfo1, item.field_8 + 1, v18);
                    if (v18 > v13)
                        v13 = v18;
                }
            }
            return field_8->size() != oldSize;
        }
        case TYPE_POWERED_BLOCK: {
            return v19 && sub_1F60A40(trackingInfo, *a4, 10);
        }
        case TYPE_TRANSPORTER:
        default: {
            return sub_1F60A40(trackingInfo, *a4, 10);
        }
    }
}

bool BaseRailTransporter::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                          bool *a4) {
    if (trackingInfo->field_0.field_0->getInstanceType() != TYPE_RAIL_TRANSPORTER
            || field_3C != dynamic_cast<BaseRailTransporter *>(trackingInfo->field_0.field_0)->field_3C) {
        return false;
    }

    if (trackingInfo->field_0.field_0->getDirection() != field_38) {
        return false;
    }

    if (trackingInfo->field_0.field_14 == field_38) {
        return true;
    }

    return Facing::OPPOSTE_FACING[field_38] == trackingInfo->field_0.field_14;
}

bool BaseRailTransporter::evaluate(CircuitSystem *system, const BlockPos *pos) {
    int oldVal = field_34;

    for (auto &it : *field_8) {
        int v4 = it.field_1C;
        if (v4 > field_34 && it.field_0 && it.field_0->getStrength() - it.field_8 > 0) {
            field_34 = v4;
        }
    }

    return field_34 != oldVal;
}
