ADD_EXECUTABLE(ClientApp Application.cpp)
TARGET_LINK_LIBRARIES(ClientApp PRIVATE
            Client
            Threads::Threads ${Boost_LIBRARIES}
)
