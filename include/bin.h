#ifndef GROOVEBOY_BIN_H
#define GROOVEBOY_BIN_H
#include <cstdint>

class Binary {
public:
    Binary(intptr_t start, uint16_t size);
    [[nodiscard]] intptr_t get_start() const;
    [[nodiscard]] uint16_t get_size() const;
private:
    intptr_t start;
    uint16_t size;
};

#endif //GROOVEBOY_BIN_H
