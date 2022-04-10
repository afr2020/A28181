cmake_minimum_required(VERSION 3.6.2)
project(zilu_gb28181)

#头文件
include_directories(include)
include_directories(/usr/local/include)
include_directories(src)


#设置编译参数-ffunction-sections -fdata-sections
add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS " -Wall -std=c++11 -no-pie -DPOSIX -DDEBUG_")



# 设置可执行文件的输出路径(EXCUTABLE_OUTPUT_PATH是全局变量)
set(EXECUTABLE_OUTPUT_PATH ./)

#源文件
add_executable(zilu_gb28181
        src/main.cpp
        src/utils/tinyxml2.cpp
        src/utils/common.cpp
        src/utils/ptz/ptz_parser.cpp
        src/config_manager.cpp
        src/gb_service/sip_server.cpp
        src/gb_service/gb28181_svr_manager.cpp
        src/gb_service/event_handler/handler_manager.cpp
        src/gb_service/event_handler/register_handler.cpp
        src/gb_service/event_handler/message_handler.cpp
        src/gb_service/event_handler/subscribe_handler.cpp
        src/gb_service/event_handler/call_handler.cpp
        src/gb_service/event_handler/base_handler.cpp
        src/gb_service/manscdp/request_sender.cpp
        src/gb_service/manscdp/xml_parser.cpp
        src/gb_service/manscdp/xml_assembly.cpp
        src/gb_service/request_manager/request_manager.cpp
        src/gb_service/request_manager/base_request.cpp
        src/gb_service/request_manager/message_request.cpp
        src/gb_service/event_handler/sdp/sdp.cpp
        src/media_transpond/media_transpond.cpp
        src/media_transpond/session_manager.cpp
        src/Infra/mutex.cpp
        src/Infra/print_log.cpp
        src/Infra/thread.cpp
        src/Infra/thread_pool.cpp
        src/Infra/time.cpp
        src/Infra/timer.cpp
        )

#设置链接库
#link_directories(${PROJECT_SOURCE_DIR}/lib/m64x86/)
message("=================${PROJECT_SOURCE_DIR}")
#find_library(JSON_LIBRARY json HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)
#find_library(eXosip2_LIBRARY eXosip2 HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)
#find_library(osip2_LIBRARY osip2 HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)
#find_library(osipparser2_LIBRARY osipparser2 HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)
#find_library(StreamResolver_LIBRARY StreamResolver HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)
#find_library(yaml-cpp_LIBRARY yaml-cpp HINTS ${PROJECT_SOURCE_DIR}/lib/m64x86/)


link_directories(/usr/local/lib)

target_link_libraries(zilu_gb28181 pthread json eXosip2 osip2 osipparser2 uuid ssl crypto resolv StreamResolver yaml-cpp)
