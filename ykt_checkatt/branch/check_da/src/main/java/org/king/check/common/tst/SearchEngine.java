package org.king.check.common.tst;

import java.util.List;

/**
 * This class is used to suggest a list of items, which will be similar to a
 * given string prefix.
 * <p/>
 * User: Yiming.You
 * Date: 2010-9-19
 */
public interface SearchEngine<E> {
    /**
     * Returns a list of elements, which will be similar to a given string prefix.
     *
     * @param prefix String prefix to match against elements
     * @return A list of E elements, which will be similar to a given string prefix.
     *         Returns empty list if no match found.
     */
    public List<E> searchAll(String prefix);

    /**
     * Returns an element, which will be most similar to a given string prefix.
     *
     * @param prefix String prefix to match against elements
     * @return An element, which will be most similar to a given string prefix.
     *         Returns <code>null</code> if no match found.
     */
    public E search(String prefix);
}
