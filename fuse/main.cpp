#define FUSE_USE_VERSION 35

#include <iostream>
#include <fuse3/fuse.h>
#include <cstring>

int getattr(const char *path, struct stat *stat, struct fuse_file_info *fi) {
    auto constexpr REGULAR_FILE = S_IFREG;
    auto constexpr FOLDER = S_IFDIR;

    if (strcmp(path, "/") == 0) {
        auto filetype = FOLDER;
        auto permissions = 0777;
        stat->st_mode = filetype | permissions;
        stat->st_nlink = 2;
        stat->st_uid = 0;
        stat->st_gid = 0;
        stat->st_size = 0;
        stat->st_blocks = 0;
        stat->st_atime = time(nullptr);

        return 0;
    }

    if (strcmp(path, "/file") == 0) {
        const std::string contents = "Hello, world!";

        auto filetype = REGULAR_FILE;
        auto permissions = 0777;
        stat->st_mode = filetype | permissions;
        stat->st_nlink = 1;
        stat->st_size = contents.size();

        return 0;
    }

    if (strcmp(path, "/ファイル") == 0) {
        const std::string contents = "ハロー・ワールド";

        auto filetype = REGULAR_FILE;
        auto permissions = 0777;
        stat->st_mode = filetype | permissions;
        stat->st_nlink = 1;
        stat->st_size = contents.size();

        return 0;
    }

    return -ENOENT;
}

int read(const char *path, char *buffer, size_t count, off_t offset, struct fuse_file_info *fi) {
    if (strcmp(path, "/file") == 0) {
        const std::string contents = "Hello, world!";

        int readBytes = 0;
        for (int i = offset; i < contents.size(); ++i) {
            if (readBytes == count) {
                return readBytes;
            }
            buffer[readBytes] = contents[i];
            readBytes += 1;
        }
        return readBytes;
    }

    if (strcmp(path, "/ファイル") == 0) {
        const std::string contents = "ハロー・ワールド";

        int readBytes = 0;
        for (int i = offset; i < contents.size(); ++i) {
            if (readBytes == count) {
                return readBytes;
            }
            buffer[readBytes] = contents[i];
            readBytes += 1;
        }
        return readBytes;
    }

    return -ENOENT;
}

int readdir(
        const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags
) {
    if (strcmp(path, "/") == 0) {
        if (offset == 0) {
            if (filler(buffer, ".", nullptr, 1, {})) return 0;
        }

        if (offset == 1) {
            if (filler(buffer, "..", nullptr, 2, {})) return 0;
        }

        if (offset == 2) {
            if (filler(buffer, "file", nullptr, 3, {})) return 0;
        }

        if (offset == 3) {
            if (filler(buffer, "ファイル", nullptr, 4, {})) return 0;
        }

        return 0;
    }

    return -ENOENT;
}


static const struct fuse_operations shrine_fuse_operations = {
        .getattr = getattr,
//        .open = open,
//        .create = create,
        .read = read,
        .readdir = readdir,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &shrine_fuse_operations, nullptr);
}