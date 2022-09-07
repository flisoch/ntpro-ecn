ADD_EXECUTABLE(ServerApp 
    Server.cpp
    Core.cpp
    Application.cpp
    entities/Trader.cpp
    entities/Order.cpp
)
TARGET_LINK_LIBRARIES(ServerApp PRIVATE Threads::Threads ${Boost_LIBRARIES})