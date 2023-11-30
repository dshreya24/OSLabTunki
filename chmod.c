#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filename = "fp.txt";
    mode_t new_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Read and write for user, read for group and others
    
    // Use chmod to change the permissions of the file
    if (chmod(filename, new_permissions) == 0) {
        printf("Permissions changed successfully.\n");
    } else {
        perror("Error changing permissions");
        return 1;
    }
    
    return 0;
}



