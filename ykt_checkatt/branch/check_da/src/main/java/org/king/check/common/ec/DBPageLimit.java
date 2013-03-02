package org.king.check.common.ec;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.extremecomponents.table.limit.Limit;

/**
 * 实现ec的数据库分页.
 * 
 * User: Yiming.You
 * Date: 2010-09-17
 */
public class DBPageLimit implements Serializable {

	private int pageSize = 50;

	private int pageNo = 1;

	private transient int totalRows = 0;

	private transient int pageCount = 0;

	private Map orderMap = null;

	private Limit limit;
	
	private List result = null;
	
	private boolean isExported = false;
	
	/**
	 * whether change the row into a map
	 */
	private boolean isMap = false;

	public DBPageLimit() {
	}

	public DBPageLimit(int pageNo) {
		this.pageNo = pageNo;
	}

	public Map getOrderMap() {
		return orderMap;
	}

	public int getPageCount() {
		return pageCount;
	}

	public void setPageCount(int pageCount) {
		this.pageCount = pageCount;
	}

	public int getPageNo() {
		return pageNo;
	}

	public void setPageNo(int pageNo) {
		this.pageNo = pageNo;
	}

	public int getPageSize() {
		return pageSize;
	}

	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}

	public int getTotalRows() {
		return totalRows;
	}

	public void setTotalRows(int totalRows) {
		this.totalRows = totalRows;
		if (limit != null) {
			limit.setRowAttributes(totalRows, pageSize);
		}
	}

	public int getRowStart() {
		return (pageNo - 1) * pageSize;

	}

	public Limit getLimit() {
		return limit;
	}

	public void setLimit(Limit limit) {
		this.limit = limit;
		this.pageNo = limit.getPage();
	}

	public boolean isExported() {
		return isExported;
	}

	public void setExported(boolean isExported) {
		this.isExported = isExported;
	}

	public void setOrderMap(Map orderMap) {
		this.orderMap = orderMap;
	}

	public List getResult() {
		return result;
	}

	public void setResult(List result) {
		this.result = result;
	}

	public boolean isMap() {
		return isMap;
	}

	public void setMap(boolean isMap) {
		this.isMap = isMap;
	}
}
