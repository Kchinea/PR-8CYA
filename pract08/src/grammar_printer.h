#// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_printer.h: definición de la clase GrammarPrinter.

#ifndef GRAMMAR_PRINTER_H_
#define GRAMMAR_PRINTER_H_

#include "grammar_model.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Clase responsable de representar una gramática en un archivo
 *
 * No realiza conversión; se limita a formatear y escribir la información
 * contenida en el modelo al archivo de salida.
 */
class GrammarPrinter {
 public:
  explicit GrammarPrinter(const GrammarModel& model, const std::string& outputFile);
  ~GrammarPrinter() = default;
  void PrintGrammar() const;
 private:
  const GrammarModel& model_;
  std::string outputFile_;
};

#endif
