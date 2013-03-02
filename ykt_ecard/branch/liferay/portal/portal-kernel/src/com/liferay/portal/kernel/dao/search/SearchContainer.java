/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.kernel.dao.search;

import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.ParamUtil;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;

/**
 * <a href="SearchContainer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SearchContainer {

	public static final String DEFAULT_CUR_PARAM = "cur";

	public static final int DEFAULT_CUR_VALUE = 1;

	public static final int DEFAULT_DELTA = 20;

	public SearchContainer() {
	}

	public SearchContainer(
		RenderRequest req, DisplayTerms displayTerms, DisplayTerms searchTerms,
		String curParam, int delta, PortletURL iteratorURL, List headerNames,
		String emptyResultsMessage) {

		_displayTerms = displayTerms;
		_searchTerms = searchTerms;

		_curParam = curParam;
		_curValue = ParamUtil.get(req, _curParam, 1);
		setDelta(delta);

		_iteratorURL = iteratorURL;

		_iteratorURL.setParameter(
			DisplayTerms.KEYWORDS,
			ParamUtil.getString(req, DisplayTerms.KEYWORDS));
		_iteratorURL.setParameter(
			DisplayTerms.ADVANCED_SEARCH,
			String.valueOf(
				ParamUtil.getBoolean(req, DisplayTerms.ADVANCED_SEARCH)));
		_iteratorURL.setParameter(
			DisplayTerms.AND_OPERATOR,
			String.valueOf(
				ParamUtil.getBoolean(req, DisplayTerms.AND_OPERATOR, true)));

		if (headerNames != null) {
			_headerNames = new ArrayList(headerNames.size());

			_headerNames.addAll(headerNames);
		}

		_emptyResultsMessage = emptyResultsMessage;
	}

	public DisplayTerms getDisplayTerms() {
		return _displayTerms;
	}

	public DisplayTerms getSearchTerms() {
		return _searchTerms;
	}

	public String getCurParam() {
		return _curParam;
	}

	public int getCurValue() {
		return _curValue;
	}

	public int getDelta() {
		return _delta;
	}

	public void setDelta(int delta) {
		if (delta <= 0) {
			_delta = DEFAULT_DELTA;
		}
		else {
			_delta = delta;
		}

		_calculateStartAndEnd();
	}

	public int getStart() {
		return _start;
	}

	public int getEnd() {
		return _end;
	}

	public int getResultEnd() {
		return _resultEnd;
	}

	public int getTotal() {
		return _total;
	}

	public void setTotal(int total) {
		_total = total;

		if (((_curValue - 1) * _delta) > _total) {
			_curValue = DEFAULT_CUR_VALUE;
		}

		_calculateStartAndEnd();
	}

	public List getResults() {
		return _results;
	}

	public void setResults(List results) {
		_results = results;
	}

	public List getResultRows() {
		return _resultRows;
	}

	public PortletURL getIteratorURL() {
		return _iteratorURL;
	}

	public void setIteratorURL(PortletURL iteratorURL) {
		_iteratorURL = iteratorURL;
	}

	public List getHeaderNames() {
		return _headerNames;
	}

	public void setHeaderNames(List headerNames) {
		_headerNames = headerNames;
	}

	public Map getOrderableHeaders() {
		return _orderableHeaders;
	}

	public void setOrderableHeaders(Map orderableHeaders) {
		_orderableHeaders = orderableHeaders;
	}

	public String getOrderByCol() {
		return _orderByCol;
	}

	public void setOrderByCol(String orderByCol) {
		_orderByCol = orderByCol;
	}

	public String getOrderByType() {
		return _orderByType;
	}

	public void setOrderByType(String orderByType) {
		_orderByType = orderByType;
	}

	public OrderByComparator getOrderByComparator() {
		return _orderByComparator;
	}

	public void setOrderByComparator(OrderByComparator orderByComparator) {
		_orderByComparator = orderByComparator;
	}

	public String getEmptyResultsMessage() {
		return _emptyResultsMessage;
	}

	public void setEmptyResultsMessage(String emptyResultsMessage) {
		_emptyResultsMessage = emptyResultsMessage;
	}

	public RowChecker getRowChecker() {
		return _rowChecker;
	}

	public void setRowChecker(RowChecker rowChecker) {
		_rowChecker = rowChecker;
	}

	public boolean isHover() {
		return _hover;
	}

	public void setHover(boolean hover) {
		_hover = hover;
	}

	private void _calculateStartAndEnd() {
		_start = (_curValue - 1) * _delta;
		_end = _start + _delta;

		_resultEnd = _end;

		if (_resultEnd > _total) {
			_resultEnd = _total;
		}
	}

	private DisplayTerms _displayTerms;
	private DisplayTerms _searchTerms;
	private String _curParam = DEFAULT_CUR_PARAM;
	private int _curValue;
	private int _delta = DEFAULT_DELTA;
	private int _start;
	private int _end;
	private int _resultEnd;
	private int _total;
	private List _results = new ArrayList();
	private List _resultRows = new ArrayList();
	private PortletURL _iteratorURL;
	private List _headerNames;
	private Map _orderableHeaders;
	private String _orderByCol;
	private String _orderByType;
	private OrderByComparator _orderByComparator;
	private String _emptyResultsMessage;
	private RowChecker _rowChecker;
	private boolean _hover = true;

}