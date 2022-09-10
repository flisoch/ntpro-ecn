ADD_LIBRARY(Server
    Server.cpp
    Core.cpp
    model/Trader.cpp
    model/Order.cpp
    model/Limit.cpp
    model/LimitTree.cpp
    model/LimitOrderBook.cpp
    dao/MemoryOrderDao.cpp
    dao/MemoryTraderDao.cpp
)
TARGET_LINK_LIBRARIES(Server PRIVATE 
                Common
                Threads::Threads ${Boost_LIBRARIES}
                )
