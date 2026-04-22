#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void system1() {
    printf("\n");
    printf("=======================================\n");
    printf("      tool/script by RefJoestar        \n");
    printf("=======================================\n");
    printf("  [1] once    - run once               \n");
    printf("  [2] forever - run forever            \n");
    printf("  [3] run     - run local file         \n");
    printf("  [q] quit    - exit                   \n");
    printf("=======================================\n");
    printf("\n");
}

void runOnce() {
    printf("[*] Executed once.\n");
}

void runForever() {
    printf("[*] Running forever... (Ctrl+C to stop)\n");
    while(1) {
        printf("[~] running...\n");
        sleep(1);
    }
}

void runFile() {
    char filename[256];
    printf("[?] Enter filename to execute: ");
    scanf("%255s", filename);

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("[!] File '%s' not found.\n", filename);
        return;
    }
    fclose(f);

    char command[300];
    snprintf(command, sizeof(command), "./%s", filename);
    printf("[*] Running: %s\n", command);
    system(command);
}

void call() {
    char text[20];

    system1();

    printf("Select mode: ");
    scanf("%19s", text);

    if (strcmp(text, "once") == 0) {
        runOnce();
    } else if (strcmp(text, "forever") == 0) {
        runForever();
    } else if (strcmp(text, "run") == 0) {
        runFile();
    } else if (strcmp(text, "q") == 0) {
        printf("[*] Exiting. Bye!\n");
        exit(0);
    } else {
        printf("[!] Unknown command '%s'.\n", text);
    }
}

int main() {
    call();
    return 0;
}
