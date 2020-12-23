target_sources(Montage PRIVATE
    FigureGenerator.cpp
    FigureGenerator.h
    FigureParticleSelection.cpp
    FigureParticleSelection.h
    FigureProcessor.cpp
    FigureProcessor.h
)

target_include_directories(Montage
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(Tests PRIVATE
    FigureProcessor.cpp
    FigureProcessor.h
)

target_include_directories(Tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(NumberProtocolControllers)
