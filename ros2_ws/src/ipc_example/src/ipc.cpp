#include "ipc_example/ipc.hpp"

namespace ipc
{
    IpcExample::IpcExample() : Node("ipc_example")
    {
        msg_pub_ = this->create_publisher<std_msgs::msg::String>("/icp_msg", 1);
        msg_timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                             std::bind(&IpcExample::msg_timer_callback, this));

        shm_buf = NULL;
        shm_fd = -1;
        buf_size = sizeof(shm_buf_t);

        sem_shm = sem_open("/sem_shm", O_CREAT, 0644, 1);

        // Create shared memory resource
        shm_fd = shm_open("/shm_buf", O_RDWR | O_CREAT, 0644);

        // Allocate shared memory size
        ftruncate(shm_fd, buf_size);

        // Map the shared memory address in local process addressing
        shm_buf = (shm_buf_t *)mmap(0, buf_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    }

    IpcExample::~IpcExample()
    {
        // Cleaning semaphore stuff
        sem_post(sem_shm);
        sem_close(sem_shm);
        // sem_unlink("/sem_shm");

        // Cleaning shared memory stuff (deletes the shared section)
        // shm_unlink("/shm_buf");
    }

    void IpcExample::msg_timer_callback()
    {

        // Now we can access the shared memory segment directly from shm_buf
        // Trying to get the semaphore and waiting until it occurs
        if (sem_wait(sem_shm) == 0)
        {
            // Semaphore picked!

            std_msgs::msg::String msg;
            msg.data = std::string(shm_buf->string);
            RCLCPP_INFO(this->get_logger(), "Publishing IPC message");
            RCLCPP_INFO(this->get_logger(), shm_buf->string);
            msg_pub_->publish(msg);

            // Realaesing the semaphore
            sem_post(sem_shm);
        }
    }

} // namespace ipc
