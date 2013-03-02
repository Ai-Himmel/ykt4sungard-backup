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

package com.liferay.portlet.wsrp;

import org.apache.wsrp4j.consumer.URLGenerator;
import org.apache.wsrp4j.consumer.URLTemplateComposer;

/**
 * <a href="URLTemplateComposerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class URLTemplateComposerImpl implements URLTemplateComposer {

	public static URLTemplateComposer getInstance() {
		if (_instance == null) {
			_instance = new URLTemplateComposerImpl();
		}

		return _instance;
	}

	private URLTemplateComposerImpl() {
	}

	/**
	 * Sets the url generator to be used.
	 */
	public void setURLGenerator(URLGenerator urlGenerator) {
		this._urlGenerator = urlGenerator;
	}

	public String createBlockingActionTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createSecureBlockingActionTemplate(
			boolean includePortletHandle, boolean includeUserContextKey,
			boolean includePortletInstanceKey, boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case
		/*
		 *
		 * if (this.urlGenerator != null) { template = createTemplate(
		 * urlGenerator.getBlockingActionURL(null), false, true, true, true,
		 * true, true, false, false, includePortletHandle,
		 * includeUserContextKey, includePortletInstanceKey, includeSessionID); }
		 */
		return template;
	}

	public String createRenderTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createSecureRenderTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createResourceTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createSecureResourceTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createDefaultTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String createSecureDefaultTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID) {

		String template = null;

		//TODO: Template processing Pluto case

		return template;
	}

	public String getNamespacePrefix() {
		return _urlGenerator.getNamespacedToken("");
	}

	private static URLTemplateComposer _instance = null;

	private URLGenerator _urlGenerator = null;

}