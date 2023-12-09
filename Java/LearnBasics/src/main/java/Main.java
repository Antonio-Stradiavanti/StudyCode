public class Main {

  static void testThrow() throws NullPointerException {
    throw new NullPointerException("Демонстация");
  }
  public static void main(String[] args) {
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
  }
}
