cmake_minimum_required(VERSION 3.0)
project(ipc_shared_memory_example)

find_package(Threads REQUIRED)


add_executable(sender src/sender.c)
target_link_libraries(sender PRIVATE Threads::Threads -lrt)
target_compile_options(sender PRIVATE -g)


add_executable(receiver src/receiver.c)
target_link_libraries(receiver PRIVATE Threads::Threads -lrt)
target_compile_options(receiver PRIVATE -g)


add_executable(clear_all src/clear_all.c)
target_link_libraries(clear_all PRIVATE Threads::Threads -lrt)
target_compile_options(clear_all PRIVATE -g)


add_executable(periodic_sender src/periodic_sender.c)
target_link_libraries(clear_all PRIVATE Threads::Threads -lrt)
target_compile_options(periodic_sender PRIVATE -g)
