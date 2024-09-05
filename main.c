#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h> // graphics

int *ctx, file_size; // current context buffer pointer, file size
char *buff; // buffer pointer
FILE *f;

#define in *(int*)

#define cf(n)       (ctx + n)                    // current context offset n
#define tcn(n)      (buff + *(ctx + n))          // current context offset n address 
#define tcnn(n,n1)  (buff + *(ctx + n) + n1)     // current context offset n address offset n1
#define tn(n)       (buff + n)                   // context address offset n

// core function
#define add_core output, pluss, add, dec, mult, dev, \
equal, less, big, not, and, or

void output(void) {
    printf("%s", tcn(1));
    ctx+=1;
}

void pluss(void) {
    (*tcn(1))++;
    ctx+=1;
}

void add(void) {
    in tcn(3) = in tcn(1) + in tcn(2);
    ctx+=3;
}

void dec(void) {
    in tcn(3) = in tcn(1) - in tcn(2);
    ctx+=3;
}

void mult(void) {
    in tcn(3) = in tcn(1) * in tcn(2);
    ctx+=3;
}

void dev(void) {
    in tcn(3) = in tcn(1) / in tcn(2);
    ctx+=3;
}

void equal(void) {
    *tcn(3) = (in tcn(1) == in tcn(2)) ? 1 : 0;
    ctx+=3;
}

void less(void) {
    *tcn(3) = (in tcn(1) < in tcn(2)) ? 1 : 0;
    ctx+=3;
}

void big(void) {
    *tcn(3) = (in cf(1) > in cf(2)) ? 1 : 0;
    ctx+=1;
}

void not(void) {
    *tcn(1) = in tcn(1) ? 0 : 1;
    ctx+=1;
}

void and(void) {
    *tcn(3) = (in tcn(1) && in tcn(2)) ? 1 : 0;
    ctx+=1;
}

void or(void) {
    *tcn(3) = (in tcn(1) || in tcn(2)) ? 1 : 0;
    ctx+=1;
}

// raylib function
#define add_raylib InitWindow1, CloseWindow1, ToggleFullscreen1, EndDrawing1, \
PutPixel, DrawText1, \
WindowShouldClose1, IsMouseButtonDown1, GetMousePosition1, GetKeyPressed1

void InitWindow1(void){
    InitWindow(in cf(1), in cf(2), tcn(3));
    ctx+=3;
}

void CloseWindow1(void){
    CloseWindow();
}

void ToggleFullscreen1(void){
    ToggleFullscreen();
}

void EndDrawing1(void){
    EndDrawing();
}

void PutPixel(void){
    DrawPixel(in tcn(1), in tcn(2), *(Color*)tcn(3));   
    ctx+=3;
}

void DrawText1(void){
    DrawText(tcn(1), in cf(2), in cf(3), in cf(4), *(Color*)cf(5));
    ctx+=5;
}

void WindowShouldClose1(void){
    *tcn(1) = WindowShouldClose();
    ctx+=1;
} 

void IsMouseButtonDown1(void){
    *tcn(2) = IsMouseButtonDown(*tcn(1));   
    ctx+=1;
}

void GetMousePosition1(void){
    in tcn(1) = GetMouseX();
    in tcn(1) = GetMouseY();
    ctx+=2;
}

void GetKeyPressed1(void){
   *cf(1) = GetKeyPressed();
   ctx+=1;
}


int main(int argc, char const *argv[]) {
    ctx = malloc(8);

    if (argc > 1) {
        f = fopen(argv[1], "rb");
    } else {
        printf("file:");
        char filename[256];
        *(filename + strlen(fgets(filename, sizeof(filename), stdin)) - 1) = 0;
        f = fopen(filename, "rb");
    }

    fread(ctx, 8, 1, f);
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    ctx = *(ctx) == -1 ? (int *)(buff = malloc((file_size = *(ctx + 1)))) + 2 : (int *)(buff = malloc(file_size));
    fseek(f, 0, SEEK_SET);
    fread(ctx, file_size, 1, f);

    void (*fn[])() = {NULL, NULL, add_core, add_raylib};
    while (((char *)ctx - buff) < file_size) {
        if (*ctx) {
            if (*ctx == 1) {
                memmove(buff + *(ctx + 2), buff + *(ctx), *(ctx + 1));
                ctx += 4;
            } else {
                fn[*ctx]();
                ctx += 1;
            }
        } else {
            if (*(ctx + 1) == 0 || *(buff + *(ctx + 1)) != 0) {
                ctx = (int *)(buff + *(ctx + 2));
                continue;
            }
			ctx += 3;
        }
    }
    
    free(buff);
    fclose(f);
    return 0;
}
