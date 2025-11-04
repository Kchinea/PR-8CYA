// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas - Forma Normal de Chomsky
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_converter.cc: implementación de la clase GrammarConverter.

#include "grammar_converter.h"
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdlib>

/**
 * @brief Constructor que inicializa el convertidor con un modelo de gramática.
 * @param model Referencia constante al modelo de gramática.
 */
GrammarConverter::GrammarConverter(const GrammarModel& model, bool debug) : model_(model), checker_(model_), debug_(debug) {}

/**
 * @brief Obtiene un símbolo no-terminal auxiliar disponible (A..Z) e lo inserta
 * en new_data.non_terminals. Si no queda ninguno, termina con error.
 * @param new_data Estructura donde se insertará el nuevo no-terminal
 * @return Symbol nuevo no-terminal asignado
 */
Symbol GrammarConverter::GetNextAux(GrammarData& new_data) const {
  for (char letter = 'A'; letter <= 'Z'; ++letter) {
    Symbol symbol(letter);
    bool used = false;
    for (const Symbol& existing : new_data.non_terminals.GetSymbols()) {
      if (existing == symbol) { 
        used = true; 
        break; 
      }
    }
    if (!used) {
      new_data.non_terminals.Insert(symbol);
      return symbol;
    }
  }
  std::cerr << "Error: demasiadas producciones; no quedan letras mayusculas para representarlas.\n";
  std::exit(1);
}

/**
 * @brief Inserta una producción (lhs -> Production) en el conjunto unique_prods si no
 * existe ya. Si debug_ está activo imprime la producción creada.
 * @return true si la producción fue insertada (era nueva), false si ya existía
 */
bool GrammarConverter::AddUniqueProduction(const Symbol& symbolOfProduction, const std::string& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const {
  auto res = unique_prods.insert({symbolOfProduction, production});
  bool inserted = res.second;
  if (debug_ && inserted) {
    std::vector<Symbol> syms;
    for (char c : production) {
      syms.push_back(Symbol(c));
    }
    Production productionAdded(symbolOfProduction, Cadena(syms));
    std::cout << "[DEBUG] Created production: " << productionAdded << std::endl;
  }
  return res.second;
}

/**
 * @brief Reemplaza terminales en un Production largo por no-terminales auxiliares.
 * Si ya existe un no-terminal que produzca el terminal, se reutiliza.
 */
void GrammarConverter::ReplaceTerminalsInProduction(std::vector<Symbol>& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const {
  for (Symbol& symbol : production) {
    if (new_data.terminals.Contains(symbol)) {
      std::string termStr(1, symbol.GetChar());
      Symbol existing = FindExistingNonTerminalForProduction(termStr, unique_prods);
      if (existing.GetChar() != '\0') {
        symbol = existing;
      } else {
        Symbol aux = GetNextAux(new_data);
        AddUniqueProduction(aux, termStr, new_data, unique_prods);
        symbol = aux;
      }
    }
  }
}


Symbol GrammarConverter::FindExistingNonTerminalForProduction(const std::string& production, const std::set<std::pair<Symbol, std::string>>& unique_prods) const {
  for (const auto& p : unique_prods) {
    if (p.second == production) return p.first;
  }
  return Symbol('\0');
}

/**
 * @brief Maneja producciones binarias y de longitud >2, descomponiéndolas en
 * producciones binarias mediante no-terminales auxiliares.
 */
void GrammarConverter::HandleBinaryOrLongProduction(const Symbol& symbolOfProduction, const std::vector<Symbol>& production, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const {
  if (production.size() == 2) {
    AddUniqueProduction(symbolOfProduction, StringifyProduction(production), new_data, unique_prods);
    return;
  }
  std::vector<Symbol> symbols(production);
  Symbol prev_left = symbolOfProduction;
  size_t m = symbols.size();
  for (size_t i = 0; i < m - 2; ++i) {
    Symbol B1 = symbols[i];
    Symbol B2 = GetNextAux(new_data);
    std::vector<Symbol> pairSyms = {B1, B2};
    AddUniqueProduction(prev_left, StringifyProduction(pairSyms), new_data, unique_prods);
    prev_left = B2;
  }
  if (m >= 3) {
    Symbol last1 = symbols[m-2];
    Symbol last2 = symbols[m-1];
    std::vector<Symbol> pairSyms = {last1, last2};
    AddUniqueProduction(prev_left, StringifyProduction(pairSyms), new_data, unique_prods);
  }
}

/**
 * @brief Convierte un vector de Symbol en su representación plana Production como
 * std::string (concatenando los caracteres de cada símbolo).
 */
std::string GrammarConverter::StringifyProduction(const std::vector<Symbol>& syms) const {
  std::string resultString;
  for (const Symbol& sym : syms) {
    char c = sym.GetChar();
    if (c != '\0') resultString.push_back(c);
    else resultString += sym.ToString();
  }
  return resultString;
}

/**
 * @brief Procesa una producción del modelo original: maneja casos triviales,
 * sustituye terminales y descompone en producciones binarias.
 */
void GrammarConverter::ProcessProduction(const Production& prod, GrammarData& new_data, std::set<std::pair<Symbol, std::string>>& unique_prods) const {
  Symbol symbolOfProduction = prod.GetNonTerminal();
  std::vector<Symbol> production = prod.GetProduction().GetSymbols();
  if (production.empty() || (production.size() == 1 && new_data.terminals.Contains(production[0]))) {
    AddUniqueProduction(symbolOfProduction, StringifyProduction(production), new_data, unique_prods);
    return;
  }
  if (production.size() >= 2) {
    ReplaceTerminalsInProduction(production, new_data, unique_prods);
  }
  HandleBinaryOrLongProduction(symbolOfProduction, production, new_data, unique_prods);
}


/**
 * @brief Convierte la gramática a Forma Normal de Chomsky
 * @return GrammarData con la gramática en FNC
 */
GrammarData GrammarConverter::ConvertToChomskyNormalForm() {
  std::cout << "=== CONVERSIÓN A FORMA NORMAL DE CHOMSKY ===" << std::endl;
  if (!checker_.RunAll()) {
    std::exit(1);
  }
  std::cout << "Checks pasaron: procediendo a la conversión (Algoritmo 1)..." << std::endl;
  GrammarData new_data;
  new_data.terminals = model_.GetTerminals();
  new_data.non_terminals = model_.GetNonTerminals();
  std::set<std::pair<Symbol, std::string>> unique_prods;
  for (const Production& prod : model_.GetProductions()) {
    ProcessProduction(prod, new_data, unique_prods);
  }
  for (const auto& pair : unique_prods) {
    const std::string& production = pair.second;
    std::vector<Symbol> syms;
    for (char c : production) {
      syms.push_back(Symbol(c));
    }
    new_data.productions.push_back(Production(pair.first, Cadena(syms)));
    if (debug_) {
      std::cout << "[DEBUG] Final production added: " << new_data.productions.back() << std::endl;
    }
  }
  std::cout << "=== CONVERSIÓN COMPLETADA ===" << std::endl;
  return new_data;
}

