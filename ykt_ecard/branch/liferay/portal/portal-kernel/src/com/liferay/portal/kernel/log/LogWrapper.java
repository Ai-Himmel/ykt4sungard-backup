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

/**
 * <a href="LogWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LogWrapper implements Log {

	public LogWrapper(Log log) {
		_log = log;
	}

	public void setLog(Log log) {
		_log = log;
	}

	public void debug(Object msg) {
		_log.debug(msg);
	}

	public void debug(Throwable t) {
		_log.debug(t);
	}

	public void debug(Object msg, Throwable t) {
		_log.debug(msg, t);
	}

	public void error(Object msg) {
		_log.error(msg);
	}

	public void error(Throwable t) {
		_log.error(t);
	}

	public void error(Object msg, Throwable t) {
		_log.error(msg, t);
	}

	public void fatal(Object msg) {
		_log.fatal(msg);
	}

	public void fatal(Throwable t) {
		_log.fatal(t);
	}

	public void fatal(Object msg, Throwable t) {
		_log.fatal(msg, t);
	}

	public void info(Object msg) {
		_log.info(msg);
	}

	public void info(Throwable t) {
		_log.info(t);
	}

	public void info(Object msg, Throwable t) {
		_log.info(msg, t);
	}

	public boolean isDebugEnabled() {
		return _log.isDebugEnabled();
	}

	public boolean isErrorEnabled() {
		return _log.isErrorEnabled();
	}

	public boolean isFatalEnabled() {
		return _log.isFatalEnabled();
	}

	public boolean isInfoEnabled() {
		return _log.isInfoEnabled();
	}

	public boolean isTraceEnabled() {
		return _log.isTraceEnabled();
	}

	public boolean isWarnEnabled() {
		return _log.isWarnEnabled();
	}

	public void trace(Object msg) {
		_log.trace(msg);
	}

	public void trace(Throwable t) {
		_log.trace(t);
	}

	public void trace(Object msg, Throwable t) {
		_log.trace(msg, t);
	}

	public void warn(Object msg) {
		_log.warn(msg);
	}

	public void warn(Throwable t) {
		_log.warn(t);
	}

	public void warn(Object msg, Throwable t) {
		_log.warn(msg, t);
	}

	private Log _log;

}