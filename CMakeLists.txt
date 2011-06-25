cmake_minimum_required (VERSION 2.6) 
project (psocxx)
set(CMAKE_BUILD_TYPE "Debug")

include_directories (${psocxx_SOURCE_DIR}/
                        ${psocxx_SOURCE_DIR}/headers)

set(source_files
    helpers/Random.cpp
    src/Vector.cpp
    src/Particle.cpp
    src/Swarm.cpp
)

add_library (PSOCXX ${LIB_TYPE} ${source_files})
set_target_properties(PSOCXX PROPERTIES VERSION 0.9.999 SOVERSION 1)
target_link_libraries(PSOCXX ${LIBS})

add_subdirectory(examples/)
