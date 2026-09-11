package com.craftinginterpreters.lox;

public class RPNConvert implements Expr.Visitor<String> {
  String print(Expr e) {
    return e.accept(this);
  }

  // Override the function for visiting binary expressions, converts the format "a + b" to look like "a b +""
  @Override
  public String visitBinaryExpr(Expr.Binary e) {
    return(e.left.accept(this) + " " + e.right.accept(this) + " " + e.operator.lexeme);
  }

  // For grouping expressions, just print them normally
  @Override
  public String visitGroupingExpr(Expr.Grouping e) {
    return e.expression.accept(this);
  }

  // For literals, return the string for printing
  @Override
  public String visitLiteralExpr(Expr.Literal e) {
    return e.value.toString();
  }

  // For unary expressions (except "-"), converts the format "! a" to "a !"
  @Override
  public String visitUnaryExpr(Expr.Unary e) {
    String operator = e.operator.lexeme;
    if (e.operator.type == TokenType.MINUS) {
      // The "-" expression is special because it is both unary and binary
      // To avoid mismatches, replace it with "~" 
      operator = "~";
    }

    return(e.right.accept(this) + " " + operator);
  }

  public static void main(String[] args) {
    // The expression "a or b and c" should convert to "b c and a or"
    Expr exp = new Expr.Binary(
        new Expr.Binary(
            new Expr.Literal("a"),
            new Token(TokenType.OR, "or", null, 1),
            new Expr.Literal("b")),
        new Token(TokenType.AND, "and", null, 1),
            new Expr.Literal("c"));

    System.out.println(new RPNConvert().print(exp));
  }
  
}
