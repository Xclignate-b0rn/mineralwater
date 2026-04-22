#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>

#define LEBAR  132
#define TINGGI  27
#define PI 3.14159265358979

int running = 1;
double waktu = 0.0;

void handle_interrupt(int sig) { running = 0; }
void tick(double *t) { (*t) += 0.06; }

void gambar(double t) {
    char canvas[TINGGI][LEBAR];
    int x, y, i;

    for (y = 0; y < TINGGI; y++)
        for (x = 0; x < LEBAR; x++)
            canvas[y][x] = ' ';

    double cx = LEBAR  / 2.0;
    double cy = TINGGI / 2.0;   // center = baris 13

    // === BINTANG LATAR ===
    for (i = 0; i < 120; i++) {
        int bx = (i * 1031 + 7)  % (LEBAR  - 2) + 1;
        int by = (i * 757  + 13) % (TINGGI - 2) + 1;
        if (canvas[by][bx] == ' ')
            canvas[by][bx] = '.';
    }

    // === PULSAR JET ATAS ===
    // panjang jet = 8 baris ke atas dari center
    for (i = 1; i <= 8; i++) {
        int jy = (int)(cy - i);
        int jx = (int)(cx);
        if (jy >= 0 && jy < TINGGI) {
            // makin jauh makin menyebar
            float spread = i * 0.4;
            char c = (i <= 2) ? '|' : (i <= 5) ? '|' : '|';
            canvas[jy][jx] = c;
            if (i > 2) {
                int s = (int)spread;
                if (jx-s >= 0)        canvas[jy][jx-s] = (i%2==0)?'.':' ';
                if (jx+s < LEBAR)     canvas[jy][jx+s] = (i%2==0)?'.':' ';
            }
        }
    }

    // === PULSAR JET BAWAH ===
    for (i = 1; i <= 8; i++) {
        int jy = (int)(cy + i);
        int jx = (int)(cx);
        if (jy >= 0 && jy < TINGGI) {
            float spread = i * 0.4;
            canvas[jy][jx] = '|';
            if (i > 2) {
                int s = (int)spread;
                if (jx-s >= 0)    canvas[jy][jx-s] = (i%2==0)?'.':' ';
                if (jx+s < LEBAR) canvas[jy][jx+s] = (i%2==0)?'.':' ';
            }
        }
    }

    // === MAGNETOSPHERE ===
    for (i = 0; i < 800; i++) {
        double sudut = i * 0.05 + t;
        double r     = 3.0 + 2.5 * sin(sudut * 3);
        int px = (int)(cx + r * cos(sudut) * 2.2);
        int py = (int)(cy + r * sin(sudut) * 0.9);
        if (px >= 0 && px < LEBAR && py >= 0 && py < TINGGI)
            if (canvas[py][px] == ' ')
                canvas[py][px] = '.';
    }

    // === ACCRETION DISK ===
    // cincin pipih di ekuator (hanya baris cy)
    for (i = 0; i < 600; i++) {
        double sudut = i * 0.03 + t * 0.7;
        double r     = 5.0 + 3.0 * fabs(cos(sudut * 2));
        int px = (int)(cx + r * cos(sudut) * 2.8);
        int py = (int)(cy + r * sin(sudut) * 0.35);
        if (px >= 0 && px < LEBAR && py >= 0 && py < TINGGI)
            if (canvas[py][px] == ' ') {
                if      (r < 5.5) canvas[py][px] = '=';
                else if (r < 7.0) canvas[py][px] = '-';
                else              canvas[py][px] = '~';
            }
    }

    // === INTI (paling atas — timpa semua) ===
    int ix = (int)cx;
    int iy = (int)cy;
    canvas[iy  ][ix]   = '#';
    canvas[iy  ][ix-1] = '@';
    canvas[iy  ][ix+1] = '@';
    canvas[iy-1][ix]   = '@';
    canvas[iy+1][ix]   = '@';
    canvas[iy  ][ix-2] = 'O';
    canvas[iy  ][ix+2] = 'O';

    // === CETAK ===
    printf("\033[H\033[J");

    for (y = 0; y < TINGGI; y++) {
        for (x = 0; x < LEBAR; x++) {
            char c = canvas[y][x];
            if      (c == '#')             printf("\033[97m#\033[0m");
            else if (c == '@')             printf("\033[93m@\033[0m");
            else if (c == 'O')             printf("\033[33mO\033[0m");
            else if (c == '|' || c==':')   printf("\033[96m%c\033[0m", c);
            else if (c == '=' || c == '-') printf("\033[94m%c\033[0m", c);
            else if (c == '~')             printf("\033[95m~\033[0m");
            else                           printf("%c", c);
        }
        putchar('\n');
    }

    printf("\033[90mJet \033[96m|\033[0m  "
           "Accretion disk \033[94m~=-\033[0m  "
           "Magnetosphere \033[37m.\033[0m  "
           "Inti \033[97m#\033[93m@O\033[0m\n");
    printf("\033[90mCtrl+C untuk keluar\033[0m\n");
}

int main() {
    signal(SIGINT, handle_interrupt);

    while (running) {
        gambar(waktu);
        tick(&waktu);
        usleep(50000);
    }

    printf("\n\033[0mBintang neutron collapsed.\n");
    return 0;
}
