#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 다이아몬드 모양을 그리는 함수
void diamond(unsigned char* image, int width, int height, int center_x, int center_y, int size) {
    for (int y = -size; y <= size; y++) {
        for (int x = -size; x <= size; x++) {
            if (abs(x) + abs(y) == size) {
                int draw_x = center_x + x;
                int draw_y = center_y + y;
                if (draw_x >= 0 && draw_x < width && draw_y >= 0 && draw_y < height) {
                    image[draw_y * width + draw_x] = 150; // 회색 
                }
            }
            else if (abs(x) + abs(y) < size) {
                int draw_x = center_x + x;
                int draw_y = center_y + y;
                if (draw_x >= 0 && draw_x < width && draw_y >= 0 && draw_y < height) {
                    image[draw_y * width + draw_x] = 255; // 흰색 
                }
            }
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    int num_diamonds = atoi(argv[1]); // 입력받는 다이아몬드 갯수

    if (num_diamonds <= 0)
        return 1;

    unsigned char* a;
    FILE* fip, * fop;

    srand(time(NULL)); // 난수 생성

    fip = fopen("lena_128.raw", "rb");
    a = calloc(128 * 128, sizeof(unsigned char));
    fread(a, sizeof(unsigned char), 128 * 128, fip);

    for (int i = 0; i < num_diamonds; i++) {

        // 랜덤한 위치에 다이아몬드 모양 그리기
        int diamond_size = 2; // 다이아몬드의 크기
        int center_x = ((rand() % 128) + 1); // 위치 x의 범위: 1~128 
        int center_y = ((rand() % 128) + 1); // 위치 y의 범위: 1~128
        diamond(a, 128, 128, center_x, center_y, diamond_size);
    }

    fop = fopen("레나-900.raw", "wb");
    fwrite(a, sizeof(unsigned char), 128 * 128, fop);
    fclose(fop);
    free(a);

    return 0;
}
