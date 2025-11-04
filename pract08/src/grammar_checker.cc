// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas - Forma Normal de Chomsky
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_checker.cc: Implementación de GrammarChecker

#include "grammar_checker.h"
#include "production.h"
#include <iostream>
#include <string>
#include <set>

GrammarChecker::GrammarChecker(const GrammarModel& model) : model_(model) {}


/**
 * @brief ejecuta todos los test y comprueba que ninuno falle, termina imprimiendo los errores.
 * @return bool de si se pasaron los test o no
 */
bool GrammarChecker::RunAll() {
  std::vector<std::string> errors;
  bool valid = true;
  valid = (CheckEmpty(errors) && valid);
  valid = (CheckUnit(errors) && valid);
  valid = (CheckUseless(errors) && valid);
  if (!errors.empty()) {
    for (const auto& error : errors) {
      std::cerr << error << std::endl;
    }
  }
  return valid;
}

/**
 * @brief Test que comprueba las producciones vacias 
 * @param errors un vector pasado por referencia al que le añadiremos posibles errores
 * @return bool de si se paso el test o no
 */
bool GrammarChecker::CheckEmpty(std::vector<std::string>& errors) const {
  bool valid = true;
  for (const Production& prod : model_.GetProductions()) {
    const Cadena& body = prod.GetProduction();
    if(prod.GetNonTerminal() == getInitial()) {
      continue;
    }
    if (body.Longitud() == 0) {
      std::string error = "";
      error += "Error: la producción " + prod.ToString() + " es una producción vacía; la gramática es inválida.";
      errors.push_back(error);
      valid = false;
    }
  }
  return valid;
}


/**
 * @brief Test que comprueba las producciones unitarias 
 * @param errors un vector pasado por referencia al que le añadiremos posibles errores
 * @return bool de si se paso el test o no
 */
bool GrammarChecker::CheckUnit(std::vector<std::string>& errors) const {
  bool valid = true;
  for (const Production& prod : model_.GetProductions()) {
    const Cadena& body = prod.GetProduction();
    if (body.Longitud() == 1) {
      Symbol sym = body.GetSymbols()[0];
      if (model_.GetNonTerminals().Contains(sym)) {
        std::string error = "";
        error += "Error: la producción " + prod.ToString() + " es una producción unitaria; la gramática es inválida.";
        errors.push_back(error);
        valid = false;
      }
    }
  }
  return valid;
}

/**
 * @brief Test que comprueba las producciones inutiles 
 * @param errors un vector pasado por referencia al que le añadiremos posibles errores
 * @return bool de si se paso el test o no
 */
bool GrammarChecker::CheckUseless(std::vector<std::string>& errors) const {
  bool valid = true;
  // productores de cadenas
  std::set<Symbol> producesStrings;
  bool changed = true;
  while (changed) {
    changed = false;
    for (const Production& prod : model_.GetProductions()) {
      Symbol nonTerminal = prod.GetNonTerminal();
      if (producesStrings.contains(nonTerminal)) continue;
      bool isValid = true;
      for (const Symbol& symbol : prod.GetProduction().GetSymbols()) {
        if (model_.GetNonTerminals().Contains(symbol)) {
          if (!producesStrings.contains(symbol)) { 
            isValid = false; 
            break; 
          }
        } else {
        }
      }
      if (isValid) {
        producesStrings.insert(nonTerminal);
        changed = true;
      }
    }
  }

  // Alcanzables desde símbolo inicial
  std::set<Symbol> reachableFromS;
  std::vector<Symbol> non_terms = model_.GetNonTerminals().GetSymbols();
  std::set<Symbol> NontermsReachable;
  if (!non_terms.empty()) {
    Symbol start = non_terms[0];
    reachableFromS.insert(start);
    bool reach_changed = true;
    while (reach_changed) {
      reach_changed = false;
      for (const Production& prod : model_.GetProductions()) {
        if (!reachableFromS.contains(prod.GetNonTerminal())) continue;
        for (const Symbol& symbol : prod.GetProduction().GetSymbols()) {
          if(model_.GetNonTerminals().Contains(symbol) && !NontermsReachable.contains(symbol)) {
            NontermsReachable.insert(symbol);
          }
          if (model_.GetNonTerminals().Contains(symbol) && !reachableFromS.contains(symbol)) {
            reachableFromS.insert(symbol);
            reach_changed = true;
          }
        }
      }
    }
  }
  // Si existe algún no-terminal que no sea tanto reachableFromS y producesStrings, hay inútiles
  for (const Symbol& symbol : model_.GetNonTerminals().GetSymbols()) {
    if (!producesStrings.contains(symbol) || !reachableFromS.contains(symbol)) {
      std::string error = "";
      error += "Error: el símbolo " + symbol.ToString() + " es inútil (no productivo o no alcanzable); la gramática es inválida.";
      errors.push_back(error);
      valid = false;
    }
  }
  std::cout << "Terminales alcanzables desde S : " << model_.GetNonTerminals().GetSymbols()[0] << " "; 
  for ( Symbol& symbol : non_terms) {
    if (NontermsReachable.contains(symbol)) {
      std::cout << symbol << " ";
    }
  }
  std::cout << std::endl;
  return valid;
}
