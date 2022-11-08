# Build library
add_library(xml SHARED XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})
