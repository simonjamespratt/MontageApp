target_sources(Montage PRIVATE
    AdjacentStepsProtocolController.cpp
    AdjacentStepsProtocolController.h
    BasicProtocolController.cpp
    BasicProtocolController.h
    CycleProtocolController.cpp
    CycleProtocolController.h
    NumberProtocolController.h
    NumberProtocolController.cpp
)

target_include_directories(Montage
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
