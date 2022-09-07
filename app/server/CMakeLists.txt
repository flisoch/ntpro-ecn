ADD_EXECUTABLE(ServerApp Application.cpp)
TARGET_LINK_LIBRARIES(ServerApp PRIVATE Server Threads::Threads ${Boost_LIBRARIES})