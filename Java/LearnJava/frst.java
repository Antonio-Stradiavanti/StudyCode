package LearnJava;
import java.util.*;
class frst {
    // Главный метод, без него программа не может быть скомпилирована
    public static void main (String[] args) {
        // System -> Класс, обеспечивает интрерфейс с операционной системой 
        // out -> Стандартный поток вывода
        // println(выражение типа String)
        Scanner scan = new Scanner(System.in);

        System.out.println("<< Если хотите прекратить ввод данных ведите \"ХВАТИТ\" : ");
        // Любая последовательность символов из потока символов может быть сохранена в строке.
        while (scan.hasNextInt()) {
            int a = scan.nextInt();
            System.out.println("Значение а = " + a);
        }
        scan.close();
    }
}
