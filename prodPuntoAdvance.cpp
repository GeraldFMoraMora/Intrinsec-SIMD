#include <iostream>
#include <chrono>
#include <immintrin.h> // Extension para intrínsecos de AVX2

float dotProductAVX(const float* a, const float* b, int N) {
    __m256 sum = _mm256_setzero_ps(); // Inicializo el acumulador a cero
    for (int i = 0; i < N; i += 8) {
        __m256 aVec = _mm256_loadu_ps(a + i); // Cargo 8 elementos de a
        __m256 bVec = _mm256_loadu_ps(b + i); // Cargo 8 elementos de b
        sum = _mm256_add_ps(sum, _mm256_mul_ps(aVec, bVec)); // Sumar el producto al acumulador
    }

    alignas(32) float result[8];
    _mm256_store_ps(result, sum); // Almaceno el resultado en memoria

    // Sumo los elementos del resultado y devuelvo el valor final del producto punto
    return result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
}

int main() {
    const int N = 504; // Longitud de los vectores
    alignas(32) float array1[N]; // Almaceno el primer vector en una alineación de 32 bytes
    alignas(32) float array2[N]; // Almaceno el segundo vector en una alineación de 32 bytes

    // Inicializo los vectores con valores arbitrarios
    for (int i = 0; i < N; i++) {
        array1[i] = 1.0f;
        array2[i] = 2.0f;
    }

    auto start = std::chrono::high_resolution_clock::now(); // Inicio la medición de tiempo

    // Calculo el producto punto utilizando AVX2
    float resultAVX = dotProductAVX(array1, array2, N);

    auto end = std::chrono::high_resolution_clock::now(); // Finalizo la medición de tiempo

    std::chrono::duration<double> duration = end - start; // Se calcula tiempo de ejecucion por diferencia.

    // Imprimo el resultado del producto punto y el tiempo de ejecución
    std::cout << "El resultado del producto punto con AVX2 es: " << resultAVX << std::endl;
    std::cout << "Tiempo de ejecución con AVX2: " << duration.count() << " segundos" << std::endl;

    return 0; 
}
