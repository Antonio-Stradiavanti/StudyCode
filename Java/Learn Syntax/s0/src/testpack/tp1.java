package testpack;

public class tp1 {
    String name;
    double bal;
    tp1 (String name, double bal) {
        this.name = name; this.bal = bal;
    }
    void print () {
        System.out.println("<< name : " + name + "," +
                " bal : " + bal + ";");
    }
}
