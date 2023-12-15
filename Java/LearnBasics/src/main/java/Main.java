import Annotation.MyAnno;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

interface Callback {
  void callback(int param);
}
@MyAnno(str = "Первая аннотация", val = 100)
class Client implements Callback {
  public void callback(int p) {
    System.out.println("Callback вызван со значением " + p);
  }
}
public class Main {

  static void testThrow() throws NullPointerException {
    throw new NullPointerException("Демонстация");
  }
  public static void main(String[] args) {

    Callback c = new Client();
    c.callback(10);

    int priorityLevel;
    int eventCode = 6010;
    priorityLevel = switch(eventCode) {
      case 8900:
        yield 1;
      case 2000, 6010, 9128:
        yield 2;
      case 7023, 9300, 1002:
        yield 3;
      default:
        yield 0;
    };
    System.out.println("Уровень приоритета кода события " + eventCode + " равен : " + priorityLevel);
    try {
      testThrow();
    } catch (NullPointerException e) {
      System.out.println("Перехватим исключение второй раз ))");
    }

    DateFormat dt = new SimpleDateFormat("dd.MM.yy");
    Calendar cal = Calendar.getInstance();
    cal.add(Calendar.MONTH, 3);
    System.out.println("До : " + dt.format(cal.getTime()));

  }
}
