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

package com.liferay.portal.webdav.methods;

import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Tuple;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.webdav.InvalidRequestException;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.portal.webdav.WebDAVRequest;
import com.liferay.portal.webdav.WebDAVUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.servlet.ServletResponseUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.StringReader;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.Namespace;
import org.dom4j.io.SAXReader;

/**
 * <a href="PropfindMethodImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class PropfindMethodImpl extends BasePropMethodImpl implements Method {

	public int process(WebDAVRequest webDavReq) throws WebDAVException {
		try {
			HttpServletResponse res = webDavReq.getHttpServletResponse();

			Set props = getProps(webDavReq);

			String xml = getResponseXML(webDavReq, props);

			res.setStatus(WebDAVUtil.SC_MULTI_STATUS);
			res.setContentType(ContentTypes.TEXT_XML_UTF8);

			try {
				ServletResponseUtil.write(res, xml);
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e);
				}
			}

			return -1;
		}
		catch (InvalidRequestException ire) {
			return HttpServletResponse.SC_BAD_REQUEST;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	protected Set getProps(WebDAVRequest webDavReq)
		throws InvalidRequestException {

		try {
			Set props = new HashSet();

			HttpServletRequest req = webDavReq.getHttpServletRequest();

			String xml = new String(FileUtil.getBytes(req.getInputStream()));

			if (Validator.isNull(xml)) {
				return props;
			}

			if (_log.isDebugEnabled()) {
				_log.debug(
					"Request XML: \n" +
						XMLFormatter.toString(xml, StringPool.FOUR_SPACES));
			}

			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			Element prop = root.element("prop");

			Iterator itr = prop.elements().iterator();

			while (itr.hasNext()) {
				Element el = (Element)itr.next();

				String prefix = el.getNamespacePrefix();
				String uri = el.getNamespaceURI();

				Namespace namespace = null;

				if (uri.equals(WebDAVUtil.DAV_URI.getURI())) {
					namespace = WebDAVUtil.DAV_URI;
				}
				else if (Validator.isNull(prefix)) {
					namespace = Namespace.get(uri);
				}
				else {
					namespace = Namespace.get(prefix, uri);
				}

				props.add(new Tuple(el.getName(), namespace));
			}

			return props;
		}
		catch (Exception e) {
			throw new InvalidRequestException(e);
		}
	}

	private static Log _log = LogFactory.getLog(PropfindMethodImpl.class);

}