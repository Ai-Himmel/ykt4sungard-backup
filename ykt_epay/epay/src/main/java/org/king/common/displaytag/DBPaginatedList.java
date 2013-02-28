package org.king.common.displaytag;

import org.displaytag.pagination.PaginatedList;
import org.displaytag.properties.SortOrderEnum;

import java.util.ArrayList;
import java.util.List;

/**
 * 实现displaytag的数据库的分页接口.
 * User: Yiming.You
 * Date: 2010-7-4
 */
public class DBPaginatedList implements PaginatedList {

    private List result = null;

    private int totalCount = 0;

    private int pageNo = 1;

    private int pageSize = 50;

    private SortOrderEnum sortDirection = SortOrderEnum.ASCENDING;

    private String sortCriterion;

    private boolean autoCount = false;

    /**
     * 使用了哪种导出功能，若正常分页，则该值为null
     */
    private String exportValue;

    /**
     * * 获取分页的结果集
     */
    public List getList() {
        if (result == null) {
            return new ArrayList();
        }
        return result;
    }

    /**
     * * 获取当前页数
     */
    public int getPageNumber() {
        return pageNo;
    }

    /**
     * * 获取每页的个数
     */
    public int getObjectsPerPage() {
        return pageSize;
    }

    /**
     * * 获取整个结果集的个数
     */
    public int getFullListSize() {
        return totalCount;
    }

    /**
     * * 获取排序字段
     */
    public String getSortCriterion() {
        return sortCriterion;
    }

    /**
     * * 升序还是降序
     */
    public SortOrderEnum getSortDirection() {
        return sortDirection;
    }

    /**
     * * 返回一个查询的id
     */
    public String getSearchId() {
        return Integer.toHexString(pageSize * 10000 + pageNo);
    }

    public void setResult(List result) {
        this.result = result;
    }

    public void setTotalCount(int totalCount) {
        this.totalCount = totalCount;
    }

    public void setPageNo(int pageNo) {
        this.pageNo = pageNo;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public void setSortDirection(SortOrderEnum sortDirection) {
        this.sortDirection = sortDirection;
    }

    public void setOrder(String order) {
        if ("desc".equalsIgnoreCase(order)) {
            this.sortDirection = SortOrderEnum.DESCENDING;
        } else if ("asc".equalsIgnoreCase(order)) {
            this.sortDirection = SortOrderEnum.ASCENDING;
        }
    }

    public String getOrder() {
        String order = null;
        if (SortOrderEnum.ASCENDING.equals(sortDirection)) {
            order = "asc";
        } else if (SortOrderEnum.DESCENDING.equals(sortDirection)) {
            order = "desc";
        }
        return order;
    }

    public String getOppositeOrder() {
        String order = null;
        if (SortOrderEnum.ASCENDING.equals(sortDirection)) {
            order = "desc";
        } else if (SortOrderEnum.DESCENDING.equals(sortDirection)) {
            order = "asc";
        }
        return order;
    }

    public void setSortCriterion(String sortCriterion) {
        this.sortCriterion = sortCriterion;
    }

    public boolean isAutoCount() {
        return autoCount;
    }

    public void setAutoCount(boolean autoCount) {
        this.autoCount = autoCount;
    }

    public String getExportValue() {
        return exportValue;
    }

    public void setExportValue(String exportValue) {
        this.exportValue = exportValue;
    }
}
