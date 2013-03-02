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

package com.liferay.portal.servlet;

import com.liferay.portal.job.Scheduler;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.pop.MessageListener;
import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.portlet.PortletLayoutListener;
import com.liferay.portal.kernel.search.Indexer;
import com.liferay.portal.kernel.servlet.URLEncoder;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.model.ActivityTrackerInterpreter;

import java.util.Locale;
import java.util.Map;
import java.util.ResourceBundle;

import javax.portlet.Portlet;
import javax.portlet.PreferencesValidator;

import javax.servlet.ServletContext;

/**
 * <a href="PortletContextWrapper.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletContextWrapper {

	public PortletContextWrapper(
		String portletName, ServletContext	servletContext,
		Portlet portletInstance,
		ConfigurationAction configurationActionInstance,
		Indexer indexerInstance, Scheduler schedulerInstance,
		FriendlyURLMapper friendlyURLMapperInstance,
		URLEncoder urlEncoderInstance,
		PortletDataHandler portletDataHandlerInstance,
		PortletLayoutListener portletLayoutListenerInstance,
		ActivityTrackerInterpreter activityTrackerInterpreterInstance,
		MessageListener popMessageListenerInstance,
		PreferencesValidator prefsValidatorInstance, Map resourceBundles,
		Map customUserAttributes) {

		_portletName = portletName;
		_servletContext = servletContext;
		_portletInstance = portletInstance;
		_configurationActionInstance = configurationActionInstance;
		_indexerInstance = indexerInstance;
		_schedulerInstance = schedulerInstance;
		_friendlyURLMapperInstance = friendlyURLMapperInstance;
		_urlEncoderInstance = urlEncoderInstance;
		_portletDataHandlerInstance = portletDataHandlerInstance;
		_portletLayoutListenerInstance = portletLayoutListenerInstance;
		_activityTrackerInterpreterInstance =
			activityTrackerInterpreterInstance;
		_popMessageListenerInstance = popMessageListenerInstance;
		_prefsValidatorInstance = prefsValidatorInstance;
		_resourceBundles = resourceBundles;
		_customUserAttributes = customUserAttributes;
	}

	public String getPortletName() {
		return _portletName;
	}

	public ServletContext getServletContext() {
		return _servletContext;
	}

	public Portlet getPortletInstance() {
		return _portletInstance;
	}

	public void removePortletInstance() {
		_portletInstance = null;
	}

	public ConfigurationAction getConfigurationActionInstance() {
		return _configurationActionInstance;
	}

	public Indexer getIndexerInstance() {
		return _indexerInstance;
	}

	public Scheduler getSchedulerInstance() {
		return _schedulerInstance;
	}

	public FriendlyURLMapper getFriendlyURLMapperInstance() {
		return _friendlyURLMapperInstance;
	}

	public URLEncoder getURLEncoderInstance() {
		return _urlEncoderInstance;
	}

	public PortletDataHandler getPortletDataHandlerInstance() {
		return _portletDataHandlerInstance;
	}

	public PortletLayoutListener getPortletLayoutListenerInstance() {
		return _portletLayoutListenerInstance;
	}

	public ActivityTrackerInterpreter getActivityTrackerInterpreterInstance() {
		return _activityTrackerInterpreterInstance;
	}

	public MessageListener getPopMessageListenerInstance() {
		return _popMessageListenerInstance;
	}

	public PreferencesValidator getPreferencesValidatorInstance() {
		return _prefsValidatorInstance;
	}

	public ResourceBundle getResourceBundle(Locale locale) {
		ResourceBundle resourceBundle = (ResourceBundle)_resourceBundles.get(
			LocaleUtil.toLanguageId(locale));

		if (resourceBundle == null) {
			resourceBundle = (ResourceBundle)_resourceBundles.get(
				locale.getLanguage());

			if (resourceBundle == null) {
				resourceBundle = (ResourceBundle)_resourceBundles.get(
					LocaleUtil.toLanguageId(LocaleUtil.getDefault()));
			}
		}

		return resourceBundle;
	}

	public Map getCustomUserAttributes() {
		return _customUserAttributes;
	}

	private String _portletName;
	private ServletContext _servletContext;
	private Portlet _portletInstance;
	private ConfigurationAction _configurationActionInstance;
	private Indexer _indexerInstance;
	private Scheduler _schedulerInstance;
	private FriendlyURLMapper _friendlyURLMapperInstance;
	private URLEncoder _urlEncoderInstance;
	private PortletDataHandler _portletDataHandlerInstance;
	private PortletLayoutListener _portletLayoutListenerInstance;
	private ActivityTrackerInterpreter _activityTrackerInterpreterInstance;
	private MessageListener _popMessageListenerInstance;
	private PreferencesValidator _prefsValidatorInstance;
	private Map _resourceBundles;
	private Map _customUserAttributes;

}