add_executable(DeJong DeJong.cpp)
target_link_libraries(DeJong PSOCXX  ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
