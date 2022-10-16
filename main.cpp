//
// Created by Alejandro D on 15/10/22.
//

#include <iostream>
#include "library.hpp"

using namespace std;

void ej_lista_no_ordenada() {
  List<int> values{3, 2, 1, 4};
  cout << values << endl;

  // Con for_each podemos, por ejemplo, encontrar el número más grande
  int biggest = (int)NULL;
  values.for_each([&biggest](int value) {
    if (value > biggest) {
      biggest = value;
    }
    return false;
  });

  cout << "Biggest value: " << biggest << '\n';
}

void ej_lista_con_frecuencia() {
  // Podemos crear una lista de frecuencia a partir de una lista de valores.
  // La estructura contará las repeticiones y hará los 'push' necesarios
  ListFre<string> list_fre { "Hola", "Hola", "Hola", "Jaa", "Jaa", "Aaa" };
  cout << list_fre << '\n';

  // También podemos crear una lista con frecuencia a partir de una lista de valores de la forma {valor, frecuencia}
  ListFre<string> list_fre2 { { .value = "Hola", .fre = 3 }, { "Jaa", 2 }, { "Aaa", 1 } };
  cout << list_fre2 << '\n';

  // Al final una lista ordenada no es más que la composición de List<FreValue<T>> con un método especial
  // para contar las frecuencias push_fre
}

void ej_indexado() {
  // Para indexar podemos usar un juego de for_each_node y una lista de apuntadores a nodos para guardar
  // los nodos. El método push_ord es muy flexible porque permite especificar una función de obtención de valores
  ListFre<string> list_fre { "Hola", "Hola", "Hola", "Jaa", "Jaa", "Aaa", "Zola", "Zola", "Zola", "Bola" };
  cout << list_fre << '\n';

  // En este ejemplo ordenaremos una lista de frecuencia en base con número de repeticiones
  List<Node<FreValue<string>> *> ordenada_por_repeticiones;
  list_fre.for_each_node([&ordenada_por_repeticiones](auto * fre_value) {
    ordenada_por_repeticiones.push_ord<int>(fre_value, [](auto * fre_value) {
      return fre_value->value.fre;
    });
    return false;
  });

  // Podemos ver el resultado de la ordenación recorriendo la lista de apuntadores a nodos y accediendo a los valores
  ordenada_por_repeticiones.for_each([](auto * fre_value) {
    cout << fre_value->value << ' ';
    return false;
  });
  cout << '\n';

  // También podemos ordenar una lista de frecuencia en base con los valores de la lista (los strings)
  List<Node<FreValue<string>> *> ordenada_por_valores;
  list_fre.for_each_node([&ordenada_por_valores](auto * fre_value) {
    ordenada_por_valores.push_ord<string>(fre_value, [](auto * fre_value) {
      return fre_value->value.value;
    });
    return false;
  });

  // Podemos ver el resultado de la ordenación recorriendo la lista de apuntadores a nodos y accediendo a los valores
  ordenada_por_valores.for_each([](auto * fre_value) {
    cout << fre_value->value << ' ';
    return false;
  });
  cout << '\n';
}


int main() {

  ej_indexado();

  /*
  List<tuple<string, int>> list { { "Pepe", 10 }, { "Sofia", 9 } };
  auto pepe = list.for_each([](tuple<string, int> value) {
    return get<0>(value) == "Pepe";
  });

  cout << get<0>(pepe->value) << " : " << get<1>(pepe->value) << '\n';
   */
}