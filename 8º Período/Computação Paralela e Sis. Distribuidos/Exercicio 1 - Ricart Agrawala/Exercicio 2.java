public class Data implements Cloneable {
    private int dia;
    private int mes;
    private int ano;

    public Data(int dia, int mes, int ano) {
        if (dataValida(dia, mes, ano)) {
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        } else {
            this.dia = 1;
            this.mes = 1;
            this.ano = 1;
        }
    }

    public int compara(Data outraData) {
        if (this.ano > outraData.ano) {
            return 1;
        } else if (this.ano < outraData.ano) {
            return -1;
        } else {
            if (this.mes > outraData.mes) {
                return 1;
            } else if (this.mes < outraData.mes) {
                return -1;
            } else {
                if (this.dia > outraData.dia) {
                    return 1;
                } else if (this.dia < outraData.dia) {
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }

    public int getDia() {
        return dia;
    }

    public int getMes() {
        return mes;
    }

    public String getMesExtenso() {
        String[] meses = {
            "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
            "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
        };
        return meses[mes - 1];
    }

    public int getAno() {
        return ano;
    }

    public boolean isBissexto() {
        return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    }

    public Data clone() {
        return new Data(this.dia, this.mes, this.ano);
    }

    private boolean dataValida(int dia, int mes, int ano) {
        if (ano >= 1 && mes >= 1 && mes <= 12) {
            int[] diasPorMes = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (isBissexto() && mes == 2) {
                return dia >= 1 && dia <= 29;
            } else {
                return dia >= 1 && dia <= diasPorMes[mes];
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Data data1 = new Data(29, 2, 2020);
        Data data2 = new Data(15, 8, 2023);

        System.out.println("Data 1: " + data1.getDia() + "/" + data1.getMes() + "/" + data1.getAno());
        System.out.println("Mês por extenso: " + data1.getMesExtenso());

        System.out.println("Data 2: " + data2.getDia() + "/" + data2.getMes() + "/" + data2.getAno());
        System.out.println("Mês por extenso: " + data2.getMesExtenso());

        System.out.println("Data 1 é bissexto: " + data1.isBissexto());
        System.out.println("Data 2 é bissexto: " + data2.isBissexto());

        int comparacao = data1.compara(data2);
        if (comparacao == 0) {
            System.out.println("As datas são iguais.");
        } else if (comparacao == 1) {
            System.out.println("A data 1 é maior que a data 2.");
        } else {
            System.out.println("A data 2 é maior que a data 1.");
        }

        Data dataClone = data1.clone();
        System.out.println("Clone da Data 1: " + dataClone.getDia() + "/" + dataClone.getMes() + "/" + dataClone.getAno());
    }
}