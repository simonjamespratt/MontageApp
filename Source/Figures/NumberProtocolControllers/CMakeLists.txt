target_sources(Montage PRIVATE
    AdjacentStepsProtocolController.cpp
    AdjacentStepsProtocolController.h
    BasicProtocolController.cpp
    BasicProtocolController.h
    CycleProtocolController.cpp
    CycleProtocolController.h
    ProtocolControllerBroadcaster.h
    ProtocolControllerBroadcaster.cpp
    ProtocolControllerListener.h
)

target_include_directories(Montage
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
