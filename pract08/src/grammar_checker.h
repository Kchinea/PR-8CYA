// GrammarChecker: agrupa las comprobaciones previas a la conversión
#ifndef GRAMMAR_CHECKER_H_
#define GRAMMAR_CHECKER_H_

#include "grammar_model.h"
#include <vector>
#include <string>
#include <set>

class GrammarChecker {
 public:
  explicit GrammarChecker(const GrammarModel& model);
  ~GrammarChecker() = default;
  bool RunAll();
 private:
  const GrammarModel& model_;
  bool CheckEmpty(std::vector<std::string>& errors) const;
  bool CheckUnit(std::vector<std::string>& errors) const;
  bool CheckUseless(std::vector<std::string>& errors) const;
};

#endif
