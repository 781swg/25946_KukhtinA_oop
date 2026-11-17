#include <SDL.h>

#include <iostream>
#include <string>

const SDL_Color dark = {28, 55, 45, 255};
const SDL_Color green = {44, 143, 78, 255};
const SDL_Color light = {231, 241, 230, 255};

void rectangle(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect area = {x, y, w, h};
    SDL_RenderFillRect(renderer, &area);
}

// Маленький растровый шрифт: каждая буква состоит из сетки 5 на 7 пикселей.
void text(SDL_Renderer* renderer, const std::string& value, int x, int y,
          int scale, SDL_Color color) {
    static const unsigned char font[36][7] = {
        {14,17,17,31,17,17,17}, {30,17,17,30,17,17,30},
        {14,17,16,16,16,17,14}, {30,17,17,17,17,17,30},
        {31,16,16,30,16,16,31}, {31,16,16,30,16,16,16},
        {14,17,16,23,17,17,14}, {17,17,17,31,17,17,17},
        {14,4,4,4,4,4,14}, {7,2,2,2,18,18,12},
        {17,18,20,24,20,18,17}, {16,16,16,16,16,16,31},
        {17,27,21,21,17,17,17}, {17,25,21,19,17,17,17},
        {14,17,17,17,17,17,14}, {30,17,17,30,16,16,16},
        {14,17,17,17,21,18,13}, {30,17,17,30,20,18,17},
        {15,16,16,14,1,1,30}, {31,4,4,4,4,4,4},
        {17,17,17,17,17,17,14}, {17,17,17,17,17,10,4},
        {17,17,17,21,21,27,17}, {17,17,10,4,10,17,17},
        {17,17,10,4,4,4,4}, {31,1,2,4,8,16,31},
        {14,17,19,21,25,17,14}, {4,12,4,4,4,4,14},
        {14,17,1,2,4,8,31}, {30,1,1,14,1,1,30},
        {2,6,10,18,31,2,2}, {31,16,16,30,1,1,30},
        {14,16,16,30,17,17,14}, {31,1,2,4,8,8,8},
        {14,17,17,14,17,17,14}, {14,17,17,15,1,1,14}
    };
    for (char letter : value) {
        int index = -1;
        if (letter >= 'A' && letter <= 'Z') index = letter - 'A';
        if (letter >= '0' && letter <= '9') index = letter - '0' + 26;
        if (index >= 0) {
            for (int row = 0; row < 7; ++row) {
                for (int col = 0; col < 5; ++col) {
                    if (font[index][row] & (1 << (4 - col))) {
                        rectangle(renderer, x + col * scale, y + row * scale,
                                  scale, scale, color);
                    }
                }
            }
        }
        x += 6 * scale;
    }
}

void bill(SDL_Renderer* renderer, int x, const std::string& amount, SDL_Color color) {
    rectangle(renderer, x + 4, 612, 140, 70, dark);
    rectangle(renderer, x, 608, 140, 70, color);
    rectangle(renderer, x + 6, 614, 128, 58, light);
    rectangle(renderer, x + 10, 618, 120, 50, color);
    text(renderer, amount, x + 20, 628, 3, dark);
    text(renderer, "RUB", x + 82, 652, 1, dark);
}

void drawATM(SDL_Renderer* renderer) {
    rectangle(renderer, 0, 0, 800, 720, {242, 245, 240, 255});

    rectangle(renderer, 222, 100, 368, 480, dark);
    rectangle(renderer, 210, 88, 368, 480, {205, 216, 206, 255});
    rectangle(renderer, 210, 88, 368, 56, green);

    rectangle(renderer, 234, 166, 320, 216, dark);
    rectangle(renderer, 242, 174, 304, 200, light);
    text(renderer, "WELCOME", 264, 194, 3, dark);
    text(renderer, "SELECT AN OPERATION", 264, 228, 1, dark);
    const std::string labels[] = {"BALANCE", "WITHDRAW", "DEPOSIT", "EXIT"};
    for (int i = 0; i < 4; ++i) {
        const int x = 260 + (i % 2) * 136;
        const int y = 252 + (i / 2) * 52;
        rectangle(renderer, x, y, 128, 40, green);
        text(renderer, labels[i], x + 12, y + 13, 2, light);
    }

    text(renderer, "CARD", 238, 402, 1, dark);
    rectangle(renderer, 302, 398, 246, 22, green);
    rectangle(renderer, 312, 406, 226, 6, dark);
    text(renderer, "CASH", 238, 452, 1, dark);
    rectangle(renderer, 302, 440, 246, 50, dark);
    rectangle(renderer, 310, 448, 230, 6, {128, 148, 130, 255});

    bill(renderer, 168, "100", {193, 188, 153, 255});
    bill(renderer, 328, "500", {192, 174, 198, 255});
    bill(renderer, 488, "1000", {157, 192, 178, 255});
}

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << SDL_GetError() << '\n';
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Симулятор банкомата — статический макет",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = window ? SDL_CreateRenderer(window, -1, 0) : nullptr;
    if (!renderer) {
        std::cerr << SDL_GetError() << '\n';
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    drawATM(renderer);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) break;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_EXPOSED) {
            drawATM(renderer);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
