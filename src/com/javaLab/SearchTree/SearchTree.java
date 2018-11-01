package com.javaLab.SearchTree;

import java.util.Comparator;

public class SearchTree<K extends Comparable, V> {

    private Node root = null;
    private Comparator comparator;

    /**
     * Узел дерева
     * @param <K> тип ключа
     * @param <V> тип значения
     */
    class Node<K, V> {
        public K key;
        public V value;
        protected Node<K, V> left, right;   // Левое и правое поддерево
        protected Node<K, V> prev;          // ссылка на parent

        public Node(Node prev, K key, V value) {
            this.key = key;
            this.value = value;
            this.prev = prev;
            left = right = null;
        }
    }

    /**
     * Сравнение ключей
     * @param key1
     * @param key2
     * @return
     * -1 - key1 <  key2
     *  0 - key1 == key2
     *  1 - key1 >  key2
     */
    private int compare(K key1, K key2) {
        if (comparator == null) {
            return ((Comparable)key1).compareTo(key2); // если компаратора нет, то берем его из класса
        }
        return comparator.compare(key1, key2);
    }

    /**
     * Конструктор
     * Если нет компаратора, то будет использоваться compareTo()
     */
    public SearchTree() {
        comparator = null;
    }
    // если передается компаратор
    public SearchTree(Comparator<K> comparator) { //Comparator<? super K>
        this.comparator = comparator;
    }

    /**
     * Вставка ключа в дерево. Один ключ встречается только один раз
     * @param key ключ
     * @param value значение
     */
    public void insert(K key, V value) {
        root = insert(root, null, key, value);
    }
    private Node insert(Node curr, Node prev, K key, V value) {

        if (curr == null) {
            curr = new Node(prev, key, value);
        }
        else {
            if (compare(key, (K)curr.key) == -1)
                curr.left = insert(curr.left, curr, key, value);
            else
                if (compare(key, (K)curr.key) == 1) //Если  необходимы дублирующие ключи, удалить
                    curr.right = insert(curr.right, curr, key, value);
        }
        return curr;
    }


    /**
     * Поиск по ключу
     * @param key ключ
     * @return ссылка на узел, в котором находится заданный ключ
     */
    public Node search(K key) {
        return search(root, key);
    }
    private Node search(Node curr, K key) {
        if (curr == null || compare(key, (K)curr.key) == 0)
            return curr;
        if (compare(key, (K)curr.key) == -1)
            return search(curr.left, key);
        else
            return search(curr.right, key);
    }


    /**
     * Удаление узла по ключу
     * @param key ключ
     */
    public void remove(K key) {
        remove(root, key);
    }
    private void remove(Node curr, K key) {
        if (curr == null)
            return;
        if (compare(key, (K)curr.key) == -1) // key < curr.key
            remove(curr.left, key);
        else
            if (compare(key, (K)curr.key) == 1)
                remove(curr.right, key);
            else
                if (curr.left != null && curr.right != null) {
                    Node temp = curr.right;
                    while (temp.left != null)
                        temp = temp.left;

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

    // вывод
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
