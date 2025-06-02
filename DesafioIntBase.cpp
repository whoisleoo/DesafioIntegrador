// ADENDO: ESSA É A VERSÃO PRIMITIVA DO PROJETO COM APENAS OS RECURSOS BÁSICOS EXIGIDOS, A VERSÃO COMPLETA ESTA NO REPOSITORIO.


#include <iostream>
#include <windows.h>
using namespace std; 

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int opcMenu;
    
    float valProduto = 0;
    int valorTotal = 0;
    int vendas = 0;
    int trocoTotal = 0;

    int ultimaQtd = 0;
    int ultimaVenda = 0;
    int ultimoTroco = 0;
    float ultimoValorPago = 0;

    cout << "Bom dia! Inicie o valor do fundo de caixa: ";
    float fundoInit;
    cin >> fundoInit;
    int fundoCaixa = fundoInit * 100; 
    if (fundoCaixa < 0) {
        cout << "❌ Valor inválido! Deve ser maior que zero." << endl;
        return 1; 
    }
    cout << "Fundo de caixa inicial: R$" << fundoCaixa / 100 << endl;
    
   
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║       🛒  SUPERMERCADO              ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "\n";
    cout << "═════════════════════════════════════════════\n";
    cout << " [1] 📝 Registrar venda\n";
    cout << " [2] 📊 Emitir comprovante\n";
    cout << " [3] ❌ Sair do sistema\n";
    cout << "═════════════════════════════════════════════\n\n";
    
do {
    cout << "[SELECIONE UMA OPÇÃO]\n";
    cin >> opcMenu;
    switch (opcMenu)
    {
    case 1: {
            
            
            int qtdProduto = 0;
            int numProduto = 0;
            char continuar;
            
            do {

            cout << "Digite a quantidade do produto: ";
            cin >> qtdProduto;
            if (qtdProduto <= 0) {cout << "❌ Quantidade inválida! Deve ser maior que zero." << endl; continue;}
            
            cout << "Digite o valor do produto: ";
            cin >> valProduto; 
            if (valProduto < 0) {cout << "❌ Valor inválido! Deve ser maior que zero." << endl; continue;}

            int subTotal = qtdProduto * (valProduto * 100);
            numProduto += subTotal;
            cout << "Subtotal: R$" << numProduto / 100.0 << endl;
            cout << "Deseja continuar? (s/n): ";
            cin >> continuar;
        } 
            
            while (continuar == 's' || continuar == 'S');

                    cout << "Produto registrado com sucesso!" << endl;
                    cout << "Valor total da venda: R$" << numProduto / 100.0 << endl;
                    cout << "\n";
                    cout << "Digite o valor pago pelo cliente: ";
                    float valorPago;
                    cin >> valorPago;
                    int tempPago = valorPago * 100;
                    if (tempPago < 0) {
                        cout << "❌ Valor pago inválido! Deve ser maior que zero." << endl;
                    } else if (tempPago < numProduto) {
                        cout << "❌ Valor pago insuficiente! Venda não registrada." << endl;
                    } else {
                        int troco = tempPago - numProduto;
                        cout << "Troco: R$" << troco / 100.0 << endl;

                        valorTotal += numProduto;
                        fundoCaixa += numProduto; 
                        fundoCaixa -= troco;
                        trocoTotal += troco;
                        vendas++;

                        ultimaQtd = qtdProduto;
                        ultimaVenda = numProduto;
                        ultimoTroco = troco;
                        ultimoValorPago = tempPago;

                    } 
                  
                
        cout << "Valor total da venda: R$" << numProduto / 100.0 << endl << endl;   
        break; 
    }

    case 2: {
        if (valorTotal > 0) {
            cout << "Comprovante da ultima venda:\n";
            cout << "Quantidade de itens: " << ultimaQtd << endl;
            cout << "Total da venda: R$" << ultimaVenda / 100.0 << endl;
            cout << "Valor pago: R$" << ultimoValorPago / 100.0 << endl;
            cout << "Troco: R$" << ultimoTroco / 100.0 << endl;
        } else {
            cout << "Nenhuma venda registrada." << endl;
        }
        break; 
    }

    case 3: {
        cout << "Saindo do sistema..." << endl;
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║          🏁 RELATORIO                ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        cout << "Total de vendas: " << vendas << endl;
        cout << "Valor de entradas: R$" << valorTotal / 100.0 << endl;
        cout << "Valor de saidas: R$" << trocoTotal / 100.0 << endl;
        cout << "Saldo final: R$" << fundoCaixa / 100.0 << endl;
        break; }
    
    default: {
        cout << "❌ Opção inválida! Tente novamente." << endl;
        break; }
     } 
    } while (opcMenu != 3);
    cout << "Obrigado por usar o sistema de caixa!" << endl;
    return 0;
} 
