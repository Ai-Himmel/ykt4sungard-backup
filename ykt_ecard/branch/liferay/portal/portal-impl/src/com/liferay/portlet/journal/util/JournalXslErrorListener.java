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

package com.liferay.portlet.journal.util;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;

import java.util.Locale;

import javax.xml.transform.ErrorListener;
import javax.xml.transform.SourceLocator;
import javax.xml.transform.TransformerException;

import org.apache.xml.utils.SAXSourceLocator;
import org.apache.xml.utils.WrappedRuntimeException;

import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 * <a href="JournalXslErrorListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class JournalXslErrorListener implements ErrorListener {

	public JournalXslErrorListener(long companyId, Locale locale) {
		_companyId = companyId;
		_locale = locale;
	}

	public void error(TransformerException exception)
		throws TransformerException {

		setLocation(exception);

		throw exception;
	}

	public void fatalError(TransformerException exception)
		throws TransformerException {

		setLocation(exception);

		throw exception;
	}

	public void warning(TransformerException exception)
		throws TransformerException {

		setLocation(exception);

		throw exception;
	}

	public void setLocation(Throwable exception) {
		SourceLocator locator = null;
		Throwable cause = exception;
		Throwable rootCause = null;

		while (cause != null) {
			if (cause instanceof SAXParseException) {
				locator = new SAXSourceLocator((SAXParseException)cause);
				rootCause = cause;
			}
			else if (cause instanceof TransformerException) {
				SourceLocator causeLocator =
					((TransformerException)cause).getLocator();

				if (causeLocator != null) {
					locator = causeLocator;
					rootCause = cause;
				}
			}

			if (cause instanceof TransformerException) {
				cause = ((TransformerException)cause).getCause();
			}
			else if (cause instanceof WrappedRuntimeException) {
				cause = ((WrappedRuntimeException)cause).getException();
			}
			else if (cause instanceof SAXException) {
				cause = ((SAXException)cause).getException();
			}
			else {
				cause = null;
			}
		}

		_message = rootCause.getMessage();

		if (locator != null) {
			StringMaker sm = new StringMaker();

			sm.append(LanguageUtil.get(_companyId, _locale, "line"));
			sm.append(" #");
			sm.append(locator.getLineNumber());
			sm.append("; ");
			sm.append(LanguageUtil.get(_companyId, _locale, "column"));
			sm.append(" #");
			sm.append(locator.getColumnNumber());
			sm.append("; ");

			_location = sm.toString();
		}
		else {
			_location = StringPool.BLANK;
		}
	}

	public String getLocation() {
		return _location;
	}

	public String getMessage() {
		return _message;
	}

	public String getMessageAndLocation() {
		return _message + " " + _location;
	}

	private long _companyId;
	private Locale _locale;
	private String _location;
	private String _message;

}