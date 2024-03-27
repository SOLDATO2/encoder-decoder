#include <iostream>
#include <vector>

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

std::string decimalParaBinario(int decimal) {
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