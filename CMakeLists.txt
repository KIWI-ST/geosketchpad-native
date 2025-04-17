cmake_minimum_required(VERSION 3.8)

# set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(PROJECT_NAME "GeoSketchpadNative")

project(${PROJECT_NAME})

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/fetch_fmt.cmake)
include(cmake/fetch_glm.cmake)

add_subdirectory(engine)

# if(WIN32)

#     add_definitions(-D __WIN32__)

#     add_subdirectory(package/camera)

#     # add imgui library
#     set(IMGUI_DIR "third_party/imgui")
#     include_directories(${IMGUI_DIR})
#     add_library(imgui STATIC
#     ${IMGUI_DIR}/backends/imgui_impl_wgpu.h
#     ${IMGUI_DIR}/backends/imgui_impl_wgpu.cpp
#     ${IMGUI_DIR}/backends/imgui_impl_glfw.h
#     ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
#     ${IMGUI_DIR}/misc/cpp/imgui_stdlib.h
#     ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
#     ${IMGUI_DIR}/imconfig.h
#     ${IMGUI_DIR}/imgui.h
#     ${IMGUI_DIR}/imgui.cpp
#     ${IMGUI_DIR}/imgui_draw.cpp
#     ${IMGUI_DIR}/imgui_internal.h
#     ${IMGUI_DIR}/imgui_tables.cpp
#     ${IMGUI_DIR}/imgui_widgets.cpp
#     ${IMGUI_DIR}/imstb_rectpack.h
#     ${IMGUI_DIR}/imstb_textedit.h
#     ${IMGUI_DIR}/imstb_truetype.h
#     )
#     target_link_libraries(imgui PUBLIC rci glfw camera)

#     add_subdirectory(platform/windows)
#     set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT geosketchpad-native)

# elseif(APPLE AND IOS)
#     # add_definitions(-D __IOS__)
#     # add_subdirectory(src)
# endif()

