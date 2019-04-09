cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(vtkdemo)
add_executable(vtkdemo main.cpp)

# Найдём VTK
find_package(VTK REQUIRED)

# Теперь можно выставить директории с header-ами
include_directories(${VTK_INCLUDE_DIR})

# И указать библиотеки для линковки
target_link_libraries(vtkdemo ${VTK_LIBRARIES})
