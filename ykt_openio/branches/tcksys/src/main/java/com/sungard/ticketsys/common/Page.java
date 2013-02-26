package com.sungard.ticketsys.common;

import java.io.Serializable;
import java.util.ArrayList;

import com.sungard.ticketsys.common.Constants;

public class Page implements Serializable {

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	private long start;

	private int pageSize = Constants.DEFAULT_PAGE_SIZE;

	private Object data;

	private long totalCount;

	public Page(long start, long totalCount, int pageSize, Object data) {
		this.data = data;
		this.start = start;
		this.totalCount = totalCount;
		this.pageSize = pageSize;
	}

	@SuppressWarnings("unchecked")
	public Page() {
		this(0, 0, Constants.DEFAULT_PAGE_SIZE, new ArrayList());
	}

	/**
	 * 获得数据集
	 *
	 * @return
	 */
	public Object getResult() {
		return data;
	}

	/**
	 * 获得所有数据条数
	 *
	 * @return
	 */
	public long getTotalCount() {
		return this.totalCount;
	}

	/**
	 * 获得页 指定的大小
	 *
	 * @return
	 */
	public int getPageSize() {
		return this.pageSize;
	}

	/**
	 * 计算出页码数量
	 *
	 * @return lang型数字
	 */
	public long getTotalPageCount() {
		if (totalCount % pageSize == 0) {
			return totalCount / pageSize;
		}
		else {
			return totalCount / pageSize + 1;
		}
	}

	/**
	 * 获得当前页码
	 *
	 * @return
	 */
	public long getCurrentPageNo() {
		return start / pageSize + 1;
	}

	/**
	 * 判断是否有下一页
	 *
	 * @return
	 */
	public boolean hasNextPage() {
		return this.getCurrentPageNo() < this.getTotalPageCount();
	}

	/**
	 * 判断是否有上一页
	 *
	 * @return
	 */
	public boolean hasPreviousPage() {
		return this.getCurrentPageNo() > 1;
	}

	/**
	 * 获得开始页码
	 *
	 * @return
	 */
	public static int getStartOfPage(int pageNo) {
		return getStartOfPage(pageNo, Constants.DEFAULT_PAGE_SIZE);
	}

	public static int getStartOfPage(int pageNo, int pageSize) {
		return (pageNo - 1) * pageSize;
	}
}
