package org.king.framework.common.support;

import org.hibernate.Query;
import org.hibernate.ScrollMode;
import org.hibernate.ScrollableResults;

import java.util.List;

public class HqlPage extends Page {
    public static final HqlPage EMPTY_PAGE = new HqlPage();

    private HqlPage() {
    }

    public HqlPage(int start, int avaCount, int totalSize, int pageSize, Object data) {
        super(start, avaCount, totalSize, pageSize, data);
    }

    public static HqlPage getHibernatePageInstance(Query query, int pageNo, int pageSize) {
        return getHibernatePageInstance(query, pageNo, pageSize, true);
    }

    public static HqlPage getHibernatePageInstance(Query query, int pageNo, int pageSize, boolean isScroll) {
        if (isScroll) {
            return getScrollPageInstanceWithTotalByScroll(query, pageNo, pageSize);
        }
        return getScrollPageInstanceWithTotalByList(query, pageNo, pageSize);
    }

    protected static HqlPage getScrollPageInstanceWithTotalByScroll(Query query, int pageNo, int pageSize) {
        ScrollableResults scrollableResults = query.scroll(ScrollMode.SCROLL_SENSITIVE);
        scrollableResults.last();
        int totalCount = scrollableResults.getRowNumber();
        return fillElements(query, totalCount + 1, pageNo, pageSize);
    }

    protected static HqlPage getScrollPageInstanceWithTotalByList(Query query, int pageNo, int pageSize) {
        query.scroll(ScrollMode.FORWARD_ONLY);
        int totalCount = calculateTotalElementsByList(query);
        return fillElements(query, totalCount, pageNo, pageSize);
    }

    private static HqlPage fillElements(Query q, int totalCount, int pageNo, int pageSize) {
        if (totalCount < 1) {
            return EMPTY_PAGE;
        }
        if (pageNo < 1) pageNo = 1;
        int startIndex = getStartOfPage(pageNo, pageSize);
        List list = q.setFirstResult(startIndex - 1).setMaxResults(pageSize).list();

        int avaCount = list == null ? 0 : list.size();

        return new HqlPage(startIndex, avaCount, totalCount, pageSize, list);
    }

    private static int calculateTotalElementsByList(Query query) {
        return query.list().size();
    }
}