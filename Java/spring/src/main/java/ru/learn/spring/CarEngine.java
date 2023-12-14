package ru.learn.spring;

import org.springframework.stereotype.Component;

@Component
public class CarEngine {
  public String getEngineType() {
    return "1.9 TDi";
  }
}
