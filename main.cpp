//
// Created by Alejandro D on 15/10/22.
//

#include <iostream>
#include <fstream>

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
  ListFre<string> list_fre2 { FreValue<string>{ "Hola", 3 }, { "Jaa", 2 }, { "Aaa", 1 } };
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

void ej_diccionario() {
  KeyValueList<string, int> edades{ {.key = "Sofia", .value = 30}, {"Juan", 10}, {"Pepe", 5} };
  cout << edades << endl;

  cout << "La edad de Sofia es: " << *edades.get("Sofia") << endl;

  edades.insert("Pedro", 43);
  edades.insert_update("Pedro", 44);

 cout << edades << endl;
}

void ej_cortina() {
  Cortina<string, int> calificaciones { { .key = "Sofia", .value {10, 7}}, {"Juan", {9, 10, 8}} };
  cout << calificaciones << endl;
  calificaciones.append("Sofia", 8);
  cout << calificaciones << endl;
}

void ejercicio1() {
  ListFre<string> list_fre { "Hola", "Hola", "Hola", "Jaa", "Jaa", "Aaa", "Zola", "Zola", "Zola", "Bola" };
  cout << list_fre << '\n';
}

void ejercicio2() {
  Cortina<string, KeyValue<string, int>> comidas {
    {
      .key = "Mexicana",
      .value = {
          { .key = "Tacos", .value = 0 },
          { .key = "Chilaquiles", .value = 10 }
      }
    },
    {
      "Italiana",
        {
          { "Pizza", 4 },
          { "Ravioli", 2 },
          { "Spaghetti", 10 }
      }
    }
  };

  comidas.for_each_node([](auto * node) {
    string mas_gustado;
    string menos_gustado;
    int smallest = 5000;
    int greatest = -5000;
    node->value.value.for_each([&](auto comida) {
      if (comida.value > greatest) {
        greatest = comida.value;
        mas_gustado = comida.key;
      }
      if (comida.value < smallest) {
        smallest = comida.value;
        menos_gustado = comida.key;
      }
      return false;
    });

    cout << "La comida más gustada de " << node->value.key << " es " << mas_gustado << " con " << greatest << " votos" << endl;
    cout << "La comida menos gustada de " << node->value.key << " es " << menos_gustado << " con " << smallest << " votos" << endl;

    return false;
  });

  cout << comidas << endl;
}

void ejercicio3() {
  List<string> contenidos;

  ifstream archivo1("/Users/alejandro/CLionProjects/untitled44/archivo1.txt", ios::in );
  ifstream archivo2("/Users/alejandro/CLionProjects/untitled44/archivo2.txt", ios::in );
  ifstream archivo3("/Users/alejandro/CLionProjects/untitled44/archivo3.txt", ios::in );
  ofstream archivo4("/Users/alejandro/CLionProjects/untitled44/archivo4.txt", ios::out | ios::trunc );

  string data1, data2, data3;
  bool n1, n2, n3;
  while (
      (n1 = !getline(archivo1, data1, '\n').eof()) |
      (n2 = !getline(archivo2, data2, '\n').eof()) |
      (n3 = !getline(archivo3, data3, '\n').eof())
  ) {
    if (n1) contenidos.push_back(data1);
    if (n2) contenidos.push_back(data2);
    if (n3) contenidos.push_back(data3);
  }

  cout << contenidos << endl;

  contenidos.for_each([&](const string& value){
    archivo4 << value << '\n';
    return false;
  });
}

int main() {

  ejercicio1();
  ejercicio2();
  ejercicio3();

  /*
  List<tuple<string, int>> list { { "Pepe", 10 }, { "Sofia", 9 } };
  auto pepe = list.for_each([](tuple<string, int> value) {
    return get<0>(value) == "Pepe";
  });

  cout << get<0>(pepe->value) << " : " << get<1>(pepe->value) << '\n';
   */
  return 0;
}
