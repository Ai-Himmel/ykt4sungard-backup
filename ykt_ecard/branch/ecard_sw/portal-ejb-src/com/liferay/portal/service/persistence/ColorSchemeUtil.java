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

package com.liferay.portal.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ColorSchemeUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ColorSchemeUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.ColorScheme"),
			"com.liferay.portal.service.persistence.ColorSchemePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.ColorScheme"));

	public static com.liferay.portal.model.ColorScheme create(
		java.lang.String colorSchemeId) {
		ColorSchemePersistence persistence = (ColorSchemePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(colorSchemeId);
	}

	public static com.liferay.portal.model.ColorScheme remove(
		java.lang.String colorSchemeId)
		throws com.liferay.portal.NoSuchColorSchemeException, 
			com.liferay.portal.SystemException {
		ColorSchemePersistence persistence = (ColorSchemePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(colorSchemeId));
		}

		com.liferay.portal.model.ColorScheme colorScheme = persistence.remove(colorSchemeId);

		if (listener != null) {
			listener.onAfterRemove(colorScheme);
		}

		return colorScheme;
	}

	public static com.liferay.portal.model.ColorScheme update(
		com.liferay.portal.model.ColorScheme colorScheme)
		throws com.liferay.portal.SystemException {
		ColorSchemePersistence persistence = (ColorSchemePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = colorScheme.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(colorScheme);
			}
			else {
				listener.onBeforeUpdate(colorScheme);
			}
		}

		colorScheme = persistence.update(colorScheme);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(colorScheme);
			}
			else {
				listener.onAfterUpdate(colorScheme);
			}
		}

		return colorScheme;
	}

	public static com.liferay.portal.model.ColorScheme findByPrimaryKey(
		java.lang.String colorSchemeId)
		throws com.liferay.portal.NoSuchColorSchemeException, 
			com.liferay.portal.SystemException {
		ColorSchemePersistence persistence = (ColorSchemePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(colorSchemeId);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		ColorSchemePersistence persistence = (ColorSchemePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	private static final Log _log = LogFactory.getLog(ColorSchemeUtil.class);
}