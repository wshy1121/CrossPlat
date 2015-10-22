#@note   Hikvision Digital Technology Co., Ltd. All Rights Reserved.
#@brief  CMake子目录配置文件
#@author Yaopei
#@date   2015/7/31
#@note   the CMakeLists.txt for src. directory


PROJECT(HMSProxy)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -fPIC -O0")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O2 -Wall -fPIC")
endif()

SET(SRC_SRCS
  thread_base.cpp
  string_base.cpp
  platform_base.cpp
  mem_base.cpp
  link_tool.cpp
  socket_base.cpp
  defs.cpp
)

# shared library
#ADD_LIBRARY(CrossPlat SHARED ${SRC_SRCS} )

#static library
ADD_LIBRARY(CrossPlat STATIC ${SRC_SRCS})

# link library
#TARGET_LINK_LIBRARIES(CrossPlat)

# clean
SET_TARGET_PROPERTIES(CrossPlat PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(Decoder_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
