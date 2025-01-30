cmake_minimum_required(VERSION 3.26)
project(DigitalAudioWorkstation)

# 啟用 C++23 支援
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 檔案清單
file(GLOB SRC_FILES
    src/*.cpp
    src/audio/*.cpp
    src/gui/*.cpp
    src/utils/*.cpp
)

file(GLOB HEADER_FILES
    include/*.h
    include/audio/*.h
    include/gui/*.h
    include/utils/*.h
)

# 引入外部庫
add_subdirectory(external/imgui)
add_subdirectory(external/portaudio)

# 編譯執行檔
add_executable(daw ${SRC_FILES} ${HEADER_FILES})

# 連結庫
target_link_libraries(daw PRIVATE portaudio imgui OpenGL glfw pthread)
target_include_directories(daw PRIVATE include)
