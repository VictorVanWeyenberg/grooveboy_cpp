#ifndef GROOVEBOY_BOOP_H
#define GROOVEBOY_BOOP_H
#include <cstdint>
#include <optional>
#include <vector>

class Boop {
public:
    [[nodiscard]] uint8_t get_x() const;

    [[nodiscard]] uint8_t get_y() const;

    [[nodiscard]] uint8_t get_w() const;

    [[nodiscard]] uint8_t get_h() const;

    std::optional<uint8_t> get_north();

    std::optional<uint8_t> get_east();

    std::optional<uint8_t> get_south();

    std::optional<uint8_t> get_west();

    std::optional<uint8_t> get_callback();

    [[nodiscard]] uint8_t get_args_index() const;

    [[nodiscard]] uint8_t get_args_len() const;

private:
    struct BoopData {
        uint8_t x;
        uint8_t y;
        uint8_t w;
        uint8_t h;
        uint8_t north;
        uint8_t east;
        uint8_t south;
        uint8_t west;
        uint8_t callback;
        uint8_t args_index;
        uint8_t args_len;
    } data = {};
};

enum Direction {
    N, E, S, W
};

class Boops {
public:
    Boops(Boop* boops, uint8_t* args);
    explicit Boops(Boop& boops) = delete;
    [[nodiscard]] Boop& get_current_boop() const;
    bool move(Direction direction);

private:
    Boop* boops;
    uint8_t* args;
    uint32_t index = 0;
};

#endif //GROOVEBOY_BOOP_H
