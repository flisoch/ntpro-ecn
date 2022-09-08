include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(TARGET_SRC 
    maintest.cpp
    server/Message.cpp
    server/Registration.cpp
    server/ShowBalance.cpp
    )
add_executable( tests ${TARGET_SRC} )

target_link_libraries(tests PRIVATE
                        gtest 
                        gmock
                        gtest_main 
                        Server
                        Client
                        )
gtest_discover_tests(tests)
