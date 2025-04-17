#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fmt/format.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

int main(int argc, const char **argv)
{
    // 验证 glm
    glm::vec3 position = glm::vec3(15, 15, 15);
    float aspect = static_cast<float>(800) / static_cast<float>(600);
    float fov = glm::radians(60.0);
    glm::mat4x4  m4 = glm::perspective<float>(fov, aspect, 0.1, 1000);
    // fmt
    std::string fmt_str = fmt::format(
        R"(
            @group({0}) @binding({1}) var {2}: {3};
        )",
        m4[0].x,
        "fmt_string_test_buffer_0",
        m4[0].z,
        m4[0].y
    );
    
    std::cout << fmt_str << std::endl;
    // printf("heldasdafsdfaglo, wor12121ld!\n");
    return 1;
}
