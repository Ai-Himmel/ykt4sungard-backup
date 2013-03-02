package org.king.check.common.tst;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This class is used to suggest a list of items, which will be similar to a
 * given string prefix. Tenary Search Tree will be the primary data structure
 * to hold the complete list of E items. The searching mechanism is case insensitive.
 * <p/>
 * User: Yiming.You
 * Date: 2010-9-19
 */
public class TSTSearchEngine<E> implements SearchEngine<E> {

    private final TernarySearchTree<String> tst = new TernarySearchTree<String>();
    // We need to have this map, so that we are able to retrieve E value
    // in a case insensitive way. This is just a pseudo way for us to
    // achieve this purpose. We should really build this case insensitive
    // capability into TernarySearchTree itself. Once TernarySearchTree
    // has the capability to handle case insensitive, it should be holding
    // E value instead of String (String will be used as the key to access
    // map).
    //
    // There should be no duplicated item in List. Don't use Set, as order
    // is important for us.
    private final Map<String, List<E>> map = new HashMap<String, List<E>>();

    /**
     * Initializes a newly created {@code TSTSearchEngine} with a given list of
     * elements.
     *
     * @param sources List of elements used to fill up {@code TSTSearchEngine}
     */
    public TSTSearchEngine(List<E> sources) {
        for (E source : sources) {
            put(source);
        }
    }

    /**
     * Initializes a newly created {@code TSTSearchEngine} with empty element.
     */
    public TSTSearchEngine() {
    }

    /**
     * Returns a list of elements, which will be similar to a given string prefix.
     * The searching mechanism is case insensitive.
     *
     * @param prefix String prefix to match against elements
     * @return A list of elements, which will be similar to a given string prefix.
     *         Returns empty list if no match found.
     */
    public List<E> searchAll(String prefix) {
        final String mapKey = prefix.toUpperCase();
        final List<String> keys = tst.matchPrefix(mapKey);
        final List<E> list = new ArrayList<E>();
        for (String key : keys) {
            // map.get(key) must be non-null.
            list.addAll(map.get(key));
        }
        return list;
    }

    /**
     * Returns an element, which will be most similar to a given string prefix.
     * The searching mechanism is case insensitive.
     *
     * @param prefix String prefix to match against elements
     * @return An element, which will be most similar to a given string prefix.
     *         Returns <code>null</code> if no match found.
     */
    public E search(String prefix) {
        final String mapKey = prefix.toUpperCase();
        final List<String> keys = tst.matchPrefix(mapKey);
        if (keys.isEmpty() == false) {
            final String key = keys.get(0);
            // key must be non-null.
            final List<E> l = map.get(key);
            return l.isEmpty() == false ? l.get(0) : null;
        }
        return null;
    }

    /**
     * Insert an element into this search engine.
     *
     * @param value Element to be inserted
     */
    public final void put(E value) {
        final String mapKey = value.toString().toUpperCase();
        tst.put(mapKey, mapKey);

        List<E> list = map.get(mapKey);
        if (list == null) {
            list = new ArrayList<E>();
            map.put(mapKey, list);
        }
        // Avoid duplication. Don't use Set, as order is
        // important for us.
        if (false == list.contains(value)) {
            list.add(value);
        }
    }

    /**
     * Removes an element from this search engine.
     *
     * @param value Element to be removed
     */
    public void remove(E value) {
        final String mapKey = value.toString().toUpperCase();
        final String key = tst.remove(mapKey);
        if (key != null) {
            map.remove(key);
        }
    }
}
