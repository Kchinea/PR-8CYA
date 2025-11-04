// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas Finitos
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 14/10/2025
// Archivo alphabet.h: definición de la clase Alphabet.
// Representa un conjunto de símbolos (alfabeto) de un autómata.
// Historial de revisiones
// 14/10/2025 - Creación (primera versión)

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include "symbol.h"
#include <set>
#include <iostream>
#include <vector>

/**
 * @brief Clase que representa el alfabeto de un autómata
 */
class Alphabet {
 public:
  Alphabet() = default;
  explicit Alphabet(const std::string& str) {
    for (char c : str) {
      Insert(Symbol(c));
    }
  }
  explicit Alphabet(const std::vector<Symbol>& symbols) {
    for (const Symbol& s : symbols) {
      Insert(s);
    }
  }
  void Insert(const Symbol& s);
  bool Contains(const Symbol& s) const;
  size_t Size() const { return alphabet_.size(); }
  bool IsEmpty() const { return alphabet_.empty(); }
  void Clear() { alphabet_.clear(); }
  std::set<Symbol> GetAlphabet() const { return alphabet_; }
  std::vector<Symbol> GetSymbols() const;
  std::set<Symbol>::const_iterator begin() const { return alphabet_.begin(); }
  std::set<Symbol>::const_iterator end() const { return alphabet_.end(); }
  std::string ToString() const;
  friend std::ostream& operator<<(std::ostream& os, const Alphabet& A);
 private:
  std::set<Symbol> alphabet_;
};

#endif