package ru.learn;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ru.learn.config.SpringConfig;
import ru.learn.spring.Car;
import ru.learn.spring.CarEngine;

@SpringBootApplication
public class Application {

	public static void main(String[] args) {

		// Создадим контекст (объекты классов всегда создаются в динамической памяти)
		SpringApplication.run(Application.class, args);
		//ApplicationContext ctx = new AnnotationConfigApplicationContext(SpringConfig
		// .class);

		Car car = new Car(new CarEngine());
		//Car car = ctx.getBean(Car.class);

		car.getEngineModel();

	}

}
