// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo production.h: definición de la clase Production.

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "cadena.h"
#include "symbol.h"
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Clase que representa una producción de una gramática
 */
class Production {
 public:
  Production() : non_terminal_(Symbol('\0')), production_() {}
  Production(const Symbol& non_terminal, const Cadena& production) : non_terminal_(non_terminal), production_(production) {}
  const Symbol& GetNonTerminal() const { return non_terminal_; }
  const Cadena& GetProduction() const { return production_; }
  std::string ToString() const { return non_terminal_.ToString() + " -> " + production_.ToString(); }
  friend std::ostream& operator<<(std::ostream& os, const Production& prod) {
    os << prod.non_terminal_ << " -> " << prod.production_;
    return os;
  }

 private:
  Symbol non_terminal_;
  Cadena production_;
};

#endif
