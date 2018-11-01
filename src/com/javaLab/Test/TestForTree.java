package com.javaLab.Test;

import java.util.Comparator;

public class TestForTree implements Comparable{

    private Integer num;

    public TestForTree(int num){
        this.num = num;
    }

    public TestForTree(){

    }

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
    public int compareTo(Object o) {
        return 0;
    }

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        this.num = num;
    }
}
