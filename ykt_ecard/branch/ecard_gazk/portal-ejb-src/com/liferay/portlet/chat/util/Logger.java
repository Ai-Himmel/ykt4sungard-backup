/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.chat.util;

import com.liferay.util.StringUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="Logger.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class Logger extends com.lyrisoft.util.io.Logger {

	public static final int LOG_LEVEL_TRACE = 1;

	public static final int LOG_LEVEL_DEBUG = 2;

	public static final int LOG_LEVEL_INFO = 3;

	public static final int LOG_LEVEL_WARN = 4;

	public static final int LOG_LEVEL_ERROR = 5;

	public static final int LOG_LEVEL_FATAL = 6;

	public Logger(int level) {
		super(System.out);

		_level = level;
	}

	public void run() {
	}

	public void log(String s) {
		switch (_level) {
			case LOG_LEVEL_TRACE:
				_log.trace(s);
				break;
			case LOG_LEVEL_DEBUG:
				_log.debug(s);
			case LOG_LEVEL_INFO:
				_log.info(s);
				break;
			case LOG_LEVEL_WARN:
				_log.warn(s);
				break;
			case LOG_LEVEL_ERROR:
				_log.error(s);
				break;
			case LOG_LEVEL_FATAL:
				_log.fatal(s);
		}
	}

	public void log(Exception e) {
		String stackTrace = StringUtil.stackTrace(e);

		log(stackTrace);
	}

	private static final Log _log = LogFactory.getLog(ChatServer.class);

	private int _level;

}