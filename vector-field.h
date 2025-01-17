#pragma once

#include <utility>
#include <ranges>
#include <cassert>

#include "crutches.h"
#include "fluid.h"

namespace Pepega {
    template<typename T, int value_N, int value_M>
    struct Array {
        T arr[value_N][value_M]{};
        int N = value_N;
        int M = value_M;

        void init(int n, int m) {}

        void clear() {
            std::memset(arr, 0, sizeof(arr));
        }

        T *operator[](int n) {
            return arr[n];
        }

        Array &operator=(const Array &other) {
            if (this == &other) {
                return *this;
            }
            std::memcpy(arr, other.arr, sizeof(arr));
            return *this;
        }
    };

    template<typename T>
    struct Array<T, -1, -1>{
        std::vector<std::vector<T>> arr{};
        int N = 0;
        int M = 0;

        void init(int n, int m) {
            N = n;
            M = m;

            if constexpr (std::is_copy_constructible_v<T>) {
                arr.assign(n, std::vector<T>(m, T{}));
            } else {
                arr.resize(n);
                for (auto &line: arr) {
                    std::vector<T> tmp(m);
                    line.swap(tmp);
                }
            }
        }

        void clear() {
            arr = std::vector(N, std::vector<T>(M, T{}));
        }

        std::vector<T> &operator[](int n) {
            return arr[n];
        }

        Array &operator=(const Array &other) {
            if (this == &other) {
                return *this;
            }
            arr = other.arr;
            return *this;
        }
    };

    template<typename T, int N, int M>
    struct VectorField {
        Array<std::array<T, deltas.size()>, N, M> v;

        T &add(int x, int y, int dx, int dy, T dv) {
            return get(x, y, dx, dy) += dv;
        }

        T &get(int x, int y, int dx, int dy) {
            switch ((dx << 1) + dy) {
                case 1:
                    return v[x][y][3];
                case 2:
                    return v[x][y][1];
                case -1:
                    return v[x][y][2];
                default:
                    return v[x][y][0];
                }
            /*
            size_t i = std::ranges::find(deltas, std::pair(dx, dy)) - deltas.begin();
            assert(i < deltas.size());
            return v[x][y][i];*/
        }
    };
}