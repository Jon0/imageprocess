cmake_minimum_required(VERSION 2.8)

project( ImageProcess )

# use c++11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )

include_directories (${OpenCV_INCLUDE_DIR})

file(GLOB SRC_FILES
    "src/*.cpp"
)

# copy images to binary folder
file( COPY "${PROJECT_SOURCE_DIR}/images/" DESTINATION "${PROJECT_BINARY_DIR}/images/")

# make stuff
add_executable( ImageProcessMain ${SRC_FILES} )
target_link_libraries( ImageProcessMain ${OpenCV_LIBS} )
