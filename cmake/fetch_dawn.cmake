include(FetchContent)
FetchContent_Declare(
  dawn
  GIT_REPOSITORY https://dawn.googlesource.com/dawn
  GIT_TAG chromium/6990
  GIT_SHALLOW TRUE
)

set(DAWN_FETCH_DEPENDENCIES ON)

FetchContent_MakeAvailable(dawn)

# add_subdirectory(${dawn_SOURCE_DIR} ${dawn_BINARY_DIR})
# add_library(webgpu INTERFACE)
# target_link_libraries(webgpu INTERFACE webgpu_dawn)
# set(DAWN_FETCH_DEPENDENCIES ON)
# target_include_directories(dawn_utils PUBLIC ${CMAKE_BINARY_DIR}/_deps/dawn-src/src)
# add_library(webgpu INTERFACE)
# target_link_libraries(webgpu INTERFACE webgpu_dawn)
# target_include_directories(webgpu INTERFACE ${CMAKE_BINARY_DIR}/_deps/dawn-src/include)