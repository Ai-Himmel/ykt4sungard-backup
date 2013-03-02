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

package com.liferay.portlet.documentlibrary.util;

import com.artofsolving.jodconverter.DefaultDocumentFormatRegistry;
import com.artofsolving.jodconverter.DocumentConverter;
import com.artofsolving.jodconverter.DocumentFormat;
import com.artofsolving.jodconverter.DocumentFormatRegistry;
import com.artofsolving.jodconverter.openoffice.connection.OpenOfficeConnection;
import com.artofsolving.jodconverter.openoffice.connection.SocketOpenOfficeConnection;
import com.artofsolving.jodconverter.openoffice.converter.StreamOpenOfficeDocumentConverter;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.SystemProperties;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <a href="DocumentConversionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class DocumentConversionUtil {

	public static InputStream convert(
			String id, InputStream is, String sourceExtension,
			String targetExtension)
		throws IOException, PortalException, SystemException {

		return _instance._convert(id, is, sourceExtension, targetExtension);
	}

	public static String[] getConversions(String extension) {
		return _instance._getConversions(extension);
	}

	private DocumentConversionUtil() {
		_conversionsMap.put("svg", _DRAWING_CONVERSIONS);
		_conversionsMap.put("swf", _DRAWING_CONVERSIONS);

		_conversionsMap.put("odp", _PRESENTATION_CONVERSIONS);
		_conversionsMap.put("ppt", _PRESENTATION_CONVERSIONS);
		_conversionsMap.put("sxi", _PRESENTATION_CONVERSIONS);

		_conversionsMap.put("csv", _SPREADSHEET_CONVERSIONS);
		_conversionsMap.put("ods", _SPREADSHEET_CONVERSIONS);
		_conversionsMap.put("sxc", _SPREADSHEET_CONVERSIONS);
		_conversionsMap.put("tsv", _SPREADSHEET_CONVERSIONS);
		_conversionsMap.put("xls", _SPREADSHEET_CONVERSIONS);

		_conversionsMap.put("doc", _TEXT_CONVERSIONS);
		_conversionsMap.put("odt", _TEXT_CONVERSIONS);
		_conversionsMap.put("rtf", _TEXT_CONVERSIONS);
		_conversionsMap.put("sxw", _TEXT_CONVERSIONS);
		_conversionsMap.put("txt", _TEXT_CONVERSIONS);
		_conversionsMap.put("wpd", _TEXT_CONVERSIONS);
	}

	private InputStream _convert(
			String id, InputStream is, String sourceExtension,
			String targetExtension)
		throws IOException, PortalException, SystemException {

		if (!PrefsPropsUtil.getBoolean(
				PropsUtil.OPENOFFICE_SERVER_ENABLED,
				PropsValues.OPENOFFICE_SERVER_ENABLED)){

			return null;
		}

		StringMaker sm = new StringMaker();

		sm.append(SystemProperties.get(SystemProperties.TMP_DIR));
		sm.append("/liferay/document_conversion/");
		sm.append(id);
		sm.append(StringPool.PERIOD);
		sm.append(targetExtension);

		String fileName = sm.toString();

		File file = new File(fileName);

		if (!file.exists()) {
			DocumentFormatRegistry registry =
				new DefaultDocumentFormatRegistry();

			DocumentConverter converter = _getConverter(registry);

			DocumentFormat inputFormat = registry.getFormatByFileExtension(
				sourceExtension);

			ByteArrayOutputStream baos = new ByteArrayOutputStream();

			DocumentFormat outputFormat = registry.getFormatByFileExtension(
				targetExtension);

			converter.convert(is, inputFormat, baos, outputFormat);

			FileUtil.write(file, baos.toByteArray());
		}

		return new FileInputStream(file);
	}

	private String[] _getConversions(String extension) {
		String[] conversions = (String[])_conversionsMap.get(extension);

		if (conversions == null) {
			conversions = _DEFAULT_CONVERSIONS;
		}
		else {
			if (ArrayUtil.contains(conversions, extension)) {
				List list = new ArrayList();

				for (int i = 0; i < conversions.length; i++) {
					String conversion = conversions[i];

					if (!conversion.equals(extension)) {
						list.add(conversion);
					}
				}

				conversions = (String[])list.toArray(new String[0]);
			}
		}

		return conversions;
	}

	private DocumentConverter _getConverter(DocumentFormatRegistry registry)
		throws PortalException, SystemException {

		if ((_connection == null) || (_converter == null)) {
			String host = PrefsPropsUtil.getString(
				PropsUtil.OPENOFFICE_SERVER_HOST,
				PropsValues.OPENOFFICE_SERVER_HOST);
			int port = PrefsPropsUtil.getInteger(
				PropsUtil.OPENOFFICE_SERVER_PORT,
				PropsValues.OPENOFFICE_SERVER_PORT);

			_connection = new SocketOpenOfficeConnection(host, port);
			_converter = new StreamOpenOfficeDocumentConverter(_connection);
		}

		return _converter;
	}

	private static final String[] _DEFAULT_CONVERSIONS = new String[0];

	private static final String[] _DRAWING_CONVERSIONS = new String[] {"odg"};

	private static final String[] _PRESENTATION_CONVERSIONS = new String[] {
		"odp", "pdf", "ppt", "swf", "sxi"
	};

	private static final String[] _SPREADSHEET_CONVERSIONS = new String[] {
		"csv", "ods", "pdf", "sxc", "tsv", "xls"
	};

	private static final String[] _TEXT_CONVERSIONS = new String[] {
		"doc", "odt", "pdf", "rtf", "sxw", "txt"
	};

	private static DocumentConversionUtil _instance =
		new DocumentConversionUtil();

	private Map _conversionsMap = CollectionFactory.getHashMap();
	private OpenOfficeConnection _connection;
	private DocumentConverter _converter;

}