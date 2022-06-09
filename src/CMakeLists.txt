add_executable(DroneControl)

set(imgui_dir "${CMAKE_BINARY_DIR}/_deps/imgui-src/")

file(
    GLOB DroneControl_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${imgui_dir}/imgui*.cpp"
    "${imgui_dir}/backends/imgui_impl_sdl.cpp"
    "${imgui_dir}/backends/imgui_impl_opengl3.cpp"
)

target_sources(
    DroneControl PRIVATE
    ${DroneControl_SOURCES}
)

message(STATUS "OpenGL Library: ${OPENGL_opengl_LIBRARY}")

target_link_libraries(DroneControl PRIVATE SDL2::SDL2 OpenGL::GL libserialport::libserialport)
target_include_directories(DroneControl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${imgui_dir} ${imgui_dir}/backends)