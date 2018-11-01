package com.javaLab.Test;

import java.util.Comparator;

/**
 * Класс для тестирования SearchTree
 */
public class TestForTree implements Comparable<TestForTree>{

    private Integer num;

    public TestForTree(int num){
        this.num = num;
    }
    public TestForTree(){

    }

    // создаем компаратор с помощью анонимного класса
    public static final Comparator<TestForTree> cmp = new Comparator<>() {
        @Override
        public int compare(TestForTree o1, TestForTree o2) {
            if (o1.num < o2.num)
                return -1;
            if (o1.num > o2.num)
                return 1;
            return 0;
        }
    };

    public String toString() {
        return num.toString();
    }

    @Override
    public int compareTo(TestForTree o) {
        if (this.num < o.num)
            return -1;
        if (this.num > o.num)
            return 1;
        return 0;
    }

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        this.num = num;
    }
}
