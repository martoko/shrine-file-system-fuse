#include <vector>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <unistd.h>

int makeFileSystem(const std::string &device_path);

bool isValidDevice(const std::string &device_path);

int main(int argument_count, char *argument_values[]) {
    std::vector<std::string> arguments(argument_values, argument_values + argument_count);

    if (arguments.size() != 1) {
        std::cout << "Usage: mkfs.shrine device" << std::endl;
        return 1;
    }

    std::string device_path = arguments[0];
    if (!isValidDevice(device_path)) return 1;
    return makeFileSystem(device_path);
}

bool isValidDevice(const std::string &device_path) {
    struct stat stat_information{};
    if (stat(device_path.c_str(), &stat_information) != 0) throw std::runtime_error("Failed to stat block device");

    if (!S_ISBLK(stat_information.st_mode)) {
        std::cout << "Refusing to make file system on non-block device" << std::endl;
        return false;
    }

    if (device_path != "/dev/sde") {
        std::cout << "Refusing to make file system on a device that is not /dev/sde" << std::endl;
        return false;
    }

    int file = open(device_path.c_str(), O_NONBLOCK);
    if (file == -1) throw std::runtime_error("Failed to open block device");

    try {
        uint64_t file_size_in_bytes;
        if (ioctl(file, BLKGETSIZE64, &file_size_in_bytes) == 1) throw std::runtime_error("Failed to read size of block device");

        if (file_size_in_bytes > 8242855936) {
            std::cout << "Refusing to make file system on a device that is larger than 7.7 GiB" << std::endl;
            if (close(file) != 0)  throw std::runtime_error("Failed to close block device");
            return false;
        }
    } catch (const std::runtime_error &error) {
        if (close(file) != 0)  throw std::runtime_error("Failed to close block device");
        throw error;
    }

    if (close(file) != 0)  throw std::runtime_error("Failed to close block device");

    return true;
}

int makeFileSystem(const std::string &device_path) {
    return 0;
}
