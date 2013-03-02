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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.ServiceComponent;

import java.io.StringReader;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ServiceComponentImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServiceComponentImpl
	extends ServiceComponentModelImpl implements ServiceComponent {

	public ServiceComponentImpl() {
	}

	public void setData(String data) {
		super.setData(data);

		_dataEl = null;
	}

	public String getTablesSQL() {
		return _getData("tables-sql");
	}

	public String getSequencesSQL() {
		return _getData("sequences-sql");
	}

	public String getIndexesSQL() {
		return _getData("indexes-sql");
	}

	private String _getData(String name) {
		try {
			return _getDataEl().elementText(name);
		}
		catch (Exception e) {
			_log.error(e, e);

			return StringPool.BLANK;
		}
	}

	private Element _getDataEl() throws DocumentException {
		if (_dataEl == null) {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(getData()));

			_dataEl = doc.getRootElement();
		}

		return _dataEl;
	}

	private static Log _log = LogFactory.getLog(ServiceComponentImpl.class);

	private Element _dataEl;

}