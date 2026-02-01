// ArregloParalelo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//Libreria para definir numeros aleatorios
#include <cstdlib>
#include <vector>
#include <ctime>
//Aplicamos esta condicional para asegurar que openmp esta instalada y configurado para su correcta ejecucion
#ifdef _OPENMP
    #include <omp.h>
#endif 
 
# //Cantidad de resultados a demostrar una vez se haga la suma de arreglos

//Prototipo de funcion que imprimira los resultados
void imprimeArreglo(std::vector<float>& d, int mostrar);


int main()
{
    //Iniciamos semilla para rand()
    srand(time(NULL));
    //Declaramos N de manera aleatoria los elementos de los arreglos de 1000 a 5000
    int N = 1000 + rand() % 5000;
    // Declaramos pedazos(chunks) de manera aleatoria los elementos de los arreglos de 1 a 50
    int pedazos = 1 + rand() % 50;
    //
    int mostrar = 1 + rand() % 30;
    std::cout << "N = " << N << std::endl;
    std::cout << "pedazos = " << pedazos << std::endl;
    std::cout << "Mostrar = " << mostrar << std::endl;
    std::cout << "Sumando Arreglos en Paralelo!\n";
    std::vector<float> a(N), b(N), c(N);
    
    int i;
    //Creacion de valores de arreglos a y b
    for (i = 0; i < N; i++)
    {
        a[i] = (i * 15) + 10;
        b[i] = (i * 32) - 4; 
    }
    
    //Activaacion de openmp para utilizar recurrencia en la suma de los arreglos mediantes los pedazos(chunks)
    #pragma omp parallel for  \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a, mostrar);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b, mostrar);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c, mostrar);
}

void imprimeArreglo(std::vector<float>& d, int mostrar)
{
    for (int x = 0; x < mostrar && x < d.size(); x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
