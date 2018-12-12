//
// Created by Earthcomputer on 10/12/18.
//

#include "components/BaseCircuitComponent.h"
#include "CircuitTrackingInfo.h"

CircuitTrackingInfo::CircuitTrackingInfo(BaseCircuitComponent *component, BlockPos *pos, unsigned int a4) {
    field_84 = true;
    field_88 = 0;
    entry0.mPos = entry1.mPos = entry2.mPos = entry3.mPos = *pos;
    entry0.mComponent = entry1.mComponent = entry2.mComponent = entry3.mComponent = component;
    entry0.mComponentType = entry1.mComponentType = entry2.mComponentType = entry3.mComponentType = component->getInstanceType();
    entry0.mDirection = entry1.mDirection = entry2.mDirection = entry3.mDirection = component->getDirection();
    field_80 = a4;
    field_84 = true;
    field_88 = 0;
}
