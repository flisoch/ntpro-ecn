CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
PROJECT(exchange VERSION 0.1.0)
SET(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(Boost 1.40 COMPONENTS system REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET (PATH_INCLUDE 
    "${PROJECT_SOURCE_DIR}/common"
    "${PROJECT_SOURCE_DIR}/client"
    "${PROJECT_SOURCE_DIR}/server"
    "${PROJECT_SOURCE_DIR}/server/dao"
    "${PROJECT_SOURCE_DIR}/server/model"
)
INCLUDE_DIRECTORIES(${PATH_INCLUDE})

ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(server)
ADD_SUBDIRECTORY(client)
ADD_SUBDIRECTORY(app)
ADD_SUBDIRECTORY(googletest)
ADD_SUBDIRECTORY(test)
