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

package com.liferay.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import java.util.Map;
import java.util.StringTokenizer;

/**
 * <a href="Version.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class Version implements Comparable {

	public static final String UNKNOWN = "unknown";

	public static Version getInstance(String version) {
		Version versionObj = (Version)_versions.get(version);

		if (versionObj == null) {
			versionObj =  new Version(version);

			_versions.put(version, versionObj);
		}

		return versionObj;
	}

	public String getMajor() {
		if (_major == null) {
			return "0";
		}

		return _major;
	}

	public String getMinor() {
		if (_minor == null) {
			return "0";
		}

		return _minor;
	}

	public String getBugFix() {
		if (_bugFix == null) {
			return "0";
		}

		return _bugFix;
	}

	public String getBuildNumber() {
		return _buildNumber;
	}

	public boolean isLaterVersionThan(String version) {
		if (compareTo(getInstance(version)) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isPreviousVersionThan(String version) {
		if (compareTo(getInstance(version)) < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isSameVersionAs(String version) {
		if (compareTo(getInstance(version)) == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean includes(Version version) {
		if (equals(version)) {
			return true;
		}

		if (getMajor().equals(StringPool.STAR)) {
			return true;
		}

		if (getMajor().equals(version.getMajor())) {
			if (getMinor().equals(StringPool.STAR)) {
				return true;
			}

			if (getMinor().equals(version.getMinor())) {
				if (getBugFix().equals(StringPool.STAR)) {
					return true;
				}

				if (getBugFix().equals(version.getBugFix())) {
					if (getBuildNumber().equals(StringPool.STAR) ||
						getBuildNumber().equals(version.getBuildNumber())) {

						return true;
					}
				}
				else if (_contains(getBugFix(), version.getBugFix())) {
					return true;
				}
			}
			else if (_contains(getMinor(), version.getMinor())) {
				return true;
			}
		}
		else if (_contains(getMajor(), version.getMajor())) {
			return true;
		}

		return false;
	}

	public int compareTo(Object obj) {
		if ((obj == null) || (!(obj instanceof Version))) {
			return 1;
		}

		Version version = (Version)obj;

		// Unknown is always considered a lower version

		if (version.toString().equals(UNKNOWN)) {
			return 1;
		}

		if (toString().equals(UNKNOWN)) {
			return -1;
		}

		int result = getMajor().compareTo(version.getMajor());

		if (result != 0) {
			return result;
		}

		result = getMinor().compareTo(version.getMinor());

		if (result != 0) {
			return result;
		}

		result = getBugFix().compareTo(version.getBugFix());

		if (result != 0) {
			return result;
		}

		return getBuildNumber().compareTo(version.getBuildNumber());
	}

	public boolean equals(Object obj) {
		if ((obj == null) || (!(obj instanceof Version))) {
			return false;
		}

		Version version = (Version)obj;

		String versionString1 = toString();
		String versionString2 = version.toString();

		if (versionString1.equals(UNKNOWN) || versionString2.equals(UNKNOWN)) {
			return false;
		}

		return versionString1.equals(versionString2);
	}

	public int hashCode() {
		return toString().hashCode();
	}

	public String toString() {
		StringMaker sm = new StringMaker();

		sm.append(_major);

		if (Validator.isNotNull(_minor)) {
			sm.append(_SEPARATOR);
			sm.append(_minor);

			if (Validator.isNotNull(_bugFix)) {
				sm.append(_SEPARATOR);
				sm.append(_bugFix);

				if (Validator.isNotNull(_buildNumber)) {
					sm.append(_SEPARATOR);
					sm.append(_buildNumber);
				}
			}
		}

		return sm.toString();
	}

	protected Version(String version) {
		StringTokenizer st = new StringTokenizer(version, _SEPARATOR);

		_major = st.nextToken();

		if (st.hasMoreTokens()) {
			_minor = st.nextToken();
		}

		if (st.hasMoreTokens()) {
			_bugFix = st.nextToken();
		}

		StringMaker buildNumber = new StringMaker();

		while (st.hasMoreTokens()) {
			buildNumber.append(st.nextToken());

			if (st.hasMoreTokens()) {
				buildNumber.append(_SEPARATOR);
			}
		}

		_buildNumber = buildNumber.toString();
	}

	private boolean _contains(String containerStr, String numberStr) {
		if (containerStr.endsWith(StringPool.PLUS)) {
			String containerNumberStr =
					containerStr.substring(0, containerStr.length() - 1);

			try {
				int containerNumber = Integer.parseInt(containerNumberStr);
				int number = Integer.parseInt(numberStr);

				return containerNumber <= number;
			} catch (NumberFormatException nfe) {
				return false;
			}
		}
		return false;
	}

	private static final String _SEPARATOR = StringPool.PERIOD;

	private static Map _versions = CollectionFactory.getSyncHashMap();

	private String _major;
	private String _minor;
	private String _bugFix;
	private String _buildNumber;

}