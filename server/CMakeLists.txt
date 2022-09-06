CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
PROJECT(Server)

ADD_EXECUTABLE(ServerApp 
    Server.cpp
    entities/Order.cpp
)
TARGET_LINK_LIBRARIES(ServerApp PRIVATE Threads::Threads ${Boost_LIBRARIES})