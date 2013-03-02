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

package com.liferay.support.glassfish;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * <a href="DTDResolver.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raju Uppalapati
 * @author Brian Wing Shun Chan
 *
 */
public class DTDResolver extends DefaultHandler {

    public DTDResolver(String dtdDir) {
        _dtdDir = dtdDir;
    }

    public InputSource resolveEntity(String publicId, String systemId)
		throws IOException, SAXException {

		systemId = systemId.trim();

		if (_dtdDir == null) {
			return super.resolveEntity(publicId, systemId);
		}

		InputSource inputSource = null;

		try {
			String dtdName = systemId.substring(systemId.lastIndexOf("/") + 1);

			File file = new File(_dtdDir + File.separator + dtdName);

			FileInputStream fis = new FileInputStream(file);

			inputSource = new InputSource(fis);
		}
		catch (FileNotFoundException fnfe) {
			fnfe.printStackTrace();
		}

		return inputSource;
    }

    private String _dtdDir;

}