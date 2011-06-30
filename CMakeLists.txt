cmake_minimum_required (VERSION 2.6) 
project (psocxx)
set(CMAKE_BUILD_TYPE "Debug")


option(BUILD_EXAMPLES "Build examples" ON)
message(STATUS "Build examples: " ${BUILD_EXAMPLES})


find_package(Boost)

if(BUILD_EXAMPLES)
    find_package(OpenGL)
    find_package(GLUT)
endif(BUILD_EXAMPLES)

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

if(BUILD_EXAMPLES)
    add_subdirectory(examples/)
endif(BUILD_EXAMPLES)