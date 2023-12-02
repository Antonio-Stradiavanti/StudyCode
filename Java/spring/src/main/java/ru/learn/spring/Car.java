package ru.learn.spring;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

// Нужно объявить класс компонентом контекста приложения Spring.
@Component
public class Car {
  // Зависимость в терминах Java.
  // Не определяем конструктор явно, инъекция зависимостей заключается в
  // автоматическом создании объекта.

  // Инъекцию полей делать не рекомендуется, проще написать конструктор
  private final CarEngine carEngine;

  public void getEngineModel() {
    System.out.println("Модель двигателя автомобиля : " + carEngine.getEngineType());
  }
  public Car(CarEngine carEngine) {
    // Скопировали ссылку.
    this.carEngine = carEngine;
  }

}
