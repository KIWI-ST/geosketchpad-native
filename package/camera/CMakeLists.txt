file(GLOB_RECURSE SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR} "*.h" "*.cpp" "*.hpp")

foreach(FILE ${SOURCEFILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    if("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(samples WIN32 ${SOURCEFILES})
add_library(camera STATIC ${SOURCEFILES})
set_target_properties(camera PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET camera PROPERTY FOLDER "package/")

# target_link_libraries(geosketchpad-native PUBLIC rci imgui)
# set_property(TARGET rci PROPERTY FOLDER "third_party/")