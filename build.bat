set http_proxy=http://127.0.0.1:1080
set https_proxy=http://127.0.0.1:1080

git config --global http.sslverify "false"
git submodule init
git submodule update
git submodule foreach "git checkout $(git config -f $toplevel/.gitmodules submodule.$name.branch)"

cd third_party/rci
call build.bat
cd ../..

cmake -B build -S .	^
    -D CMAKE_BUILD_TYPE=Debug                     ^
    -D CMAKE_POLICY_DEFAULT_CMP0091=NEW             ^
    -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded     ^
    -D BUILD_SHARED_LIBS=OFF                        ^
    -D BUILD_SAMPLES=OFF                            ^
    -D DAWN_ENABLE_D3D12=ON                         ^
    -D DAWN_ENABLE_D3D11=OFF                        ^
    -D DAWN_ENABLE_NULL=OFF                         ^
    -D DAWN_ENABLE_DESKTOP_GL=OFF                   ^
    -D DAWN_ENABLE_OPENGLES=OFF                     ^
    -D DAWN_ENABLE_VULKAN=OFF                       ^
    -D DAWN_BUILD_SAMPLES=OFF                       ^
    -D TINT_BUILD_TESTS=OFF                         ^
    -D GLFW_BUILD_EXAMPLES=OFF                      ^
    -D GLFW_BUILD_EXAMPLES=OFF  ^
    -D GLFW_BUILD_TESTS=OFF     ^
    -D GLFW_BUILD_DOCS=OFF      ^
    || exit /b 1

