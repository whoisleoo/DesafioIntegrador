#include <iostream>
#include <windows.h>
using namespace std; 

int main() {
    SetConsoleOutputCP(65001);
    int opcMenu;
    
    float valProduto = 0;
    int valorTotal = 0;
    int vendas = 0;
    int trocoTotal = 0;
    

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

            cout << "Digite a quantidade do produto: ";
            int qtdProduto = 0;
            int numProduto = 0;
            cin >> qtdProduto;
            
            if (qtdProduto <= 0) {
                cout << "❌ Quantidade inválida! Deve ser maior que zero." << endl;
            } else {
                cout << "Digite o valor do produto: ";
                cin >> valProduto;
                if (valProduto < 0) {
                    cout << "❌ Valor inválido! Deve ser maior que zero." << endl;
                } else {

                    int valCentavos = valProduto * 100;
                    numProduto = valCentavos * qtdProduto;
                    
                    cout << "Produto registrado com sucesso!" << endl;
                    cout << "Valor do produto: R$" << numProduto / 100.0 << endl;

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
                    } 
                  }
                } 
        cout << "Valor total da venda: R$" << numProduto / 100.0 << endl << endl;   
        break; 
    }

    case 2: {
        if (valorTotal > 0) {
            cout << "Total de vendas: " << vendas << endl;
            cout << "Fundo de caixa atual: R$" << fundoCaixa / 100.0 << endl;
            cout << "Valor de entradas totais: R$" << valorTotal / 100.0 << endl;
            cout << "O valor de troco gasto até o momento é: R$" << trocoTotal / 100.0 << endl;
            cout << "Comprovante emitido com sucesso!" << endl << endl;
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
