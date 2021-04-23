#pragma once

//
// Created by Mike Mitterer on 23.04.21.
//
#include <cstdint>

struct Point {
    uint8_t x;
    uint8_t y;
};

struct PrecisePoint {
    double x;
    double y;

    PrecisePoint(double x, double y) : x{ x }, y{ y } {}
};

class Point3D : public Point {
public:
    uint8_t z;
};
