# Trabalho 3 - Estrutura de dados 1 
## Professor - Matheus Mendelson 
## Alunos 
* Gustavo Veloso - 17/0065251
* Wictor Girardi - 17/0047326
* Gustavo Afonso - 17/0034992 

## Execução do programa
Para a execução do trabalho entre na pasta Projeto3 e a partir do terminal execute o seguinte comando para a compilação: "$ gcc main.c ", em seguida execute o comando para a execução: " $ ./a.out ".

## Funcionamento 
Dentro do programa o usuário irá encontrar um menu com as principais funcionalidades do projeto, sendo elas: 
* 1 - Inserir novo registro
* 2 - Remover registro por nome
* 3 - Visualizar registro por nome
* 4 - Visualizar todos os registros
* 5 - Sair do programa

## 1 - Inserir novo registro
O programa irá solicitar ao usuário a entrada de dados como nome completo, endereço, data de nascimento, CEP e telefone para que sejam adicionados a lista de pessoas cadastradas. Foram implementadas as seguintes verificações de integridade para que o usuário não entre com os dados de forma errada:
* O usuário necessita entrar com o telefone dentro do formato 00000-0000 para que o número seja aceito no cadastro.
* O CEP não pode ter menos ou mais do que 10 dígitos.
* O nome deve ser completo e começar com letras maiusculas.
* a data de nascimento deve estar dentro do padrão xx/xx/xxxx.
* Um usuário cadastrado não pode ter nascido em uma data ainda não vivida.

## 2 - Remover registro por nome
O programa irá solicitar ao usuário que informe um nome já armazenado no registro para que ele possa ser deletado da lista. É necessesário que a entrada de dados seja feita com letras maiusculas tanto no nome quanto no sobrenome!

## 3 - Visualizar registro por nome
O programa irá solicitar ao usuário que ele informe um nome já armazenado no registro para que ele apresente na tela o cadastro com todos os dados da pessoa solicitada. É necessesário que a entrada de dados seja feita com letras maiusculas tanto no nome quanto no sobrenome!

## 4 - Visualizar todos os registros
O programa irá mostrar todos os registros armazenados na lista disponíveis ao usuário. 

## 5 - Sair do programa
O programa irá atualizar o arquivo *Contatos.txt* existente na pasta Projeto3 com os cadastros realizados e então irá terminar sua execução.
