// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo main.cc: programa principal para la práctica de gramáticas.
// Contiene la función main del proyecto que utiliza las clases implementadas
// para parsear archivos de gramáticas y procesarlos.

#include <iostream>
#include <string>
#include <fstream>
#include "grammar_parser.h"
#include "grammar_model.h"
#include "grammar_printer.h"
#include "grammar_converter.h"
#include "usage.h"

/**
 * @brief Función principal del programa
 * @param argc Número de argumentos
 * @param argv Array de argumentos
 * @return Código de salida
 */
int main(int argc, char* argv[]) {
  Usage usage(argc, argv);
  if (!usage.IsValid()) {
    if (!usage.GetErrorMessage().empty()) {
      std::cerr << usage.GetErrorMessage() << std::endl;
    }
    std::cerr << "Usa --help para más información." << std::endl;
    return 1;
  }
  if (usage.IsHelpRequested()) {
    usage.PrintUsage();
    return 0;
  }
  std::string inputFile = argv[1];
  std::string outputFile = argv[2];
  GrammarParser parser(inputFile);
  if (!parser.IsFileOpen()) {
    std::cerr << "Error: No se pudo abrir el archivo " << inputFile << std::endl;
    return 1;
  }
  GrammarData data = parser.Parse();
  GrammarModel model(data);
  GrammarConverter converter(model, usage.IsDebugRequested());
  GrammarData converted_data = converter.ConvertToChomskyNormalForm();
  GrammarModel converted_model(converted_data);
  GrammarPrinter printer(converted_model, outputFile);
  printer.PrintGrammar();
  return 0;
}