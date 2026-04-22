#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define LEBAR  132
#define TINGGI  27

#define PI 3.14159265358979

int running = 1;
double waktu = 0.0;

void handle_interrupt(int sig) { running = 0; }
void tick(double *t) { (*t) += 0.04; }

void gambar(double t) {
    char canvas[TINGGI][LEBAR];
    int x, y, i;

    for (y = 0; y < TINGGI; y++)
        for (x = 0; x < LEBAR; x++)
            canvas[y][x] = ' ';

    double cx = LEBAR  / 2.0;
    double cy = TINGGI / 2.0;

    // === INTI GALAKSI (bulge) ===
    for (i = 0; i < 300; i++) {
        double sudut = i * 2.39996323;           // golden angle
        double jarak = sqrt(i) * 0.28;
        int px = (int)(cx + jarak * cos(sudut));
        int py = (int)(cy + jarak * sin(sudut) * 0.5);
        if (px >= 1 && px < LEBAR-1 && py >= 1 && py < TINGGI-1) {
            if (jarak < 1.2)      canvas[py][px] = '#';
            else if (jarak < 2.5) canvas[py][px] = '@';
            else if (jarak < 4.0) canvas[py][px] = 'O';
            else                  canvas[py][px] = 'o';
        }
    }

    // === LENGAN SPIRAL (4 lengan) ===
    int n_lengan = 4;
    char bintang[] = { '*', '+', '.', '`' };

    for (int lengan = 0; lengan < n_lengan; lengan++) {
        double offset_sudut = (2.0 * PI / n_lengan) * lengan;

        for (i = 1; i < 420; i++) {
            double jarak  = sqrt(i) * 1.05;
            double sudut  = offset_sudut + (jarak * 0.38) + t;

            double noise_x = ((i * 1327 + lengan * 997)  % 100 - 50) * 0.045;
            double noise_y = ((i * 1523 + lengan * 1153) % 100 - 50) * 0.022;

            int px = (int)(cx + (jarak * cos(sudut) + noise_x));
            int py = (int)(cy + (jarak * sin(sudut) + noise_y) * 0.5);

            if (px >= 1 && px < LEBAR-1 && py >= 1 && py < TINGGI-1) {
                if (canvas[py][px] == ' ')
                    canvas[py][px] = bintang[lengan % 4];
            }
        }
    }

    // === BINTANG LATAR (background) ===
    for (i = 0; i < 180; i++) {
        int bx = (i * 1031 + 7)  % (LEBAR  - 2) + 1;
        int by = (i * 757  + 13) % (TINGGI - 2) + 1;
        if (canvas[by][bx] == ' ')
            canvas[by][bx] = '.';
    }

    // === CETAK ===
    printf("\033[H\033[J");
    printf("\033[36m");
    printf("  .: GALAXY SIMULATOR :. ");
    printf("\033[33m");
    printf("[ rotation: %.2f rad ]", t);
    printf("\033[0m\n");

    for (y = 0; y < TINGGI; y++) {
        for (x = 0; x < LEBAR; x++) {
            char c = canvas[y][x];
            if      (c == '#' || c == '@') printf("\033[97m%c\033[0m", c);
            else if (c == 'O' || c == 'o') printf("\033[93m%c\033[0m", c);
            else if (c == '*')             printf("\033[96m%c\033[0m", c);
            else if (c == '+')             printf("\033[94m%c\033[0m", c);
            else if (c == '`')             printf("\033[95m%c\033[0m", c);
            else                           printf("%c", c);
        }
        putchar('\n');
    }

    printf("\033[90mCtrl+C untuk keluar\033[0m\n");
}

int main() {
    signal(SIGINT, handle_interrupt);

    while (running) {
        gambar(waktu);
        tick(&waktu);
        usleep(60000);  // ~16 fps
    }

    printf("\n\033[0mSimulasi berhenti.\n");
    return 0;
}