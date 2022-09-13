file(GLOB_RECURSE MICROGRAD_FILES  ./*.cpp)

add_library(${PROJECT_NAME} ${MICROGRAD_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ".")