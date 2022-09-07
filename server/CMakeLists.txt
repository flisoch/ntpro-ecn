ADD_LIBRARY(Server
    Server.cpp
    Core.cpp
    entities/Trader.cpp
    entities/Order.cpp
)
TARGET_LINK_LIBRARIES(Server PRIVATE Threads::Threads ${Boost_LIBRARIES})