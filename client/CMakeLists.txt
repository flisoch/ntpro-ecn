
ADD_EXECUTABLE(ClientAppCLI 
    Client.cpp
    Application.cpp
    model/User.cpp
    ${PROJECT_SOURCE_DIR}/include/Requests.hpp
    ${PROJECT_SOURCE_DIR}/include/json.hpp
    )
TARGET_LINK_LIBRARIES(ClientAppCLI PRIVATE Threads::Threads ${Boost_LIBRARIES})