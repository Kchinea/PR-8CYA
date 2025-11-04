// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 2: Cadenas y lenguajes
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 17/09/2025
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funcion main del proyecto que usa las clases X e Y
// para que una vez recibimos en un fichero una cadena y despues de un espacio el alfabeto,
//con esto tenemos que segun el codigo que nos den insertar en el fichero de salida 
//1. Alfabeto:, 2. Longitud, 3. Inversa:, 4. Prefijos, 5. Sufijos:.
// Referencias:
// Enlaces de interes
// Historial de revisiones
// 20/09/2025 - Creacion (primera version) del codigo

#include "cadena.h"


Cadena::Cadena(const std::vector<Symbol>& symbols) : symbols_{symbols} {}

Cadena::Cadena(const std::string& string) {
  for (char c : string) {
    symbols_.push_back(Symbol(c));
  }
}

std::string Cadena::ToString() const {
  std::string result;
  for (const Symbol& symbol : GetSymbols()) {
    result += symbol.ToString();
  }
  return result;
}

std::ostream& operator<<(std::ostream& stream, const Cadena& cadena) {
  for (const auto& symbol : cadena.symbols_) {
    stream << symbol;
  }
  return stream;
}

std::istream& operator>>(std::istream& stream, Cadena& cadena) {
  cadena.symbols_.clear();
  Symbol symbol;
  while (stream >> symbol) {
    cadena.symbols_.push_back(symbol);
  }
  return stream;
}


/**
 * @brief Comprueba si todos los símbolos de la cadena pertenecen al alfabeto dado.
 *
 * Esta función verifica que cada símbolo en la cadena esté presente en el alfabeto proporcionado.
 * Si la cadena contiene únicamente el símbolo nulo ('\0'), se considera válida.
 *
 * @param alfabeto Referencia constante al alfabeto contra el cual se verifica la cadena.
 * @return true Si todos los símbolos de la cadena pertenecen al alfabeto.
 * @return false Si algún símbolo de la cadena no pertenece al alfabeto.
 */
bool Cadena::ComprobarAlf(const Alphabet& alfabeto) const {
  bool result = true;
  if (this->symbols_.size() == 1 && this->symbols_[0].GetChar() == '\0')
    return true;
  for (Symbol symbol : this->symbols_) {
    if (result == false)
      return false;
    for (Symbol simbolo : alfabeto.GetAlphabet()) {
      if (simbolo == symbol) {
        result = true;
        break;
      } else {
        result = false;
      }
    }
  }
  return result;
}


/**
 * @brief Obtiene la longitud de la cadena.
 *
 * Si la cadena contiene únicamente el carácter nulo ('\0'), se considera que su longitud es 0.
 * En caso contrario, devuelve el número de símbolos almacenados en la cadena.
 *
 * @return Tamaño de la cadena como un valor de tipo size_t.
 */
size_t Cadena::Longitud() const {
  if(this->symbols_.size() == 1 && this->symbols_[0].GetChar() == '\0')
    return 0;
  return this->symbols_.size();
}


/**
 * @brief Devuelve una versión invertida del objeto Cadena actual.
 *
 * Recorre los símbolos de la Cadena en orden inverso y construye una nueva Cadena.
 *
 * @return Cadena La representación invertida de la Cadena.
 */
Cadena Cadena::Reverse() const {
  std::vector<Symbol> result;
  for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it) {
    result.push_back(*it);
  }
  return Cadena(result);
}

