#include <stdio.h>
#include <string.h>
#include "filesys.h"

void print_help() {
    printf("Commands:\n");
    printf("  create <filename> - Create a new file\n");
    printf("  delete <filename> - Delete a file\n");
    printf("  read <filename> - Read a file\n");
    printf("  write <filename> <data> - Write data to a file\n");
    printf("  ls - List all files\n");
    printf("  help - Show this help message\n");
}

int main() {
    load_fs("filesystem.dat");
    char command[256];
    
    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) {
            printf("Error reading input.\n");
            break;
        }

        char *cmd = strtok(command, " \n");
        if (!cmd) {
            printf("No command entered.\n");
            continue;
        }

        if (strcmp(cmd, "create") == 0) {
            char *name = strtok(NULL, " \n");
            if (name) {
                if (create_file(name) != -1) {
                    printf("File '%s' created.\n", name);
                } else {
                    printf("Error creating file.\n");
                }
            }
        } else if (strcmp(cmd, "delete") == 0) {
            char *name = strtok(NULL, " \n");
            if (name) {
                if (delete_file(name) == 0) {
                    printf("File '%s' deleted.\n", name);
                } else {
                    printf("Error deleting file.\n");
                }
            }
        } else if (strcmp(cmd, "read") == 0) {
            char *name = strtok(NULL, " \n");
            if (name) {
                char buffer[4096];
                printf("Attempting to read file '%s'...\n", name);
                int read_size = read_file(name, buffer, sizeof(buffer));
                if (read_size != -1) {
                    printf("File contents: %.*s\n", read_size, buffer);
                } else {
                    printf("Error reading file '%s'.\n", name);
                }
            }
        } else if (strcmp(cmd, "write") == 0) {
            char *name = strtok(NULL, " \n");
            char *data = strtok(NULL, "\n");
            if (name && data) {
                printf("Attempting to write '%s' to file '%s'...\n", data, name);
                if (write_file(name, data, strlen(data)) != -1) {
                    printf("Data written to file '%s'.\n", name);
                } else {
                    printf("Error writing to file '%s'.\n", name);
                }
            }
        } else if (strcmp(cmd, "help") == 0) {
            print_help();
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }
    save_fs("filesystem.dat");
    return 0;
}

