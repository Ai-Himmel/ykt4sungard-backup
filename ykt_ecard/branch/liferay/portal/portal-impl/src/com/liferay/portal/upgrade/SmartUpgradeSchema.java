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

package com.liferay.portal.upgrade;

import com.liferay.portal.kernel.util.InstancePool;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SmartUpgradeSchema.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class SmartUpgradeSchema extends UpgradeProcess {

	public void upgrade() throws UpgradeException {
		String smartUpgradeSchemaImplClassName = this.getClass().getName();

		if (_alreadyUpgraded) {
			_log.info(
				"Skipping " + smartUpgradeSchemaImplClassName +
					" because it has already been executed");

			return;
		}

		_alreadyUpgraded = true;

		try {
			upgradeOnce();

			boolean doUpgrade = false;

			for (int i = 0; i < _UPGRADE_PROGRESS_CLASSES.length; i++) {
				String curUpgradeSchemaClassName =
					_UPGRADE_PROGRESS_CLASSES[i].getName();

				if (doUpgrade) {
					SmartUpgradeSchema upgradeSchema =
						(SmartUpgradeSchema)InstancePool.get(
							curUpgradeSchemaClassName);

					if (!upgradeSchema.isAlreadyUpgraded()) {
						_log.info(
							"Automatically executing " +
								curUpgradeSchemaClassName);

						upgradeSchema.setAlreadyUpgraded(true);

						upgradeSchema.upgradeOnce();
					}
				}

				if (smartUpgradeSchemaImplClassName.equals(
						curUpgradeSchemaClassName)) {

					doUpgrade = true;
				}
			}
		}
		catch (Exception e) {
			throw new UpgradeException(e);
		}
	}

	protected boolean isAlreadyUpgraded() {
		return _alreadyUpgraded;
	}

	protected void setAlreadyUpgraded(boolean alreadyUpgraded) {
		_alreadyUpgraded = alreadyUpgraded;
	}

	protected abstract void upgradeOnce() throws Exception;

	private static final Class[] _UPGRADE_PROGRESS_CLASSES = new Class[] {
		com.liferay.portal.upgrade.v4_3_0.UpgradeSchema.class,
		com.liferay.portal.upgrade.v4_3_1.UpgradeSchema.class,
		com.liferay.portal.upgrade.v4_3_2.UpgradeSchema.class,
		com.liferay.portal.upgrade.v4_3_3.UpgradeSchema.class,
		com.liferay.portal.upgrade.v4_3_4.UpgradeSchema.class,
		com.liferay.portal.upgrade.v4_4_0.UpgradeSchema.class,
	};

	private static Log _log = LogFactory.getLog(SmartUpgradeSchema.class);

	private boolean _alreadyUpgraded;

}