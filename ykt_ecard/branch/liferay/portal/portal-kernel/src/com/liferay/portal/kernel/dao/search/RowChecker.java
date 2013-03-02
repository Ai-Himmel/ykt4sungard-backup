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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import javax.portlet.RenderResponse;

/**
 * <a href="RowChecker.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RowChecker {

	public static final String ALIGN = "left";

	public static final String VALIGN = "middle";

	public static final int COLSPAN = 1;

	public static final String FORM_NAME = "fm";

	public static final String ALL_ROW_IDS = "allRowIds";

	public static final String ROW_IDS = "rowIds";

	public RowChecker(RenderResponse res) {
		this(res, ALIGN, VALIGN, COLSPAN, FORM_NAME, ALL_ROW_IDS, ROW_IDS);
	}

	public RowChecker(
		RenderResponse res, String align, String valign, String formName,
		String allRowsId, String rowId) {

		this(res, align, valign, COLSPAN, formName, allRowsId, rowId);
	}

	public RowChecker(
		RenderResponse res, String align, String valign, int colspan,
		String formName, String allRowsId, String rowId) {

		_align = align;
		_valign = valign;
		_colspan = colspan;
		_formName = res.getNamespace() + formName;

		if (Validator.isNotNull(allRowsId)) {
			_allRowsId = res.getNamespace() + allRowsId;
		}

		_rowId = res.getNamespace() + rowId;
	}

	public String getAlign() {
		return _align;
	}

	public String getValign() {
		return _valign;
	}

	public int getColspan() {
		return _colspan;
	}

	public String getFormName() {
		return _formName;
	}

	public String getAllRowsId() {
		return _allRowsId;
	}

	public String getRowId() {
		return _rowId;
	}

	public String getAllRowsCheckBox() {
		if (Validator.isNull(_allRowsId)) {
			return StringPool.BLANK;
		}
		else {
			StringMaker sm = new StringMaker();

			sm.append("<input name=\"");
			sm.append(_allRowsId);
			sm.append("\" type=\"checkbox\" ");
			sm.append("onClick=\"Liferay.Util.checkAll(");
			sm.append(_formName);
			sm.append(", '");
			sm.append(_rowId);
			sm.append("', this");
			sm.append(");\">");

			return sm.toString();
		}
	}

	public String getRowCheckBox(boolean checked, String primaryKey) {
		StringMaker sm = new StringMaker();

		sm.append("<input ");

		if (checked) {
			sm.append("checked ");
		}

		sm.append("name=\"");
		sm.append(_rowId);
		sm.append("\" type=\"checkbox\" value=\"");
		sm.append(primaryKey);
		sm.append("\" ");

		if (Validator.isNotNull(_allRowsId)) {
			sm.append("onClick=\"Liferay.Util.checkAllBox(");
			sm.append(_formName);
			sm.append(", '");
			sm.append(_rowId);
			sm.append("', ");
			sm.append(_allRowsId);
			sm.append(");\"");
		}

		sm.append(">");

		return sm.toString();
	}

	public boolean isChecked(Object obj) {
		return false;
	}

	private String _align;
	private String _valign;
	private int _colspan;
	private String _formName;
	private String _allRowsId;
	private String _rowId;

}