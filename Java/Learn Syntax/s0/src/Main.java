package LearnJava.s0.src;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.reflect.Method;

@Retention(RetentionPolicy.RUNTIME)
@interface An {
    String str();
    int val();
}
class Box {
    double w, h, d;
    void setWeight(double w) {
        this.w = w;
    }
    double getVolume () {
        return w*h*d;
    }
    void print() {
        System.out.println("w = " + w + ", h = " + h + ", d = " + d);
    }
    Box () {
        w = 0; h = 0; d = 0;
    }
    Box (double w, double h, double d) {
        this.w = w; this.h = h; this.d = d;
    }
}
public class Main {
    enum Apple {
        Jonathan, GoldenDel, RedDel, Winesap, Cortland
    }
    @An(str = "Пример аннотации из книги Шилдта", val = 777)
    public static void printAn() {
        Main m = new Main();
        try {
            // Пример использования рефлексии, получаем объект класса Class, который
            // представляет класс, содержащий целевую аннотацию.

            Class<?> c = m.getClass();
            Method met = c.getMethod("printAn");
            An an = met.getAnnotation(An.class);
            System.out.println(an.str() + " = " + an.val() + ";");

        } catch (NoSuchMethodException e) {
            System.out.println("Метод не найден");
        }
    }
    public static void main(String[] args) {

        Box b0 = new Box(), b1 = new Box(10.1, 2.5, 12.1);
        b0 = b1; b0.setWeight(100.80);
        b0.print(); b1.print();
        
        //printAn();
    }
}