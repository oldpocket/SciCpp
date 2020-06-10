/****************************************************************
  * File: quaternion.h
  * Description: Represents a Quaternion, to be used in physics simulations
  * Author: Fabio Andreozzi Godoy
  * Date: ~/05/2005 - Modified: 09/06/2020
  */

#ifndef QUARTERNION_H
#define QUARTERNION_H

#include <iostream>
#include <cmath>

class QuaternionsError {
  public:
    QuaternionsError() {}
};

class DivisionByZero {
  public:
    DivisionByZero() {}
};

class InputError {
  public:
    InputError() {}
};

template <class T> 
class Quaternion {
  private:
    T q1, q2, q3, q4;
  public:
    Quaternion(T q1_ = 0, T q2_ = 0, T q3_ = 0, T q4_ = 0) : q1(q1_), q2(q2_), q3(q3_), q4(q4_) {}
    Quaternion( const Quaternion &c );
    void SetQuaternions(T q1_, T q2_, T q3_, T q4);
    T norma(void);
    Quaternion<T> conj(void) const;  // retorna o conjugado
    Quaternion inv(void) const;      // retorna o inverso
    void ShowQuaternions(void);        // imprime na tela o valor do quaternion
    // Prototipo dos operadores
    // Incremento e decremento
    Quaternion<T>& operator++(void)  { ++q1; ++q2; ++q3; ++q4; return *this; }      // ++a
    Quaternion<T>& operator--(void)  { --q1; --q2; --q3; --q4; return *this; }      // --a
    Quaternion<T>  operator++(int i) { return Quaternion(q1++, q2++, q3++, q4++); } // a++
    Quaternion<T>  operator--(int i) { return Quaternion(q1--, q2--, q3--, q4--); } // a--
    // Operadores de comparacao
    bool operator==(const Quaternion<T> &a) {
      return (a.q1==q1)&&(a.q2==q2)&&(a.q3==q3)&&(a.q4==q4); 
    };
    bool operator!=(const Quaternion<T> &a) {
      return (a.q1!=q1)&&(a.q2!=q2)&&(a.q3!=q3)&&(a.q4!=q4); 
    };
    // Operadores de atribuicao
    bool operator=(const Quaternion<T> &a) { q1=a.q1; q2=a.q2; q3=a.q3; q4=a.q4; return 1; }
    Quaternion<T>& operator+=(const Quaternion<T> &b) {
      q1 = q1 + b.q1;
      q2 = q2 + b.q2;
      q3 = q3 + b.q3;
      q4 = q4 + b.q4; 
      return *this;
    }
    Quaternion<T>& operator-=(const Quaternion<T> &b) {
      q1 = q1 - b.q1;
      q2 = q2 - b.q2;
      q3 = q3 - b.q3;
      q4 = q4 - b.q4; 
      return *this;
    }
    Quaternion<T>& operator*=(const Quaternion<T> &b) {
      q1 = q1 * b.q1;
      q2 = q2 * b.q2;
      q3 = q3 * b.q3;
      q4 = q4 * b.q4; 
      return *this;
    }
    Quaternion<T>& operator/=(const Quaternion<T> &b) {
      if (!(b.q1||b.q2||b.q3||b.q4)) throw DivisionByZero();
      q1 = q1 / b.q1;
      q2 = q2 / b.q2;
      q3 = q3 / b.q3;
      q4 = q4 / b.q4; 
      return *this;
    }
    // Multiplicacao, divisao, soma, subtracao
    friend Quaternion<T> operator*<>(const Quaternion<T> &, const Quaternion<T> &);
    friend Quaternion<T> operator/<>(const Quaternion<T> &, const Quaternion<T> &);
    friend Quaternion<T> operator+<>(const Quaternion<T> &, const Quaternion<T> &);
    friend Quaternion<T> operator-<>(const Quaternion<T> &, const Quaternion<T> &);
    // Entrada e saida por stream
    friend std::ostream& operator<< <> (std::ostream &a, const Quaternion<T> &b);
    friend std::istream& operator>> <> (std::istream &a,  Quaternion<T> &b);
};

// Atribui valores ao quaternion
template<class T> void Quaternion<T>::SetQuaternions(T q1_, T q2_, T q3_, T q4_) {
  q1 = q1_;
  q2 = q2_;
  q3 = q3_;
  q4 = q4_;
};

// Norma de um numero quaternion
template<class T> T Quaternion<T>::norma(void) {
  return sqrtf(q1*q1 + q2*q2 + q3*q3 + q4*q4);
};

// Conjugado de um numero quaternion
template<class T> Quaternion<T> Quaternion<T>::conj(void) const {
  Quaternion a;
  a.q1 = +q1;
  a.q2 = -q2;
  a.q3 = -q3;
  a.q4 = -q4;
  return a;
};

// Inverso de um numero quaternion
template<class T> Quaternion<T> Quaternion<T>::inv(void) const {
  Quaternion<T> c;
  T qq;
  qq = (q1 * q1) + (q2 * q2) + (q3 * q3) + (q4 * q4);
  if (!qq) throw DivisionByZero();
  c.q1 =  q1 / qq;
  c.q2 = -q2 / qq;
  c.q3 = -q3 / qq;
  c.q4 = -q4 / qq;
  return c;
};

// Exibe o quaternion na tela
template<class T> void Quaternion<T>::ShowQuaternions(void) {
  std::cout << "q = " << q1 << " + " << q2 << "i + ";
  std::cout << q3 << "j + " << q4 << "k" << std::endl;
};


// Sobrecarga dos operadores
// Multiplicacao
template<class T> Quaternion<T> operator*(const Quaternion<T> &a, const Quaternion<T> &b) {
  Quaternion<T> c;
  c.q1 = a.q1*b.q1 - a.q2*b.q2 - a.q3*b.q3 - a.q4*b.q4;
  c.q2 = a.q1*b.q2 + a.q2*b.q1 + a.q3*b.q4 - a.q4*b.q3;
  c.q3 = a.q1*b.q3 - a.q2*b.q4 + a.q3*b.q1 + a.q4*b.q2;
  c.q4 = a.q1*b.q4 + a.q2*b.q3 - a.q3*b.q2 + a.q4*b.q1;
  return c;
};
// Divisao
template<class T> Quaternion<T> operator/(const Quaternion<T> &a, const Quaternion<T> &b) {
  Quaternion<T> c = a * b.inv();
  return c;
};
// Soma
template<class T> Quaternion<T> operator+(const Quaternion<T> &a, const Quaternion<T> &b) {
  Quaternion<T> c;
  c.q1 = a.q1+b.q1;
  c.q2 = a.q2+b.q2;
  c.q3 = a.q3+b.q3;
  c.q4 = a.q4+b.q4;
  return c;
};
// Subtracao
template<class T> Quaternion<T> operator-(const Quaternion<T> &a, const Quaternion<T> &b) {
  Quaternion<T> c;
  c.q1 = a.q1-b.q1;
  c.q2 = a.q2-b.q2;
  c.q3 = a.q3-b.q3;
  c.q4 = a.q4-b.q4;
  return c;
};
// Saida stream
template<class T> std::ostream& operator<< (std::ostream &a, const Quaternion<T> &b) {
  a << "Saida: " << b.q1 << "," << b.q2 << "," << b.q3 << "," << b.q4 << std::endl; 
  return a;
}
// Entrada stream
template<class T> std::istream& operator>> (std::istream &a,  Quaternion<T> &b) {
  a >> b.q1;
  a.ignore();
  a >> b.q2;
  a.ignore();
  a >> b.q3;
  a.ignore();
  a >> b.q4;
  a.ignore();
  return a;
}


#endif // QUARTERNION_H
