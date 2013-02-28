package org.king.framework.dao;

public class MyQuery {
    private static final int DEFAULT_PAGE_SIZE = 10;
    private ParaList paralist = new ParaList();
    private String groupby;
    private String orderby;
    private String queryString;
    private boolean isCache = false;

    private boolean isOffset = false;

    private int pageSize = 10;
    private int pageStartNo;

    public String getGroupby() {
        return groupby;
    }

    public void setGroupby(String groupby) {
        this.groupby = groupby;
    }

    public boolean isCache() {
        return isCache;
    }

    public void setCache(boolean isCache) {
        this.isCache = isCache;
    }

    public String getOrderby() {
        return orderby;
    }

    public void setOrderby(String orderby) {
        this.orderby = orderby;
    }

    public int getPageSize() {
        return pageSize;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public int getPageStartNo() {
        return pageStartNo;
    }

    public void setPageStartNo(int pageStartNo) {
        this.pageStartNo = pageStartNo;
    }

    public ParaList getParalist() {
        return paralist;
    }

    public void setParalist(ParaList paralist) {
        this.paralist = paralist;
    }

    public String getQueryString() {
        return queryString;
    }

    public void setQueryString(String queryString) {
        this.queryString = queryString;
    }

    public void setOffset(boolean isOffset) {
        this.isOffset = isOffset;
    }

    public final void addPara(Object obj, int typeNo) {
        paralist.addPara(new Para(obj, typeNo));
    }

    public boolean isOffset() {
        return isOffset;
    }
}