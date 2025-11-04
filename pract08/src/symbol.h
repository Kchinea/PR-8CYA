// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas Finitos
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 14/10/2025
// Archivo symbol.h: definición de la clase Symbol.
// Representa un símbolo del alfabeto de un autómata.
// Historial de revisiones
// 14/10/2025 - Creación (primera versión)

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <iostream>
#include <string>

/**
 * @brief Clase que representa un símbolo del alfabeto
 */
class Symbol {
 public:
  Symbol() = default;
  Symbol(char c) : symbol_(c == '&' ? '\0' : c) {}  // & representa epsilon
  bool operator<(const Symbol& other) const { return symbol_ < other.symbol_; }
  bool operator==(const Symbol& other) const { return symbol_ == other.symbol_; }
  bool operator!=(const Symbol& other) const { return symbol_ != other.symbol_; }
  char GetChar() const { return symbol_; }
  void SetChar(char c) { symbol_ = (c == '&' ? '\0' : c); }
  bool IsEpsilon() const { return (symbol_ == '\0'); }
  static Symbol Epsilon() { return Symbol('&'); }
  // Devuelve una representación en cadena del símbolo
  std::string ToString() const;
 private:
  char symbol_;
};

std::ostream& operator<<(std::ostream& os, const Symbol& s);
std::istream& operator>>(std::istream& is, Symbol& s);

#endif