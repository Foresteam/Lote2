cmake_minimum_required(VERSION 3.0.0)
project(Lote2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(--std=gnu++20 -pthread)
# add_executable(Lote2 main.cpp)
add_executable(Lote2
    src/main.cpp
    src/Runtime.h
    src/Runtime.cpp
    src/Scope/Module.h
    src/Scope/Module.cpp
    src/Scope/Scope.h
    src/Scope/Scope.cpp
    src/Operator/Operator.h
    src/Operator/Operator.cpp
    src/Object/Function/CFunction.h
    src/Object/Function/CFunction.cpp
    src/Object/Function/Function.h
    src/Object/Function/Function.cpp
    src/Object/Pointer/Pointer.h
    src/Object/Pointer/Pointer.cpp
    src/Object/Object.h
    src/Object/Object.cpp
    src/Lib/Stack/Stack.h
    src/Lib/Stack/Stack.cpp
    src/Lib/Utils.h
    src/Lib/Utils.cpp
    src/Exceptions/Exception.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Lote2 PRIVATE Threads::Threads)
include(CPack)
