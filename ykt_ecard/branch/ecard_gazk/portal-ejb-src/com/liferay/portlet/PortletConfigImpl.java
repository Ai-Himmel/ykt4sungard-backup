/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet;

import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletInfo;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.CollectionFactory;
import com.liferay.util.lang.FastStringBuffer;

import java.io.ByteArrayInputStream;

import java.util.Collections;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Map;
import java.util.PropertyResourceBundle;
import java.util.ResourceBundle;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;

/**
 * <a href="PortletConfigImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.23 $
 *
 */
public class PortletConfigImpl implements PortletConfig {

	public PortletConfigImpl(String portletName, PortletContext portletCtx,
							 Map params, String resourceBundle,
							 PortletInfo portletInfo) {

		_rootPortletId = Portlet.getRootPortletId(portletName);
		_portletId = portletName;
		_portletName = _rootPortletId;

		int pos = _portletName.indexOf(Portlet.WAR_SEPARATOR);
		if (pos != -1) {
			_portletName = _portletName.substring(0, pos);

			_warFile = true;
		}

		_portletCtx = portletCtx;
		_params = params;
		_resourceBundle = resourceBundle;
		_portletInfo = portletInfo;
		_bundlePool = CollectionFactory.getHashMap();
	}

	public String getPortletId() {
		return _portletId;
	}

	public String getPortletName() {
		return _portletName;
	}

	public boolean isWARFile() {
		return _warFile;
	}

	public PortletContext getPortletContext() {
		return _portletCtx;
	}

	public ResourceBundle getResourceBundle(Locale locale) {
		if (_resourceBundle == null) {
			String poolId = _portletId;

			ResourceBundle bundle = (ResourceBundle)_bundlePool.get(poolId);

			if (bundle == null) {
				FastStringBuffer sb = new FastStringBuffer();

				try {
					sb.append(WebKeys.JAVAX_PORTLET_TITLE);
					sb.append("=");
					sb.append(_portletInfo.getTitle());
					sb.append("\n");

					sb.append(WebKeys.JAVAX_PORTLET_SHORT_TITLE);
					sb.append("=");
					sb.append(_portletInfo.getShortTitle());
					sb.append("\n");

					sb.append(WebKeys.JAVAX_PORTLET_KEYWORDS);
					sb.append("=");
					sb.append(_portletInfo.getKeywords());
					sb.append("\n");

					bundle = new PropertyResourceBundle(
						new ByteArrayInputStream(sb.toString().getBytes()));
				}
				catch (Exception e) {
					e.printStackTrace();
				}

				_bundlePool.put(poolId, bundle);
			}

			return bundle;
		}
		else {
			String poolId = _portletId + "." + locale.toString();

			ResourceBundle bundle = (ResourceBundle)_bundlePool.get(poolId);

			if (bundle == null) {
				if (!_warFile &&
					_resourceBundle.equals(
						StrutsResourceBundle.class.getName())) {

					String companyId =
						(String)_portletCtx.getAttribute(WebKeys.COMPANY_ID);

					bundle = StrutsResourceBundle.getBundle(
						_portletName, companyId, locale);
				}
				else {
					PortletContextWrapper pcw =
						PortletContextPool.get(_rootPortletId);

					bundle = pcw.getResourceBundle(locale);
				}

				bundle = new PortletResourceBundle(bundle, _portletInfo);

				_bundlePool.put(poolId, bundle);
			}

			return bundle;
		}
	}

	public String getInitParameter(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		return (String)_params.get(name);
	}

	public Enumeration getInitParameterNames() {
		return Collections.enumeration(_params.keySet());
	}

	private String _rootPortletId;
	private String _portletId;
	private String _portletName;
	private boolean _warFile;
	private PortletContext _portletCtx;
	private Map _params;
	private String _resourceBundle;
	private PortletInfo _portletInfo;
	private Map _bundlePool;

}