ADD_LIBRARY(Server
    Server.cpp
    Core.cpp
    model/Trader.cpp
    model/Order.cpp
)
TARGET_LINK_LIBRARIES(Server PRIVATE Threads::Threads ${Boost_LIBRARIES})
