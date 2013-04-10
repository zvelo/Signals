SET(FLAGS "-Wall -W -fPIC -DCLD_WINDOWS -fvisibility=hidden")
SET(DEBUG_FLAGS "-Wall -W -O0 -g -fPIC -DCLD_WINDOWS ")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS} -Weffc++ -fvisibility-inlines-hidden ")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS} -Weffc++ -fvisibility-inlines-hidden ")
SET(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -Wl,--exclude-libs,ALL -Wl,--gc-sections")

ADD_EXECUTABLE(signals-example Example.cpp)
