cmake_minimum_required(VERSION 3.10)

project(PyEmbedd C CXX)

add_executable(PyEmbedd main.cpp)

find_package(Python COMPONENTS Interpreter Development)

message("Python_FOUND:${Python_FOUND}")
message("Python_VERSION:${Python_VERSION}")
message("Python_Development_FOUND:${Python_Development_FOUND}")
message("Python_LIBRARIES:${Python_LIBRARIES}")


find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon ${Python_LIBRARIES} -lpython3.8)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)


#target_link_libraries(PyEmbedd ${Python_LIBRARIES} -lpython3.8)

target_include_directories(PyEmbedd PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/PyLib/python3.8/")

target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC}
               )

