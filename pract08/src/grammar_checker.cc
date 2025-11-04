// Implementación de GrammarChecker
#include "grammar_checker.h"
#include "production.h"
#include <iostream>
#include <string>
#include <set>

GrammarChecker::GrammarChecker(const GrammarModel& model) : model_(model) {}

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

bool GrammarChecker::CheckEmpty(std::vector<std::string>& errors) const {
  bool valid = true;
  for (const Production& prod : model_.GetProductions()) {
    const Cadena& body = prod.GetProduction();
    if (body.Longitud() == 0) {
      std::string error = "";
      error += "Error: la producción " + prod.ToString() + " es una producción vacía; la gramática es inválida.";
      errors.push_back(error);
      valid = false;
    }
  }
  return valid;
}

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

bool GrammarChecker::CheckUseless(std::vector<std::string>& errors) const {
  bool valid = true;
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

  // Alcanzables: desde símbolo inicial (primer no terminal en la lista)
  std::set<Symbol> reachableFromS;
  std::vector<Symbol> non_terms = model_.GetNonTerminals().GetSymbols();
  if (!non_terms.empty()) {
    Symbol start = non_terms[0];
    reachableFromS.insert(start);
    bool reach_changed = true;
    while (reach_changed) {
      reach_changed = false;
      for (const Production& prod : model_.GetProductions()) {
        if (!reachableFromS.contains(prod.GetNonTerminal())) continue;
        for (const Symbol& symbol : prod.GetProduction().GetSymbols()) {
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
  return valid;
}
