// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo usage.h: definición de la clase Usage.
// Historial de revisiones
// 03/11/2025 - Actualización para gramáticas

#ifndef USAGE_H_
#define USAGE_H_

#include <string>

class Usage {
 public:
  Usage(int argc, char* argv[]);
  bool IsHelpRequested() const { return help_requested_; }
  bool IsValid() const { return valid_; }
  std::string GetProgramName() const { return program_name_; }
  std::string GetErrorMessage() const { return error_message_; }
  bool IsDebugRequested() const { return debug_requested_; }
  void PrintUsage() const;
 private:
  bool help_requested_ = false;
  bool valid_ = false;
  bool debug_requested_ = false;
  std::string program_name_;
  std::string error_message_;
  bool HasGraExtension(const std::string& filename) const;
};

#endif
