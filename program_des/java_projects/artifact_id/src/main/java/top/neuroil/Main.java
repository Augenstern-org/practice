package top.neuroil;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
        Calculator add = (a, b) -> a+b;

        System.out.println(add.operate(1, 2));
    }
}