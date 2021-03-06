file(GLOB SRC_FILES
    "*.cpp"
)

file(GLOB INC_FILES
    "*.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${INC_FILES})
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE project_options
          project_warnings
          CONAN_PKG::fmt
          CONAN_PKG::spdlog
          CONAN_PKG::ms-gsl
          CONAN_PKG::range-v3)

add_executable(${PROJECT_NAME}_main main.cpp)
target_link_libraries(
  ${PROJECT_NAME}_main
  PRIVATE project_options
          project_warnings
          ${PROJECT_NAME}
          CONAN_PKG::fmt
          CONAN_PKG::spdlog
          CONAN_PKG::ms-gsl
          CONAN_PKG::range-v3)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/input
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/../)

