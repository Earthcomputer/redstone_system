//
// Created by joseph on 10/12/18.
//

#include "components/BaseCircuitComponent.h"
#include "CircuitTrackingInfo.h"

CircuitTrackingInfo::CircuitTrackingInfo(BaseCircuitComponent *component, BlockPos *pos, unsigned int a4) {
    field_84 = true;
    field_88 = 0;
    field_0.field_8 = field_20.field_8 = field_40.field_8 = field_60.field_8 = *pos;
    field_0.field_0 = field_20.field_0 = field_40.field_0 = field_60.field_0 = component;
    field_0.field_18 = field_20.field_18 = field_40.field_18 = field_60.field_18 = component->getInstanceType();
    field_0.field_14 = field_20.field_14 = field_40.field_14 = field_60.field_14 = component->getDirection();
    field_80 = a4;
    field_84 = true;
    field_88 = 0;
}
