FROM ros:humble-ros-core-jammy

WORKDIR /ros2_ws

COPY ros2_ws/ .

RUN apt update 

RUN apt install ros-dev-tools -y

RUN . "/opt/ros/$ROS_DISTRO/setup.sh" && \
    colcon build --symlink-install --cmake-args=-DCMAKE_BUILD_TYPE=Release

# Cleaning up
RUN apt remove ros-dev-tools -y

# setup entrypoint
COPY --chmod=755 ./ros_entrypoint.sh /

ENTRYPOINT ["/ros_entrypoint.sh"]