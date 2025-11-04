// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas Finitos
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 14/10/2025
// Archivo alphabet.cc: implementación de la clase Alphabet.
// Historial de revisiones
// 14/10/2025 - Creación (primera versión)

#include "alphabet.h"

/**
 * @brief Inserta un símbolo en el alfabeto
 * @param s Símbolo a insertar
 */
void Alphabet::Insert(const Symbol& s) {
  alphabet_.insert(s);
}

/**
 * @brief Verifica si un símbolo está en el alfabeto
 * @param s Símbolo a verificar
 * @return true si está en el alfabeto, false en caso contrario
 */
bool Alphabet::Contains(const Symbol& s) const {
  return alphabet_.find(s) != alphabet_.end();
}

/**
 * @brief Obtiene todos los símbolos como vector
 * @return Vector con todos los símbolos del alfabeto
 */
std::vector<Symbol> Alphabet::GetSymbols() const {
  std::vector<Symbol> symbols;
  for (const Symbol& s : alphabet_) {
    symbols.push_back(s);
  }
  return symbols;
}

/**
 * @brief Convierte el alfabeto a string
 * @return Representación en string del alfabeto
 */
std::string Alphabet::ToString() const {
  std::string result = "{";
  bool first = true;
  for (const Symbol& s : alphabet_) {
    if (!first) result += ", ";
    result += s.GetChar();
    first = false;
  }
  result += "}";
  return result;
}

/**
 * @brief Operador de salida para la clase Alphabet
 * @param os Stream de salida
 * @param A Alfabeto a imprimir
 * @return Referencia al stream de salida
 */
std::ostream& operator<<(std::ostream& os, const Alphabet& A) {
  os << "{";
  bool first = true;
  for (const Symbol& s : A.alphabet_) {
    if (!first) os << ", ";
    os << s;
    first = false;
  }
  os << "}";
  return os;
}