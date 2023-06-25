/**
 * Implement a minimal clone of the `ls` program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024
#define NAME_MAX 14


struct flags {
    int long_list;
    int list_all;
};

struct flags *make_flags() {
    struct flags *temp = malloc(sizeof(struct flags));
    temp->long_list = 0;
    temp->list_all = 0;
    return temp;
}

void ls_clone(char *, struct flags *ls_flags);
void handle_directory(char *, struct flags *, void (*fcn)(char *, struct flags *));
void print_file(struct stat *, char *, struct flags *);

int main(int argc, char *argv[]) {
    struct flags *ls_flags = make_flags();

    for (int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'a':
                    ls_flags->list_all = 1;
                    break;
                case 'l':
                    ls_flags->long_list = 1;
                default:
                    break;
            }
        }
    }

    ls_clone(".", ls_flags);

    return 0;
}

void ls_clone(char *file, struct flags *ls_flags) {

    // Define a stuct stat buffer
    struct stat statbuffer;

    // Attempt to call `stat()` and populate the buffer struct
    if (stat(file, &statbuffer) == -1) {
        fprintf(stderr, "ls_clone: can't access %s\n", file);
        return;
    }

    // Check if this file is a directory
    if ((statbuffer.st_mode & S_IFMT) == S_IFDIR) {
        if (strcmp(file, ".") == 0) {
            handle_directory(file, ls_flags, ls_clone);
        } else {
            print_file(&statbuffer, file, ls_flags);
        }
    } else {
        print_file(&statbuffer, file, ls_flags);
    }
}

void print_file(struct stat *statbuffer, char *name, struct flags *ls_flags) {

    if (ls_flags->list_all == 0 && name[0] == '.') {
        return;
    }

    if (ls_flags->long_list == 1) {
        char file_type;
        switch (statbuffer->st_mode & S_IFMT) {
            case S_IFDIR:
                file_type = 'd';
                break;
            case S_IFREG:
                file_type = '-';
                break;
            case S_IFLNK:
                file_type = 'l';
                break;
            default:
                file_type = '-';
                break;
        }

        char perms[10];
        perms[0] = (statbuffer->st_mode & S_IRUSR) ? 'r' : '-';
        perms[1] = (statbuffer->st_mode & S_IWUSR) ? 'w' : '-';
        perms[2] = (statbuffer->st_mode & S_IXUSR) ? 'x' : '-';
        perms[3] = (statbuffer->st_mode & S_IRGRP) ? 'r' : '-';
        perms[4] = (statbuffer->st_mode & S_IWGRP) ? 'w' : '-';
        perms[5] = (statbuffer->st_mode & S_IXGRP) ? 'x' : '-';
        perms[6] = (statbuffer->st_mode & S_IROTH) ? 'r' : '-';
        perms[7] = (statbuffer->st_mode & S_IWOTH) ? 'w' : '-';
        perms[8] = (statbuffer->st_mode & S_IXOTH) ? 'x' : '-';
        perms[9] = '\0';

        printf("%c%s %d %s\n", file_type, perms, statbuffer->st_nlink, name);
    } else {
        printf("%s\t", name);
    }

}

void handle_directory(char *directory, struct flags *ls_flags, void (*fcn)(char *, struct flags *)) {
    char name[MAX_PATH];
    struct dirent *dir_pos;
    DIR *dir_fd = opendir(directory);

    if (dir_fd == NULL) {
        fprintf(stderr, "handle_directory: can't open %s\n", directory);
        return;
    }

    while ((dir_pos = readdir(dir_fd)) != NULL) {
        // Skip the hidden files "." and ".."
        if (strcmp(dir_pos->d_name, ".") == 0 || strcmp(dir_pos->d_name, "..") == 0) {
            continue;
        }

        if (strlen(directory) + strlen(dir_pos->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "handle_directory: name too long");
            return;
        } else {
            sprintf(name, "%s/%s", directory, dir_pos->d_name);
            (*fcn)(dir_pos->d_name, ls_flags);
        }
    }
    closedir(dir_fd);
}
