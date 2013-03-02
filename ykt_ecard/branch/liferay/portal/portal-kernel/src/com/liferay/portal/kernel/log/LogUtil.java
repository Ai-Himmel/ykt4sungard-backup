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

import com.liferay.portal.kernel.util.StackTraceUtil;

import java.io.PrintWriter;
import java.io.StringWriter;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import javax.servlet.ServletException;
import javax.servlet.jsp.JspException;

/**
 * <a href="LogUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LogUtil {

	public static final int STACK_TRACE_LENGTH = 20;

	public static final boolean REMOVE_UNKNOWN_SOURCE = true;

	public static void debug(Log log, Properties props) {
		if (log.isDebugEnabled()) {
			StringWriter sw = new StringWriter();

			props.list(new PrintWriter(sw));

			log.debug(sw.getBuffer().toString());
		}
	}

	public static void log(Log log, Throwable t) {
		if (t instanceof JspException) {
			log(log, (JspException)t);
		}
		else if (t instanceof ServletException) {
			log(log, (ServletException)t);
		}
		else {
			Throwable cause = t.getCause();

			if (cause != null) {
				log(log, cause);
			}
			else {
				_log(log, t);
			}
		}
	}

	public static void log(Log log, JspException jspe) {
		Throwable cause = jspe.getRootCause();

		if (cause == null) {
			cause = jspe;
		}

		if ((cause != jspe) && (cause instanceof JspException)) {
			log(log, (JspException)cause);
		}
		else if (cause instanceof ServletException) {
			log(log, (ServletException)cause);
		}
		else {
			_log(log, cause);
		}
	}

	public static void log(Log log, ServletException se) {
		Throwable cause = se.getRootCause();

		if (cause == null) {
			cause = se;
		}

		if (cause instanceof JspException) {
			log(log, (JspException)cause);
		}
		else if ((cause != se) && (cause instanceof ServletException)) {
			log(log, (ServletException)cause);
		}
		else {
			_log(log, cause);
		}
	}

	private static void _log(Log log, Throwable cause) {
		StackTraceElement[] steArray =
			(StackTraceElement[])cause.getStackTrace();

		// Make the stack trace more readable by limiting the number of
		// elements.

		if (steArray.length > STACK_TRACE_LENGTH) {
			int count = 0;

			List steList = new ArrayList();

			for (int i = 0; i < steArray.length; i++) {
				StackTraceElement ste = (StackTraceElement)steArray[i];

				// Make the stack trace more readable by removing elements that
				// refer to classes with no packages, or starts with a $, or are
				// Spring classes, or are standard reflection classes.

				String className = ste.getClassName();

				boolean addElement = true;

				if (REMOVE_UNKNOWN_SOURCE && (ste.getLineNumber() < 0)) {
					addElement = false;
				}

				if (className.startsWith("$") ||
					className.startsWith("java.lang.reflect.") ||
					className.startsWith("org.springframework.") ||
					className.startsWith("sun.reflect.")) {

					addElement = false;
				}

				if (addElement) {
					steList.add(ste);

					count++;
				}

				if (count >= STACK_TRACE_LENGTH) {
					break;
				}
			}

			steArray = (StackTraceElement[])steList.toArray(
				new StackTraceElement[0]);

			cause.setStackTrace(steArray);
		}

		log.error(StackTraceUtil.getStackTrace(cause));
	}

}