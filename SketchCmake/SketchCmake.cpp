#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>

char intParaChar(int entrada) {
    if (entrada == 1) {
        return '1';
    }
    else if (entrada == 0) {
        return '0';
    }
}

int charParaInt(char entrada) {
    if (entrada == '1') {
        return 1;
    }
    else if (entrada == '0') {
        return 0;
    }
}

std::string decimalParaBinario(int decimal)
{
    std::vector<int> binario;

    // Caso especial para o valor zero
    if (decimal == 0)
        binario.push_back(0);

    while (decimal > 0) {
        int sobra = decimal % 2;
        binario.push_back(sobra);
        decimal = decimal / 2;
    }

    // Preenche com zeros à esquerda para garantir que tenha 8 bits
    while (binario.size() < 8) {
        binario.push_back(0);
    }

    std::string binario_f;
    for (int x = binario.size() - 1; x >= 0; x--) {
        binario_f += intParaChar(binario[x]);
    }

    return binario_f;
}

int binarioParaDecimal(std::string casaBinaria) {
    int soma = 0;
    int tamanho = casaBinaria.size() - 1;
    for (int x = 0; x < 6; x++) {
        char casaChar = casaBinaria[tamanho];
        int potencia = pow(2, x);
        int casaInt = charParaInt(casaChar);
        soma = soma + (casaInt * potencia);
        tamanho--;
    }
    return soma;
}

int main() {
    std::string v64;
    std::string valorBinario;
    std::string colinha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string FraseParaTraduzir = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";

    for (int x = 0; x < FraseParaTraduzir.size(); x++) {
        std::string binario = decimalParaBinario(int(FraseParaTraduzir[x]));
        valorBinario += binario;
    }

    //adiciona padding
    while (valorBinario.size() % 6 != 0) {
        valorBinario += '0'; // adiciona os zeros no final da string
    }

    std::vector<std::string> vetTemp;
    int ultimaCasaSalva = 0;
    for (int l = 0; l < valorBinario.size(); l = l + 6) {
        std::string casaBinaria;
        for (int v = 6; v > 0; v--) {
            casaBinaria += valorBinario[ultimaCasaSalva];
            ultimaCasaSalva++;
        }
        vetTemp.push_back(casaBinaria);
    }

    //traduz string para decimal convertido
    for (int x = 0; x < vetTemp.size(); x++) {
        v64 += colinha[binarioParaDecimal(vetTemp[x])];
    }

    //adiciona padding na string base64
    while (v64.size() % 4 != 0) {
        v64 += '='; // adiciona os paddings no final da string
    }

    std::cout << v64;
}
