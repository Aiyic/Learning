cmake_minimum_required(VERSION 3.20)
project(proxy-asio CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# asio: header-only，仅下载不运行其 CMake（避免编译 asio 自带的 examples/tests）
FetchContent_Declare(asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-31-0
  GIT_SHALLOW TRUE
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
)
FetchContent_MakeAvailable(asio)

# spdlog: 结构化日志
FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1
  GIT_SHALLOW TRUE
)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_ENABLE_PIC ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

set(LIB_HEADERS
  src/lib/log/log.hpp
  src/lib/config/config.hpp
  src/lib/proto/frame.hpp
  src/lib/auth/auth.hpp
  src/lib/proxy/proxy.hpp
  src/lib/tunnel/pipe.hpp
)

set(COMMON_DEFS ASIO_STANDALONE ASIO_HAS_CO_AWAIT)
if(WIN32)
  list(APPEND COMMON_DEFS _WIN32_WINNT=0x0601)
endif()

# Windows 下 asio 走 Winsock，需链接 ws2_32 / mswsock
if(WIN32)
  set(WIN_LIBS ws2_32 mswsock)
else()
  set(WIN_LIBS)
endif()

add_executable(proxy_serve src/server/main.cpp ${LIB_HEADERS})
target_include_directories(proxy_serve PRIVATE src/lib ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(proxy_serve PRIVATE spdlog::spdlog ${WIN_LIBS})
target_compile_definitions(proxy_serve PRIVATE ${COMMON_DEFS})
target_compile_options(proxy_serve PRIVATE -Wall -Wextra -Wno-unused-parameter)

add_executable(proxy_client src/client/main.cpp ${LIB_HEADERS})
target_include_directories(proxy_client PRIVATE src/lib ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(proxy_client PRIVATE spdlog::spdlog ${WIN_LIBS})
target_compile_definitions(proxy_client PRIVATE ${COMMON_DEFS})
target_compile_options(proxy_client PRIVATE -Wall -Wextra -Wno-unused-parameter)
