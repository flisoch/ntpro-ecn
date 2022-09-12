include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(TARGET_SRC 
    maintest.cpp
    common/MessageTest.cpp
    common/OrderDtoTest.cpp
    server/RegistrationTest.cpp
    server/ShowBalanceTest.cpp
    server/TraderDaoTest.cpp
    server/OrderBookTest.cpp
    server/CoreTest.cpp
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
