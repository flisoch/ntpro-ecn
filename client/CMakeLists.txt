
ADD_LIBRARY(Client 
    Client.cpp
    model/User.cpp
    ${PROJECT_SOURCE_DIR}/include/Requests.hpp
    ${PROJECT_SOURCE_DIR}/include/json.hpp
    )
TARGET_LINK_LIBRARIES(Client PRIVATE Threads::Threads ${Boost_LIBRARIES})