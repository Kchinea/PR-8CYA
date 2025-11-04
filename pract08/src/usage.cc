// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo usage.cc: implementación de la clase Usage.
// Historial de revisiones
// 03/11/2025 - Actualización para gramáticas

#include "usage.h"
#include <iostream>
#include <vector>

/**
 * @brief Constructor de Usage.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 */
Usage::Usage(int argc, char* argv[]) {
  if (argc >= 1) {
    program_name_ = argv[0];
  }
  std::vector<std::string> positional;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      help_requested_ = true;
      valid_ = true;
      return;
    } else if (arg == "-d" || arg == "--debug") {
      debug_requested_ = true;
    } else {
      positional.push_back(arg);
    }
  }
  if (positional.size() != 2) {
    valid_ = false;
    error_message_ = "Error: Número incorrecto de argumentos. Uso: <input.gra> <output.gra> [--debug]";
    return;
  }
  std::string input_file = positional[0];
  std::string output_file = positional[1];
  if (!HasGraExtension(input_file)) {
    valid_ = false;
    error_message_ = "Error: El archivo de entrada debe tener extensión .gra";
    return;
  }
  if (!HasGraExtension(output_file)) {
    valid_ = false;
    error_message_ = "Error: El archivo de salida debe tener extensión .gra";
    return;
  }

  valid_ = true;
}

/**
 * @brief Verifica si un archivo tiene extensión .gra
 * @param filename Nombre del archivo a verificar
 * @return true si tiene extensión .gra, false en caso contrario
 */
bool Usage::HasGraExtension(const std::string& filename) const {
  if (filename.length() < 4) {
    return false;
  }
  return filename.substr(filename.length() - 4) == ".gra";
}

/**
 * @brief Imprime el mensaje de uso del programa en la consola.
 */
void Usage::PrintUsage() const {
  std::cout << "Uso: " << program_name_ << " <archivo_entrada> <archivo_salida> [--debug]" << std::endl;
  std::cout << "  archivo_entrada: archivo que contiene la definición de la gramática" << std::endl;
  std::cout << "  archivo_salida: archivo donde se escribirá la gramática procesada" << std::endl;
  std::cout << std::endl;
  std::cout << "Formato del archivo de gramática:" << std::endl;
  std::cout << "  - Número de símbolos terminales" << std::endl;
  std::cout << "  - Lista de símbolos terminales (uno por línea)" << std::endl;
  std::cout << "  - Número de símbolos no terminales" << std::endl;
  std::cout << "  - Lista de símbolos no terminales (uno por línea)" << std::endl;
  std::cout << "  - Número de producciones" << std::endl;
  std::cout << "  - Lista de producciones en formato: NoTerminal produccion" << std::endl;
  std::cout << std::endl;
  std::cout << "Opciones:" << std::endl;
  std::cout << "  -h, --help    Muestra esta ayuda" << std::endl;
  std::cout << "  -d, --debug   Muestra en salida estándar (stdout) las producciones que se van creando durante la conversión" << std::endl;
}
