#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE (1 * 1024 * 1024 * 1024) // 1 GB

void file_path(const char *src_path, const char *dest_path) {
    int ret,src_fd, dest_fd;
    struct stat st;
    void *src, *dest;

    src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0)
	{
        perror("open() error...!");
        _exit(1);
    }

	ret = fstat(src_fd, &st);
    if (ret < 0)
	{
        perror("fstat error...!");
        close(src_fd);
        _exit(1);
    }

    if (st.st_size > MAX_FILE_SIZE)
	{
        fprintf(stderr, "max allowed size of 1 GB\n");
        close(src_fd);
        _exit(1);
    }

    src = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src == MAP_FAILED)
	{
        perror("mmap() error");
        close(src_fd);
        _exit(1);
    }

    dest_fd = open(dest_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0)
	{
        perror("open() error");
        munmap(src, st.st_size);
        close(src_fd);
        _exit(1);
    }

    if (ftruncate(dest_fd, st.st_size) == -1)
	{
        perror("Error setting destination file size");
        munmap(src, st.st_size);
        close(src_fd);
        close(dest_fd);
        _exit(1);
    }

    dest = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, dest_fd, 0);
    if (dest == MAP_FAILED)
	{
        perror("mmap() error");
        munmap(src, st.st_size);
        close(src_fd);
        close(dest_fd);
        _exit(1);
    }

    memcpy(dest, src, st.st_size);

    munmap(src, st.st_size);
    munmap(dest, st.st_size);
    close(src_fd);
    close(dest_fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
	{
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    file_path(argv[1], argv[2]);

    printf("File copied successfully from %s to %s\n", argv[1], argv[2]);

    return EXIT_SUCCESS;
}

