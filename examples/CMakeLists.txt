add_executable(test Test.cpp)
target_link_libraries(test PSOCXX  ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
