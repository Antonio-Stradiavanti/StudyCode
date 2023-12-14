package ru.learn.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import ru.learn.spring.Car;
import ru.learn.spring.CarEngine;

@Configuration
// В проекте содержится один или несколько классов с аннотацией компонент.
@ComponentScan
public class SpringConfig {
  @Bean
  public Car getCar() {
    return new Car(new CarEngine());
  }
}
