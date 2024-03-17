#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <chrono>
// funcoes para criptografar string para base64 
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
//----------------------------------------------

//funcoes para decriptografar base64 para string legivel
char decodeCaractere(char c) {
    const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    auto it = base64Chars.find(c);
    if (it != std::string::npos) {
        return it; // Retorna a posição do caractere na string
    }
    else {
        return -1; // caractere inválido
    }
}

std::string base64Decode(std::string StringCodificada) {
    std::string decodedString;
    int bits = 0, buffer = 0;

    for (char c : StringCodificada) {
        if (c == '=') break; // padding encontrado, termina a decodificação

        int val = decodeCaractere(c);
        if (val == -1) continue; // caractere inválido, ignorado

        buffer = (buffer << 6) | val;
        bits += 6;

        while (bits >= 8) {
            bits -= 8;
            char decodedChar = buffer >> bits;
            decodedString.push_back(decodedChar);
        }
    }

    return decodedString;
}
//----------------------------------------------


//funcoes para criptografar string para SHA256

std::string rightRotate(std::string str, int x) {
    std::string result = str;
    int length = str.length();

    // Verifica se o valor de x é válido
    if (x >= length)
        return "Valor de x é maior ou igual ao tamanho da string.";

    // Move x posições para a direita
    for (int i = 0; i < length; ++i) {
        result[(i + x) % length] = str[i];
    }

    return result;
}

std::string rightShift(std::string input, int x) {
    std::string result = input;  // Cria uma cópia da string de entrada

    // Realiza o deslocamento à direita
    for (int i = 0; i < x; ++i) {
        char lastChar = result.back();  // Obtém o último caractere
        result.pop_back();  // Remove o último caractere
        result.insert(result.begin(), '0');  // Insere '0' no início
    }

    return result;
}

std::string XOR(std::string str1, std::string str2, std::string str3) {
    std::string result;
    for (size_t i = 0; i < str1.size(); ++i) {
        char s1 = str1[i];
        char s2 = str2[i];
        char s3 = str3[i];

        // Usando o operador XOR (^) para calcular o resultado
        char xor_result = (s1 ^ s2) ^ s3;
        result += xor_result;
    }
    return result;
}

std::string somar2Binarios(std::string bin1, std::string bin2) {
    // Verifica se as strings têm o tamanho correto (32 bits)
    if (bin1.size() != 32 || bin2.size() != 32) {
        return "Erro: As strings devem ter 32 bits cada.";
    }

    std::string resultado;
    int carry = 0; // Representa o bit de transporte

    // Percorre as strings da direita para a esquerda
    for (int i = 31; i >= 0; --i) {
        int bit1 = bin1[i] - '0'; // Converte char para int (0 ou 1)
        int bit2 = bin2[i] - '0';

        // Realiza a soma dos bits e do bit de transporte
        int soma = bit1 + bit2 + carry;
        resultado.insert(resultado.begin(), '0' + (soma % 2)); // Insere o bit no início da string
        carry = soma / 2; // Atualiza o bit de transporte
    }

    return resultado;
}
std::string somar4Binarios(std::string bin1, std::string bin2, std::string bin3, std::string bin4) {
    // Verifica se as strings têm o tamanho correto (32 bits)
    if (bin1.size() != 32 || bin2.size() != 32 || bin3.size() != 32 || bin4.size() != 32) {
        return "Erro: As strings devem ter 32 bits cada.";
    }

    std::string resultado;
    int carry = 0; // Representa o bit de transporte

    // Percorre as strings da direita para a esquerda
    for (int i = 31; i >= 0; --i) {
        int bit1 = bin1[i] - '0'; // Converte char para int (0 ou 1)
        int bit2 = bin2[i] - '0';
        int bit3 = bin3[i] - '0';
        int bit4 = bin4[i] - '0';

        // Realiza a soma dos bits e do bit de transporte
        int soma = bit1 + bit2 + bit3 + bit4 + carry;
        resultado.insert(resultado.begin(), '0' + (soma % 2)); // Insere o bit no início da string
        carry = soma / 2; // Atualiza o bit de transporte
    }

    return resultado;
}
std::string somar5Binarios(std::string bin1, std::string bin2, std::string bin3, std::string bin4, std::string bin5){
    // Verifica se as strings têm o tamanho correto (32 bits)
    if (bin1.size() != 32 || bin2.size() != 32 || bin3.size() != 32 || bin4.size() != 32 || bin5.size() != 32) {
        return "Erro: As strings devem ter 32 bits cada.";
    }

    std::string resultado;
    int carry = 0; // Representa o bit de transporte

    // Percorre as strings da direita para a esquerda
    for (int i = 31; i >= 0; --i) {
        int bit1 = bin1[i] - '0'; // Converte char para int (0 ou 1)
        int bit2 = bin2[i] - '0';
        int bit3 = bin3[i] - '0';
        int bit4 = bin4[i] - '0';
        int bit5 = bin5[i] - '0';

        // Realiza a soma dos bits e do bit de transporte
        int soma = bit1 + bit2 + bit3 + bit4 + bit5 + carry;
        resultado.insert(resultado.begin(), '0' + (soma % 2)); // Insere o bit no início da string
        carry = soma / 2; // Atualiza o bit de transporte
    }

    return resultado;
}

std::vector<std::string> calcularPartesFracionadas() {
    std::vector<std::string> results;
    int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311 };
    int numPrimes = sizeof(primes) / sizeof(primes[0]);

    for (int i = 0; i < numPrimes; ++i) {
        double cubeRoot = cbrt(primes[i]);
        double fractionalPart = cubeRoot - std::floor(cubeRoot);

        std::ostringstream bitRepresentation;
        for (int j = 0; j < 32; ++j) {
            fractionalPart *= 2;
            if (fractionalPart >= 1) {
                bitRepresentation << "1";
                fractionalPart -= 1;
            }
            else {
                bitRepresentation << "0";
            }
        }
        results.push_back(bitRepresentation.str());
    }

    return results;
}

std::string FuncaoChoice(std::string e, std::string f, std::string g) {
    if (e.length() != f.length() || f.length() != g.length()) {
        std::cerr << "As strings de entrada devem ter o mesmo comprimento." << std::endl;
        return "";
    }

    std::string result;
    for (size_t i = 0; i < e.length(); ++i) {
        bool e_bit = e[i] == '1';
        bool f_bit = f[i] == '1';
        bool g_bit = g[i] == '1';

        bool first_part = (e_bit && f_bit) ^ ((!e_bit) && g_bit);
        result += (first_part ? '1' : '0');
    }

    return result;
}

std::string FuncaoMajority(std::string a, std::string b, std::string c) {
    if (a.length() != b.length() || b.length() != c.length()) {
        std::cerr << "As strings de entrada devem ter o mesmo comprimento." << std::endl;
        return "";
    }

    std::string result;
    for (size_t i = 0; i < a.length(); ++i) {
        bool a_bit = a[i] == '1';
        bool b_bit = b[i] == '1';
        bool c_bit = c[i] == '1';

        bool majority_bit = (a_bit && b_bit) ^ (a_bit && c_bit) ^ (b_bit && c_bit);
        result += (majority_bit ? '1' : '0');
    }

    return result;
}

std::string binarioParaHexadecimal(std::string binario) {
    if (binario.length() != 32) {
        return "Erro: A string binária deve ter 32 bits.";
    }

    std::string resultado;
    for (size_t i = 0; i < binario.length(); i += 4) {
        int valor_decimal = 0;
        for (size_t j = 0; j < 4; ++j) {
            valor_decimal = (valor_decimal << 1) + (binario[i + j] - '0');
        }

        char digito_hexadecimal = (valor_decimal < 10) ? ('0' + valor_decimal) : ('a' + valor_decimal - 10);
        resultado += digito_hexadecimal;
    }

    return resultado;
}

std::string sha256Encode(std::string FraseParaTraduzirSHA256) {
    
    if (FraseParaTraduzirSHA256.size() > 55) {
        std::cout << "Nao foi possivel codificar em SHA256 pois a string tem um tamanho maior do que 55";
        return "";
    }
    else {
        std::string MessageBlock;

        //resulta em um bloco de 512 bits, caso o tamanho da frase para criptografar seja maior que 512 em binario (8 casas), o tamanho do bloco deve dobrar
        for (int x = 0; x < 512; x++) { // porem eu irei apenas fazer com um bloco de 512 bits
            MessageBlock += "0";
        }

        std::string valorBinarioSHA256;

        for (int x = 0; x < FraseParaTraduzirSHA256.size(); x++) {
            std::string binario = decimalParaBinario(int(FraseParaTraduzirSHA256[x]));
            valorBinarioSHA256 += binario;
        }

        //std::cout << valorBinarioSHA256 << std::endl;

        // insere o valor binario no MessageBlock
        int x1 = 0;
        while (x1 < valorBinarioSHA256.size()) {
            MessageBlock[x1] = valorBinarioSHA256[x1];
            x1++;
        }
        //adicionamos +1 no final do valor binario
        MessageBlock[x1] = '1';
        //std::cout << MessageBlock << std::endl;

        int tamanhoEmBits = FraseParaTraduzirSHA256.size() * 8;
        std::string tamanhoBinarioSHA256 = decimalParaBinario(tamanhoEmBits);

        int tamanhoMessageBlock = MessageBlock.size(); //pega o tamanho do messageBlock
        for (int x = tamanhoBinarioSHA256.size(); x >= 0; x--) {
            MessageBlock[tamanhoMessageBlock] = tamanhoBinarioSHA256[x];
            tamanhoMessageBlock--;
        }
        //std::cout << "------------------------------------------------------" << std::endl;
        /*for (int x = 0; x < MessageBlock.size(); x++) {
            if ((x + 1) % 32 == 0) {
                std::cout << "" << std::endl;
            }
            else {
                std::cout << MessageBlock[x];
            }
        }*/
        //std::cout << "------------------------------------------------------" << std::endl;

        //adicionar 

        std::vector<std::string> MessageSchedule;



        std::string BlocoTemp;
        for (int x = 0; x < MessageBlock.size(); x++) {
            if ((x + 1) % 32 == 0) {
                BlocoTemp += MessageBlock[x];
                MessageSchedule.push_back(BlocoTemp);
                BlocoTemp.clear();
            }
            else {
                BlocoTemp += MessageBlock[x];
            }
        }


        //std::cout << MessageSchedule.size() << std::endl;

        //Completa o vetor com 0s ate atingir 64 espacos no vetor.
        for (int x = 15; x < 63; x++) {
            MessageSchedule.push_back("00000000000000000000000000000000");
        }


        /*for (int x = 0; x < MessageSchedule.size(); x++) {
            std::cout << MessageSchedule[x];
            std::cout << "-> w";
            std::cout << x << std::endl;
        }*/
        //std::cout << "------------------------------------------------------" << std::endl;

        //calculo megamalvonico

        for (int x = 0; x < 48; x++) {
            std::string w0 = MessageSchedule[x];
            std::string w1 = MessageSchedule[x + 1];
            std::string w9 = MessageSchedule[x + 9];
            std::string w14 = MessageSchedule[x + 14];

            std::string σ0 = XOR(rightRotate(w1, 7), rightRotate(w1, 18), rightShift(w1, 3));
            std::string σ1 = XOR(rightRotate(w14, 17), rightRotate(w14, 19), rightShift(w14, 10));

            std::string w16 = somar4Binarios(w0, σ0, w9, σ1);
            MessageSchedule[x + 16] = w16;
        }

        /*for (int x = 0; x < MessageSchedule.size(); x++) {
            std::cout << MessageSchedule[x];
            std::cout << "-> w";
            std::cout << x << std::endl;
        }*/

        std::string h0, h1, h2, h3, h4, h5, h6, h7;

        h0 = "01101010000010011110011001100111";
        h1 = "10111011011001111010111010000101";
        h2 = "00111100011011101111001101110010";
        h3 = "10100101010011111111010100111010";
        h4 = "01010001000011100101001001111111";
        h5 = "10011011000001010110100010001100";
        h6 = "00011111100000111101100110101011";
        h7 = "01011011111000001100110100011001";
        //std::cout << "------------------------------------------------------" << std::endl;

        std::vector<std::string> K_constants = calcularPartesFracionadas();

        /*for (int x = 0; x < K_constants.size(); x++) {
            std::cout << K_constants[x] << std::endl;
        }*/

        std::string a, b, c, d, e, f, g, h;

        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;
        f = h5;
        g = h6;
        h = h7;
        // std::cout << "------------------------------------------------------" << std::endl;
        for (int x = 0; x < 64; x++) {
            std::string Σ1;
            Σ1 = XOR(rightRotate(e, 6), rightRotate(e, 11), rightRotate(e, 25));

            std::string Choice = FuncaoChoice(e, f, g);

            std::string Temp1 = somar5Binarios(h, Σ1, Choice, K_constants[x], MessageSchedule[x]);

            std::string Σ0 = XOR(rightRotate(a, 2), rightRotate(a, 13), rightRotate(a, 22));

            std::string Majority = FuncaoMajority(a, b, c);

            std::string Temp2 = somar2Binarios(Majority, Σ0);

            std::string Temp1_2 = somar2Binarios(Temp1, Temp2);

            std::string d_Temp1 = somar2Binarios(d, Temp1);

            h = g;
            g = f;
            f = e;
            e = d_Temp1;
            d = c;
            c = b;
            b = a;
            a = Temp1_2;


        }


        h0 = binarioParaHexadecimal(somar2Binarios(a, h0));
        h1 = binarioParaHexadecimal(somar2Binarios(b, h1));
        h2 = binarioParaHexadecimal(somar2Binarios(c, h2));
        h3 = binarioParaHexadecimal(somar2Binarios(d, h3));
        h4 = binarioParaHexadecimal(somar2Binarios(e, h4));
        h5 = binarioParaHexadecimal(somar2Binarios(f, h5));
        h6 = binarioParaHexadecimal(somar2Binarios(g, h6));
        h7 = binarioParaHexadecimal(somar2Binarios(h, h7));

        std::string SHA256;
        SHA256 += h0;
        SHA256 += h1;
        SHA256 += h2;
        SHA256 += h3;
        SHA256 += h4;
        SHA256 += h5;
        SHA256 += h6;
        SHA256 += h7;

        return SHA256;
    }
    
    
}
//----------------------------------------------

//funcoes para decriptografar SHA256

std::string generateCombinations(std::string SHA256) {
    int maxLength = 55;
    std::vector<char> alphabet;
    for (char c = 'a'; c <= 'z'; ++c) {
        alphabet.push_back(c);
    }

    for (int length = 1; length <= maxLength; ++length) {
        std::vector<int> indices(length, 0);
        std::vector<char> combination(length, 'a');

        int size = alphabet.size();
        while (true) {
            for (int i = 0; i < length; ++i) {
                combination[i] = alphabet[indices[i]];
            }

            // Generate all mixed-case combinations
            for (int i = 0; i < (1 << length); ++i) {
                for (int j = 0; j < length; ++j) {
                    if ((i & (1 << j)) != 0) {
                        combination[j] = toupper(alphabet[indices[j]]);
                    }
                    else {
                        combination[j] = alphabet[indices[j]];
                    }
                }
                std::string stringTemporaria;
                for (int x = 0; x < combination.size(); x++) {
                    stringTemporaria += combination[x];
                }

                std::string possivelSHA = sha256Encode(stringTemporaria);
                std::cout << stringTemporaria << std::endl;

                if (possivelSHA == SHA256) {
                    std::cout << "SHA256 ENCONTRADO!" << std::endl;

                    std::cout << SHA256;
                    std::cout << "<---SHA256 INSERIDO NA FUNCAO PARA SER ENCONTRADA" << std::endl;
                    std::cout << possivelSHA;
                    std::cout << "<---SHA256 CALCULADO VIA BRUTEFORCE" << std::endl;
                    return stringTemporaria;

                }


            }

            int k = length - 1;
            while (k >= 0 && indices[k] == size - 1) {
                k--;
            }

            if (k < 0) {
                break;
            }

            indices[k]++;
            for (int j = k + 1; j < length; ++j) {
                indices[j] = 0;
            }
        }
    }
}
//----------------------------------------------
int main() {
    std::string v64;
    std::string valorBinario;
    std::string colinha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string FraseParaTraduzir = "Man";

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

    std::cout << FraseParaTraduzir;
    std::cout << "<--- String original" << std::endl;

    std::cout << v64;
    std::cout << "<--- String na base64" << std::endl;

    std::cout << base64Decode(v64);
    std::cout << "<--- String decodificada" << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;

    //HMAC SHA256-----------------------------------------------------------------------------------------------------------------------------------------
    std::string stringParaSHA256 = "zzz";
    std::string SHA256 = sha256Encode(stringParaSHA256);
    if (SHA256 != "") {
        std::cout << "Frase que sera inserida no encode sha256: ";
        std::cout << stringParaSHA256 << std::endl;
        std::cout << "Resultado do encoder que tambem deve ser o resultado esperado do decoder: " << std::endl;
        std::cout << SHA256 << std::endl;

        std::cout << "ATENCAO: Este calculo pode demorar MUITO tempo dependendo do tamanho da string." << std::endl;
        std::cout << "Pressione Enter para continuar..." << std::endl;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        std::cin.get();

        auto start = std::chrono::high_resolution_clock::now();
        
        std::string stringFinal = generateCombinations(SHA256);

        std::cout << stringFinal;
        std::cout << "<--- STRING QUE CORRESPONDE A SHA ENCONTRADO" << std::endl;
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
    }
}
