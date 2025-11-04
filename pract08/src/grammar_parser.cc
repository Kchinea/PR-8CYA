// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_parser.cc: implementación de la clase GrammarParser.

#include "grammar_parser.h"

/**
 * @brief Constructor de la clase GrammarParser
 * @param filename Nombre del archivo a parsear
 */
GrammarParser::GrammarParser(const std::string& filename) : filename_(filename) {
  file_.open(filename);
  if (!file_.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
  }
}

/**
 * @brief Parsea el archivo y retorna los datos de la gramática
 * @return Estructura GrammarData con la información de la gramática
 */
GrammarData GrammarParser::Parse() {
  GrammarData data;
  if (!IsFileOpen()) {
    std::cerr << "Error: Archivo no está abierto para lectura." << std::endl;
    return data;
  }
  data.terminals = ReadTerminals();
  data.non_terminals = ReadNonTerminals();
  data.productions = ReadProductions(data.terminals, data.non_terminals);
  file_.close();
  return data;
}

/**
 * @brief Lee los símbolos terminales del archivo
 * @return Alphabet con los símbolos terminales
 */
Alphabet GrammarParser::ReadTerminals() {
  Alphabet terminals;
  int num_terminals;
  file_ >> num_terminals;
  file_.ignore();
  for (int i = 0; i < num_terminals; ++i) {
    std::string line;
    std::getline(file_, line);
    if (!line.empty()) {
      for (char c : line) {
        if (c != ' ' && c != '\t') {
          terminals.Insert(Symbol(c));
        }
      }
    }
  }
  return terminals;
}

/**
 * @brief Lee los símbolos no terminales del archivo
 * @return Alphabet con los símbolos no terminales
 */
Alphabet GrammarParser::ReadNonTerminals() {
  Alphabet non_terminals;
  int num_non_terminals;
  file_ >> num_non_terminals;
  file_.ignore();
  for (int i = 0; i < num_non_terminals; ++i) {
    std::string line;
    std::getline(file_, line);
    if (!line.empty()) {
      for (char c : line) {
        if (c != ' ' && c != '\t') {
          non_terminals.Insert(Symbol(c));
        }
      }
    }
  }
  return non_terminals;
}

/**
 * @brief Lee las producciones del archivo con validación
 * @param terminals Alfabeto de símbolos terminales
 * @param non_terminals Alfabeto de símbolos no terminales
 * @return Vector con las producciones validadas
 */
std::vector<Production> GrammarParser::ReadProductions(const Alphabet& terminals, const Alphabet& non_terminals) {
  std::vector<Production> productions;
  int num_productions;
  file_ >> num_productions;
  file_.ignore();
  for (int i = 0; i < num_productions; ++i) {
    std::string line;
    std::getline(file_, line);
    if (line.empty()) continue;
    std::istringstream iss(line);
    char non_terminal_char;  
    if (iss >> non_terminal_char) {
      Symbol non_terminal(non_terminal_char);
      if (!non_terminals.Contains(non_terminal)) {
        std::cerr << "Error: Símbolo no terminal '" << non_terminal_char 
                  << "' no está en el alfabeto de no terminales (producción " << (i+1) << ")" << std::endl;
        continue;
      }
      std::string production_str;
      std::getline(iss, production_str);
      if (!production_str.empty() && production_str[0] == ' ') {
        production_str = production_str.substr(1);
      }
      bool valid_production = true;
      for (char c : production_str) {
        if (c != ' ' && c != '\t' && c != '&') {  // Permitir & como epsilon
          Symbol sym(c);
          if (!terminals.Contains(sym) && !non_terminals.Contains(sym)) {
            std::cerr << "Error: Símbolo '" << c << "' en la producción no está en ningún alfabeto (producción " 
                      << (i+1) << ")" << std::endl;
            valid_production = false;
            break;
          }
        }
      }
      if (valid_production) {
        Cadena production(production_str);
        productions.push_back(Production(non_terminal, production));
      }
    }
  }
  return productions;
}
