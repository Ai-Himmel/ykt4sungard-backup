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
	 * ������ݼ�
	 *
	 * @return
	 */
	public Object getResult() {
		return data;
	}

	/**
	 * ���������������
	 *
	 * @return
	 */
	public long getTotalCount() {
		return this.totalCount;
	}

	/**
	 * ���ҳ ָ���Ĵ�С
	 *
	 * @return
	 */
	public int getPageSize() {
		return this.pageSize;
	}

	/**
	 * �����ҳ������
	 *
	 * @return lang������
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
	 * ��õ�ǰҳ��
	 *
	 * @return
	 */
	public long getCurrentPageNo() {
		return start / pageSize + 1;
	}

	/**
	 * �ж��Ƿ�����һҳ
	 *
	 * @return
	 */
	public boolean hasNextPage() {
		return this.getCurrentPageNo() < this.getTotalPageCount();
	}

	/**
	 * �ж��Ƿ�����һҳ
	 *
	 * @return
	 */
	public boolean hasPreviousPage() {
		return this.getCurrentPageNo() > 1;
	}

	/**
	 * ��ÿ�ʼҳ��
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
