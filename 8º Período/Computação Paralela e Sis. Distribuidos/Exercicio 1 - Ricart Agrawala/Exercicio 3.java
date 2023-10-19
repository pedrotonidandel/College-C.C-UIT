class Produto {
    private String nome;
    private double preco;
    private int quantidadeEmEstoque;

    public Produto(String nome, double preco, int quantidadeEmEstoque) {
        this.nome = nome;
        this.preco = preco;
        this.quantidadeEmEstoque = quantidadeEmEstoque;
    }

}

class ItemPedido {
    private Produto produto;
    private int quantidade;

    public ItemPedido(Produto produto, int quantidade) {
        this.produto = produto;
        this.quantidade = quantidade;
    }

    public double calcularSubtotal() {
        return produto.getPreco() * quantidade;
    }

}

class Pedido {
    private Cliente cliente;
    private ItemPedido[] itens;
    private Pagamento pagamento;

    public Pedido(Cliente cliente, ItemPedido[] itens, Pagamento pagamento) {
        this.cliente = cliente;
        this.itens = itens;
        this.pagamento = pagamento;
    }

    public double calcularTotal() {
        double total = 0;
        for (ItemPedido item : itens) {
            total += item.calcularSubtotal();
        }
        return total;
    }

}

class Cliente {
    private String nome;
    private String endereco;

    public Cliente(String nome, String endereco) {
        this.nome = nome;
        this.endereco = endereco;
    }

}

class Pagamento {
    private String metodo;
    private double valor;

    public Pagamento(String metodo, double valor) {
        this.metodo = metodo;
        this.valor = valor;
    }

}

public class SupermercadoApp {
    public static void main(String[] args) {
        Produto produto1 = new Produto("Arroz", 10.0, 50);
        Produto produto2 = new Produto("Feijão", 5.0, 30);

        ItemPedido item1 = new ItemPedido(produto1, 3);
        ItemPedido item2 = new ItemPedido(produto2, 2);

        ItemPedido[] itens = {item1, item2};

        Cliente cliente = new Cliente("João", "Rua A, 123");

        Pagamento pagamento = new Pagamento("Cartão", 25.0);

        Pedido pedido = new Pedido(cliente, itens, pagamento);

        System.out.println("Total do pedido: " + pedido.calcularTotal());
    }
}