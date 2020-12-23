target_sources(Montage PRIVATE
    AdjacentStepsProtocolController.cpp
    AdjacentStepsProtocolController.h
    BasicProtocolController.cpp
    BasicProtocolController.h
)

target_include_directories(Montage
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
