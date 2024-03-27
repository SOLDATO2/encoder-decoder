# Encoder-Decoder
Integrantes:
>Felipe Porto Caldeira do Nascimento

>Alexandre Wahl

# Objetivo
Este projeto visa demonstrar como uma string pode ser codificada na base64 e SHA256. 

# Funções
O projeto contem as seguintes funções:

**base64Encode(std::string String)**

Recebe uma string e retorna outra codificada na base64 (não aceita numeros e nem caracteres especiais alem de '+' e '/'

**base64Decode(std::string String)**

Recebe uma string codificada na base64 e retorna uma string legivel

**std::string sha256Encode(std::string FraseParaTraduzirSHA256)**

Recebe uma string e retorna uma string codificada em SHA256

**std::string generateCombinations(std::string SHA256)**

Recebe uma string codificada em SHA256 e utiliza brute force para encontrar uma string que possui o mesmo hash inserido na função e retorna a string decodificada caso seja encontrado uma. (não aceita caracteres especiais, espaços e numeros)*
