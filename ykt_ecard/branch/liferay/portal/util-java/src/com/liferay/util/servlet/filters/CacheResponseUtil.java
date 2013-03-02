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

package com.liferay.util.servlet.filters;

import com.liferay.util.servlet.Header;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletResponse;

/**
 * <a href="CacheResponseUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class CacheResponseUtil {

	public static void write(HttpServletResponse res, CacheResponseData data)
		throws IOException {

		Map headers = data.getHeaders();

		Iterator itr = headers.keySet().iterator();

		while (itr.hasNext()) {
			String headerKey = (String)itr.next();

			List headerValues = (List)headers.get(headerKey);

			for (int i = 0; i < headerValues.size(); i++) {
				Header header = (Header)headerValues.get(i);

				int type = header.getType();

				if (type == Header.DATE_TYPE) {
					res.addDateHeader(headerKey, header.getDateValue());
				}
				else if (type == Header.INTEGER_TYPE) {
					res.addIntHeader(headerKey, header.getIntValue());
				}
				else if (type == Header.STRING_TYPE) {
					res.addHeader(headerKey, header.getStringValue());
				}
			}
		}

		res.setContentType(data.getContentType());

		ServletResponseUtil.write(res, data.getData());
	}

}