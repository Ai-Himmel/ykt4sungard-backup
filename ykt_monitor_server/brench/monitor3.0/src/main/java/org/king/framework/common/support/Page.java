package org.king.framework.common.support;

import java.io.Serializable;
import org.king.framework.Constants;

public class Page
  implements Serializable
{
  private int start;
  private int pageSize = Constants.DEFAULT_PAGE_SIZE;
  private int currentPageSize;
  private int currentPageNo;
  private Object data;
  private int totalSize;
  private int totalPageCount;

  public Page()
  {
    this(0, 0, 0, Constants.DEFAULT_PAGE_SIZE, new Object());
  }

  public Page(int start, int currentPageSize, int totalSize, int pageSize, Object data)
  {
    this.currentPageSize = currentPageSize;
    this.pageSize = pageSize;
    this.start = start;
    this.totalSize = totalSize;
    this.data = data;

    currentPageNo = ((start - 1) / pageSize + 1);
    totalPageCount = ((totalSize + pageSize - 1) / pageSize);
    if ((totalSize == 0) && (currentPageSize == 0)) {
      currentPageNo = 1;
      totalPageCount = 1;
    }
  }

  public int getTotalSize()
  {
    return totalSize;
  }

  public int getTotalPageCount()
  {
    return totalPageCount;
  }

  public int getPageSize()
  {
    return pageSize;
  }

  public Object getResult()
  {
    return data;
  }

  public int getCurrentPageNo()
  {
    return currentPageNo;
  }

  public int getSize()
  {
    return currentPageSize;
  }

  public boolean hasNextPage()
  {
    return getCurrentPageNo() < getTotalPageCount();
  }

  public boolean hasPreviousPage()
  {
    return getCurrentPageNo() > 1;
  }

  protected int getStartOfPreviousPage()
  {
    return Math.max(start - pageSize, 1);
  }

  protected int getStartOfNextPage()
  {
    return start + currentPageSize;
  }

  protected static int getStartOfPage(int pageNo)
  {
    return getStartOfPage(pageNo, Constants.DEFAULT_PAGE_SIZE);
  }

  protected static int getStartOfPage(int pageNo, int pageSize)
  {
    int startIndex = (pageNo - 1) * pageSize + 1;
    if (startIndex < 1) startIndex = 1;
    return startIndex;
  }
}