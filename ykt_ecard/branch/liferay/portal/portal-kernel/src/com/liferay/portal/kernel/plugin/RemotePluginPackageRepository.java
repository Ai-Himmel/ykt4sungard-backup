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

package com.liferay.portal.kernel.plugin;

import com.liferay.portal.kernel.util.StringPool;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="RemotePluginPackageRepository.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Jorge Ferrer
 *
 */
public class RemotePluginPackageRepository {

	public static final String LOCAL_URL = "LOCAL_URL";

	public static final String SETTING_USE_DOWNLOAD_URL = "use-download-url";

	public RemotePluginPackageRepository(String repositoryURL) {
		_repositoryURL = repositoryURL;
	}

	public String getRepositoryURL() {
		return _repositoryURL;
	}

	public List getPluginPackages() {
		return _pluginPackages;
	}

	public Properties getSettings() {
		return _settings;
	}

	public void setSettings(Properties settings) {
		_settings = settings;
	}

	public Set getTags() {
		return _tags;
	}

	public void addPluginPackage(PluginPackage pluginPackage) {

		// Avoid duplicates

		PluginPackage existingPackage = (PluginPackage)_moduleIdIndex.get(
			pluginPackage.getModuleId());

		if (existingPackage != null) {
		   return;
		}

		_artifactURLIndex.put(pluginPackage.getArtifactURL(), pluginPackage);
		_moduleIdIndex.put(pluginPackage.getModuleId(), pluginPackage);
		_addToGroupAndArtifactIndex(
			pluginPackage.getGroupId(), pluginPackage.getArtifactId(),
			pluginPackage);
		_pluginPackages.add(pluginPackage);
		_tags.addAll(pluginPackage.getTags());
	}

	public PluginPackage findPluginByArtifactURL(String artifactURL) {
		return (PluginPackage)_artifactURLIndex.get(artifactURL);
	}

	public PluginPackage findPluginPackageByModuleId(String moduleId) {
		return (PluginPackage)_moduleIdIndex.get(moduleId);
	}

	public List findPluginsByGroupIdAndArtifactId(
		String groupId, String artifactId) {

		return (List)_groupAndArtifactIndex.get(
			groupId + StringPool.SLASH + artifactId);
	}

	public void removePlugin(PluginPackage pluginPackage) {
		_artifactURLIndex.remove(pluginPackage.getArtifactURL());
		_moduleIdIndex.remove(pluginPackage.getModuleId());
		_removeFromGroupAndArtifactIndex(
			pluginPackage.getGroupId(), pluginPackage.getArtifactId(),
			pluginPackage.getModuleId());
		_pluginPackages.remove(pluginPackage);
	}

	private void _addToGroupAndArtifactIndex(
		String groupId, String artifactId, PluginPackage pluginPackage) {

		List plugins = findPluginsByGroupIdAndArtifactId(groupId, artifactId);

		if (plugins == null) {
			plugins = new ArrayList();

			_groupAndArtifactIndex.put(
				groupId+ StringPool.SLASH + artifactId, plugins);
		}

		plugins.add(pluginPackage);
	}

	private void _removeFromGroupAndArtifactIndex(
		String groupId, String artifactId, String moduleId) {

		List plugins = findPluginsByGroupIdAndArtifactId(groupId, artifactId);

		if (plugins != null) {
			Iterator itr = plugins.iterator();

			while (itr.hasNext()) {
				PluginPackage pluginPackage = (PluginPackage)itr.next();

				if (pluginPackage.getModuleId().equals(moduleId)) {
					itr.remove();

					break;
				}
			}
		}
	}

	private String _repositoryURL;
	private Map _artifactURLIndex = new HashMap();
	private Map _moduleIdIndex = new HashMap();
	private Map _groupAndArtifactIndex = new HashMap();
	private List _pluginPackages = new ArrayList();
	private Properties _settings = null;
	private Set _tags = new TreeSet();

}