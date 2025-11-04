// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas Finitos
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 14/10/2025
// Archivo symbol.cc: implementación de la clase Symbol.
// Historial de revisiones
// 14/10/2025 - Creación (primera versión)

#include "symbol.h"

/**
 * @brief Operador de salida para la clase Symbol
 * @param os Stream de salida
 * @param s Símbolo a imprimir
 * @return Referencia al stream de salida
 */
std::ostream& operator<<(std::ostream& os, const Symbol& s) {
  if (s.IsEpsilon()) {
    os << "&"; 
  } else {
    os << s.GetChar();
  }
  return os;
}

/**
 * @brief Operador de entrada para la clase Symbol
 * @param is Stream de entrada
 * @param s Símbolo a leer
 * @return Referencia al stream de entrada
 */
std::istream& operator>>(std::istream& is, Symbol& s) {
  char c;
  is >> c;
  s.SetChar(c);
  return is;
}

/**
 * @brief devuelve el equivalente en string a la clase Symbol
 * @return string resultante
 */
std::string Symbol::ToString() const {
  if (IsEpsilon()) return std::string("&");
  return std::string(1, GetChar());
}