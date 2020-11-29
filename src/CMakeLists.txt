# Generic test that uses conan libs
add_executable(aoc2020 main.cpp)
target_link_libraries(
  aoc2020
  PRIVATE project_options
          project_warnings
          CONAN_PKG::fmt
          CONAN_PKG::spdlog
          CONAN_PKG::ms-gsl
          CONAN_PKG::range-v3)
