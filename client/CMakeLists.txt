
ADD_LIBRARY(Client 
    Client.cpp
    model/User.cpp
    )
TARGET_LINK_LIBRARIES(Client PRIVATE Threads::Threads ${Boost_LIBRARIES})
