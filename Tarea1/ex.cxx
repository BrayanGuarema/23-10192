#include <vector>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream> // Librería necesaria para manejar archivos

using namespace std;

double mean(vector<double> v);
double variance(vector<double> v);
double pearson_r(vector<double> A, vector<double> B);
vector<char> dec_to_octopus(int n);
vector<char> dec_to_hexakaidecapus(int n);
vector<char> septapus_to_dec(vector<char> s);
vector<char> octopus_to_dec(vector<char> s);
vector<char> hexakaidecapus_to_dec(vector<char> s);
vector<char> septapus_to_octopus(vector<char> s);
vector<char> septapus_to_hexakaidecapus(vector<char> s);
vector<char> octapus_to_septapus(vector<char> s);
vector<char> octopus_to_hexakaidecapus(vector<char> s);
vector<char> hexakaidecapus_to_septapus(vector<char> s);
vector<char> hexakaidecapus_to_octopus(vector<char> s);

int main(){
  // 1. CREACIÓN DEL ARCHIVO METADATA.TXT
    ofstream archivo; // Creamos un objeto de flujo de salida
    archivo.open("metadata.txt"); // Creamos o abrimos el archivo

    if (archivo.is_open()) {
        archivo << "Modelo de IA usado: Gemini (Google)" << endl;
        archivo << "Algoritmo: Coeficiente de Correlacion de Pearson" << endl;
        archivo << "Autor: [Tu Nombre o ID]" << endl;
        archivo.close(); // Siempre cerrar el archivo al terminar
        cout << "Archivo 'metadata.txt' generado con exito." << endl;
    } else {
        cout << "Error al crear el archivo de metadatos." << endl;
    }
  return 0;
}

double mean(vector<double> v){
  double acum_v = 0;
  
  if (v.empty()){
    return 0;
  }
    
  for (int i = 0; i < v.size(); i++) {
    acum_v += v[i];
  }
  
  return acum_v / v.size();
}

double variance(vector<double> v){
  double acum = 0;
  
  if (v.empty()){
    return 0;
  } 

  for (int i = 0; i < v.size(); i++) {
    acum += (v[i] - mean(v)) * (v[i] - mean(v));
  }

  return acum / v.size();
}

double pearson_r(vector<double> A, vector<double> B){
  // Hecho con IA
  
  // Verificamos que tengan el mismo tamaño y no estén vacíos
    if (A.size() != B.size() || A.empty()) return 0;

    int n = A.size();
    double meanA = mean(A);
    double meanB = mean(B);

    double numerator = 0;
    double sumSqA = 0;
    double sumSqB = 0;

    for (int i = 0; i < n; i++) {
        double diffA = A[i] - meanA;
        double diffB = B[i] - meanB;

        // Numerador: Sumatoria de (Ai - mediaA) * (Bi - mediaB)
        numerator += diffA * diffB;
        
        // Denominador: Sumatorias de cuadrados para la desviación
        sumSqA += diffA * diffA;
        sumSqB += diffB * diffB;
    }

    double denominator = sqrt(sumSqA * sumSqB);

    // Evitamos la división por cero si uno de los vectores es constante
    if (denominator == 0) return 0;

    return numerator / denominator;
}

vector<char> dec_to_septapus(int n) {
    vector<char> reverso;
    vector<char> res;

    if (n == 0) {
        vector<char> r;
        r.push_back('0');
        return r;
    }
    
    while (n > 0) {
        int residuo = n % 7;
        reverso.push_back(residuo + '0');
        n = n / 7;
    }
    
    for (int i = reverso.size() - 1; i >= 0; i--) {
        res.push_back(reverso[i]);
    }
    return res;
}

vector<char> dec_to_octopus(int n) {
    vector<char> reverso;
    vector<char> res;

    if (n == 0) {
        vector<char> r;
        r.push_back('0');
        return r;
    }
    
    while (n > 0) {
        reverso.push_back((n % 8) + '0');
        n = n / 8;
    }

    for (int i = reverso.size() - 1; i >= 0; i--) {
        res.push_back(reverso[i]);
    }
    return res;
}

vector<char> dec_to_hexakaidecapus(int n) {
    vector<char> reverso;
    vector<char> res;

    if (n == 0) {
        vector<char> r;
        r.push_back('0');
        return r;
    }
    
    while (n > 0) {
        int residuo = n % 16;
        if (residuo < 10) {
            reverso.push_back(residuo + '0');
        } else {
            if (residuo == 10){
                reverso.push_back('A');
            } 
            if (residuo == 11){
                reverso.push_back('B');
            } 
            if (residuo == 12){
                reverso.push_back('C');
            } 
            if (residuo == 13){
                reverso.push_back('D');
            } 
            if (residuo == 14){
                reverso.push_back('E');
            } 
            if (residuo == 15) {
                reverso.push_back('F');
            }
        }
        n = n / 16;
    }
    
    for (int i = reverso.size() - 1; i >= 0; i--) {
        res.push_back(reverso[i]);
    }
    return res;
}

vector<char> septapus_to_dec(vector<char> s) {
    int suma = 0;
    vector<char> res;

    for (int i = 0; i < s.size(); i++) {
        int digito = s[i] - '0';
        suma = suma + digito * pow(7, s.size() - 1 - i);
    }
    
    if (suma == 0){
        res.push_back('0');
    } else {
        vector<char> temporal;
        while (suma > 0) {
            temporal.push_back((suma % 10) + '0');
            suma /= 10;
        }
        for (int i = temporal.size() - 1; i >= 0; i--) {
            res.push_back(temporal[i]);
        }
    }
    return res;
}

vector<char> octopus_to_dec(vector<char> s) {
    int suma = 0;
    vector<char> res;
    vector<char> temporal;

    for (int i = 0; i < s.size(); i++) {
        suma = suma + (s[i] - '0') * pow(8, s.size() - 1 - i);
    }
    
    while (suma > 0) {
        temporal.push_back((suma % 10) + '0');
        suma /= 10;
    }
    
    for (int i = temporal.size() - 1; i >= 0; i--){
        res.push_back(temporal[i]);
    } 
    return res;
}

vector<char> hexakaidecapus_to_dec(vector<char> s) {
    int suma = 0;
    vector<char> res;
    vector<char> temporal;

    for (int i = 0; i < s.size(); i++) {
        int d;
        if (s[i] >= '0' && s[i] <= '9') d = s[i] - '0';
        else if (s[i] == 'A') d = 10;
        else if (s[i] == 'B') d = 11;
        else if (s[i] == 'C') d = 12;
        else if (s[i] == 'D') d = 13;
        else if (s[i] == 'E') d = 14;
        else if (s[i] == 'F') d = 15;
        suma = suma + d * pow(16, s.size() - 1 - i);
    }
    
    while (suma > 0) {
        temporal.push_back((suma % 10) + '0');
        suma /= 10;
    }
    for (int i = temporal.size() - 1; i >= 0; i--){
        res.push_back(temporal[i]);
    } 
    return res;
}

vector<char> septapus_to_octopus(vector<char> s) {
    int dec = 0;
    for (int i = 0; i < s.size(); i++){
      dec += (s[i] - '0') * pow(7, s.size() - 1 - i);  
    } 
    return dec_to_octopus(dec);
}

vector<char> septapus_to_hexakaidecapus(vector<char> s) {
    int dec = 0;
    
    for (int i = 0; i < s.size(); i++){
        dec += (s[i] - '0') * pow(7, s.size() - 1 - i);
    }

    return dec_to_hexakaidecapus(dec);
}

vector<char> octapus_to_septapus(vector<char> s) {
    int dec = 0;
    
    for (int i = 0; i < s.size(); i++) {
        dec += (s[i] - '0') * pow(8, s.size() - 1 - i);
    }

    return dec_to_septapus(dec);
}

vector<char> octopus_to_hexakaidecapus(vector<char> s) {
    int dec = 0;

    for (int i = 0; i < s.size(); i++) {
        dec += (s[i] - '0') * pow(8, s.size() - 1 - i);
    }

    return dec_to_hexakaidecapus(dec);
}

vector<char> hexakaidecapus_to_septapus(vector<char> s) {
    int dec = 0;
    int d;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9'){
            d = s[i] - '0';
        } else {
            d = s[i] - 'A' + 10;
        } 
        dec += d * pow(16, s.size() - 1 - i);
    }

    return dec_to_septapus(dec);
}

vector<char> hexakaidecapus_to_octopus(vector<char> s) {
    int dec = 0;
    int d;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            d = s[i] - '0';
        } else {
            d = s[i] - 'A' + 10;
        }
        dec += d * pow(16, s.size() - 1 - i);
    }
    return dec_to_octopus(dec);
}
