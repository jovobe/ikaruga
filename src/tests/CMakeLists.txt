set(TEST_SOURCES
        FilesystemTest.cpp
        ../game/Filesystem.cpp
        )

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY} ${SDL2_MIXER_LIBRARY})
target_link_libraries(tests xml)
target_link_libraries(tests ${Boost_LIBRARIES})
target_link_libraries(tests ${IKARUGA_LIBS})
