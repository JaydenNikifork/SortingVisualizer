#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <string.h>

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    unsigned int index = 0;
    for (int i : v) {
        if (index == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else if (index == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        SDL_RenderDrawLine(renderer, index, 99, index, i);
        ++index; 
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

void selection_sort(std::vector<int>& v, SDL_Renderer* renderer) {
    for (unsigned int i=0; i<v.size(); ++i) {
        for (unsigned int j=i; j<v.size(); ++j) {
            if (v[j] < v[i]) {
                std::swap(v[j], v[i]);
                
                draw_state(v, renderer, i, j);
            }
        }
    }
}

void merge(std::vector<int>& v, SDL_Renderer* renderer, int s, int mid, int e) {
    std::vector<int> tmp;
    int it1 = s;
    int it2 = mid+1;

    while (it1 <= mid || it2 <= e) {
        if (it1 <= mid && it2 <= e) {
            if (v[it1] < v[it2]) {
                tmp.push_back(v[it1]);
                ++it1;
            } else {
                tmp.push_back(v[it2]);
                ++it2;
            }
        } else if (it1 <= mid) {
            tmp.push_back(v[it1]);
            ++it1;
        } else if (it2 <= e) {
            tmp.push_back(v[it2]);
            ++it2;
        }
    }

    for (int i=0; i<tmp.size(); ++i) {
        v[s+i] = tmp[i];
        draw_state(v, renderer, i, s+i);
    }
}

void merge_sort(std::vector<int> &v, SDL_Renderer* renderer, int s, int e) {
    if (s >= e) return;

    int mid = s + (e - s) / 2;

    merge_sort(v, renderer, s, mid);
    merge_sort(v, renderer, mid+1, e);
    merge(v, renderer, s, mid, e);
}

void bubble_sort(std::vector<int> &v, SDL_Renderer *renderer) {
    for (int i=v.size()-1; i>=0; --i) {
        for (int j=0; j<i; ++j) {
            if (v[j] > v[j+1]) {
                std::swap(v[j], v[j+1]);
                draw_state(v, renderer, i, j);
            }
        }
    }
}

int partition(std::vector<int> &v, SDL_Renderer *renderer, int low, int high) {
    int pivot = high;

    int i = low - 1;

    for (int j=low; j<=high-1; ++j) {
        if (v[j] < v[pivot]) {
            ++i;
            std::swap(v[i], v[j]);
            draw_state(v, renderer, i, j);
        }
    }

    std::swap(v[i+1], v[pivot]);
    draw_state(v, renderer, i+1, pivot);

    return i+1;
}

void quick_sort(std::vector<int> &v, SDL_Renderer *renderer, int low, int high) {
    if (low >= high) return;

    int pt = partition(v, renderer, low, high);

    quick_sort(v, renderer, low, pt - 1);
    quick_sort(v, renderer, pt + 1, high);
}

int main(int argc, char *argv[]) {
    std::random_device rd;
    std::uniform_int_distribution d(1, 99);
    std::vector<int> v;

    for (int i=0; i<100; i++) {
        v.push_back(d(rd));
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(
        100*10, 100*10, 0,
        &window, &renderer);
    SDL_RenderSetScale(renderer,10,10);

    if (argc == 1 || strcmp(argv[1], "selection") == 0) selection_sort(v, renderer);
    else if (strcmp(argv[1], "merge") == 0) merge_sort(v, renderer, 0, v.size());
    else if (strcmp(argv[1], "bubble") == 0) bubble_sort(v, renderer);
    else if (strcmp(argv[1], "quick") == 0) merge_sort(v, renderer, 0, v.size() - 1);

    for (int i : v) {
        std::cout << i << " ";
    }

    return 0;
}