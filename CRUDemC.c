#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//Cria um tipo de variavel 
typedef struct {

     int cd_funcionario;
     char nm_funcionario[50];
     char endereco[50];
     char dataNasc[11];
     char telefone[15];
     char cpf[15];
     char cargo[40];
     char dpto[30];
     float vl_salario;

} reg_funcionario;

//criando apontador para lista
typedef struct Tipoitem *Tipoapontador;

//Item tendo o conteudo e o proximo que aponta para a proxima posicao
//Nome depois da Struct por
typedef struct Tipoitem
{
     reg_funcionario conteudo;
     Tipoapontador proximo;
     
} Tipoitem;

//Lista contendo o primeiro da lista e o ultimo
typedef struct 
{
     Tipoapontador primeiro;
     Tipoapontador Ultimo;

} TipoLista;

void gotoxy(int x, int y){
     COORD coord;
     coord.X = (short)x;
     coord.Y = (short)y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void telaCadastro(){

     gotoxy(15,4);
     printf("   Codigo funcionario...: ");
     gotoxy(15,6);
     printf("1. Nome funcionario.....: ");
     gotoxy(15,8);
     printf("2. Endereco funcionario.: ");
     gotoxy(15, 10);
     printf("3. Data de nascimento...: ");
     gotoxy(15, 12);
     printf("4. Telefone.............: ");
     gotoxy(15, 14);
     printf("5. CPF..................: ");
     gotoxy(15, 16);
     printf("6. Cargo................: ");
     gotoxy(15, 18);
     printf("7. Departamento.........: ");
     gotoxy(15, 20);
     printf("8. Valor salario........: ");
}

void limpaMSG(){
     gotoxy(9,26); 
     printf("                                                          ");
     gotoxy(9,27);
     printf("                                                       ");
}

void tela(){

     int aux = 0;
     for(int x = 1; x<=80; x++){

          gotoxy(x,0);
          printf("-");
          gotoxy(x,3);
          printf("-");
          gotoxy(x,28);
          printf("-");
          gotoxy(x,25);
          printf("-");
          
     }
     for(int x = 1; x<= 28; x++){

          gotoxy(1,aux);
          printf("|\n");
          gotoxy(81,aux);
          printf("|\n");
          aux++;

     }

     gotoxy(2,26);
     printf("MSG.:");

     gotoxy(2,27);
     printf("OP..:");

     gotoxy(2, 1);
     printf("UNICV");
     gotoxy(20, 1);
     printf("SISTEMA DE GESTAO DE CLIENTE");
     gotoxy(61, 1);
     printf("Estrutura de dados");
}

Tipoapontador buscaCodigo(TipoLista *Lista, int codigoBusca){

     Tipoapontador p;

     p = Lista->primeiro;

     while (p != NULL)
     {
          if(codigoBusca == p->conteudo.cd_funcionario){

               break;;
          }
          p = p->proximo;
     }
     
     return p;
     
}

void gravar(TipoLista *Lista){

     FILE *ptr;
     char *filename = "Funcionario.dat";
     char *modoGravacao = "wb";
     Tipoapontador p;
     reg_funcionario reg_func;
     p = Lista->primeiro;

     
     if(p == NULL){

          printf("Lista vazia.");

     } else {

          if((ptr = fopen(filename, modoGravacao)) == NULL){

               printf("Erro ao abrir arquivo.");

          } else{

               while (p != NULL)
               {
                    reg_func = p->conteudo;
                    fwrite(&reg_func, sizeof(reg_func), 1, ptr);
                    p = p->proximo;
               }

               fclose(ptr);
          
          }

     }

}

void lerArquivo(TipoLista *Lista)
{
    FILE *ptr = fopen("Funcionario.dat", "rb");
    if (ptr == NULL)
        return;

    reg_funcionario reg_func;
    while (fread(&reg_func, sizeof(reg_funcionario), 1, ptr) == 1)
    {
        Tipoapontador novo = (Tipoapontador)malloc(sizeof(Tipoitem));
        novo->conteudo = reg_func;
        novo->proximo = NULL;

        if (Lista->primeiro == NULL)
        {
            Lista->primeiro = novo;
            Lista->Ultimo = novo;
        }
        else
        {
            Lista->Ultimo->proximo = novo;
            Lista->Ultimo = novo;
        }
    }
    fclose(ptr);
}

void registraCliente(TipoLista *Lista){

     int opMenu;

     do{
          int op;
          system("cls");
          tela();

          telaCadastro();
          
          Tipoapontador p, aux;
          reg_funcionario funcionario;
          p = (Tipoapontador)malloc(sizeof(Tipoitem));
          
          do{

               gotoxy(9,26);
               printf("Digite o codigo do funcionario ou 0 para finalizar: ");
               gotoxy(41,4);
               scanf("%d", &funcionario.cd_funcionario);

               aux = buscaCodigo(Lista, funcionario.cd_funcionario);

               if(aux != NULL){

                    limpaMSG();
                    gotoxy(9,26);
                    printf("Codigo ja cadastrado");
                    getch();

               } else if(funcionario.cd_funcionario == 0){

                    limpaMSG();
                    gotoxy(9,26);
                    printf("Cadastro finalizado!");
                    getch();
                    return;

               }
               
          }while (aux != NULL);
          
          limpaMSG();
          gotoxy(9,26);
          printf("Digite o nome do funcionario: ");
          gotoxy(41,6);
          fflush(stdin);
          fgets(funcionario.nm_funcionario, 50, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o endereco do funcionario ");
          gotoxy(41,8);
          fflush(stdin);
          fgets(funcionario.endereco, 50, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite a data de nascimento do funcionario ");
          gotoxy(41,10);
          fflush(stdin);
          fgets(funcionario.dataNasc, 11, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o telefone do funcionario");
          gotoxy(41,12);
          fflush(stdin);
          fgets(funcionario.telefone, 15, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o CPF do funcionario ");
          gotoxy(41,14);
          fflush(stdin);
          fgets(funcionario.cpf, 15, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o cargo do funcionario ");
          gotoxy(41,16);
          fflush(stdin);
          fgets(funcionario.cargo, 40, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o departamento do funcionario ");
          gotoxy(41,18);
          fflush(stdin);
          fgets(funcionario.dpto, 30, stdin);

          limpaMSG();
          gotoxy(9,26);
          printf("Digite o salario do funcionario: ");
          gotoxy(41,20);
          scanf("%f", &funcionario.vl_salario);

          limpaMSG();
          gotoxy(9,26);
          printf("Deseja confirmar o cadastro?\t1. SIM\t2. NAO");
          gotoxy(9,27);
          scanf("%d", &op);

          if(op == 1){

               int count = 0;
               int posicao;
               limpaMSG();
               system("cls");
               tela();
               

               p->conteudo = funcionario;

               gotoxy(15,9);
               printf("1. Adicionar ao comeco da fila");
               gotoxy(15,11);
               printf("2. Adicionar ao final da fila");
               gotoxy(15,13);
               printf("3. Adicionar a uma posicao especifica");
               gotoxy(9,26);
               printf("Digite a opcao para adicionar");
               gotoxy(9,27);
               scanf("%d", &op);

               switch (op)
               {
                    case 1: //Adiciona no começo da lista

                         if(Lista->primeiro == NULL){

                              Lista->primeiro = p;
                              Lista->primeiro->proximo = NULL;
                              Lista->Ultimo = p;

                         } else {
                              aux = Lista->primeiro;
                              Lista->primeiro = p;
                              p->proximo = aux;
                         }
                         gotoxy(9,26);
                         printf("Adicionado ao comeco da lista              ");
                         getch();

                         break;
               
                    case 2: //Adiciona ao final da lista
                         
                         if(Lista->primeiro == NULL){

                              Lista->primeiro = p;
                              Lista->primeiro->proximo = NULL;
                              Lista->Ultimo = p;

                         } else {

                              aux = Lista->Ultimo;
                              aux->proximo = p;
                              Lista->Ultimo = p;
                              p->proximo = NULL;
                         }
                         
                         gotoxy(9,26);
                         printf("Adicionado ao final da lista           ");
                         getch();

                         break;

                    case 3: //Adiciona em um lugar especifico

                         aux = Lista->primeiro;
                         Tipoapontador aux2 = aux;

                         gotoxy(9,26);
                         printf("Digite a posicao para incluir");
                         gotoxy(9,27);
                         scanf("%d", &posicao);

                         if(posicao == 1 && Lista->primeiro == NULL){
               
                              Lista->primeiro = p;
                              Lista->primeiro->proximo = NULL;
                              Lista->Ultimo = p;

                         } else{

                              while (aux != NULL){

                                   count++;
                                   

                                   if(posicao == 1){

                                        Lista->primeiro = p;
                                        p->proximo = aux2;
                                        break;
                                        

                                   } else if(posicao == count){

                                        aux2->proximo = p;
                                        p->proximo = aux;
                                        break;

                                   } else if(aux->proximo == NULL && posicao != count){

                                        aux = Lista->Ultimo;
                                        Lista->Ultimo = p;
                                        aux->proximo = p;
                                        p->proximo = NULL;

                                   }

                                   aux2 = aux;
                                   aux = aux->proximo;
                              }
                         }

                         gotoxy(9,26);
                         printf("Adicionado a posicao %d da lista   ", posicao);
                         getch();

                         break;
                         
                    default:
                         
                         gotoxy(9,26);
                         printf("Opcao invalida!            ");
                         getch();

                         break;
               }

               gotoxy(9,26);
               printf("Deseja cadastrar outro cliente?  1.SIM   2.NAO");
               gotoxy(9,27);
               scanf("%d", &opMenu);

               if(opMenu != 1){
                    gotoxy(9,26);
                    printf("Cadastro finalizado! Voltando ao menu");
               }
          }
     }while (opMenu == 1 );
}

void removeDaLista(TipoLista *Lista){

     system("cls");
     tela();
     limpaMSG();
     int op, count;
     Tipoapontador p, aux;


     gotoxy(9, 26);
     printf("Digite uma opcao ou 0 para cancelar");

     gotoxy(15,6);
     printf("1. Remover cadastro do final da lista");
     gotoxy(15,8);
     printf("2. Remover do inicio da lista");
     gotoxy(15,10);
     printf("3. Remover de uma posicao especifica");

     gotoxy(9,27);
     scanf("%d", &op);

     //Se nao tiver nenhum cadastro ele aponta erro e retorna
     if(Lista->primeiro == NULL){

          limpaMSG();
          gotoxy(9,26);
          printf("Nenhum cadastro realizado.");
          getch();
          return;

     } else {

          //Escolher entre remover do final, inicio ou posicao especifica
          switch (op){

               case 1: //Remove do final

                    p = Lista->primeiro;

                    //Caso so tenha um registro na lista 
                    if(p->proximo == NULL){

                         free(Lista->primeiro);
                         free(Lista->Ultimo);
                         free(p);

                         return;

                    } else{

                    
                         //Caso a lista nao esteja vazia faz o laço para achar o penultimo
                         while(p != NULL){

                              if(p->proximo == NULL){

                                   Lista->Ultimo = aux;
                                   aux->proximo = NULL;
                                   free(p);
                                   return;
                              }
                              aux = p;
                              p = p->proximo;
                         }
                    }

                    break;
               
               case 2: //Remove do inicio da lista
                    
                    p = Lista->primeiro;
                    aux = p->proximo;
                    Lista->primeiro = aux;
                    free(p);
                    break; 
               
               case 3: //Remove de uma posicao especifica

                    system("cls");
                    tela();
                    p = Lista->primeiro;
                    aux = p;
                    count = 0;
                    
                    gotoxy(9, 26);
                    printf("Digite a posicao que deseja excluir");
                    scanf("%d", &op);

                    //Se a lista so tiver um registro
                    if(p->proximo == NULL && op == 1){

                         free(p);
                         return;

                    } else {

                         while (p != NULL){
                             
                              count++;
                              if(op == count){
                                   
                                   //Se a posicao for a ultima da lista
                                   if(p->proximo == NULL){

                                        aux->proximo = NULL;
                                        Lista->Ultimo = aux;
                                        free(p);
                                        return;

                                   } else{

                                        aux->proximo = p->proximo;
                                        free(p);
                                        return;
                                   }   
                              }

                              aux = p;
                              p = p->proximo;
                         
                         }
                    }
                    break;

               default:
                    
                    limpaMSG();
                    gotoxy(9,26);
                    printf("Opcao invalida");
                    break;

          }
     }
}

void consulta(TipoLista *Lista){

     system("cls");
     tela();
     Tipoapontador p;
     p = Lista->primeiro;
     int count = 1;

     if(Lista->primeiro == NULL){

          gotoxy(30,10);
          printf("Lista vazia!");
          gotoxy(9,26);
          printf("Digite ENTER para voltar ao menu");
          getch();
          return;

     } else{

          while(p != NULL){

               system("cls");
               tela();
               telaCadastro();
               gotoxy(9,26);
               printf("Pressione ENTER para ir para o proximo cadastro");
               gotoxy(50,24);
               printf("Posicao na lista: %d", count);

               gotoxy(41,4);
               printf("%d", p->conteudo.cd_funcionario);

               gotoxy(41,6);
               printf("%s", p->conteudo.nm_funcionario);

               gotoxy(41,8);
               printf("%s", p->conteudo.endereco);

               gotoxy(41,10);
               printf("%s", p->conteudo.dataNasc);

               gotoxy(41,12);
               printf("%s", p->conteudo.telefone);

               gotoxy(41,14);
               printf("%s", p->conteudo.cpf);

               gotoxy(41,16);
               printf("%s", p->conteudo.cargo);

               gotoxy(41,18);
               printf("%s", p->conteudo.dpto);

               gotoxy(41,20);
               printf("%.2f", p->conteudo.vl_salario);

               p = p->proximo;
               count++;
               getch();
          }
     }
}

void alterarDados(TipoLista *Lista){

     system("cls");
     tela();
     int codigo, op;
     Tipoapontador p;

     if(Lista->primeiro == NULL){

          gotoxy(25,10);
          printf("Nenhum cadastro encontrado");
          gotoxy(9,26);
          printf("Digite ENTER para voltar ao menu");
          getch();
          return;

     } else{

          do{
               gotoxy(9,26);
               printf("Digite o codigo do funcionario para alteracao");
               gotoxy(9,27);
               scanf("%d", &codigo);

               p = buscaCodigo(Lista, codigo);

               if(p == NULL){

                    limpaMSG();
                    system("cls");
                    tela();
                    gotoxy(30,10);
                    printf("Codigo nao cadastrado");

               } else {

                    limpaMSG();
                    telaCadastro();
                    gotoxy(41,4);
                    printf("%d", p->conteudo.cd_funcionario);

                    gotoxy(41,6);
                    printf("%s", p->conteudo.nm_funcionario);

                    gotoxy(41,8);
                    printf("%s", p->conteudo.endereco);

                    gotoxy(41,10);
                    printf("%s", p->conteudo.dataNasc);

                    gotoxy(41,12);
                    printf("%s", p->conteudo.telefone);

                    gotoxy(41,14);
                    printf("%s", p->conteudo.cpf);

                    gotoxy(41,16);
                    printf("%s", p->conteudo.cargo);

                    gotoxy(41,18);
                    printf("%s", p->conteudo.dpto);

                    gotoxy(41,20);
                    printf("%.2f", p->conteudo.vl_salario);


                    gotoxy(9,26);
                    printf("Digite o campo para alterar ou 0 para voltar ao menu");
                    scanf("%d", &op);

                    do{
                         switch (op)
                         {
                         case 1:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo nome do funcionario");
                              gotoxy(41,6);
                              fflush(stdin);
                              fgets(p->conteudo.nm_funcionario, 50, stdin);
                              break;

                         case 2:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo endereco do funcionario");
                              gotoxy(41,8);
                              fflush(stdin);
                              fgets(p->conteudo.endereco, 50, stdin);
                              break;

                         case 3:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite a data de nascimento do funcionario");
                              gotoxy(41,10);
                              fflush(stdin);
                              fgets(p->conteudo.dataNasc, 10, stdin);
                              break;
                         
                         case 4:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo telefone do funcionario");
                              gotoxy(41,12);
                              fflush(stdin);
                              fgets(p->conteudo.telefone, 15, stdin);
                              break;
                         
                         case 5:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o cpf do funcionario");
                              gotoxy(41,14);
                              fflush(stdin);
                              fgets(p->conteudo.cpf, 15, stdin);
                              break;
                         
                         case 6:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo cargo do funcionario");
                              gotoxy(41,16);
                              fflush(stdin);
                              fgets(p->conteudo.cargo, 40, stdin);
                              break;
                         
                         case 7:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo departamento do funcionario");
                              gotoxy(41,18);
                              fflush(stdin);
                              fgets(p->conteudo.dpto, 30, stdin);
                              break;
                         
                         case 8:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Digite o novo valor do salario do funcionario");
                              gotoxy(41,20);
                              scanf("%f", &p->conteudo.vl_salario);
                              break;
                         
                         case 0:
                              
                              limpaMSG();
                              gotoxy(9,26);
                              printf("Alteracao cancelada");
                              getch();
                              return;
                         
                         default:

                              limpaMSG();
                              gotoxy(9,26);
                              printf("Opcao invalida");
                              getch();
                              break;
                         }

                    }while ((op < 1 || op > 8) || (op == 0));
                    
                    
               }

               limpaMSG();
               gotoxy(9,26);
               printf("Deseja alterar os dados de outro funcionario? 1.SIM 2.NAO");
               scanf("%d", &op);

          }while (op == 1);
          
     }

}

int main(){

     int op;

     TipoLista Lista;

     Lista.primeiro = NULL;
     Lista.Ultimo = NULL;

     lerArquivo(&Lista);
     
     do{
          
          system("cls");
          tela();
          gotoxy(9,26);
          printf("Digite a opcao que deseja.");
          gotoxy(25,6);
          printf("1. Registrar funcionario");
          gotoxy(25,8);
          printf("2. Remover funcionario");
          gotoxy(25,10);
          printf("3. Consultar funcionario");
          gotoxy(25,12);
          printf("4. Alterar dados de funcionario");
          gotoxy(25,14);
          printf("5. Encerrar programa");
          gotoxy(9,27);
          scanf("%d", &op);
          switch(op){

               case 1: //Registra cliente

                    registraCliente(&Lista);
                    break;
               
               case 2: //Exclui da lista
                    
                    removeDaLista(&Lista);
                    break;
               
               case 3: //Consulta

                    consulta(&Lista);
                    break;

               case 4: //Altera dados
                    
                    alterarDados(&Lista);
                    break;

               case 5:

                    gravar(&Lista);
                    limpaMSG();
                    gotoxy(9,26);
                    printf("Programa finalizado");
                    break;

               default:
                    printf("Numero invalido");
          }
     }while (op != 5);

     return 0;
}