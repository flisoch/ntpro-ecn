
ADD_LIBRARY(Client 
    Client.cpp
    model/User.cpp
    )
TARGET_LINK_LIBRARIES(Client PRIVATE 
            Common
            Threads::Threads ${Boost_LIBRARIES}
    )
