// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_model.cc: implementación de la clase GrammarModel.

#include "grammar_model.h"

GrammarModel::GrammarModel(const GrammarData& data)
    : terminals_(data.terminals),
      non_terminals_(data.non_terminals),
      productions_(data.productions) {}
