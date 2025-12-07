#include <oneapi/tbb.h>

#include <SFML/Graphics.hpp>
#include <atomic>
#include <chrono>
#include <complex>

using Complex = std::complex<double>;

int mandelbrot(Complex const& c) {
    int i = 0;
    auto z = c;
    for (; i != 256 && norm(z) < 4.; ++i) {
        z = z * z + c;
    }
    return i;
}

auto to_color(int k) {
    return k < 256 ? sf::Color{static_cast<sf::Uint8>(10 * k), 0, 0}
                   : sf::Color::Black;
}

int main() {
    const int display_width = 800;
    const int display_height = 800;

    Complex const top_left{-2.2, 1.5};
    Complex const lower_right{0.8, -1.5};
    auto const diff = lower_right - top_left;

    auto const delta_x = diff.real() / display_width;
    auto const delta_y = diff.imag() / display_height;

    sf::Image image;
    image.create(display_width, display_height);

    const double x_min = -2.0;
    const double x_max = 1.0;
    const double y_min = -1.0;
    const double y_max = 1.0;

    tbb::parallel_for(
        tbb::blocked_range<int>(0, display_height),
        [&](tbb::blocked_range<int> const& r) {
            for (int y = r.begin(); y != r.end(); ++y) {
                for (int x = 0; x != display_width; ++x) {
                    auto k = mandelbrot(top_left + Complex{delta_x * x, delta_y * y});
                    image.setPixel(x, y, to_color(k));
                }
            }
        });
    image.saveToFile("mandelbrot.png");
}