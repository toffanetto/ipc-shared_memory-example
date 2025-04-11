cmake_minimum_required(VERSION 3.0)
project(ipc_shared_memory_example)

# Add the executable for the first source file
add_executable(sender src/sender.c)
target_compile_options(sender PRIVATE -g)

# Add the executable for the second source file
add_executable(receiver src/receiver.c)
target_compile_options(receiver PRIVATE -g)

