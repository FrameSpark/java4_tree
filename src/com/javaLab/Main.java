package com.javaLab;

import com.javaLab.SearchTree.SearchTree;
import com.javaLab.Test.TestForTree;

public class Main {

    public static void main(String[] args) {
        SearchTree<TestForTree, String> tree =
                new SearchTree<>(TestForTree.cmp);

        TestForTree test = new TestForTree(2);
        tree.insert(test, "two");

        test = new TestForTree(1);
        tree.insert(test, "one");

        test = new TestForTree(11);
        tree.insert(test, "eleven");

        test = new TestForTree(3);
        tree.insert(test, "three");


        test = new TestForTree(7);
        tree.insert(test, "seven");

        tree.print();

        System.out.println("Delete key '7'");
        test = new TestForTree(7);
        tree.remove(test);

        tree.print();
    }
}
