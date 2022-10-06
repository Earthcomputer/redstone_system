//
// Created by Earthcomputer on 10/12/18.
//

#include "BaseRailTransporter.h"
#include "../Facing.h"

bool BaseRailTransporter::sub_1F60A40(const CircuitTrackingInfo *trackingInfo, int a3, int a4) {
    for (auto &item : *mDependencies) {
        if (item.mPos == trackingInfo->entry1.mPos) {
            return false;
        }
    }

    CircuitComponentList::Item item;
    item.field_8 = a3 - 1 < 0 ? 0 : a3 - 1;
    item.mPos = trackingInfo->entry1.mPos;
    item.mDirection = trackingInfo->entry0.mDirection;
    item.field_19 = true;
    item.mComponent = trackingInfo->entry1.mComponent;
    item.field_1C = a4 - 1 < 0 ? 0 : a4 - 1;
    mDependencies->push_back(&item);
    return true;
}

bool BaseRailTransporter::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                    bool *a5) {
    if (!*a5)
        return false;

    const BaseCircuitComponent *component = trackingInfo->entry2.mComponent;
    auto oldSize = mDependencies->size();
    int v13 = 0;
    bool v19 = *a5;
    *a5 = true;
    switch (component->getInstanceType()) {
        case TYPE_RAIL_TRANSPORTER: {
            CircuitTrackingInfo trackingInfo1 = *trackingInfo;
            for (auto &item : *component->mDependencies) {
                if (item.field_1C - 1 > 0) {
                    BlockPos pos = item.mPos; // TODO: wat
                    int v18 = item.field_1C;
                    sub_1F60A40(&trackingInfo1, item.field_8 + 1, v18);
                    if (v18 > v13)
                        v13 = v18;
                }
            }
            return mDependencies->size() != oldSize;
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
    if (trackingInfo->entry0.mComponent->getInstanceType() != TYPE_RAIL_TRANSPORTER
            || mRailType != dynamic_cast<BaseRailTransporter *>(trackingInfo->entry0.mComponent)->mRailType) {
        return false;
    }

    if (trackingInfo->entry0.mComponent->getDirection() != mDirection) {
        return false;
    }

    if (trackingInfo->entry0.mDirection == mDirection) {
        return true;
    }

    return Facing::OPPOSITE_FACING[mDirection] == trackingInfo->entry0.mDirection;
}

bool BaseRailTransporter::evaluate(CircuitSystem *system, const BlockPos *pos) {
    int oldVal = mStrength;

    for (auto &item : *mDependencies) {
        int v4 = item.field_1C;
        if (v4 > mStrength && item.mComponent && item.mComponent->getStrength() - item.field_8 > 0) {
            mStrength = v4;
        }
    }

    return mStrength != oldVal;
}
