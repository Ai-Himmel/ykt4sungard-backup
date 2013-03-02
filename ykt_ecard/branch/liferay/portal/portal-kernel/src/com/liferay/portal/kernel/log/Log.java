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
 * <a href="Log.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface Log {

	public void debug(Object msg);

	public void debug(Throwable t);

	public void debug(Object msg, Throwable t);

	public void error(Object msg);

	public void error(Throwable t);

	public void error(Object msg, Throwable t);

	public void fatal(Object msg);

	public void fatal(Throwable t);

	public void fatal(Object msg, Throwable t);

	public void info(Object msg);

	public void info(Throwable t);

	public void info(Object msg, Throwable t);

	public boolean isDebugEnabled();

	public boolean isErrorEnabled();

	public boolean isFatalEnabled();

	public boolean isInfoEnabled();

	public boolean isTraceEnabled();

	public boolean isWarnEnabled();

	public void trace(Object msg);

	public void trace(Throwable t);

	public void trace(Object msg, Throwable t);

	public void warn(Object msg);

	public void warn(Throwable t);

	public void warn(Object msg, Throwable t);

}