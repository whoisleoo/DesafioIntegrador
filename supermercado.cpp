// /033[1;31m /033[0m [VERMEIO]
// /033[1;32m /033[0m [VERDE]
// /033[1;36m /033[0m [CIANO]
// /033[1;33m /033[0m [LARANJA]
// cout << "\033[2J\033[1;1H"; [CLEAR]

//´PROGRAMADA FEITO POR GABRIEL SCHAFRANSKI, LEONARDO MARCONATO, E ESDRAS OBSERVOU O PROCESSO 👀

#include <iostream>
#include <windows.h>
using namespace std;

// DEFINIÇÃO DE VARIAVEIS
long double valor = 0;
int quantidade = 0;
long double troco = 0;
long double valorTotal;
long double trocoTotal = 0;
long double pagamento = 0;
long double ultimaVenda = 0;
int ultimaQtd = 0;
long double ultimoTroco = 0;
long double ultimoPagamento = 0;
int vendaRealizada = 0;
long double valorVenda = 0;

long double valorCaixa = 0;
int quantProdutos = 0;
bool registrarVenda = true;

int main(){
SetConsoleOutputCP(65001);
int opt;
//CRIAR FUNDO DE CAIXA
long double fundoDeCaixa = 0;
cout << "\033[1;32m 💵 Defina um valor para inicializar o caixa: R$\033[0m";
cin >> fundoDeCaixa;
if(fundoDeCaixa < 0){
    cout << "\033[1;31m❌ Entrada invalida! Porfavor, tente novamente!\033[0m\n";
    cin.get();
    cin.ignore();
    cout << "\033[2J\033[1;1H";
}else{
    cout << "\033[1;32m 💰 Valor iniciado em: R$" << fundoDeCaixa << "R$\033[0m\n";
    bool close = true;

    cout << "\033[1;36m🏧 Digite qualquer coisa para entrar.\033[0m";
    cin.get();
    cin.ignore();
    cout << "\033[2J\033[1;1H";

long double fundoDeCaixaPrim = fundoDeCaixa;
//COMEÇO DO SISTEMA
 do{
    cout << "\033[1;36m"; 
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       🛒  SUPERMERCADO RICKLI        ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "\033[0m\n\n"; 
    
    cout << "\033[1;33m";
    cout << "[SELECIONE UMA OPÇÃO]\n\n";
    cout << "\033[0m";


    cout << "\033[1;33m";
    cout << "═════════════════════════════════════════════\n";
    cout << "[1] Regitro de vendas 💵\n";
    cout << "[2] Emissão de comprovante 📃\n";
    cout << "[3] Fechamento caixa ❌\n";
    cout << "═════════════════════════════════════════════\n";
    cout << "\033[0m";

    cout << "\n\033[36m👉 Digite a opção aqui: \033[0m";
    cin >> opt;

    switch (opt)
    {
    case 1: {
     //REGISTO DE VENDAS
     long double valorTotal = 0;
    do{
        cout << "\033[2J\033[1;1H";
   cout << "\033[1;32m"; 
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       💵  REGISTRO DE VENDA          ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";

    cout << "═════════════════════════════════════════════\n\n";
    cout << "\033[0m"; 

        cout << "\033[32m 💵 Digite o valor do produto a ser vendido: R$ \033[0m";
        cin >> valor;
        if(valor <= 0){
             cout << "\033[1;31m❌ Entrada invalida! Porfavor, tente novamente!\033[0m\n";
             cin.get();
             cin.ignore();
             cout << "\033[2J\033[1;1H";
        }else{
        cout << "\033[33m📦 Digite a quantidade de produtos a serem vendidos: \033[0m";
        cin >> quantidade;
            if(quantidade <= 0){
                cout << "\033[1;31m❌ Entrada invalida! Porfavor, tente novamente!\033[0m\n";
                cin.get();
                cin.ignore();
                cout << "\033[2J\033[1;1H";
            } else{
              cout << "\033[2J\033[1;1H";
              valorVenda = quantidade * valor;
              valorTotal += valorVenda;

              cout << "\033[1;32m 💰 Valor registrado de: R$" << valorVenda << "\n";
              cout << "Deseja adicionar outro produto? [S / N]\033[0m\n";
              cout << "\033[36m👉 Digite a opção aqui: \033[0m";
              char verificar;
              cin >> verificar;
              if(verificar == 'S' || verificar == 's'){
                continue;
              }else{
                cout << "\033[2J\033[1;1H";
                registrarVenda = false;
              }
                cout << "\033[1;32m Valor total da venda: R$" << valorTotal << "\033[0m\n";
                cout << "\033[1;32m💲 Insira o valor pago pelo cliente: \033[0m";
                cin >> pagamento;

                if(pagamento < valorTotal){
                    cout << "\033[2J\033[1;1H";
                    cout << "\033[1;31m❌ ERRO! Valor pago insuficiente!\033[0m\n";
                } else if(pagamento > valorTotal){
                    cout << "\033[2J\033[1;1H";
                    troco = pagamento - valorTotal;
                    while(troco > fundoDeCaixa){
                        cout << "\033[2J\033[1;1H";
                        cout << "\033[1;31m❌ ERRO! O caixa não possui fundos suficiente para o pagamento, digite novamente: \033[0m";
                        cin >> pagamento;
                        troco = pagamento - valorTotal;
                        while(pagamento < valorTotal){
                         cout << "\033[2J\033[1;1H";
                         cout << "\033[1;31m❌ ERRO! Valor pago insuficiente! digite o valor novamente: \033[0m\n";
                         cin >> pagamento;
                        }
                        
                    }
                    cout << "\033[1;36m[SUCESSO] 🤝 Venda realizada com sucesso no valor de R$" << valorTotal << "!\033[0m\n";
                    troco = pagamento - valorTotal;
                    trocoTotal += troco;
                    valorCaixa += pagamento;
                    valorCaixa -= troco;
                    vendaRealizada++;
                    
                    cout << "\n\033[1;32m 💵 Seu troco foi de R$" << troco << " reais para um pagamento de R$" << pagamento << " reais.\n";
                }else if(pagamento == valorTotal){
                     cout << "\033[2J\033[1;1H";
                     cout << "\033[1;36m[SUCESSO] 🤝 Venda realizada com sucesso no valor de\033[0m \033[1;32mR$" << valorTotal << " reais!\033[0m\n";
                     valorCaixa += pagamento;
                     fundoDeCaixa += valorCaixa;
                     vendaRealizada++;
                }
            }
        }

    }while(registrarVenda);

        cout << "\033[1;36m⬅ Digite alguma coisa ai pra voltar\033[0m";
        cin.get();
        cin.ignore();
        cout << "\033[2J\033[1;1H";
        break;
    }


    // INICIO DA EMISSÃO DE COMPROVANTE
    case 2: {
    cout << "\033[2J\033[1;1H";
    cout << "\033[1;36m"; 
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       📃 EMISSÃO DE COMPROVANTE      ║\n";
    cout << "╚══════════════════════════════════════╝\n\n";
     cout << "═════════════════════════════════════════════\n\n";
    cout << "\033[0m"; 

    if(vendaRealizada != 0) {

    ultimaVenda = valorVenda ;
    ultimaQtd = quantidade ;
    ultimoTroco = troco ;
    ultimoPagamento = pagamento ;


    cout << "\033[1;37m 📃 Comprovante da ultima venda: \033[0m\n\n";
    cout << "\033[1;37m═════════════════════════════════════════════\033[0m\n\n";
    cout << "💸\033[1;32m Subtotal da venda: R$" << ultimaVenda << "\033[0m\n";
    cout << "🔢 \033[1;36mQuantidade de produtos vendidos: " << ultimaQtd << "\033[0m\n";
    cout << "💰\033[1;32m Pagamento realizado: R$" << pagamento << "\033[0m\n";
    cout << "🤝 \033[1;32mTroco realizado: R$" << ultimoTroco << "\033[0m\n"; 
    cout << "\033[1;37m═════════════════════════════════════════════\033[0m\n\n";
    } else {
    cout << "❌\033[1;31m Nenhuma venda realizada.\033[0m\n" ;
    }
    
    



        cout << "\033[1;36m⬅ Digite alguma coisa ai pra voltar\033[0m";
        cin.get();
        cin.ignore();
        cout << "\033[2J\033[1;1H";
        break;
    }
    case 3: {
        //FECHAMENTO DO CAIXA
        cout << "\033[2J\033[1;1H";
        cout << "\033[1;31m"; 
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║        ❌  FECHAMENTO CAIXA          ║\n";
        cout << "╚══════════════════════════════════════╝\n\n";
        cout << "═════════════════════════════════════════════\n\n";
        cout << "\033[0m"; 

        cout << "🏧\033[1;32m Valor iniciado no caixa: R$" << fundoDeCaixaPrim << "\033[0m\n";
        cout << "💰\033[1;32m Total de vendas feitas: " << vendaRealizada << "\033[0m\n";
        cout << "💳\033[1;32m Total de entradas: R$" <<  valorCaixa << "\033[0m\n";
        cout << "💹\033[1;32m Total de saidas em troco: R$" << trocoTotal << "\033[0m\n"; 
        cout << "🏗\033[1;32m Valor total bruto: R$" << fundoDeCaixaPrim + valorCaixa << "\033[0m\n";


        cout << "\033[1;36m⬅ Digite alguma coisa ai pra voltar\033[0m";
        cin.get();
        cin.ignore();
        cout << "\033[2J\033[1;1H";



        close = false;
    
        break;
    }
    default: {
        //TRATAMENTO DE ERRO
        cout << "\033[2J\033[1;1H";
        cout << "\033[1;31m❌ Entrada invalida! Porfavor, tente novamente!\033[0m\n";
        break;
     }
    }
 








 }while(close);

}














    return 0;
}