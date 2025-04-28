#ifndef ipc_example__ipc_HPP_
#define ipc_example__ipc_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// IPC POSIX libraries
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>

#include <string>

#define PAYLOAD_SIZE 64

typedef struct shm_buf_
{
    uint32_t size;
    char string[PAYLOAD_SIZE];
} shm_buf_t;

namespace ipc
{
    class IpcExample : public rclcpp::Node
    {
    public:
        IpcExample();
        ~IpcExample();

    private:
        shm_buf_t *shm_buf = NULL;
        int shm_fd;
        size_t buf_size;
        sem_t *sem_shm;

        void msg_timer_callback();

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr msg_pub_;
        rclcpp::TimerBase::SharedPtr msg_timer_;
    };
} // namespace ipc
#endif // ipc_example__ipc_HPP_
