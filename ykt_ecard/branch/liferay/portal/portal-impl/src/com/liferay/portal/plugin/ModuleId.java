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

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.util.CollectionFactory;
import com.liferay.util.Version;

import java.util.Map;
import java.util.StringTokenizer;

/**
 * <a href="ModuleId.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class ModuleId {

	public static ModuleId getInstance(String moduleId) {
		ModuleId moduleIdObj = (ModuleId)_moduleIds.get(moduleId);

		if (moduleIdObj == null) {
			moduleIdObj =  new ModuleId(moduleId);

			_moduleIds.put(moduleId, moduleIdObj);
		}

		return moduleIdObj;
	}

	public static String toString(
		String groupId, String artifactId, String version, String type) {

		return groupId + StringPool.SLASH + artifactId + StringPool.SLASH +
			version + StringPool.SLASH + type;
	}

	public String getGroupId() {
		return _groupId;
	}

	public String getArtifactId() {
		return _artifactId;
	}

	public String getPackageId() {
		return _groupId + StringPool.SLASH + _artifactId;
	}

	public String getVersion() {
		return _pluginVersion.toString();
	}

	public String getType() {
		return _type;
	}

	public String getArtifactPath() {
		return StringPool.SLASH + _groupId + StringPool.SLASH + _artifactId +
			StringPool.SLASH + _pluginVersion + StringPool.SLASH +
				getArtifactWARName();
	}

	public String getArtifactWARName() {
		return _artifactId + StringPool.DASH + _pluginVersion +
			StringPool.PERIOD + _type;
	}

	public boolean isLaterVersionThan(String version) {
		return _pluginVersion.isLaterVersionThan(version);
	}

	public boolean isPreviousVersionThan(String version) {
		return _pluginVersion.isPreviousVersionThan(version);
	}

	public boolean isSameVersionAs(String version) {
		return _pluginVersion.isSameVersionAs(version);
	}

	public boolean equals(Object obj) {
		if (!(obj instanceof ModuleId)) {
			return false;
		}

		ModuleId moduleId = (ModuleId)obj;

		return toString().equals(moduleId.toString());
	}

	public int hashCode() {
		return toString().hashCode();
	}

	public String toString() {
		return toString(
			_groupId, _artifactId, _pluginVersion.toString(), _type);
	}

	protected ModuleId(
		String groupId, String artifactId, Version pluginVersion, String type) {

		_groupId = groupId;
		_artifactId = artifactId;
		_pluginVersion = pluginVersion;
		_type = type;
	}

	protected ModuleId(String moduleId) {
		StringTokenizer st = new StringTokenizer(moduleId, StringPool.SLASH);

		if (st.countTokens() < 4) {
			throw new RuntimeException(
				"The moduleId " + moduleId + " is not correct");
		}

		_groupId = st.nextToken();
		_artifactId = st.nextToken();
		_pluginVersion = Version.getInstance(st.nextToken());
		_type = st.nextToken();
	}

	private static Map _moduleIds = CollectionFactory.getSyncHashMap();

	private String _artifactId;
	private String _groupId;
	private Version _pluginVersion;
	private String _type;

}