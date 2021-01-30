target_sources(Montage PRIVATE
    DurationProtocolController.h
    DurationProtocolController.cpp
)

target_include_directories(Montage
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
