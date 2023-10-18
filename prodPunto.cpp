#include <iostream>
#include <chrono>
#include <vector>

float dotProduct(const std::vector<float>& a, const std::vector<float>& b) {
    float result = 0.0f; // Inicializo en 0.0
    for (size_t i = 0; i < a.size(); i++) { //Recorro elementos de los vectores
        result += a[i] * b[i]; // Se calcula el producto punto elemento a elemento
    }
    return result; // Devuelvo el resultado
}

int main() {
    const int N = 504; // N es un múltiplo de 4 y es mayor que 500
    std::vector<float> array1(N, 1.0f); // Inicializo con valores arbitrarios
    std::vector<float> array2(N, 2.0f); // Inicializo con valores arbitrarios

    auto start = std::chrono::high_resolution_clock::now(); // Inicializo medición de tiempo

    // Mando a llamar el calculo del producto punto
    float result = dotProduct(array1, array2);

    auto end = std::chrono::high_resolution_clock::now(); // Finalizo medición de tiempo

    std::chrono::duration<double> duration = end - start; // Se calcula tiempo de ejecucion por diferencia.
    std::cout << "El resultado del producto punto es: " << result << std::endl;
    std::cout << "Tiempo de ejecución sin optimización: " << duration.count() << " segundos" << std::endl;

    return 0;
}
