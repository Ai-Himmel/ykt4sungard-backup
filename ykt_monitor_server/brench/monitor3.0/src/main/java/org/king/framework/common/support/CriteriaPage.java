package org.king.framework.common.support;

import java.util.List;
import org.hibernate.Criteria;
import org.hibernate.ScrollMode;
import org.hibernate.ScrollableResults;

public class CriteriaPage extends Page
{
  public static final CriteriaPage EMPTY_PAGE = new CriteriaPage();

  private CriteriaPage()
  {
  }

  public CriteriaPage(int start, int avaCount, int totalSize, int pageSize, Object data)
  {
    super(start, avaCount, totalSize, pageSize, data);
  }

  public static CriteriaPage getHibernatePageInstance(Criteria criteria, int pageNo, int pageSize)
  {
    return getHibernatePageInstance(criteria, pageNo, pageSize, true);
  }

  public static CriteriaPage getHibernatePageInstance(Criteria criteria, int pageNo, int pageSize, boolean isScroll)
  {
    if (isScroll) {
      return getScrollPageInstanceWithTotalByScroll(criteria, pageNo, pageSize);
    }

    return getScrollPageInstanceWithTotalByList(criteria, pageNo, pageSize);
  }

  protected static CriteriaPage getScrollPageInstanceWithTotalByScroll(Criteria criteria, int pageNo, int pageSize)
  {
    ScrollableResults scrollableResults = criteria.scroll(ScrollMode.SCROLL_SENSITIVE);

    scrollableResults.last();
    int totalCount = scrollableResults.getRowNumber();
    return fillElements(criteria, totalCount + 1, pageNo, pageSize);
  }

  protected static CriteriaPage getScrollPageInstanceWithTotalByList(Criteria criteria, int pageNo, int pageSize)
  {
    criteria.scroll(ScrollMode.FORWARD_ONLY);
    int totalCount = calculateTotalElementsByList(criteria);
    return fillElements(criteria, totalCount, pageNo, pageSize);
  }

  private static CriteriaPage fillElements(Criteria criteria, int totalCount, int pageNo, int pageSize)
  {
    if (totalCount < 1)
      return EMPTY_PAGE;
    if (pageNo < 1)
      pageNo = 1;
    int startIndex = getStartOfPage(pageNo, pageSize);

    List list = criteria.setFirstResult(startIndex - 1).setMaxResults(pageSize).list();

    int avaCount = list == null ? 0 : list.size();

    return new CriteriaPage(startIndex, avaCount, totalCount, pageSize, list);
  }

  private static int calculateTotalElementsByList(Criteria criteria)
  {
    return criteria.list().size();
  }
}