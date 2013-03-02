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

package com.liferay.portal.wsrp;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.portlet.PortletConfigFactory;

import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.MissingResourceException;
import java.util.ResourceBundle;
import java.util.Set;

import javax.portlet.PortletConfig;
import javax.portlet.PortletMode;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

import oasis.names.tc.wsrp.v1.types.CookieProtocol;
import oasis.names.tc.wsrp.v1.types.LocalizedString;
import oasis.names.tc.wsrp.v1.types.MarkupType;
import oasis.names.tc.wsrp.v1.types.PortletDescription;
import oasis.names.tc.wsrp.v1.types.RegistrationContext;
import oasis.names.tc.wsrp.v1.types.ServiceDescription;
import oasis.names.tc.wsrp.v1.types.UserContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.producer.provider.DescriptionHandler;
import org.apache.wsrp4j.util.WindowStates;

/**
 * <a href="DescriptionHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class DescriptionHandlerImpl implements DescriptionHandler {

	public PortletDescription getPortletDescription(String portletHandle,
			RegistrationContext regContext, UserContext userContext,
			String[] desiredLocales) throws WSRPException {
		long companyId = WSRPUtil.getCompanyId();

		Portlet portlet = null;

		try {
			portlet = PortletLocalServiceUtil.getPortletById(companyId,
					portletHandle);
		}
		catch (Exception e) {
			throw new WSRPException(ErrorCodes.LOAD_SERVICEDESCRIPTION_FAILED,
					e);
		}

		return _getPortletDescription(portlet, regContext, desiredLocales);
	}

	public PortletDescription getPortletDescription(String portletHandle)
			throws WSRPException {
		return getPortletDescription(portletHandle, null, null, null);
	}

	public PortletDescription[] getProducerOfferedPortletDescriptions(
			RegistrationContext regContext, String[] desiredLocales)
			throws WSRPException {
		long companyId = WSRPUtil.getCompanyId();

		PortletDescription[] portletDescriptions = null;

		try {
			List portlets = PortletLocalServiceUtil.getPortlets(companyId);
			portletDescriptions = new PortletDescription[portlets.size()];

			for (int i = 0; i < portlets.size(); i++) {
				Portlet portlet = (Portlet) portlets.get(i);

				portletDescriptions[i] = _getPortletDescription(portlet,
						regContext, desiredLocales);
			}
		}
		catch (Exception e) {
			throw new WSRPException(ErrorCodes.LOAD_SERVICEDESCRIPTION_FAILED,
					e);
		}

		return portletDescriptions;
	}

	public boolean isRegistrationRequired() throws WSRPException {
		return false;
	}

	public ServiceDescription getServiceDescription(
			RegistrationContext regContext, String[] desiredLocales)
			throws WSRPException {
		ServiceDescription serviceDescription = new ServiceDescription();
		serviceDescription.setRequiresRegistration(isRegistrationRequired());

		CookieProtocol cookieProtocol = CookieProtocol.perGroup;
		serviceDescription.setRequiresInitCookie(cookieProtocol);

		PortletDescription[] portletDescriptions = getProducerOfferedPortletDescriptions(
				regContext, desiredLocales);

		serviceDescription.setOfferedPortlets(portletDescriptions);

		return serviceDescription;
	}

	private PortletDescription _getPortletDescription(Portlet portlet,
			RegistrationContext regContext, String[] desiredLocales)
			throws WSRPException {
		PortletDescription portletDescription = new PortletDescription();

		Set localesSet = portlet.getSupportedLocales();
		String[] locales = (String[]) localesSet.toArray(new String[localesSet
				.size()]);

		// Required
		portletDescription.setPortletHandle(portlet.getPortletId());

		// Required
		Map portletModesMap = portlet.getPortletModes();
		Set mimeTypes = portletModesMap.keySet();
		MarkupType[] markupTypes = new MarkupType[mimeTypes.size()];
		Iterator it = mimeTypes.iterator();
		int i = 0;

		for (i = 0; it.hasNext(); i++) {
			boolean viewModeFound = false;
			String mimeType = (String) it.next();
			markupTypes[i] = new MarkupType();

			markupTypes[i].setMimeType(mimeType);

			// Required
			Set portletModesSet = (Set) portletModesMap.get(mimeType);
			String[] portletModes = null;

			// Make sure we have at least VIEW
			if (!portletModesSet.contains(PortletMode.VIEW.toString())) {
				portletModes = new String[portletModesSet.size() + 1];
				portletModes[portletModes.length - 1] = WSRPUtil
						.toWsrpMode(PortletMode.VIEW.toString());
			}
			else {
				portletModes = new String[portletModesSet.size()];
			}

			Iterator itr = portletModesSet.iterator();

			for (int j = 0; itr.hasNext(); j++) {
				String mode = (String) itr.next();

				portletModes[j] = WSRPUtil.toWsrpMode(mode);
			}

			markupTypes[i].setModes(portletModes);

			// Required
			String[] windowStates = { WindowStates._normal,
					WindowStates._minimized, WindowStates._maximized };
			markupTypes[i].setWindowStates(windowStates);

			markupTypes[i].setLocales(locales);
		}

		// make sure we have at least one
		if (mimeTypes.size() <= 0) {
			markupTypes = new MarkupType[1];
			markupTypes[0] = new MarkupType();
			markupTypes[0].setMimeType("text/html");

			// Required
			String[] portletModes = { WSRPUtil.toWsrpMode(PortletMode.VIEW
					.toString()) };
			markupTypes[0].setModes(portletModes);

			// Required
			String[] windowStates = { WindowStates._normal,
					WindowStates._minimized, WindowStates._maximized };
			markupTypes[i].setWindowStates(windowStates);

			markupTypes[0].setLocales(locales);
		}

		portletDescription.setMarkupTypes(markupTypes);

		// get portlet config so we can get localized title
		ServletContext ctx = WSRPUtil.getServletContext();

		PortletConfig portletConfig = PortletConfigFactory.create(portlet,
			ctx);

		// get requested language
		HttpServletRequest req = WSRPUtil.getHttpServletRequest();
		Locale requestLocale = req.getLocale();
		String lang = requestLocale.getDisplayLanguage();
		ResourceBundle resourceBundle = portletConfig
				.getResourceBundle(requestLocale);

		LocalizedString shortTitle = new LocalizedString();
		shortTitle.setLang(lang);
		shortTitle.setValue(_getResourceString(resourceBundle, JavaConstants.JAVAX_PORTLET_SHORT_TITLE, StringPool.BLANK));
		portletDescription.setShortTitle(shortTitle);

		LocalizedString title = new LocalizedString();
		title.setLang(lang);
		title.setValue(_getResourceString(resourceBundle, JavaConstants.JAVAX_PORTLET_TITLE, StringPool.BLANK));
		portletDescription.setTitle(title);

		portletDescription.setGroupID(portlet.getPortletId());

		return portletDescription;
	}

	private String _getResourceString(ResourceBundle bundle, String key, String def) {
		String value = def;

		try {
			value = bundle.getString(key);
		}
		catch (MissingResourceException e){}

		return value;
	}
	private Log _log = LogFactory.getLog(ServiceDescription.class);

}