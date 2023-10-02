~Matrix(){
    for (int i = 0; i < Rows; i++){
      delete[] matrix[i];
    }
    delete[] matrix;
  }