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
    field_3A = true;
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
