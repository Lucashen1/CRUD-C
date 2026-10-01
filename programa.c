#include <stdio.h>
#include <locale.h> //inclue uma biblioteca em linguagem
#include <conio.h>  //para usar getch() = aguardar presionar tecla para continuar
#include <windows.h>
#include <stdlib.h>
#include <string.h> //para usar strcpy

#define INICIO_ARANJO 1
#define TAMANHO_MAXIMO 10

// funcao para posicionar cursos em um ponto especifico da tela
void gotoxy(int x, int y)
{

    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// funcao que limpa o campo MSG do programa
void limpaMsg()
{

    gotoxy(7, 23);
    printf("                                                                    ");
}
void limpaOpcao()
{

    gotoxy(9, 24);
    printf("                                                            ");
}

// struct serve para agrupar varias variaveis de um tipo. typedef serve para apelidar a variavel.
typedef struct
{ // cria a var do tipo cliente com codigo de cliente, nome, cpf, numero

    int codigoCliente;
    char nomeCliente[50];
    char endereco[50];
    int numeroEndereco;
    char nmrCPF[20];
    char cidade[50];
    char uf[5];
    char dataCadastro[19];
    char numeroTelefone[15];

} reg_cliente; // é o nome do tipo da variavel

// funcao que cria uma lista de dados do tipo reg_Clie que tem os campos do cliente(nome, codigo...)
typedef struct
{ // cria uma lista

    reg_cliente dados[TAMANHO_MAXIMO]; // tamanho maximo do vetor dados é 10. 10 clientes podem ser cadastrados
    int ultimo;
    int primeiro;

} tipo_lista;

// faz a tela pontilhada
void tela()
{

    for (int i = 0; i <= 80; i++)
    {

        gotoxy(i, 0);
        printf("-");
        gotoxy(i, 3);
        printf("-");
        gotoxy(i, 25);
        printf("-");
        gotoxy(i, 22);
        printf("-");
    }

    for (int i = 1; i <= 25; i++)
    {

        gotoxy(0, i);
        printf("|");
        gotoxy(80, i);
        printf("|");
    }

    gotoxy(2, 1);
    printf("UNICV");
    gotoxy(20, 1);
    printf("SISTEMA DE GESTAO DE CLIENTE");
    gotoxy(61, 1);
    printf("Estrutura de dados");
    gotoxy(2, 24);
    printf("OPCAO:");
    gotoxy(2, 23);
    printf("MSG:");
}

// Campos clientes
void tela_clie()
{

    gotoxy(8, 5);
    printf("Codigo de cliente..:");
    gotoxy(5, 7);
    printf("1. Nome do cliente....:");
    gotoxy(5, 9);
    printf("2. Endereco...........:");
    gotoxy(5, 11);
    printf("3. Numero.............:");
    gotoxy(5, 13);
    printf("4. cpf................:");
    gotoxy(5, 15);
    printf("5. Cidade.............:");
    gotoxy(5, 17);
    printf("6. Estado.............:");
    gotoxy(5, 19);
    printf("7. Data de cadastro...:");
    gotoxy(5, 21);
    printf("8. telefone...........:");
}

// pesquisa pelo codigo na lista de dados
int pesquisaCodigo(tipo_lista *Lista, int codigo)
{
    int x;

    for (x = 0; x < Lista->ultimo; x++)
    {

        if (Lista->dados[x].codigoCliente == codigo)
        {

            return x;
        }
    }

    return -1;
}

// Inclui clientes
void inclusao(tipo_lista *Lista)
{

    reg_cliente clie; // vai pegar todos os dados do tipo cliente.
    int result;
    int op;

    // Feito para incluir mais de um cliente por vez
    do
    {

        // Feito para validar se o codigo ja foi cadastrado ou cancelar
        do
        {

            system("cls");
            tela();
            limpaMsg();
            tela_clie();

            gotoxy(30, 2);
            printf("-----inclusao-----");

            gotoxy(7, 23);
            printf("Digite 0 para cancelar");

            gotoxy(29, 5);
            scanf("%d", &clie.codigoCliente);
            result = pesquisaCodigo(Lista, clie.codigoCliente);

            if (result != -1)
            {

                gotoxy(07, 23);
                printf("Codigo ja cadastrado..");
                getch();
            }
            else if (clie.codigoCliente == 0)
            {

                limpaMsg();
                gotoxy(7, 23);
                printf("Inclusao cancelada. Digite qualquer tecla para voltar ao menu");
                getch();
                return;
            }

        } while ((result != -1) || (clie.codigoCliente == 0));

        if (clie.codigoCliente != 0)
        {

            gotoxy(29, 7);
            fflush(stdin);
            fgets(clie.nomeCliente, 50, stdin);

            gotoxy(29, 9);
            fflush(stdin);
            fgets(clie.endereco, 50, stdin);

            gotoxy(29, 11);
            scanf("%d", &clie.numeroEndereco);

            gotoxy(29, 13);
            fflush(stdin);
            fgets(clie.nmrCPF, 13, stdin);

            gotoxy(29, 15);
            fflush(stdin);
            fgets(clie.cidade, 30, stdin);

            gotoxy(29, 17);
            fflush(stdin);
            fgets(clie.uf, 5, stdin);

            gotoxy(29, 19);
            fflush(stdin);
            fgets(clie.dataCadastro, 10, stdin);

            gotoxy(29, 21);
            fflush(stdin);
            fgets(clie.numeroTelefone, 15, stdin);
        }

        gotoxy(7, 23);
        printf("Deseja incluir o cliente a lista?  1. Sim  2. Nao");
        gotoxy(10, 24);
        scanf("%d", &op);

        if (op == 1)
        {

            // com ponteiros usamos -> para acessar campos
            Lista->dados[Lista->ultimo] = clie; // se a opçao foi 1 ele vai jogar todos os dados na lista
            Lista->ultimo++;
        }

        limpaMsg();
        limpaOpcao();

        gotoxy(7, 23);
        printf("Deseja cadastrar outro cliente?  1. Sim  2. Nao");
        gotoxy(10, 24);
        scanf("%d", &op);

    } while (op == 1);
}

// Altera dados de clientes ja registrados
void alteracao(tipo_lista *Lista)
{

    reg_cliente clie;
    int entrada, result;

    // Valida o valor digitado no codigo do cliente
    do
    {

        limpaMsg();
        limpaOpcao();
        gotoxy(17, 5);
        system("cls");
        tela();

        gotoxy(30, 2);
        printf("---alteracao---");

        gotoxy(7, 23);
        printf("Digite o codigo do cliente: ");
        gotoxy(9, 24);
        scanf("%d", &clie.codigoCliente);

        result = pesquisaCodigo(Lista, clie.codigoCliente);

        if (clie.codigoCliente == 0)
        {

            limpaMsg();
            gotoxy(7, 23);
            printf("Alteracao cancelada. Digite qualquer tecla para voltar ao menu.");
            getch();
            return;
        }
        else if (result == -1)
        {

            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Cliente nao cadastrado.");
            getch();
        }
    } while (result == -1);

    tela_clie();

    //Mostra dados apos validar o codigo.
    gotoxy(29, 5);
    printf("%d", Lista->dados[result].codigoCliente);
    gotoxy(29, 7);
    printf("%s", Lista->dados[result].nomeCliente);
    gotoxy(29, 9);
    printf("%s", Lista->dados[result].endereco);
    gotoxy(29, 11);
    printf("%d", Lista->dados[result].numeroEndereco);
    gotoxy(29, 13);
    printf("%s", Lista->dados[result].nmrCPF);
    gotoxy(29, 15);
    printf("%s", Lista->dados[result].cidade);
    gotoxy(29, 17);
    printf("%s", Lista->dados[result].uf);
    gotoxy(29, 19);
    printf("%s", Lista->dados[result].dataCadastro);
    gotoxy(29, 21);
    printf("%s", Lista->dados[result].numeroTelefone);

    //Feito para alterar mais de uma vez
    do
    {

        limpaMsg();
        limpaOpcao();
        gotoxy(7, 23);
        printf("Digite o campo que quer alterar ou 0 para voltar ao menu.");
        gotoxy(9, 24);
        scanf("%d", &entrada);

        int auxInt;
        char auxString[50];
        

        switch (entrada)
        {

        case 1: // MUDA O NOME

            gotoxy(29, 7);
            fflush(stdin);
            fgets(auxString, 50, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar o nome? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].nomeCliente, auxString);
            }
            break;

        case 2: // MUDA O ENDERECO

            gotoxy(29, 9);
            fflush(stdin);
            fgets(auxString, 50, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar o endereco? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].endereco, auxString);
            }
            break;

        case 3: // MUDA O NUMERO ENDERECO

            gotoxy(29, 11);
            fflush(stdin);
            scanf("%d", &auxInt);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar o nome? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);

            if(auxInt == 1){

                Lista->dados[result].numeroEndereco = auxString;
            }
            break;

        case 4: // MUDA O CPF

            gotoxy(29, 13);
            fflush(stdin);
            fgets(auxString, 50, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar o endereco? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].nmrCPF, auxString);
            }
            break;

        case 5: // MUDA A CIDADE

            gotoxy(29, 15);
            fflush(stdin);
            fgets(auxString, 50, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar a cidade? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].cidade, auxString);
            }
            break;

        case 6: // MUDA UF

            gotoxy(29, 17);
            fflush(stdin);
            fgets(auxString, 50, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar a sigla do estado? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].uf, auxString);
            }
            break;

        case 7: // MUDA DATA CADASTRO

            gotoxy(7, 23);
            printf("Nao e possivel alterar a data de cadastro");
            break;

        case 8: // MUDA TELEFONE
            
            gotoxy(29, 21);
            fflush(stdin);
            fgets(auxString, 14, stdin);

            limpaMsg();
            limpaOpcao();

            gotoxy(7, 23);
            printf("Deseja alterar a sigla do estado? (1. SIM\t2. NAO");
            gotoxy(9, 24);
            scanf("%d", &auxInt);
            if(auxInt == 1){
                strcpy(Lista->dados[result].numeroTelefone, auxString);
            }
            break;

        case 0: // VOLTA PRO MENU
            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Alteracao cancelada");
            getch();
            break;

        default: // OPCAO INVALIDA
            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Opcao invalida.");
            getch();
            break;

        }

    } while (entrada != 0);

}

//Excluir todos os dados do cliente pelo codigo.
void exclusao(tipo_lista *Lista)
{

    system("cls");
    tela();
    int entrada, result;

    gotoxy(30, 2);
    printf("---Escolheu exclusao---");

    do
    {
        gotoxy(7, 23);
        printf("Digite o codigo do cliente para exclusao ou 0 para voltar ao menu");
        gotoxy(9, 24);
        scanf("%d", &entrada);

        result = pesquisaCodigo(Lista, entrada);

        if (entrada == 0)
        {

            break;

        }

        else if (result == -1)
        {

            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Codigo nao cadastrado");
            getch();

        }

    } while ((entrada <= 0) || (result == -1));

    if ((entrada != 0) && (result != -1))
    {
        tela_clie();
        gotoxy(29, 5);
        printf("%d", Lista->dados[result].codigoCliente);
        gotoxy(29, 7);
        printf("%s", Lista->dados[result].nomeCliente);
        gotoxy(29, 9);
        printf("%s", Lista->dados[result].endereco);
        gotoxy(29, 11);
        printf("%d", Lista->dados[result].numeroEndereco);
        gotoxy(29, 13);
        printf("%s", Lista->dados[result].nmrCPF);
        gotoxy(29, 15);
        printf("%s", Lista->dados[result].cidade);
        gotoxy(29, 17);
        printf("%s", Lista->dados[result].uf);
        gotoxy(29, 19);
        printf("%s", Lista->dados[result].dataCadastro);
        gotoxy(29, 21);
        printf("%s", Lista->dados[result].numeroTelefone);

        limpaMsg();
        limpaOpcao();
        gotoxy(7, 23);
        printf("Deseja excluir o cliente? 1. Sim  2. Nao");
        gotoxy(9, 24);
        scanf("%d", &entrada);

        if (entrada == 1)
        {
            for (int x = result; x < Lista->ultimo; x++)
            {
                Lista->dados[x] = Lista->dados[x + 1];
            }
            Lista->ultimo--;

            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Cliente excluido.");
            getch();
        }
        else
        {
            limpaMsg();
            limpaOpcao();
            gotoxy(7, 23);
            printf("Exclusao cancelada");
            getch();
        }
    }
}

void consulta(tipo_lista *Lista)
{
    int op, entrada, result;
    system("cls");
    tela();
    gotoxy(30, 2);
    printf("---consulta---");
    do
    {
        do
        {
            tela();
            gotoxy(7, 23);
            printf("Digite o codigo do cliente ou 0 para sair");
            gotoxy(9, 24);
            scanf("%d", &entrada);

            result = pesquisaCodigo(Lista, entrada);
            if (entrada == 0)
            {
                limpaMsg();
                gotoxy(7, 23);
                printf("Consulta cancelada.");
                getch();
                main();
            }
            else if (result == -1)
            {
                limpaMsg();
                limpaOpcao();
                gotoxy(7, 23);
                printf("Nenhum registro encontrado");
                getch();
            }
        } while ((result == -1) || (entrada == 0));

        if ((result != -1) && (entrada != 0))
        {
            tela_clie();

            gotoxy(29, 5);
            printf("%d", Lista->dados[result].codigoCliente);
            gotoxy(29, 7);
            printf("%s", Lista->dados[result].nomeCliente);
            gotoxy(29, 9);
            printf("%s", Lista->dados[result].endereco);
            gotoxy(29, 11);
            printf("%d", Lista->dados[result].numeroEndereco);
            gotoxy(29, 13);
            printf("%s", Lista->dados[result].nmrCPF);
            gotoxy(29, 15);
            printf("%s", Lista->dados[result].cidade);
            gotoxy(29, 17);
            printf("%s", Lista->dados[result].uf);
            gotoxy(29, 19);
            printf("%s", Lista->dados[result].dataCadastro);
            gotoxy(29, 21);
            printf("%s", Lista->dados[result].numeroTelefone);
        }
        limpaMsg();

        gotoxy(2, 23);
        printf("Deseja consultar outro cliente? 1. Sim 2. Nao");
        scanf("%d", &op);

    } while (op == 1);
}

void listaCadastros(tipo_lista *Lista)
{
    system("cls");
    tela();
    limpaMsg();
    limpaOpcao();
    int count = 6;
    int x;

    gotoxy(30, 2);
    printf("--Lista de cadastros--");
    gotoxy(2, 5);
    printf("CODIGO");
    gotoxy(9, 5);
    printf("NOME");
    gotoxy(25, 5);
    printf("ENDERECO");
    gotoxy(40, 5);
    printf("TEL");
    gotoxy(55, 5);
    printf("NASCIMENTO");
    gotoxy(70, 5);
    printf("INCLUSAO");

    if (Lista->ultimo != 0)
    {

        for (x = 0; x <= Lista->ultimo - 1; x++)
        {
            gotoxy(5, count);
            printf("%d\t", Lista->dados[x].codigoCliente);
            printf("%s\t", Lista->dados[x].nomeCliente);
            printf("%s, %s\t", Lista->dados[x].endereco, Lista->dados[x].numeroEndereco);

            count++;
        }
    }
    else
    {
        gotoxy(20, 8);
        printf("Nenhum cadastro foi encontrado!");
    }
    getch();
    main();
}

void fimPrograma()
{
    system("cls");
    tela();
    gotoxy(30, 2);
    printf("Programa finalizado.");
}
void invalido()
{
    system("cls");
    tela();
    gotoxy(30, 2);
    printf("Opcao invalida");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int ch;
    tipo_lista Lista;

    Lista.primeiro = 0;
    Lista.ultimo = 0;

    do
    {
        system("cls");
        tela();
        system("color 1F"); // muda a cor do fundo e da letra o 1 � o fundo e o F a letra.
        gotoxy(30, 5);
        printf("1. Inclusao");
        gotoxy(30, 7);
        printf("2. Alteracao");
        gotoxy(30, 9);
        printf("3. Exclusao");
        gotoxy(30, 11);
        printf("4. Consultar");
        gotoxy(30, 13);
        printf("5. Listar cadastros");
        gotoxy(30, 15);
        printf("6. Finaliza");

        gotoxy(7, 23);
        printf("Digite a opcao que deseja.");
        gotoxy(9, 24);
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            inclusao(&Lista); // manda o enderço da lista original
            break;
        case 2:
            alteracao(&Lista);
            break;
        case 3:
            exclusao(&Lista);
            break;
        case 4:
            consulta(&Lista);
            break;
        case 5:
            listaCadastros(&Lista);
            break;
        case 6:
            fimPrograma();
            break;
        default:
            invalido();
            break;
        }
        // getch();
    } while (ch != 6);
    return 0;
}
