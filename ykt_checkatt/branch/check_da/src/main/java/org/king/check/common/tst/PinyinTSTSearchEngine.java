package org.king.check.common.tst;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This class is used to suggest a list of items, based on given Pinyin prefix.
 * The suggested list will be in non-Pinyin. If the item is unable to be
 * translated to Pinyin, its behavior will be similar to TSTSearchEngine. However,
 * all the non-alphabetical characters will be ignored.
 * <p/>
 * For example, in PinyinTSTSearchEngine :
 * database    : hel@lo
 * input       : hello
 * output      : hel@lo
 * <p/>
 * In TSTSearchEngine :
 * database    : hel@lo
 * input       : hel@lo
 * output      : hel@lo
 * <p/>
 * The searching mechanism is case insensitive.
 * User: Yiming.You
 * Date: 2010-9-19
 */
public class PinyinTSTSearchEngine<E> implements SearchEngine<E> {

    // Re-use TSTSearchEngine, as we just like its case-insensitive behavior.
    protected final TSTSearchEngine<String> searchEngine = new TSTSearchEngine<String>();
    // Translate Pinyin to list of items.
    protected Map<String, List<E>> pinyinMap = new HashMap<String, List<E>>();

    /**
     * Initializes a newly created {@code PinyinTSTSearchEngine} with a given list of
     * elements.
     *
     * @param sources List of elements used to fill up {@code PinyinTSTSearchEngine}
     */
    public PinyinTSTSearchEngine(List<E> sources) {
        for (E source : sources) {
            put(source);
        }
    }

    /**
     * Initializes a newly created {@code PinyinTSTSearchEngine} with empty element.
     */
    public PinyinTSTSearchEngine() {
    }

    /**
     * Returns a list of elements, which will be similar to a given pinyin prefix.
     * The searching mechanism is case insensitive.
     *
     * @param pinyinPrefix Pinyin prefix to match against elements
     * @return A list of elements, which will be similar to a given pinyin prefix.
     *         Returns empty list if no match found.
     */
    public List<E> searchAll(String pinyinPrefix) {
        List<String> pinyins = searchEngine.searchAll(pinyinPrefix);
        List<E> list = new ArrayList<E>();
        for (String pinyin : pinyins) {
            // map.get(pinyin) must be non-null.
            final List<E> tmps = pinyinMap.get(pinyin);
            for (E tmp : tmps) {
                if (list.contains(tmp) == false) {
                    // Avoid duplication.
                    list.add(tmp);
                }
            }
        }
        return list;
    }

    /**
     * Returns an element, which will be most similar to a given pinyin prefix.
     * The searching mechanism is case insensitive.
     *
     * @param pinyinPrefix String prefix to match against elements
     * @return An element, which will be most similar to a given string prefix.
     *         Returns <code>null</code> if no match found.
     */
    public E search(String pinyinPrefix) {
        List<String> pinyins = searchEngine.searchAll(pinyinPrefix);
        if (pinyins.isEmpty() == false) {
            final String pinyin = pinyins.get(0);
            // pinyin must be non-null.
            List<E> l = pinyinMap.get(pinyin);
            return l.isEmpty() == false ? l.get(0) : null;
        }
        return null;
    }

    /**
     * Insert an element into this search engine.
     *
     * @param value Element to be inserted
     */
    public void put(E value) {
        final List<String> pinyins = PinyinUtil.toHanyuPinyin(value.toString());
        for (String pinyin : pinyins) {
            searchEngine.put(pinyin);

            List<E> list = pinyinMap.get(pinyin);
            if (list == null) {
                list = new ArrayList<E>();
                pinyinMap.put(pinyin, list);
            }
            if (list.contains(value) == false) {
                // Avoid duplication.
                list.add(value);
            }
        }
    }

    /**
     * Removes an element from this search engine.
     *
     * @param value Element to be removed
     */
    public void remove(E value) {
        final List<String> pinyins = PinyinUtil.toHanyuPinyin(value.toString());
        for (String pinyin : pinyins) {
            searchEngine.remove(pinyin);
            final List list = pinyinMap.get(pinyin);
            list.remove(value);
            if (list.isEmpty()) {
                pinyinMap.remove(pinyin);
            }
        }
    }
}
