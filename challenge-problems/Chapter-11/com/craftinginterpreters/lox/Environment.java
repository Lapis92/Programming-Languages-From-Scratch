package com.craftinginterpreters.lox;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Environment {
  final Environment enclosing;
  private final List<Object> values = new ArrayList<>();
  Environment() {
    enclosing = null;
  }

  Environment(Environment enclosing) {
    this.enclosing = enclosing;
  }
  
  void define(String name, Object value) {
    values.put(name, value);
  }
  Environment ancestor(int distance) {
    Environment environment = this;
    for (int i = 0; i < distance; i++) {
      environment = environment.enclosing; // [coupled]
    }

    return environment;
  }
  Object getAt(int distance, String name) {
    Environment environment = this;
    for (int i = 0; i < distance; i++) {
      environment = environment.enclosing;
    }
    return ancestor(distance).values.get(name);
  }
  void assignAt(int distance, Token name, Object value) {
    Environment environment = this;
    for (int i = 0; i < distance; i++) {
      environment = environment.enclosing;
    }
    environment.values.set(slot, value);
  }
  @Override
  public String toString() {
    String result = values.toString();
    if (enclosing != null) {
      result += " -> " + enclosing.toString();
    }

    return result;
  }
}
