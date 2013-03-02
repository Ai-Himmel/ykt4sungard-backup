package org.king.check.common.tst;

import org.king.check.domain.Department;

import java.util.ArrayList;
import java.util.List;

/**
 * We are only interested in 'abc' and '123'.
 * User: Yiming.You
 * Date: 2010-9-20
 */
public class DepartmentSearchEngine extends PinyinTSTSearchEngine<Department> {
    public DepartmentSearchEngine(List<Department> sources) {
        super(sources);
    }

    public DepartmentSearchEngine() {
    }

    /**
     * Insert an element into this search engine.
     *
     * @param value Element to be inserted
     */
    public void put(Department value) {
        final List<String> pinyins = PinyinUtil.toHanyuPinyin(value.getName());
        for (String pinyin : pinyins) {
            super.searchEngine.put(pinyin);

            List<Department> list = pinyinMap.get(pinyin);
            if (list == null) {
                list = new ArrayList<Department>();
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
    public void remove(Department value) {
        final List<String> pinyins = PinyinUtil.toHanyuPinyin(value.getName());
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
