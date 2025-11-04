// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_printer.cc: implementación de la clase GrammarPrinter.

#include "grammar_printer.h"

/**
 * @brief Constructor de GrammarPrinter.
 * @param model Referencia al modelo de gramática.
 * @param outputFile Nombre del archivo de salida.
 */
GrammarPrinter::GrammarPrinter(const GrammarModel& model, const std::string& outputFile) 
    : model_(model), outputFile_(outputFile) {}

/**
 * @brief Imprime la información de la gramática en el archivo de salida.
 */
void GrammarPrinter::PrintGrammar() const {
  std::ofstream file(outputFile_);
  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo de salida " << outputFile_ << std::endl;
    return;
  }
  file << model_.GetTerminals().Size() << std::endl;
  for (const Symbol& terminal : model_.GetTerminals()) {
    file << terminal << std::endl;
  }
  file << model_.GetNonTerminals().Size() << std::endl;
  for (const Symbol& non_terminal : model_.GetNonTerminals()) {
    file << non_terminal << std::endl;
  }
  file << model_.GetProductions().size() << std::endl;
  for (const Production& production : model_.GetProductions()) {
    file << production << std::endl;
  }
  file.close();
  std::cout << "Gramática impresa correctamente en " << outputFile_ << std::endl;
}

