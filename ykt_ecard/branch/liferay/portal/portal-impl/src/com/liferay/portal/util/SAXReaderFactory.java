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

package com.liferay.portal.util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.io.SAXReader;

/**
 * <a href="SAXReaderFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SAXReaderFactory {

	public static SAXReader getInstance() {
		return getInstance(true);
	}

	public static SAXReader getInstance(boolean validate) {

		// Crimson cannot do XSD validation. See the following links:
		//
		// http://www.geocities.com/herong_yang/jdk/xsd_validation.html
		// http://www.burnthacker.com/archives/000086.html
		// http://www.theserverside.com/news/thread.tss?thread_id=22525

		SAXReader reader = null;

		try {
			reader = new SAXReader(_SAX_PARSER_IMPL, validate);

			reader.setEntityResolver(new EntityResolver());

			reader.setFeature(_FEATURES_VALIDATION, validate);
			reader.setFeature(_FEATURES_VALIDATION_SCHEMA, validate);
			reader.setFeature(
				_FEATURES_VALIDATION_SCHEMA_FULL_CHECKING, validate);
			reader.setFeature(_FEATURES_DYNAMIC, validate);
		}
		catch (Exception e) {
			_log.warn("XSD validation is diasabled because " + e.getMessage());

			reader = new SAXReader(validate);

			reader.setEntityResolver(new EntityResolver());
		}

		return reader;
	}

	private static final String _SAX_PARSER_IMPL =
		"org.apache.xerces.parsers.SAXParser";

	private static final String _FEATURES_VALIDATION =
		"http://xml.org/sax/features/validation";

	private static final String _FEATURES_VALIDATION_SCHEMA =
		"http://apache.org/xml/features/validation/schema";

	private static final String _FEATURES_VALIDATION_SCHEMA_FULL_CHECKING =
		"http://apache.org/xml/features/validation/schema-full-checking";

	private static final String _FEATURES_DYNAMIC =
		"http://apache.org/xml/features/validation/dynamic";

	private static Log _log = LogFactory.getLog(SAXReaderFactory.class);

}