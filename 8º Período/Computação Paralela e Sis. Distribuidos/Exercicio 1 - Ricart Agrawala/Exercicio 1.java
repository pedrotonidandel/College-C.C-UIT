public class Aluno {
    private int matricula;
    private String nome;
    private double notaProva1;
    private double notaProva2;
    private double notaTrabalho;

    public Aluno(int matricula, String nome, double notaProva1, double notaProva2, double notaTrabalho) {
        this.matricula = matricula;
        this.nome = nome;
        this.notaProva1 = notaProva1;
        this.notaProva2 = notaProva2;
        this.notaTrabalho = notaTrabalho;
    }

    public double media() {
        double mediaProvas = (notaProva1 + notaProva2) * 2.5;
        double mediaTrabalho = notaTrabalho * 2;
        return (mediaProvas + mediaTrabalho) / 5;
    }

    public double final() {
        double mediaFinal = media();
        if (mediaFinal < 6.0) {
            return 10.0 - mediaFinal;
        }
        return 0;
    }

    public static void main(String[] args) {
        Aluno aluno1 = new Aluno(1, "João", 7.5, 8.0, 9.0);
        System.out.println("Média do aluno 1: " + aluno1.media());
        System.out.println("Nota necessária na final para o aluno 1: " + aluno1.final());

        Aluno aluno2 = new Aluno(2, "Maria", 5.0, 6.0, 7.0);
        System.out.println("Média do aluno 2: " + aluno2.media());
        System.out.println("Nota necessária na final para o aluno 2: " + aluno2.final());
    }
}