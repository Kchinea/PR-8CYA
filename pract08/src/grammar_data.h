// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_data.h: definición de la estructura GrammarData.

#ifndef GRAMMAR_DATA_H_
#define GRAMMAR_DATA_H_

#include <vector>
#include "alphabet.h"
#include "production.h"

/**
 * @brief Estructura que contiene los datos de una gramática parseada
 */
struct GrammarData {
  Alphabet terminals;
  Alphabet non_terminals;
  std::vector<Production> productions;
};

#endif
