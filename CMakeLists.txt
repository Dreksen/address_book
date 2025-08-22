cmake_minimum_required(VERSION 3.16)
project(address_book)

set(CMAKE_CXX_STANDARD 17)

set(SQLITE3_LIBRARY "/usr/lib64/libsqlite3.so")

add_executable(address_book
        main.cpp
        database.cpp
)

target_link_libraries(address_book PRIVATE ${SQLITE3_LIBRARY})
