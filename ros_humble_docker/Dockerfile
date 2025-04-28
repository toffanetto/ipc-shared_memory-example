FROM ros:humble-ros-core-jammy

WORKDIR /ros2_ws

COPY ros2_ws/ .

RUN apt update 

RUN apt install ros-dev-tools -y

RUN colcon build --symlink-install --cmake-args=-DCMAKE_BUILD_TYPE=Release

# Cleaning up
# RUN apt remove ros-dev-tool -y

# setup entrypoint
COPY ./ros_entrypoint.sh /

ENTRYPOINT ["/ros_entrypoint.sh"]