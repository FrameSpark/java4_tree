package com.javaLab.SearchTree;

import java.util.Comparator;
import  java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

public class SearchTree<K extends Comparable, V> {

    private Node root = null;
    private Comparator comparator;

    class Node<K, V> {
        public K key;
        public V value;
        protected Node<K, V> left, right;   // Левое и правое поддерево
        protected Node<K, V> prev;          // ссылка на предка

        public Node(Node prev, K key, V value) {
            // TODO клонирование объекта, а не присваивание ссылки
            this.key = key;
            this.value = value;
            this.prev = prev;
            left = right = null;
        }
    }

    // если нет компаратора
    public SearchTree() {
        comparator = null;
    }
    // если передается компаратор
    public SearchTree(Comparator<K> comparator) { //Comparator<? super K>
        this.comparator = comparator;
    }

    //вставка
    public void insert(K key, V value) {
        root = insert(root, null, key, value);
    }
    private Node insert(Node curr, Node prev, K key, V value) {

        if (curr == null) {
            curr = new Node(prev, key, value);
        }
        else {
            if (comparator != null)
                if (comparator.compare(key, curr.key) == -1)
                    curr.left = insert(curr.left, curr, key, value);
                else
                    curr.right = insert(curr.right, curr, key, value);
            else {
                // TODO if comp is NULL
            }

        }
        return curr;
    }

    //поиск по ключу
    public Node search(K key) {
        return search(root, key);
    }
    private Node search(Node curr, K key) {
        if (comparator != null) {
            if (curr == null || comparator.compare(key, curr.key) == 0)
                return curr;
            if (comparator.compare(key, curr.key) == -1)
                return search(curr.left, key);
            else
                return search(curr.right, key);
        }
        else {
            // TODO if comp is NULL
        }
        return null;
    }

    //удаление по ключу
    public void remove(K key) {
        remove(root, key);
    }
    private void remove(Node curr, K key) {
        if (curr == null)
            return;
        if (comparator != null) {
            if (comparator.compare(key, curr.key) == -1) // key < curr.key
                remove(curr.left, key);
            else
                if (comparator.compare(key, curr.key) == 1)
                    remove(curr.right, key);
                else
                    if (curr.left != null && curr.right != null) {
                        Node temp = curr.right;
                        while (temp.left != null)
                            temp = temp.left;

                        // TODO клонирование объекта, а не присваивание ссылки
                        curr.key = temp.key;
                        curr.value = temp.value;
                        replace(temp, temp.right);
                    }
                    else
                        if (curr.left != null)
                            replace(curr, curr.left);
                        else
                            if (curr.right != null)
                                replace(curr, curr.right);
                            else
                                replace(curr, null);
        }
        else {
            // TODO if comp is NULL
        }
    }
    private void replace(Node a, Node b) {
        if (a.prev == null)
            root = b;
        else
            if (a == a.prev.left)
                a.prev.left = b;
            else
                a.prev.right = b;
        if (b != null)
            b.prev = a.prev;
    }

    //вывод
    public void print() {
        System.out.println("TREE ");
        print(root);
        System.out.println();
    }
    private void print(Node curr) {
        if (curr != null) {
            print(curr.left);
            System.out.println(curr.key.toString() + " (" +  curr.value.toString() + ")");
            print(curr.right);
        }
    }
}
