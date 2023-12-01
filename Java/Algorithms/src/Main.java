class Matrix {
  /*
  Алгоритм Штрассена можно применять для матриц любого размера, но он является наиболее эффективным для квадратных матриц.

  Порядок новой матрицы число строк первой на число столбцов второй N1xM2.

  Написать эффективный алгоритм !!!

  */
  private final int n, m;
  private double[][] data;

  Matrix (int n, int m) {
    this.n = n; this.m = m;
    data = new double[this.n][this.m];
    for (int i = 0; i < this.n; ++i) {
      for (int j = 0; j < this.m; ++j) {
        data[i][j] = Math.random()*(100+1);
      }
    }
  }
  public Matrix multiply (Matrix B) {
    Matrix C = new Matrix(n, B.m);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        C.data[i][j] = 0;
        for (int k = 0; k < m; ++k) {
          C.data[i][j] += this.data[i][k]*B.data[k][j];
        }
      }
    }

    return C;
  }

  public void print() {
    for (double[] d : data) {
      for (double el : d) {
        System.out.print(el + ", ");
      }
      System.out.println();
    }
    System.out.println("---");

  }

}
class Box {
  private final double width, height, depth ;
  int tst;
  Box () {
    width = -1; height = -1; depth = -1;
  }
  Box (double len) {
    width = height = depth = len;
  }
  Box (double w, double h, double d) {
    width = w; height = h; depth = d;
  }
  // Конструктор копирования
  Box (Box B) {
    this.width = B.width;
    this.height = B.height;
    this.depth = B.depth;
  }
  double volume () {
    return width * height * depth;
  }
}
class BoxWeight extends Box {
  private final double weight;
  BoxWeight () {
    super();
    weight = -1;
  }
  BoxWeight (double width, double height, double depth, double weight) {
    super(width, height, depth);
    this.weight = weight;
  }
  BoxWeight (BoxWeight B) {
    super(B);
    this.weight = B.weight;
  }
}
public class Main {
  public static void main(String[] args) {
    Matrix A = new Matrix(2, 2);
    Matrix B = new Matrix(2, 2);
    Matrix C = A.multiply(B);

    A.print(); B.print(); C.print();

  }
}