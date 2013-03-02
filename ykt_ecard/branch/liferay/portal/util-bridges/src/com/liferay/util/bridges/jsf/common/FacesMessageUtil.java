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

package com.liferay.util.bridges.jsf.common;

import com.liferay.portal.kernel.language.LanguageUtil;

import java.util.Locale;

import javax.faces.application.FacesMessage.Severity;
import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;

/**
 * <a href="FacesMessageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class provides static convenience methods for creating FacesMessage
 * objects from locale-specific values in the Liferay portal.properties file,
 * and adding them to the FacesContext either globally, or to individual
 * components.
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class FacesMessageUtil {

	public static void error(FacesContext facesContext, String key) {
		error(null, facesContext, key);
	}

	public static void error(
		FacesContext facesContext, String key, Object argument) {

		error(null, facesContext, key, argument);
	}

	public static void error(
		FacesContext facesContext, String key, Object[] arguments) {

		error(null, facesContext, key, arguments);
	}

	public static void error(
		String clientId, FacesContext facesContext, String key) {

		_addMessage(clientId, facesContext, FacesMessage.SEVERITY_ERROR, key);
	}

	public static void error(
		String clientId, FacesContext facesContext, String key,
		Object argument) {

		_addMessage(
			clientId, facesContext, FacesMessage.SEVERITY_ERROR, key, argument);
	}

	public static void error(
		String clientId, FacesContext facesContext, String key,
		Object[] arguments) {

		_addMessage(
			clientId, facesContext, FacesMessage.SEVERITY_ERROR, key,
			arguments);
	}

	public static void info(FacesContext facesContext, String key) {
		info(null, facesContext, key);
	}

	public static void info(
		FacesContext facesContext, String key, Object argument) {

		info(null, facesContext, key, argument);
	}

	public static void info(
		FacesContext facesContext, String key, Object[] arguments) {

		info(null, facesContext, key, arguments);
	}

	public static void info(
		String clientId, FacesContext facesContext, String key) {

		_addMessage(clientId, facesContext, FacesMessage.SEVERITY_INFO, key);
	}

	public static void info(
		String clientId, FacesContext facesContext, String key,
		Object argument) {

		_addMessage(
			clientId, facesContext, FacesMessage.SEVERITY_INFO, key, argument);
	}

	public static void info(
		String clientId, FacesContext facesContext, String key,
		Object[] arguments) {

		_addMessage(
			clientId, facesContext, FacesMessage.SEVERITY_INFO, key, arguments);
	}

	private static void _addMessage(
		String clientId, FacesContext facesContext, Severity severity,
		String key) {

		Locale locale = JSFPortletUtil.getLocale(facesContext);

		String message = LanguageUtil.get(locale, key);

		FacesMessage facesMessage = new FacesMessage(severity, message, null);

		facesContext.addMessage(clientId, facesMessage);
	}

	private static void _addMessage(
		String clientId, FacesContext facesContext, Severity severity,
		String key, Object argument) {

		Locale locale = JSFPortletUtil.getLocale(facesContext);

		String message = LanguageUtil.format(locale, key, argument);

		FacesMessage facesMessage = new FacesMessage(severity, message, null);

		facesContext.addMessage(clientId, facesMessage);
	}

	private static void _addMessage(
		String clientId, FacesContext facesContext, Severity severity,
		String key, Object[] arguments) {

		Locale locale = JSFPortletUtil.getLocale(facesContext);

		String message = LanguageUtil.format(locale, key, arguments);

		FacesMessage facesMessage = new FacesMessage(severity, message, null);

		facesContext.addMessage(clientId, facesMessage);
	}

}