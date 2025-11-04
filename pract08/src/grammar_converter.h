// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas - Forma Normal de Chomsky
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_converter.h: definición de la clase GrammarConverter.

#ifndef GRAMMAR_CONVERTER_H_
#define GRAMMAR_CONVERTER_H_

#include "grammar_model.h"
#include "grammar_data.h"
#include "grammar_checker.h"
#include <vector>
#include <set>
#include <string>

/**
 * @brief Clase para convertir gramáticas a Forma Normal de Chomsky
 * 
 * Pasos para la conversión a FNC:
 * 1. Eliminar símbolos inútiles
 * 2. Eliminar producciones vacías (&)
 * 3. Eliminar producciones unitarias
 * 4. Convertir producciones largas y mixtas (si es necesario)
 */
class GrammarConverter {
 public:
  explicit GrammarConverter(const GrammarModel& model, bool debug = false);
  ~GrammarConverter() = default;
  GrammarData ConvertToChomskyNormalForm();
 private:
  Symbol GetNextAux(GrammarData& new_data) const;
  std::string StringifyProduction(const std::vector<Symbol>& syms) const;
  void ProcessProduction(const Production& prod, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const;
  bool AddUniqueProduction(const Symbol& symbolOfProduction, const std::string& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const;
  void ReplaceTerminalsInProduction(std::vector<Symbol>& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const;
  void HandleBinaryOrLongProduction(const Symbol& symbolOfProduction, const std::vector<Symbol>& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const;
  Symbol FindExistingNonTerminalForProduction(const std::string& production, const std::set<std::pair<Symbol, std::string>>& unique_prods) const;
  const GrammarModel& model_;
  GrammarChecker checker_;
  bool debug_ = false;
};

#endif
