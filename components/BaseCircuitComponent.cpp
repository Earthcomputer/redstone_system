//
// Created by Earthcomputer on 10/12/18.
//

#include "BaseCircuitComponent.h"

BaseCircuitComponent::BaseCircuitComponent() {
    mDependencies = new CircuitComponentList;
    field_20 = false;
    field_21 = true;
    field_22 = false;
    // field_24
    field_30 = true;
    mStrength = 0;
    mDirection = Facing::NONE;
    mAllowPowerUp = false;
    mAllowPowerDown = true;
}

BaseCircuitComponent::~BaseCircuitComponent() {
    delete mDependencies;
}

bool BaseCircuitComponent::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    bool removedAny = false;
    for (auto it = mDependencies->begin(); it != mDependencies->end();) {
        if (it->mPos == *pos) {
            it = mDependencies->erase(it);
            removedAny = true;
        } else {
            ++it;
        }
    }
    return removedAny;
}

bool BaseCircuitComponent::hasSource(BaseCircuitComponent *component) {
    if (mDependencies->size() <= 0)
        return false;

    for (auto &item : *mDependencies) {
        BaseCircuitComponent *comp = item.mComponent;
        if (comp) {
            if (comp == component) {
                return true;
            }
            if (comp->hasChildrenSource()) {
                //e = component; FIXME
                if (comp->hasSource(component)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool BaseCircuitComponent::trackPowerSource(const CircuitTrackingInfo *trackingInfo, int a3, bool a4, bool a5) {
    for (auto &item : *mDependencies) {
        if (item.mPos == trackingInfo->entry1.mPos) {
            if (item.field_19 || a4) {
                if (item.field_8 - 1 <= trackingInfo->field_80 - 1) {
                    return false;
                } else {
                    if (trackingInfo->field_80 - 1 >= 0) {
                        item.field_8 = trackingInfo->field_80 - 1;
                    } else {
                        item.field_8 = 0;
                    }
                    return true;
                }
            } else {
                item.field_19 = true;
                if (trackingInfo->entry1.mComponent && trackingInfo->entry1.mComponent->getStrength() - (trackingInfo->field_80 - 1) <= 0) {
                    item.field_8 = std::max(std::min(item.field_8, trackingInfo->field_80 - 1), 0);
                    return true;
                } else {
                    if (trackingInfo->field_80 - 1 >= 0) {
                        item.field_8 = trackingInfo->field_80 - 1;
                    } else {
                        item.field_8 = 0;
                    }
                    return true;
                }
            }
        }
    }

    CircuitComponentList::Item item;
    item.field_8 = a3 - 1 >= 0 ? a3 - 1 : 0;
    item.mPos = trackingInfo->entry1.mPos;
    item.mDirection = trackingInfo->entry1.mDirection;
    item.field_19 = a4;
    item.mComponent = trackingInfo->entry1.mComponent;
    item.field_1C = a5 ? 1 : 0; // TODO: this correct?
    mDependencies->push_back(&item);
    return true;
}

bool BaseCircuitComponent::trackPowerSourceDuplicates(const CircuitTrackingInfo *trackingInfo, int a3, bool a4) {
    for (auto &item : *mDependencies) {
        if (item.mPos == trackingInfo->entry1.mPos) {
            if (item.field_19 || a4) {
                if (item.field_8 - 1 <= trackingInfo->field_80 - 1) {
                    return false;
                } else {
                    if (trackingInfo->field_80 - 1 >= 0) {
                        item.field_8 = trackingInfo->field_80 - 1;
                    } else {
                        item.field_8 = 0;
                    }
                    return true;
                }
            } else {
                item.field_19 = true;
                if (trackingInfo->field_80 - 1 >= 0) {
                    item.field_8 = trackingInfo->field_80 - 1;
                } else {
                    item.field_8 = 0;
                }
                return true;
            }
        }
    }

    CircuitComponentList::Item item;
    item.field_8 = a3 - 1 >= 0 ? a3 - 1 : 0;
    item.mPos = trackingInfo->entry1.mPos;
    item.mDirection = trackingInfo->entry1.mDirection;
    item.field_19 = a4;
    item.mComponent = trackingInfo->entry1.mComponent;
    mDependencies->push_back(&item);
    return true;
}

bool BaseCircuitComponent::hasDirectPower() {
    for (auto &item : *mDependencies) {
        if (item.field_19) {
            return true;
        }
    }
    return false;
}
