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

package com.liferay.portal.plugin;

import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.plugin.RemotePluginPackageRepository;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Properties;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;

/**
 * <a href="PluginPackageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class PluginPackageImpl implements Comparable, PluginPackage {

	public static final String STATUS_ALL = "all";

	public static final String STATUS_INSTALLATION_IN_PROCESS =
		"installationInProcess";

	public static final String STATUS_NEWER_VERSION_INSTALLED =
		"newerVersionInstalled";

	public static final String STATUS_NOT_INSTALLED = "notInstalled";

	public static final String STATUS_NOT_INSTALLED_OR_OLDER_VERSION_INSTALLED =
		"notInstalledOrOlderVersionInstalled";

	public static final String STATUS_OLDER_VERSION_INSTALLED =
		"olderVersionInstalled";

	public static final String STATUS_SAME_VERSION_INSTALLED =
		"sameVersionInstalled";

	public PluginPackageImpl(String moduleId) {
		_moduleId = ModuleId.getInstance(moduleId);
	}

	public String getModuleId() {
		return _moduleId.toString();
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getVersion() {
		return _moduleId.getVersion();
	}

	public boolean isLaterVersionThan(PluginPackage pluginPackage) {
		return _moduleId.isLaterVersionThan(pluginPackage.getVersion());
	}

	public boolean isPreviousVersionThan(PluginPackage pluginPackage) {
		return _moduleId.isPreviousVersionThan(pluginPackage.getVersion());
	}

	public boolean isSameVersionAs(PluginPackage pluginPackage) {
		return _moduleId.isSameVersionAs(pluginPackage.getVersion());
	}

	public String getRecommendedDeploymentContext() {
		String context = _recommendedDeploymentContext;

		if (Validator.isNull(context)) {
			context = _moduleId.getArtifactId();
		}

		return context;
	}

	public void setRecommendedDeploymentContext(
		String recommendedDeploymentContext) {

		_recommendedDeploymentContext = recommendedDeploymentContext;
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public String getAuthor() {
		return _author;
	}

	public void setAuthor(String author) {
		_author = author;
	}

	public List getTypes() {
		return _types;
	}

	public void setTypes(List types) {
		_types = types;
	}

	public List getTags() {
		return _tags;
	}

	public void setTags(List tags) {
		_tags = tags;
	}

	public List getLicenses() {
		return _licenses;
	}

	public void setLicenses(List licenses) {
		_licenses = licenses;
	}

	public List getLiferayVersions() {
		return _liferayVersions;
	}

	public void setLiferayVersions(List liferayVersions) {
		_liferayVersions = liferayVersions;
	}

	public String getShortDescription() {
		return _shortDescription;
	}

	public void setShortDescription(String shortDescription) {
		_shortDescription = shortDescription;
	}

	public String getLongDescription() {
		return _longDescription;
	}

	public void setLongDescription(String longDescription) {
		_longDescription = longDescription;
	}

	public String getChangeLog() {
		return _changeLog;
	}

	public void setChangeLog(String changeLog) {
		_changeLog = changeLog;
	}

	public List getScreenshots() {
		return _screenshots;
	}

	public void setScreenshots(List screenshots) {
		_screenshots = screenshots;
	}

	public String getPageURL() {
		return _pageURL;
	}

	public void setPageURL(String pageURL) {
		_pageURL = pageURL;
	}

	public String getDownloadURL() {
		String useDownloadURL = getRepository().getSettings().getProperty(
			RemotePluginPackageRepository.SETTING_USE_DOWNLOAD_URL);

		if (!GetterUtil.getBoolean(useDownloadURL, true)) {
			return getArtifactURL();
		}

		if (Validator.isNotNull(_downloadURL)) {
			return _downloadURL;
		}

		return getArtifactURL();
	}

	public void setDownloadURL(String downloadURL) {
		_downloadURL = downloadURL;
	}

	public RemotePluginPackageRepository getRepository() {
		return _repository;
	}

	public void setRepository(RemotePluginPackageRepository repository) {
		_repository = repository;
	}

	public String getRepositoryURL() {
		if (_repository != null) {
			return _repository.getRepositoryURL();
		}
		else {
			return RemotePluginPackageRepository.LOCAL_URL;
		}
	}

	public String getContext() {
		return _context;
	}

	public void setContext(String context) {
		_context = context;
	}

	public String getArtifactURL() {
		return getRepositoryURL() + _moduleId.getArtifactPath();
	}

	public String getArtifactId() {
		return _moduleId.getArtifactId();
	}

	public String getGroupId() {
		return _moduleId.getGroupId();
	}

	public String getPackageId() {
		return _moduleId.getPackageId();
	}

	public Properties getDeploymentSettings() {
		return _deploymentSettings;
	}

	public void setDeploymentSettings(Properties deploymentSettings) {
		_deploymentSettings = deploymentSettings;
	}

	public int compareTo(Object obj) {
		if (!(obj instanceof PluginPackage)) {
			return -1;
		}

		PluginPackage pluginPackage = (PluginPackage)obj;

		return getName().compareTo(pluginPackage.getName());
	}

	public boolean equals(Object obj) {
		if (!(obj instanceof PluginPackage)) {
			return false;
		}

		PluginPackage pluginPackage = (PluginPackage)obj;

		EqualsBuilder equalsBuilder = new EqualsBuilder();

		equalsBuilder.append(getModuleId(), pluginPackage.getModuleId());
		equalsBuilder.append(
			getRepositoryURL(), pluginPackage.getRepositoryURL());

		return equalsBuilder.isEquals();
	}

	public int hashCode() {
		HashCodeBuilder hashCodeBuilder = new HashCodeBuilder();

		hashCodeBuilder.append(getModuleId());
		hashCodeBuilder.append(getRepositoryURL());

		return hashCodeBuilder.hashCode();
	}

	public String toString() {
		StringMaker sm = new StringMaker();

		sm.append(StringPool.SLASH);
		sm.append(_context);
		sm.append(StringPool.COLON);
		sm.append(_moduleId);

		return sm.toString();
	}

	private ModuleId _moduleId;
	private String _recommendedDeploymentContext;
	private String _name;
	private Date _modifiedDate;
	private String _author;
	private List _types = new ArrayList();
	private List _tags = new ArrayList();
	private List _licenses = new ArrayList();
	private List _liferayVersions = new ArrayList();
	private String _shortDescription = StringPool.BLANK;
	private String _longDescription = StringPool.BLANK;
	private String _changeLog = StringPool.BLANK;
	private List _screenshots = new ArrayList();
	private String _pageURL;
	private String _downloadURL;
	private RemotePluginPackageRepository _repository;
	private String _context;
	private Properties _deploymentSettings;

}