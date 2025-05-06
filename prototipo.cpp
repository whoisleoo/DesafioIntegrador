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

struct ItemCarrinho
{
    int indiceProduto;
    int quantProduto;
};


Produto produtos;
vector<ItemCarrinho> carrinho;

void registrarProduto();
void listaProduto();
void realizarVenda();
void carrinhoCompras();
void visualizarCarrinho();
void finalizarCompra();
void clearScreen();


int main(){
    do{
    cout << "Bem vindo ao sistema de super-mercado VERSÃO BETA 2.0\n\n";
    cout << "[SELECIONE UMA OPÇÃO]\n";
    cout << "[1] Registrar produto.\n";
    cout << "[2] Lista de produtos.\n";
    cout << "[3] Realizar venda.\n";
    cout << "[4] Carrinho de Compras.\n";
    cout << "[5] Visualizar Carrinho.\n";
    cout << "[6] Finalizar Compras. \n";
    cout << "[7] Sair.\n";
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
        carrinhoCompras();
        break;
    case 5:
        visualizarCarrinho();
        break;
    case 6:
        finalizarCompra();
        break;
    case 7:
        close = false;
        break;
    default:
        cout << "Invalido.\n";
        clearScreen();
        break;
    }




    } while(close);
    cout << "Até mais!\n";
    return 0;
}

void registrarProduto(){
    clearScreen();
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
    clearScreen();
}


void listaProduto(){
    clearScreen();
    cout << "[LISTA DE PRODUTOS]\n\n";
    cout << "EM ESTOQUE: " << produtos.product.size() << "\n\n";

    for(int i = 0; i < produtos.product.size(); i++){
            cout << " | NUMERAÇÃO: " << i << "\n";
            cout << " | PRODUTO: " << produtos.product[i] << "\n";
            cout << " | PREÇO: " << produtos.price[i] << "\n\n";
    }
    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    clearScreen();
}


void realizarVenda(){
    do{
    clearScreen();
    int num;
    int quantidadeProduto;
    float valorPago;
    cout << "[REALIZAR VENDA DE PRODUTO]\n";
    cout << "Digite a numeração do produto a ser comprado (Caso não saiba, verifica a lista de produtos) : ";
    cin >> num;
    cout << "Digite a quantidade do produto: ";
    cin >> quantidadeProduto;
    if(quantidadeProduto > 0){

    clearScreen();
    float valorTotal = produtos.price[num] * quantidadeProduto;

    if(num >= 0 && num < produtos.product.size()){
    cout << "[SUCESSO]\n\n";
    cout << "| PRODUTO ENCONTRADO: " << produtos.product[num] << " | QUANTIDADE: " << quantidadeProduto << "\n";
    cout << "| PREÇO TOTAL: R$" << valorTotal << " REAIS | \n\n";
    cout << "Digite o valor pago pelo cliente: R$";
    cin >> valorPago;
    clearScreen();


        if(valorPago == valorTotal){
            cout << "Produto pago com sucesso!\n\n";
            cout << "Valor do produto: R$" << valorTotal << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n";
            cout << "TOTAL: R$" << valorPago << " Reais \n";
            closeSale = false;
        }else if(valorPago < valorTotal){
            float valorNecessario = valorTotal - valorPago;
            cout << "Não foi possivel realizar o pagamento!\n\n";
            cout << "Valor do produto: R$" << valorTotal << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n\n";
            cout << "Ainda precisa de: R$" << valorNecessario << " Reais para completar o pagamento\n";
            closeSale = false;

        }else if(valorPago > valorTotal){
            float troco = valorPago - valorTotal;
            cout << "Produto pago com sucesso!\n\n";
            cout << "Valor do produto: R$" << valorTotal << " Reais \n";
            cout << "Valor pago pelo cliente: R$" << valorPago << " Reais \n\n";
            cout << "Troco do cliente: R$" << troco << " Reais \n";
            closeSale = false;
        } else{
            cout << "ERRO [404].\n";
            cout << "Algo deu errado, verifique se tudo foi digitado corretamente e tente novamente.\n\n";
        }
    } else{
        cout << "[ERRO 404]\n\n";
        cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
        cout << "(Verifique a lista de produtos pra uma consulta mais avançada)\n\n";
    }
}else{
    cout << "[ERRO]\n\n";
    cout << "Quantidade de produto inválida.\n";
}
    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    clearScreen();
 } while(closeSale);
}




void carrinhoCompras() {
    int numProduto;
    int quantidade;

    clearScreen(); 
    cout << "Digite o número do produto a ser adicionado no carrinho: ";
    cin >> numProduto;

    if (numProduto >= 0 && numProduto < produtos.product.size()) {
        cout << "Produto selecionado: " << produtos.product[numProduto] << "\n\n";
        
        cout << "Digite a quantidade a ser comprada: ";
        cin >> quantidade;

        bool numEncontrado = false;
        
    
        for (auto& item : carrinho) {
            if (item.indiceProduto == numProduto) {
               
                item.quantProduto += quantidade;
                numEncontrado = true;
                break;
            }
        }

        if (!numEncontrado) {
            carrinho.push_back({numProduto, quantidade});
            cout << "Produto(s) adicionado(s) com sucesso ao carrinho!\n\n";
        } else {
            cout << "Produto atualizado no carrinho!\n\n";
        }

    } else {
        cout << "[ERRO 404]\n\n";
        cout << "NÃO FOI ENCONTRADO NENHUM PRODUTO VÁLIDO COM ESSA NUMERAÇÃO!\n";
        cout << "(Verifique a lista de produtos para uma consulta mais avançada)\n\n";
    }

    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    clearScreen();
}


void visualizarCarrinho(){
clearScreen();
cout << "[Carrinho de Compras]\n\n";
float totalCarrinho = 0.0;

for(auto& item : carrinho){
    float precoProduto = produtos.price[item.indiceProduto];
    string nomeItem = produtos.product[item.indiceProduto];
    float totalItem = precoProduto * item.quantProduto;

    cout << "Produto: " << nomeItem << " | Quantidade: " << item.quantProduto << "\n";
    cout << "Preço: R$" << precoProduto << "\n";
    cout << "Total: R$" << totalItem << "\n\n";

    totalCarrinho += totalItem;
}

cout << "\n Total do carrinho: R$" << totalCarrinho << "\n\n";
cout << "Pressione qualquer tecla para continuar... ";
cin.ignore();
cin.get();
clearScreen();
}



void finalizarCompra(){
clearScreen();
float totalCarrinho = 0.0;

for(auto& item : carrinho){
    totalCarrinho += produtos.price[item.indiceProduto] * item.quantProduto;
}

if(totalCarrinho > 0){

cout << "[FINALIZAR COMPRA]\n\n";
cout << "Valor total da compra: R$" << totalCarrinho << "\n\n";

float valorPago;
cout << "Valor pago pelo cliente: R$";
cin >> valorPago;

if(valorPago < totalCarrinho){
    float valorFaltante;
    cout << "Valor insuficiente para concluir a compra.\n\n";
    valorFaltante = totalCarrinho - valorPago;
    cout << "Ainda falta: " << valorFaltante << "\n";
} else{
    float troco = valorPago - totalCarrinho;
    cout << "Compra concluida com sucesso!\n\n";
    cout << "Troco do cliente: R$" << troco << "\n";

    carrinho.clear();
    cout << "Pressione qualquer tecla para continuar... ";
    cin.ignore();
    cin.get();
    clearScreen();
}

} else{
cout << "Seu carrinho está vazio, pressione qualquer tecla pra  continuar... ";
    cin.ignore();
    cin.get();  
    clearScreen();
    }
}



void clearScreen() {
    string escape = "\033[2J\033[1;1H";
    cout << escape;
}
