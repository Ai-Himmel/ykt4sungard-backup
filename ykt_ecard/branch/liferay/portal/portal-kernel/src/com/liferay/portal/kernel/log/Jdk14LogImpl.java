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

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * <a href="Jdk14LogImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Jdk14LogImpl implements Log {

	public Jdk14LogImpl(Logger log) {
		_log = log;
	}

	public void debug(Object msg) {
		_log.log(Level.FINE, msg.toString());
	}

	public void debug(Throwable t) {
		_log.log(Level.FINE, t.getMessage(), t);
	}

	public void debug(Object msg, Throwable t) {
		_log.log(Level.FINE, msg.toString(), t);
	}

	public void error(Object msg) {
		_log.log(Level.SEVERE, msg.toString());
	}

	public void error(Throwable t) {
		_log.log(Level.SEVERE, t.getMessage(), t);
	}

	public void error(Object msg, Throwable t) {
		_log.log(Level.SEVERE, msg.toString(), t);
	}

	public void fatal(Object msg) {
		_log.log(Level.SEVERE, msg.toString());
	}

	public void fatal(Throwable t) {
		_log.log(Level.SEVERE, t.getMessage(), t);
	}

	public void fatal(Object msg, Throwable t) {
		_log.log(Level.SEVERE, msg.toString(), t);
	}

	public void info(Object msg) {
		_log.log(Level.INFO, msg.toString());
	}

	public void info(Throwable t) {
		_log.log(Level.INFO, t.getMessage(), t);
	}

	public void info(Object msg, Throwable t) {
		_log.log(Level.INFO, msg.toString(), t);
	}

	public boolean isDebugEnabled() {
		return _log.isLoggable(Level.FINE);
	}

	public boolean isErrorEnabled() {
		return _log.isLoggable(Level.SEVERE);
	}

	public boolean isFatalEnabled() {
		return _log.isLoggable(Level.SEVERE);
	}

	public boolean isInfoEnabled() {
		return _log.isLoggable(Level.INFO);
	}

	public boolean isTraceEnabled() {
		return _log.isLoggable(Level.FINEST);
	}

	public boolean isWarnEnabled() {
		return _log.isLoggable(Level.WARNING);
	}

	public void trace(Object msg) {
		_log.log(Level.FINEST, msg.toString());
	}

	public void trace(Throwable t) {
		_log.log(Level.FINEST, t.getMessage(), t);
	}

	public void trace(Object msg, Throwable t) {
		_log.log(Level.FINEST, msg.toString(), t);
	}

	public void warn(Object msg) {
		_log.log(Level.WARNING, msg.toString());
	}

	public void warn(Throwable t) {
		_log.log(Level.WARNING, t.getMessage(), t);
	}

	public void warn(Object msg, Throwable t) {
		_log.log(Level.WARNING, msg.toString(), t);
	}

	private Logger _log;

}