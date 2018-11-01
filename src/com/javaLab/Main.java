package com.javaLab;

import com.javaLab.SearchTree.SearchTree;
import com.javaLab.Test.TestForTree;

public class Main {

    public static void main(String[] args) {
        SearchTree<TestForTree, String> tree =
                new SearchTree<>(TestForTree.cmp);

        TestForTree test = new TestForTree();
        test.setNum(2);
        tree.insert(test, "two");

        TestForTree test2 = new TestForTree();
        test2.setNum(1);
        tree.insert(test2, "one");


        TestForTree test3 = new TestForTree();
        test3.setNum(3);
        tree.insert(test3, "three");

        tree.print();

        System.out.println("Delete key '2'");
        tree.remove(test);

        tree.print();
    }
}
