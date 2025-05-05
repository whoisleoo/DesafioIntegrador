#include <iostream>
#include <vector>
using namespace std;

bool close = true;
bool closeSale = true;
int mainOption;

struct Produto
{
    vector<float> price;
    vector<string> product;
};

Produto produtos;


void registrarProduto();
void listaProduto();
void realizarVenda();

int main(){
    do{
    cout << "Bem vindo ao sistema de super-mercado VERSÃO BETA 1.0\n\n";
    cout << "[SELECIONE UMA OPÇÃO]\n";
    cout << "[1] Registrar produto.\n";
    cout << "[2] Lista de produtos.\n";
    cout << "[3] Realizar venda.\n";
    cout << "[4] Sair.\n";
    cin >> mainOption;

    switch (mainOption)
    {
    case 1:
       registrarProduto();
        break;
    case 2:
        listaProduto();
        break;
    case 3:
        realizarVenda();
        break;
    case 4:
        close = false;
        break;
    default:

        break;
    }




    } while(close);
    cout << "Até mais!\n";
    return 0;
}

void registrarProduto(){
    system("clear");
    string nome;
    float preco;
    cout << "Digite o nome do produto (Não utilizar espaço) : ";

    cin >> nome;
    cout << "Digite o preço do produto seguindo o exemplo (0.00) : ";
    cin >> preco;
    
    produtos.product.push_back(nome);
    produtos.price.push_back(preco);

    cout << "Produto registrado com sucesso, digite qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    system("clear");
}


void listaProduto(){
    system("clear");
    cout << "[LISTA DE PRODUTOS]\n\n";
    for(int i = 0; i < produtos.product.size(); i++){
            cout << " | NUMERAÇÃO: " << i << "\n";
            cout << " | PRODUTO: " << produtos.product[i] << "\n";
            cout << " | PREÇO: " << produtos.price[i] << "\n\n";
    }
    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    system("clear");
}


void realizarVenda(){
    do{
    system("clear");
    int num;
    float valorPago;
    cout << "[REALIZAR VENDA DE PRODUTO]\n";
    cout << "Digite a numeração do produto a ser comprado (Caso não saiba, verifica a lista de produtos) : ";
    cin >> num;

    system("clear");

    if(num >= 0 && num < produtos.product.size()){
    cout << "[SUCESSO]\n\n";
    cout << "| PRODUTO ENCONTRADO: " << produtos.product[num] << " | PREÇO: R$" << produtos.price[num] << " REAIS | \n\n";
    cout << "Digite o valor pago pelo cliente: R$";
    cin >> valorPago;
    system("clear");
        if(valorPago == produtos.price[num]){
            cout << "Produto pago com sucesso!\n\n";
            cout << "Valor do produto: R$" << produtos.price[num] << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n";
            cout << "TOTAL: R$" << valorPago << " Reais \n";
        }else if(valorPago < produtos.price[num]){
            float valorNecessario = produtos.price[num] - valorPago;
            cout << "Não foi possivel realizar o pagamento!\n\n";
            cout << "Valor do produto: R$" << produtos.price[num] << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n\n";
            cout << "Ainda precisa de: R$" << valorNecessario << " Reais para completar o pagamento\n";

        }else if(valorPago > produtos.price[num]){
            float troco = valorPago - produtos.price[num];
            cout << "Produto pago com sucesso!\n\n";
            cout << "Valor do produto: R$" << produtos.price[num] << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n\n";
            cout << "Troco do cliente: R$" << troco << " Reais \n";
        } else{
            cout << "ERRO [404].\n";
            cout << "Algo deu errado, verifique se tudo foi digitado corretamente e tente novamente.\n\n";
        }
    } else{
        cout << "[ERRO 404]\n\n";
        cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
        cout << "(Verifique a lista de produtos pra uma consulta mais avançada)\n\n";
    }
    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
 } while(closeSale);
}
