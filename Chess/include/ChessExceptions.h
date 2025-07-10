#pragma once
#include <exception>
#include <string>

// Exception thrown when an invalid move is attempted
class InvalidMoveException : public std::exception {
public:
    InvalidMoveException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// Exception thrown when no piece is found at a specified position
class PieceNotFoundException : public std::exception {
public:
    PieceNotFoundException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// Exception thrown when a move results in a check condition
class CheckException : public std::exception {
public:
    CheckException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};
