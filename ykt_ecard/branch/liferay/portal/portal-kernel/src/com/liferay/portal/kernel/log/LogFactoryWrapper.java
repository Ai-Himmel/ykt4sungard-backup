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

package com.liferay.portal.kernel.log;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Vector;

/**
 * <a href="LogFactoryWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LogFactoryWrapper implements LogFactory {

	public LogFactoryWrapper(LogFactory logFactory) {
		_logFactory = logFactory;
	}

	public void setLogFactory(LogFactory logFactory) {
		_logFactory = logFactory;

		Iterator itr1 = _logs.entrySet().iterator();

		while (itr1.hasNext()) {
			Map.Entry entry = (Map.Entry)itr1.next();

			String name = (String)entry.getKey();
			List list = (List)entry.getValue();

			Iterator itr2 = list.iterator();

			while (itr2.hasNext()) {
				LogWrapper logWrapper = (LogWrapper)itr2.next();

				logWrapper.setLog(_logFactory.getLog(name));
			}
		}
	}

	public Log getLog(Class c) {
		return getLog(c.getName());
	}

	public Log getLog(String name) {
		List list = (List)_logs.get(name);

		if (list == null) {
			list = new Vector();

			_logs.put(name, list);
		}

		Log log = new LogWrapper(_logFactory.getLog(name));

		list.add(log);

		return log;
	}

	private LogFactory _logFactory;
	private Map _logs = new Hashtable();

}