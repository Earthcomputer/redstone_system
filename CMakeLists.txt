cmake_minimum_required(VERSION 3.12)
project(redstone_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(redstone_system
        BlockPos.h
        CircuitComponentList.h
        CircuitSceneGraph.h
        CircuitSystem.h
        CircuitTrackingInfo.cpp
        CircuitTrackingInfo.h
        components/BaseCircuitComponent.cpp
        components/BaseCircuitComponent.h
        components/BaseRailTransporter.cpp
        components/BaseRailTransporter.h
        components/CapacitorComponent.h
        components/ComparatorCapacitor.cpp
        components/ComparatorCapacitor.h
        components/ConsumerComponent.cpp
        components/ConsumerComponent.h
        components/PistonConsumer.cpp
        components/PistonConsumer.h
        components/PoweredBlockComponent.cpp
        components/PoweredBlockComponent.h
        components/ProducerComponent.cpp
        components/ProducerComponent.h
        components/PulseCapacitor.cpp
        components/PulseCapacitor.h
        components/RedstoneTorchCapacitor.cpp
        components/RedstoneTorchCapacitor.h
        components/RepeaterCapacitor.cpp
        components/RepeaterCapacitor.h
        components/TransporterComponent.cpp
        components/TransporterComponent.h
        Facing.h
        main.cpp components/ComponentType.h CircuitSceneGraph.cpp)