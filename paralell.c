#include <stdio.h>

// MicroOS instance handlers
void q(char* name) {
    printf("MicroOS: %s - kernel loaded\n", name);
    printf("MicroOS: %s - __OS__ initialized\n", name);
}

void w1(char* name) {
    printf("MicroOS: %s - system started\n", name);
}

void r(char* name) {
    printf("MicroOS: %s - running\n", name);
}

// MicroOS spawner, manages multiple OS instances
void micro() {
    char name1[50], name2[50], name3[50];
    
    printf("\n--- MicroOS Configuration ---\n");
    
    printf("Enter name for MicroOS 1: ");
    scanf("%s", name1);
    q(name1);
    printf("\n");
    
    printf("Enter name for MicroOS 2: ");
    scanf("%s", name2);
    w1(name2);
    printf("\n");
    
    printf("Enter name for MicroOS 3: ");
    scanf("%s", name3);
    r(name3);
}

// OSprimer, main coordinator
void parallel() {
    printf("\n=== Paralell_OS Starting ===\n");
    micro();
    printf("\n=== All MicroOS instances running ===\n\n");
}

int main() {
    parallel();
    return 0;
}