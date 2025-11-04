// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_parser.h: definición de la clase GrammarParser.

#ifndef GRAMMAR_PARSER_H_
#define GRAMMAR_PARSER_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "grammar_data.h"
#include "production.h"
#include "alphabet.h"

/**
 * @brief Clase que parsea archivos de gramáticas
 */
class GrammarParser {
 public:
  explicit GrammarParser(const std::string& filename);
  GrammarData Parse();
  bool IsFileOpen() const { return file_.is_open(); }
 private:
  std::ifstream file_;
  std::string filename_;
  Alphabet ReadTerminals();
  Alphabet ReadNonTerminals();
  std::vector<Production> ReadProductions(const Alphabet& terminals, const Alphabet& non_terminals);
};

#endif
