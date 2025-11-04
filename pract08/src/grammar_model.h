// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_model.h: definición de la clase GrammarModel.

#ifndef GRAMMAR_MODEL_H_
#define GRAMMAR_MODEL_H_

#include "grammar_data.h"
#include "production.h"
#include "alphabet.h"
#include <vector>

/**
 * @brief Contenedor inmutable de los datos de una gramática
 *
 * Esta clase encapsula la información parseada por GrammarParser y expone
 * accesores para uso por conversores o impresores.
 */
class GrammarModel {
 public:
  explicit GrammarModel(const GrammarData& data);
  const Alphabet& GetTerminals() const { return terminals_; }
  const Alphabet& GetNonTerminals() const { return non_terminals_; }
  const Symbol& getInitial() const {return productions_[0].GetNonTerminal();} 
  const std::vector<Production>& GetProductions() const { return productions_; }
 private:
  Alphabet terminals_;
  Alphabet non_terminals_;
  std::vector<Production> productions_;
};

#endif
