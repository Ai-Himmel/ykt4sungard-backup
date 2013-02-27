package org.king.common.displaytag;

import org.displaytag.pagination.PaginatedList;
import org.displaytag.properties.SortOrderEnum;

import java.util.ArrayList;
import java.util.List;

/**
 * ʵ��displaytag�����ݿ�ķ�ҳ�ӿ�.
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
     * ʹ�������ֵ������ܣ���������ҳ�����ֵΪnull
     */
    private String exportValue;

    /**
     * * ��ȡ��ҳ�Ľ����
     */
    public List getList() {
        if (result == null) {
            return new ArrayList();
        }
        return result;
    }

    /**
     * * ��ȡ��ǰҳ��
     */
    public int getPageNumber() {
        return pageNo;
    }

    /**
     * * ��ȡÿҳ�ĸ���
     */
    public int getObjectsPerPage() {
        return pageSize;
    }

    /**
     * * ��ȡ����������ĸ���
     */
    public int getFullListSize() {
        return totalCount;
    }

    /**
     * * ��ȡ�����ֶ�
     */
    public String getSortCriterion() {
        return sortCriterion;
    }

    /**
     * * �����ǽ���
     */
    public SortOrderEnum getSortDirection() {
        return sortDirection;
    }

    /**
     * * ����һ����ѯ��id
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

    public String getOppositeOrder(){
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
