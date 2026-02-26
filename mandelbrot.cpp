#include <cmath>
#include <cstdint>

extern "C" {

    static uint8_t* pixel_buffer = nullptr;
    static int total_bytes = 0;

    uint8_t* allocate_buffer(int width, int height) {
        total_bytes = width * height * 4; // 4 bytes por pixel (RGBA)
        pixel_buffer = new uint8_t[total_bytes];
        return pixel_buffer;
    }

    void generate_mandelbrot(
        int width,
        int height,
        double centerX,
        double centerY,
        double zoom,
        int maxIter
    ) {
        //calcular a metade da tela fora do loop para economizar processamento
        double half_width = width * 0.5;
        double half_height = height * 0.5;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {

                double c_re = centerX + (col - half_width) / zoom;
                double c_im = centerY + (row - half_height) / zoom;

                double z_re = 0.0;
                double z_im = 0.0;
                int n = 0;

                // loop do fractal de mandelbrot
                while ((z_re * z_re + z_im * z_im) <= 4.0 && n < maxIter) {
                    double next_re = (z_re * z_re) - (z_im * z_im) + c_re;
                    z_im = 2.0 * z_re * z_im + c_im;
                    z_re = next_re;
                    n++;
                }

                // cálculo do índice do array 1D
                int pixel_index = (row * width + col) * 4;

                // lógica de cor com variáveis diferentes
                uint8_t intensity = static_cast<uint8_t>(255.0 * n / maxIter);

                pixel_buffer[pixel_index + 0] = intensity; // Red
                pixel_buffer[pixel_index + 1] = intensity; // Green
                pixel_buffer[pixel_index + 2] = intensity; // Blue
                pixel_buffer[pixel_index + 3] = 255;       // Alpha (opacidade máxima)
            }
        }
    }
}