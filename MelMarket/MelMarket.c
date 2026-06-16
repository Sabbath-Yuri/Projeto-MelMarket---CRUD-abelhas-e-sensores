#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define max_abelhas 50
#define max_sensores 100
#define valor_mel_kg 25.0
#include <windows.h>

typedef struct tabela_abelha
{
    int id;
    char nome_popular[40];
    char nome_cientifico[50];
    int regiao;
    float producao_de_mel;
} tabela_abelha;

typedef struct tabela_sensores
{
    int id;
    char tipo[30];
    float valor;
    int idAbelha;
} tabela_sensores;

void pesquisar_abelhas(int a, char pesquisa[], tabela_abelha abelhas[]);
void ler_texto(char palavra[], int tamanho);
void listar_abelhas(int a, tabela_abelha abelhas[]);
void mostrar_abelha(int a, tabela_abelha abelhas[]);
float ler_float(float min);
int ler_inteiro(int min, int max);
void ler_dados_abelha(tabela_abelha abelhas[], int qtdabelhas);
int buscar_abelha_id (tabela_abelha abelhas[], int qtdabelhas, int alterar_dados_id);
void alterar_abelha(tabela_abelha abelhas[], int alvo);
void remover_abelha(int alvo, int *qtdabelhas, tabela_abelha abelhas[], int *qtdsensores, int id_abelha, tabela_sensores sensores[]);
void ler_dados_sensores(tabela_sensores sensores[], int qtdsensores, int qtdabelhas, tabela_abelha abelhas[]);
void mostrar_idabelha_disponiveis(tabela_abelha abelhas[], int qtdabelhas);
void listar_sensores(int a, tabela_sensores sensores[]);
void mostrar_sensor(int a, tabela_sensores sensores[]);
void buscar_sensor_por_idabelha(int alvo, int qtdsensores, tabela_sensores sensores[], tabela_abelha abelhas[], int qtdabelhas);
int buscar_sensor_id (tabela_sensores sensores[], int qtdsensores, int id_digitado);
void mostrar_idsensor_disponiveis(tabela_sensores sensores[], int qtdsensores);
void remover_sensor(int alvo, int *qtsensores, tabela_sensores sensores[]);
int remover_sensor_idAbelha(int id_abelha, int *qtdsensores, tabela_sensores sensores[]);
void alterar_leitura_sensor(tabela_sensores sensores[], int alvo);
float producao_de_mel(tabela_abelha abelhas[], int qtdabelhas);
int quantidade_sensores_temp(tabela_sensores sensores[], int qtdsensores);
float media_temperatura_sensores(tabela_sensores sensores[], int qtdsensores);
void escolher_regiao_abelha(tabela_abelha abelhas[], int alvo);
void abelhas_por_regiao (int qtdabelhas, tabela_abelha abelhas[]);
float estoque_mel(int qtdabelhas, tabela_abelha abelhas[]);
void menu_abelhas(int *qtdabelhas, int *prox_id_abelha, tabela_abelha abelhas[], int *qtdsensores, tabela_sensores sensores[]);
void menu_sensore(int *qtdabelhas, int *prox_id_sensor, tabela_abelha abelhas[], int *qtdsensores, tabela_sensores sensores[]);
void menu_relatorios(int qtdabelhas, tabela_abelha abelhas[], int qtdsensores, tabela_sensores sensores[]);




int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
    int opcao;
    int qtdabelhas = 0, qtdsensores = 0, prox_id_abelha = 1, prox_id_sensor = 1;
    tabela_abelha abelhas[max_abelhas] = {0};
    tabela_sensores sensores[max_sensores] = {0};
    do
    {
        system("clear||cls");
        printf("===== SISTEMA MelMarket =====\n");
        printf("1. Gerenciar abelhas.\n2. Gerenciar Sensores.\n3. Relatórios.\n4. Sair.");
        printf("\nEscolha uma opção: ");
        opcao = ler_inteiro(1, 4);
        switch (opcao)
        {
        case 1:
            menu_abelhas(&qtdabelhas, &prox_id_abelha, abelhas, &qtdsensores, sensores);
            break;

        case 2:
            menu_sensore(&qtdabelhas, &prox_id_sensor, abelhas, &qtdsensores, sensores);
            break;

        case 3:
           menu_relatorios(qtdabelhas, abelhas, qtdsensores, sensores);
            break;

        case 4:
            break;

        }
    } while (opcao != 4);
    return 0;
}

void ler_texto(char palavra[], int tamanho)//função para ler, verificar e modularizar textos(strings)
{
    int c;
    fgets(palavra, tamanho, stdin);
    if (strchr(palavra, '\n') == NULL)
    {
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
    int k = 0;
    while (palavra[k] != '\0')
    {
        if (palavra[k] == '\n')
        {
            palavra[k] = '\0';
        }
        k++;
    }
}

void pesquisar_abelhas(int a, char pesquisa[], tabela_abelha abelhas[])//busca uma abelha através da posição dela no vetor de struct
{
    int encontrou = 0;
    if (pesquisa[0] == '\0')
    {
        printf("Pesquisa vazia\n");
        return;
    }
    for (int i = 0; i < a; i++)
    {
        int diferente = 0, j = 0;
        while (pesquisa[j] != '\0' && abelhas[i].nome_popular[j] != '\0' && diferente == 0)
        {
            char letra_pesquisa = pesquisa[j];
            char letra_nome = abelhas[i].nome_popular[j];
            if (letra_pesquisa >= 'A' && letra_pesquisa <= 'Z')
            {
                letra_pesquisa += 32;
            }
            if (letra_nome >= 'A' && letra_nome <= 'Z')
            {
                letra_nome += 32;
            }
            if (letra_pesquisa != letra_nome)
            {
                diferente = 1;
            }
            j++; 
        }
        if (pesquisa[j] != '\0')
        {
            diferente = 1;
        }
        if (diferente == 0)
        {
            encontrou = 1;
            mostrar_abelha(i, abelhas);
        }
    }
    if (encontrou == 0)
    {
        printf("Não foram encontradas abelhas que correspondam a pesquisa\n");
    }
}

void listar_abelhas(int a, tabela_abelha abelhas[])//Lista todas as abelhas
{
    for (int i = 0; i < a; i++)
    {
        mostrar_abelha(i, abelhas);
    }
}

void mostrar_abelha(int a, tabela_abelha abelhas[])//Mostra uma abelha em específico atráves da posição dela no vetor de struct
{
    printf("Id: %d\n", abelhas[a].id);
    printf("Nome popular: %s\n", abelhas[a].nome_popular);
    printf("Nome científico: %s\n", abelhas[a].nome_cientifico);
    switch (abelhas[a].regiao)
    {
    case 1:
        printf("Regiao: Norte\n");
        break;
    
    case 2:
        printf("Regiao: Nordeste\n");
        break;

    case 3:
        printf("Regiao: Centro-Oeste\n");
        break;

    case 4:
        printf("Regiao: Sudeste\n");
        break;

    case 5:
        printf("Regiao: Sul\n");
        break;

    }
    printf("Produção de mel (em kg/mês): %.2f kg\n\n", abelhas[a].producao_de_mel);
}

int ler_inteiro(int min, int max)//Função para ler, modularizar e verificar valores inteiros
{
    int lixo, numero;
    while (scanf("%d", &numero) != 1 || numero < min || numero > max)
    {
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        printf("Entrada inválida, tente novamente: ");
    }
    while ((lixo = getchar()) != '\n' && lixo != EOF);
    return numero;
}

float ler_float(float min)//Função para ler, modularizar e verificar valores float
{
    float numero;
    int lixo;
    while ((scanf("%f", &numero) != 1) || numero < min)
    {
        while ((lixo = getchar()) != '\n' && lixo != EOF);
        printf("Entrada inválida\n");
    }
    while ((lixo = getchar()) != '\n' && lixo != EOF);
    return numero;
}
void ler_dados_abelha(tabela_abelha abelhas[], int qtdabelhas)//Função para ler os dados da abelha que será cadastrada
{
    printf("\n");
    printf("Digite o nome popular da abelha: ");
    ler_texto(abelhas[qtdabelhas].nome_popular, 40);
    printf("Digite o nome cientifico da abelha: ");
    ler_texto(abelhas[qtdabelhas].nome_cientifico, 50);
    escolher_regiao_abelha(abelhas, qtdabelhas);
    printf("Digite quanto essa abelha produz de mel (em kg/mês): ");
    abelhas[qtdabelhas].producao_de_mel = ler_float(0.0001);
}

int buscar_abelha_id (tabela_abelha abelhas[], int qtdabelhas, int alterar_dados_id)//Busca uma abelha através do id dela, retorna a posição
{
    for(int i = 0; i < qtdabelhas; i++){
        if(abelhas[i].id == alterar_dados_id){
            return i;
        }
    }
    return -1;
}

void alterar_abelha(tabela_abelha abelhas[], int alvo)//Função para alterar as informações de uma abelha
{
    int opcao3;
    do{
        system("clear||cls");
        printf("\nDados atuais:\n");
        mostrar_abelha(alvo, abelhas);
        printf("\nQual informação vc gostaria de mudar?\n1. Nome Popular\n2. Nome Científico\n3. Região\n4. Produção de mel\n5. Voltar\n");
        printf("Escolha uma opção: ");
        opcao3 = ler_inteiro(1, 5);
        switch (opcao3)
        {
            case 1:
                printf("Digite o novo nome popular da abelha: ");
                ler_texto(abelhas[alvo].nome_popular, 40);
                printf("Alteração feita com sucesso!\n");
                break;
                            
            case 2:
                printf("Digite o novo nome científico da abelha: ");
                ler_texto(abelhas[alvo].nome_cientifico, 50);
                printf("Alteração feita com sucesso!\n");
                break;

            case 3:
                escolher_regiao_abelha(abelhas, alvo);
                break;

            case 4:
                printf("Digite a nova quantia de mel (kg/mês) que a abelha produz:");
                abelhas[alvo].producao_de_mel = ler_float(0.0001);
                printf("Alterção feita com sucesso!\n");
                break;

            case 5:
                break;

        }
    }while(opcao3 != 5);
}

void remover_abelha(int alvo, int *qtdabelhas, tabela_abelha abelhas[], int *qtdsensores, int id_abelha, tabela_sensores sensores[])//Função para remover abelha e sensores associados (se houver)
{
    printf("Deseja realmente remover?\n1. Sim\n2. Não.\n");
    printf("Digite a escolha: ");
    int sensor_removido = 0;
    int confirmacao = ler_inteiro(1, 2);
    if(confirmacao == 1){
        for(int i = alvo; i < *qtdabelhas - 1; i++){
            abelhas[i] = abelhas[i + 1];
        }
        if(*qtdsensores > 0){
           sensor_removido = remover_sensor_idAbelha(id_abelha, qtdsensores, sensores);
        }
        (*qtdabelhas)--;
        printf("Operação bem sucedida, abelha removida com sucesso!!!\n");
        if(sensor_removido == 1){
            printf("O(s) sensor(es) associado(s) à abelha também foi(ram) removido(s)\n");
        }
    }
    else{
        printf("Operação abortada.\n");
    }
}

void mostrar_idabelha_disponiveis(tabela_abelha abelhas[], int qtdabelhas)//Mostra o Id das abelhas presentes no vetor do struct disponíveis
{
    printf("ID'S disponíveis:\n");
    for(int i = 0; i < qtdabelhas; i++){
        printf("Abelha %d id: %d\n", i+1, abelhas[i].id);
    }
    puts("");
}

void ler_dados_sensores(tabela_sensores sensores[], int qtdsensores, int qtdabelhas, tabela_abelha abelhas[])//Função para ler os dados do sensor
{
    int opcao;
    int verify; //verifica se existe a abelha
    int id_abelha; // recebe o id digitado pelo usuario
    printf("\n");
    printf("Tipos de sensores:\n1. Temperatura\n2. Luminosidade\n3. Umidade\n");
    printf("Digite o valor correspondente ao tipo desejado: ");
    opcao = ler_inteiro(1, 3);
    switch (opcao)
    {
    case 1:
        strcpy(sensores[qtdsensores].tipo, "Temperatura");
        break;
    
    case 2:
        strcpy(sensores[qtdsensores].tipo, "Luminosidade");
        break;

    case 3:
        strcpy(sensores[qtdsensores].tipo, "Umidade");
        break;

    }
    if(strcmp(sensores[qtdsensores].tipo, "Temperatura") == 0){
        printf("Digite o valor de leitura do sensor: ");
        sensores[qtdsensores].valor = ler_float(-273.15);
    }
    else{
        printf("Digite o valor de leitura do sensor: ");
        sensores[qtdsensores].valor = ler_float(0.0);
    }
    do{
        mostrar_idabelha_disponiveis(abelhas, qtdabelhas);
        printf("Digite o id da abelha a qual o sensor será vinculado: ");
        id_abelha = ler_inteiro(1, 999999);
        verify = buscar_abelha_id(abelhas, qtdabelhas, id_abelha);
        if(verify == -1){
            printf("Id inválido, tente novamente!\n");
        }
    }while (verify == -1);
    sensores[qtdsensores].idAbelha = id_abelha;
}

void listar_sensores(int a, tabela_sensores sensores[])//Mostra todos os sensores presentes no vetor de struct
{
    for (int i = 0; i < a; i++)
    {
        mostrar_sensor(i, sensores);
    }
}

void mostrar_sensor(int a, tabela_sensores sensores[])//Mostra um sensor específico através da sua posição no vetor do struct
{
    printf("Id: %d\n", sensores[a].id);
    printf("Tipo: %s\n", sensores[a].tipo);
    if (strcmp(sensores[a].tipo, "Temperatura") == 0){
        printf("Valor de leitura: %.2f °C\n", sensores[a].valor);
    }
    else if(strcmp(sensores[a].tipo, "Luminosidade") == 0){
        printf("Valor de leitura: %.2f lux\n", sensores[a].valor);
    }
    else{
        printf("Valor de leitura: %.2f %%\n", sensores[a].valor);
    }
    printf("Id da abelha vinculado ao sensor: %d\n\n", sensores[a].idAbelha);
}

void buscar_sensor_por_idabelha(int alvo, int qtdsensores, tabela_sensores sensores[], tabela_abelha abelhas[], int qtdabelhas)//Busca um sensor através do ID abelha associado ao mesmo
{
    int verify = buscar_abelha_id(abelhas, qtdabelhas, alvo);
    if(verify != -1){
        int achou = 0;
        for(int i = 0; i < qtdsensores; i++){
            if(sensores[i].idAbelha == alvo){
                if(achou == 0){
                    printf("Sensor(es) associado(s) a abelha de id %d:\n", alvo);
                }
                mostrar_sensor(i, sensores);
                achou = 1;
            }
        }
        if(achou == 0){
            printf("Não há sensores vinculados à essa abelha!!!\n");
        }
    }
    else{
        printf("Não há uma abelha com esse id!!!\n");
    }
}

int buscar_sensor_id (tabela_sensores sensores[], int qtdsensores, int id_digitado)//Busca um sensor através do id dele, retorna a posição
{
    for(int i = 0; i < qtdsensores; i++){
        if(sensores[i].id == id_digitado){
            return i;
        }
    }
    return -1;
}

void mostrar_idsensor_disponiveis(tabela_sensores sensores[], int qtdsensores)//Mostra o ID dos sensores existentes
{
    printf("ID'S disponíveis:\n");
    for(int i = 0; i < qtdsensores; i++){
        printf("Sensor %d id: %d\n", i+1, sensores[i].id);
    }
    puts("");
}

void remover_sensor(int alvo, int *qtsensores, tabela_sensores sensores[])//Remove um sensor através da sua posição
{
    printf("Deseja realmente remover?\n1. Sim\n2. Não.\n");
    printf("Digite a escolha: ");
    int confirmacao = ler_inteiro(1, 2);
    if(confirmacao == 1){
        for(int i = alvo; i < *qtsensores - 1; i++){
            sensores[i] = sensores[i + 1];
        }
        (*qtsensores)--;
        printf("Operação bem sucedida, sensor removido com sucesso!!!\n");
    }
    else{
        printf("Operação abortada.\n");
    }
}

int remover_sensor_idAbelha(int id_abelha, int *qtdsensores, tabela_sensores sensores[])//Remove os sensores associados à um ID abelha específico
{
    int confir = 0;
    for(int i = 0; i < *qtdsensores; i++){
        if(sensores[i].idAbelha == id_abelha){
            for(int j = i; j < (*qtdsensores) - 1; j++){
                sensores[j] = sensores[j+1];
            }
            confir = 1;
            (*qtdsensores)--;
            i--;
        }
    }
    return confir;
}

void alterar_leitura_sensor(tabela_sensores sensores[], int alvo)//Altera o valor de leitura de um sensor pre-existente
{
    printf("Digite o novo valor de leitura do sensor: ");
    if (strcmp(sensores[alvo].tipo, "Temperatura") == 0) {
        sensores[alvo].valor = ler_float(-273.15);
    } else {
        sensores[alvo].valor = ler_float(0.0);
    }
    printf("Leitura alterada com sucesso!\n");
}

float producao_de_mel(tabela_abelha abelhas[], int qtdabelhas)//Retorna o valor da soma da produção de mel de todas as abelhas cadastradas por mês
{
    float soma = 0;
    for(int i = 0; i < qtdabelhas; i++){
        soma += abelhas[i].producao_de_mel;
    }
    return soma;
}

int quantidade_sensores_temp(tabela_sensores sensores[], int qtdsensores)//Retornar o a quantidade de sensores de temperatura cadastrados
{
    int quantidade = 0;
    for(int i = 0; i < qtdsensores; i++){
        if (strcmp(sensores[i].tipo, "Temperatura") == 0){
            quantidade++;
        }
    }
    return quantidade;
}

float media_temperatura_sensores(tabela_sensores sensores[], int qtdsensores)//Calcula a média das leituras de temperatura
{
    int quantidade = 0;
    float media, soma = 0;
    for(int i = 0; i < qtdsensores; i++){
        if (strcmp(sensores[i].tipo, "Temperatura") == 0){
            quantidade++;
            soma += sensores[i].valor;
        }
    }
    if(quantidade == 0){
        return 0;
    }
    media = (soma * 1.0)/quantidade;
    return media;
}

void escolher_regiao_abelha(tabela_abelha abelhas[], int alvo)//Lê a região a qual abelha está
{
    int opcao;
    printf("Regiões para a abelha:\n1. Norte\n2. Nordeste\n3. Centro-Oeste\n4. Sudeste\n5. Sul\nEscolha uma das regiões:  ");
    opcao = ler_inteiro(1, 5);
    switch (opcao)
    {
    case 1:
        abelhas[alvo].regiao = 1;
        break;
    
    case 2:
        abelhas[alvo].regiao = 2;
        break;
    
    case 3:
        abelhas[alvo].regiao = 3;
        break;
    
    case 4:
        abelhas[alvo].regiao = 4;
        break;
    
    case 5:
        abelhas[alvo].regiao = 5;
        break;
    
    }
}

void abelhas_por_regiao (int qtdabelhas, tabela_abelha abelhas[])//Contabiliza as abelhas por região
{
    int norte = 0, nordeste = 0, centro_oeste = 0, sudeste = 0, sul = 0;
    for(int i = 0; i < qtdabelhas; i++){
        switch (abelhas[i].regiao)
        {
        case 1:
            norte++;
            break;
        
        case 2:
            nordeste++;
            break;
        
        case 3:
            centro_oeste++;
            break;
        
        case 4:
            sudeste++;
            break;
        
        case 5:
            sul++;
            break;
        
        
        }
    }
    printf("Abelhas na região Norte: %d \n", norte);
    printf("Abelhas na região Nordeste: %d \n", nordeste);
    printf("Abelhas na região Centro-Oeste: %d \n", centro_oeste);
    printf("Abelhas na região Sudeste: %d \n", sudeste);
    printf("Abelhas na região Sul: %d \n", sul);
}

float estoque_mel(int qtdabelhas, tabela_abelha abelhas[])//Calcula a quantia de mel total produzida pelas abelhas por mês
{
    float estoque = 0;
    for(int i = 0; i < qtdabelhas; i++){
        estoque += abelhas[i].producao_de_mel;
    }
    return estoque;
}

void menu_abelhas(int *qtdabelhas, int *prox_id_abelha, tabela_abelha abelhas[], int *qtdsensores, tabela_sensores sensores[])//Local onde acontecem as interações referentes as abelhas
{
    int alvo, alterar_dados_id, id_digitado, opcao2;
    char pesquisa[40];
    do
    {
        system("clear||cls");
        printf("===== Menu Abelhas =====\n");
        printf("1. Cadastrar abelha\n2. Listar todas\n3. Buscar por nome popular\n4. Alterar dados\n5. Remover\n6. Voltar");
        printf("\nEscolha uma opção: ");
        opcao2 = ler_inteiro(1, 6);
        switch (opcao2)
        {
        case 1:
            system("clear||cls");
            if (*qtdabelhas < max_abelhas)
            {
                abelhas[*qtdabelhas].id = (*prox_id_abelha);
                ler_dados_abelha(abelhas, *qtdabelhas);
                (*qtdabelhas)++;
                (*prox_id_abelha)++;
            }
            else
            {
                printf("A quantidade de abelhas cadastradas já está no limite.\n");
            }
            system("Pause");
            break;

        case 2:
            system("clear||cls");
            if (*qtdabelhas == 0)
            {
                printf("Não há abelhas cadastradas!\n");
            }
            else
            {
                printf("\n");
                listar_abelhas(*qtdabelhas, abelhas);
            }
            system("Pause");
            break;

        case 3:
            system("clear||cls");
            printf("\nDigite um nome para pesquisa: ");
            ler_texto(pesquisa, 40);
            puts("");
            pesquisar_abelhas(*qtdabelhas, pesquisa, abelhas);
            system("Pause");
            break;

        case 4:
            system("clear||cls");
            if (*qtdabelhas > 0)
            {
                mostrar_idabelha_disponiveis(abelhas, *qtdabelhas);
                printf("Digite o Id da abelha para modificar: ");
                alterar_dados_id = ler_inteiro(1, 999999);
                alvo = buscar_abelha_id(abelhas, *qtdabelhas, alterar_dados_id);
                if (alvo == -1)
                {
                    printf("Não há uma abelha com esse ID!\n");
                }
                else
                {
                    alterar_abelha(abelhas, alvo);
                }
            }
            else
            {
                printf("Não há abelhas cadastradas!\n");
            }
            system("Pause");
            break;

        case 5:
            system("clear||cls");
            if (*qtdabelhas > 0)
            {
                mostrar_idabelha_disponiveis(abelhas, *qtdabelhas);
                printf("Digite o id da abelha que você deseja excluir: ");
                id_digitado = ler_inteiro(1, 999999);
                alvo = buscar_abelha_id(abelhas, *qtdabelhas, id_digitado);
                if (alvo == -1)
                {
                    printf("Não há uma abelha com esse ID!\n");
                }
                else
                {
                    remover_abelha(alvo, qtdabelhas, abelhas, qtdsensores, id_digitado, sensores);
                }
            }
            else
            {
                printf("Não há abelhas cadastradas!\n");
            }
            system("Pause");
            break;

        case 6:
            break;
        }
    } while (opcao2 != 6);
}

void menu_sensore(int *qtdabelhas, int *prox_id_sensor, tabela_abelha abelhas[], int *qtdsensores, tabela_sensores sensores[])//Local onde acontecem as interações referentes aos sensores
{
    int alvo, alterar_dados_id, id_digitado, opcao2;;
    do
    {
        system("clear||cls");
        printf("===== Menu Sensores =====\n");
        printf("1. Cadastrar sensor\n2. Listar sensores\n3. Buscar por ID da abelha\n4. Alterar leitura\n5. Remover\n6. Voltar");
        printf("\nEscolha uma opção: ");
        opcao2 = ler_inteiro(1, 6);
        switch (opcao2)
        {
        case 1:
            system("clear||cls");
            if (*qtdsensores >= max_sensores)
            {
                printf("Limite máximo de sensores atingido!\n");
            }
            else if (*qtdabelhas > 0)
            {
                sensores[*qtdsensores].id = (*prox_id_sensor);
                ler_dados_sensores(sensores, *qtdsensores, *qtdabelhas, abelhas);
                (*qtdsensores)++;
                (*prox_id_sensor)++;
            }
            else
            {
                printf("Não há abelhas cadastradas, portanto não é possível inserir um novo sensor\n");
            }
            system("Pause");
            break;

        case 2:
            system("clear||cls");
            if (*qtdsensores > 0)
            {
                printf("Sensores cadastrados:\n\n");
                listar_sensores(*qtdsensores, sensores);
            }
            else
            {
                printf("Não há sensores cadastrados!\n");
            }
            system("Pause");
            break;

        case 3:
            system("clear||cls");
            if (*qtdsensores > 0)
            {
                mostrar_idabelha_disponiveis(abelhas, *qtdabelhas);
                printf("Digite o id da abelha: ");
                alvo = ler_inteiro(1, 999999);
                buscar_sensor_por_idabelha(alvo, *qtdsensores, sensores, abelhas, *qtdabelhas);
            }
            else
            {
                printf("Não há sensores cadastrados!\n");
            }
            system("Pause");
            break;

        case 4:
            system("clear||cls");
            if (*qtdsensores > 0)
            {
                mostrar_idsensor_disponiveis(sensores, *qtdsensores);
                printf("Digite o Id do sensor para alterar a leitura: ");
                alterar_dados_id = ler_inteiro(1, 999999);
                alvo = buscar_sensor_id(sensores, *qtdsensores, alterar_dados_id);
                if (alvo == -1)
                {
                    printf("Não há um sensor com esse ID!\n");
                }
                else
                {
                    alterar_leitura_sensor(sensores, alvo);
                }
            }
            else
            {
                printf("Não há sensores cadastrados!\n");
            }
            system("Pause");
            break;

        case 5:
            system("clear||cls");
            if (*qtdsensores > 0)
            {
                mostrar_idsensor_disponiveis(sensores, *qtdsensores);
                printf("Digite o id do sensor que você deseja excluir: ");
                id_digitado = ler_inteiro(1, 999999);
                alvo = buscar_sensor_id(sensores, *qtdsensores, id_digitado);
                if (alvo == -1)
                {
                    printf("Não há um sensor com esse ID!\n");
                }
                else
                {
                    remover_sensor(alvo, qtdsensores, sensores);
                }
            }
            else
            {
                printf("Não há sensores cadastrados!\n");
            }
            system("Pause");
            break;

        case 6:
            break;
        }
    } while (opcao2 != 6);
}

void menu_relatorios(int qtdabelhas, tabela_abelha abelhas[], int qtdsensores, tabela_sensores sensores[])//Local onde acontecem as interações referentes aos relatórios
{
    int opcao2;
    float media_producao, media_temperatura, estoque, faturamento;
    do
    {
        system("clear||cls");
        printf("===== Relatorios =====\n");
        printf("1. Média geral de produção de mel\n2. Média de temperatura dos sensores\n3. Quantidade de abelhas por região\n4. Estoque\n5. Faturamento\n6. Voltar.");
        printf("\nEscolha uma opção: ");
        opcao2 = ler_inteiro(1, 6);
        switch (opcao2)
        {
        case 1:
            system("clear||cls");
            if (qtdabelhas > 0)
            {
                media_producao = producao_de_mel(abelhas, qtdabelhas) / (qtdabelhas * 1.0);
                printf("Média geral da procução de mel = %.2f\n", media_producao);
            }
            else
            {
                printf("Não há abelhas cadastradas, portanto não é possível haver a média de produção de mel!\n");
            }
            system("Pause");
            break;

        case 2:
            system("clear||cls");
            if (qtdsensores > 0)
            {
                if (quantidade_sensores_temp(sensores, qtdsensores) == 0)
                {
                    printf("Não há sensores de temperatura cadastrados!\n");
                }
                else
                {
                    media_temperatura = media_temperatura_sensores(sensores, qtdsensores);
                    printf("Média de temperatura = %.2f °C\n", media_temperatura);
                }
            }
            else
            {
                printf("Não há sensores cadastrados!\n");
            }
            system("Pause");
            break;

        case 3:
            system("clear||cls");
            if (qtdabelhas > 0)
            {
                abelhas_por_regiao(qtdabelhas, abelhas);
            }
            else
            {
                printf("Não há abelhas cadastradas, portanto não é possível haver abelhas em alguma região!\n");
            }
            system("Pause");
            break;

        case 4:
            system("clear||cls");
            if (qtdabelhas > 0)
            {
                estoque = estoque_mel(qtdabelhas, abelhas);
                printf("Quantidade de mel presente no estoque: %.2f kg\n", estoque);
            }
            else
            {
                printf("Não há abelhas cadastradas, portanto não é possível haver um estoque de mel!\n");
            }
            system("Pause");
            break;

        case 5:
            system("clear||cls");
            if (qtdabelhas > 0)
            {
                faturamento = estoque_mel(qtdabelhas, abelhas) * valor_mel_kg;
                printf("Faturamento: %.2f R$\n", faturamento);
            }
            else
            {
                printf("Não há abelhas cadastradas, portanto o estoque está zerado!\n");
            }
            system("Pause");
            break;

        case 6:
            break;
        }
    } while (opcao2 != 6);
}