// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas - Forma Normal de Chomsky
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 03/11/2025
// Archivo grammar_checker.h:  agrupa las comprobaciones previas a la conversión
#ifndef GRAMMAR_CHECKER_H_
#define GRAMMAR_CHECKER_H_

#include "grammar_model.h"
#include <vector>
#include <string>
#include <set>

class GrammarChecker {
 public:
  explicit GrammarChecker(const GrammarModel& model);
  const Symbol& getInitial() const {return model_.getInitial();}
  ~GrammarChecker() = default;
  bool RunAll();
 private:
  const GrammarModel& model_;
  bool CheckEmpty(std::vector<std::string>& errors) const;
  bool CheckUnit(std::vector<std::string>& errors) const;
  bool CheckUseless(std::vector<std::string>& errors) const;
};

#endif
