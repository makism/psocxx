add_executable(DeJong DeJong.cpp camera.cpp)
target_link_libraries(DeJong PSOCXX  ${GLUT_LIBRARY} ${OPENGL_LIBRARY})
