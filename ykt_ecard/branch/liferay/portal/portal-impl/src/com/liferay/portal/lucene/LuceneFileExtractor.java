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

package com.liferay.portal.lucene;

import com.liferay.portal.kernel.util.CharPool;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PropsValues;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.jackrabbit.extractor.HTMLTextExtractor;
import org.apache.jackrabbit.extractor.MsExcelTextExtractor;
import org.apache.jackrabbit.extractor.MsPowerPointTextExtractor;
import org.apache.jackrabbit.extractor.MsWordTextExtractor;
import org.apache.jackrabbit.extractor.OpenOfficeTextExtractor;
import org.apache.jackrabbit.extractor.PdfTextExtractor;
import org.apache.jackrabbit.extractor.PlainTextExtractor;
import org.apache.jackrabbit.extractor.RTFTextExtractor;
import org.apache.jackrabbit.extractor.TextExtractor;
import org.apache.jackrabbit.extractor.XMLTextExtractor;
import org.apache.lucene.document.Field;

/**
 * <a href="LuceneFileExtractor.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LuceneFileExtractor {

	public Field getFile(String field, InputStream is, String fileExt) {
		String text = null;

		try {
			fileExt = GetterUtil.getString(fileExt).toLowerCase();

			TextExtractor extractor = null;

			String contentType = null;
			String encoding = System.getProperty("encoding");

			if (fileExt.equals(".doc")) {
				extractor = new MsWordTextExtractor();

				contentType = "application/vnd.ms-word";
			}
			else if (fileExt.equals(".htm") || fileExt.equals(".html")) {
				extractor = new HTMLTextExtractor();

				contentType = "text/html";
			}
			else if (fileExt.equals(".odb") || fileExt.equals(".odf") ||
					 fileExt.equals(".odg") || fileExt.equals(".odp") ||
					 fileExt.equals(".ods") || fileExt.equals(".odt")) {

				extractor = new OpenOfficeTextExtractor();

				contentType = "application/vnd.oasis.opendocument.";

				if (fileExt.equals(".odb")) {
					contentType += "database";
				}
				else if (fileExt.equals(".odf")) {
					contentType += "formula";
				}
				else if (fileExt.equals(".odg")) {
					contentType += "graphics";
				}
				else if (fileExt.equals(".odp")) {
					contentType += "presentation";
				}
				else if (fileExt.equals(".ods")) {
					contentType += "spreadsheet";
				}
				else if (fileExt.equals(".odt")) {
					contentType += "text";
				}
			}
			else if (fileExt.equals(".pdf")) {
				extractor = new PdfTextExtractor();

				contentType = "application/pdf";
			}
			else if (fileExt.equals(".ppt")) {
				extractor = new MsPowerPointTextExtractor();

				contentType = "application/vnd.ms-powerpoint";
			}
			else if (fileExt.equals(".rtf")) {
				extractor = new RTFTextExtractor();

				contentType = "application/rtf";
			}
			else if (fileExt.equals(".txt")) {
				extractor = new PlainTextExtractor();

				contentType = "text/plain";
			}
			else if (fileExt.equals(".xls")) {
				extractor = new MsExcelTextExtractor();

				contentType = "application/vnd.ms-excel";
			}
			else if (fileExt.equals(".xml")) {
				extractor = new XMLTextExtractor();

				contentType = "text/xml";
			}

			if (extractor != null) {
				if (_log.isInfoEnabled()) {
					_log.info(
						"Using extractor " + extractor.getClass().getName() +
							" for extension " + fileExt);
				}

				StringMaker sm = new StringMaker();

				BufferedReader reader = new BufferedReader(
					extractor.extractText(is, contentType, encoding));

				int i;

				while ((i = reader.read()) != -1) {
					sm.append((char)i);
				}

				reader.close();

				text = sm.toString();

				if (Validator.isNotNull(
						PropsValues.LUCENE_FILE_EXTRACTOR_REGEXP_STRIP)) {

					text = regexpStrip(text);
				}
			}
			else {
				if (_log.isInfoEnabled()) {
					_log.info("No extractor found for extension " + fileExt);
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Extractor returned text:\n\n" + text);
		}

		if (text == null) {
			text = StringPool.BLANK;
		}

		return LuceneFields.getText(field, text);
	}

	public Field getFile(String field, byte[] byteArray, String fileExt)
		throws IOException {

		InputStream in = new BufferedInputStream(
			new ByteArrayInputStream(byteArray));

		return getFile(field, in, fileExt);
	}

	public Field getFile(String field, File file, String fileExt)
		throws IOException {

		InputStream in = new FileInputStream(file);

		return getFile(field, in, fileExt);
	}

	protected String regexpStrip(String text) {
		char[] array = text.toCharArray();

		for (int i = 0; i < array.length; i++) {
			String s = String.valueOf(array[i]);

			if (!s.matches(PropsValues.LUCENE_FILE_EXTRACTOR_REGEXP_STRIP)) {
				array[i] = CharPool.SPACE;
			}
		}

		return new String(array);
	}

	private static Log _log = LogFactory.getLog(LuceneFileExtractor.class);

}