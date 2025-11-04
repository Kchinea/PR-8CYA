// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 2: Cadenas y lenguajes
// Autor: Kyliam Chinea Salcedo
// Correo: alu0101548050@ull.edu.es
// Fecha: 17/09/20245
// Archivo cya-P02-strings.cc: programa cliente.
// Contiene la funcion main del proyecto que usa las clases X e Y
// para que una vez recibimos en un fichero una cadena y despues de un espacio el alfabeto,
//con esto tenemos que segun el codigo que nos den insertar en el fichero de salida 
//1. Alfabeto:, 2. Longitud, 3. Inversa:, 4. Prefijos, 5. Sufijos:.
// Referencias:
// Enlaces de interes
// Historial de revisiones
// 20/09/20245 - Creacion (primera version) del codigo

#ifndef CADENA_H_
#define CADENA_H_

#include "alphabet.h"
#include "symbol.h"
#include <vector>
#include <iostream>

class Cadena {
 public:
  Cadena() = default;
  Cadena(const std::vector<Symbol>& symbols);
  Cadena(const std::string& str); 
  size_t Longitud() const;
  const std::vector<Symbol>& GetSymbols() const { return symbols_; }
  bool ComprobarAlf(const Alphabet&) const;
  Cadena Reverse() const;
  std::string ToString() const;
  bool operator<(const Cadena& other) const {return symbols_ < other.symbols_;}
  friend std::ostream& operator<<(std::ostream&, const Cadena&);
  friend std::istream& operator>>(std::istream&, Cadena&);

 private:
  std::vector<Symbol> symbols_;
};

std::ostream& operator<<(std::ostream&, const Cadena&);
std::istream& operator>>(std::istream&, Cadena&);

#endif