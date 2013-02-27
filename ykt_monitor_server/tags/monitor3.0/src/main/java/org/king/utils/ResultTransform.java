package org.king.utils;

import org.apache.commons.beanutils.BeanComparator;
import org.apache.commons.collections.ComparatorUtils;
import org.apache.commons.collections.comparators.ComparableComparator;
import org.apache.commons.collections.comparators.ComparatorChain;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.MyQuery;

import java.text.DecimalFormat;
import java.util.*;

/**
 * .用于转换查询结果
 * User: Yiming.You
 * Date: 2010-8-5
 */
public class ResultTransform {
    private static DecimalFormat decimalFormat = new DecimalFormat("0.000%");

    /**
     * 将查询结果中的数组转换为map
     *
     * @param list .
     * @param keys .
     * @return .
     */
    public static List arrayToMap(List list, String[] keys) {
        List result = new ArrayList();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Map map = new HashMap();
                for (int j = 0; j < keys.length; j++) {
                    map.put(keys[j], row[j]);
                }
                result.add(map);
            }
        }
        return result;
    }

    /**
     * 对结果中的状态数据进行统计
     *
     * @param map       .
     * @param statusMap .
     * @return .
     */
    public static List calculateStatusResult(Map map, Map statusMap) {
        List result = new ArrayList();
        Iterator iterator = map.entrySet().iterator();
        while (iterator.hasNext()) {
            Map.Entry entry = (Map.Entry) iterator.next();
            Map row = (Map) entry.getValue();

            Iterator statusIter = statusMap.entrySet().iterator();
            while (statusIter.hasNext()) {
                Map.Entry status = (Map.Entry) statusIter.next();
                String key = (String) status.getKey();
                String value = (String) status.getValue();
                Long duration = Long.valueOf(0);
                if (row.containsKey(Integer.valueOf(key))) {
                    duration = (Long) row.get(Integer.valueOf(key));
                }
                row.put(value, getPercent(duration, (Long) row.get("total")));
            }
            result.add(row);
        }
        return result;
    }

    public static void sortResult(List result, String[] fields) {
        if (fields == null) {
            return;
        }
        Comparator instance = ComparableComparator.getInstance();
        //允许null
        instance = ComparatorUtils.nullLowComparator(instance);
        //逆序
//        instance = ComparatorUtils.reversedComparator(instance);
        List sortFields = new ArrayList();
        for (int i = 0; i < fields.length; i++) {
            Comparator comparator = new BeanComparator(fields[i], instance);
            sortFields.add(comparator);
        }
        ComparatorChain multiSort = new ComparatorChain(sortFields);
        Collections.sort(result, multiSort);
    }

    public static String getPercent(Long duration, Long total) {
        return decimalFormat.format(duration.doubleValue() / total.doubleValue());
    }

    /**
     * 对select count hql的结果进行转换，得到count值
     *
     * @param list .
     * @return .
     */
    public static Integer getCount(List list) {
        if (list != null && list.size() > 0) {
            return (Integer) list.get(0);
        }
        return Integer.valueOf(0);
    }

    /**
     * selectQuery like 'select count(distinct field)'
     *
     * @param queryTranslate .
     * @param selectQuery    .
     * @return
     */
    public static MyQuery getMyQuery(QueryTranslate queryTranslate, String selectQuery) {
        String queryString = queryTranslate.getQueryString();
        String hql = queryTranslate.getQueryString();
        int index = queryString.indexOf("from");
        if (index != -1) {
            hql = selectQuery + " " + queryString.substring(index, queryString.length());
        }
        MyQuery myQuery = new MyQuery();
        myQuery.setQueryString(hql);
        myQuery.getParalist().addAll(queryTranslate.getParalist());
        return myQuery;
    }
}
