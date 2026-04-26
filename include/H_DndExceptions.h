#pragma once
#include <stdexcept>
#include <string>

struct DndException : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct SaveError : DndException {
    using DndException::DndException;
};

struct LoadError : DndException {
    using DndException::DndException;
};
