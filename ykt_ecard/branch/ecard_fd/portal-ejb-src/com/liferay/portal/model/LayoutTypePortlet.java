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

package com.liferay.portal.model;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.PwdGenerator;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.List;
import java.util.Properties;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LayoutTypePortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class LayoutTypePortlet extends LayoutType {

	public static final String COLUMN_ORDER = "column-order";

	public static final String NARROW_1 = "narrow-1";

	public static final String NARROW_2 = "narrow-2";

	public static final String WIDE_1 = "wide-1";

	public static final String WIDE_2 = "wide-2";

	public static final String STATE_MAX = "state-max";

	public static final String STATE_MIN = "state-min";

	public static final String MODE_ABOUT = "mode-about";

	public static final String MODE_CONFIG = "mode-config";

	public static final String MODE_EDIT = "mode-edit";

	public static final String MODE_EDIT_DEFAULTS = "mode-edit-defaults";

	public static final String MODE_HELP = "mode-help";

	public static final String MODE_PREVIEW = "mode-preview";

	public static final String MODE_PRINT = "mode-print";

	public LayoutTypePortlet(Layout layout) {
		super(layout);

		setColumnOrder(getColumnOrder());
	}

	public String getColumnOrder() {
		return getTypeSettingsProperties().getProperty(COLUMN_ORDER);
	}

	public void setColumnOrder(String columnOrder) {
		if (Validator.isNull(columnOrder)) {
			columnOrder = PropsUtil.get(
				PropsUtil.DEFAULT_USER_LAYOUT_COLUMN_ORDER);
		}

		_numOfColumns = StringUtil.split(columnOrder).length;

		getTypeSettingsProperties().setProperty(COLUMN_ORDER, columnOrder);
	}

	public int getNumOfColumns() {
		return _numOfColumns;
	}

	public Portlet[] getPortlets() throws PortalException, SystemException {
		Portlet[] narrow1Portlets = getNarrow1Portlets();
		Portlet[] narrow2Portlets = getNarrow2Portlets();
		Portlet[] wide1Portlets = getWide1Portlets();
		Portlet[] wide2Portlets = getWide2Portlets();

		Portlet[] portlets = new Portlet[
			narrow1Portlets.length + narrow2Portlets.length +
				wide1Portlets.length + wide2Portlets.length];

		System.arraycopy(
			narrow1Portlets, 0, portlets, 0, narrow1Portlets.length);

		System.arraycopy(
			narrow2Portlets, 0, portlets, narrow1Portlets.length,
			narrow2Portlets.length);

		System.arraycopy(
			wide1Portlets, 0, portlets,
			narrow1Portlets.length + narrow2Portlets.length,
			wide1Portlets.length);

		System.arraycopy(
			wide2Portlets, 0, portlets,
			narrow1Portlets.length + narrow2Portlets.length +
				wide1Portlets.length,
			wide2Portlets.length);

		return portlets;
	}

	public Portlet[] addStaticPortlets(
			Portlet[] portlets, String startPortletIds, String endPortletIds)
		throws PortalException, SystemException {

		// Static portlets that will be added to the start

		String[] startPortletIdsArray = StringUtil.split(startPortletIds);
		List startPortletsList = null;
		Set startPortletIdsSet = null;

		if (startPortletIdsArray.length > 0) {
			startPortletsList = new ArrayList();
			startPortletIdsSet = new HashSet();

			for (int i = 0; i < startPortletIdsArray.length; i++) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					getLayout().getCompanyId(), startPortletIdsArray[i]);

				if ((portlet != null) && (!portlet.isInstanceable())) {
					Portlet staticPortlet = (Portlet)portlet.clone();

					staticPortlet.setStatic(true);

					startPortletsList.add(staticPortlet);
					startPortletIdsSet.add(staticPortlet.getPortletId());
				}
			}
		}

		// Static portlets that will be added to the end

		String[] endPortletIdsArray = StringUtil.split(endPortletIds);
		List endPortletsList = null;
		Set endPortletIdsSet = null;

		if (endPortletIdsArray.length > 0) {
			endPortletsList = new ArrayList();
			endPortletIdsSet = new HashSet();

			for (int i = 0; i < endPortletIdsArray.length; i++) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					getLayout().getCompanyId(), endPortletIdsArray[i]);

				if ((portlet != null) && (!portlet.isInstanceable())) {
					Portlet staticPortlet = (Portlet)portlet.clone();

					staticPortlet.setStatic(true);

					endPortletsList.add(staticPortlet);
					endPortletIdsSet.add(staticPortlet.getPortletId());
				}
			}
		}

		// Return the original array of portlets if no static portlets are
		// specified

		if ((startPortletIdsArray.length == 0) &&
			(endPortletIdsArray.length == 0)) {

			return portlets;
		}

		// New array of portlets that contain the static portlets

		List portletsList = new ArrayList(
			portlets.length + startPortletIdsArray.length +
				endPortletIdsArray.length);

		if (startPortletsList != null) {
			portletsList.addAll(startPortletsList);
		}

		for (int i = 0; i < portlets.length; i++) {
			Portlet portlet = portlets[i];
			String portletId = portlet.getPortletId();

			// Add the portlet if and only if it is not also a static portlet

			if (((startPortletIdsSet == null) ||
					(!startPortletIdsSet.contains(portletId))) &&
				((endPortletIdsSet == null) ||
					(!endPortletIdsSet.contains(portletId)))) {

				portletsList.add(portlet);
			}
		}

		if (endPortletsList != null) {
			portletsList.addAll(endPortletsList);
		}

		return (Portlet[])portletsList.toArray(new Portlet[0]);
	}

	// Narrow 1

	public String getNarrow1() {
		return getTypeSettingsProperties().getProperty(NARROW_1);
	}

	public void setNarrow1(String narrow1) {
		getTypeSettingsProperties().setProperty(NARROW_1, narrow1);
	}

	public Portlet[] getNarrow1Portlets()
		throws PortalException, SystemException {

		return _getPortlets(getNarrow1());
	}

	public void setNarrow1Portlets(Portlet[] portlets) {
		setNarrow1(StringUtil.merge(_getPortletIds(portlets)));
	}

	// Narrow 2

	public String getNarrow2() {
		return getTypeSettingsProperties().getProperty(NARROW_2);
	}

	public void setNarrow2(String narrow2) {
		getTypeSettingsProperties().setProperty(NARROW_2, narrow2);
	}

	public Portlet[] getNarrow2Portlets()
		throws PortalException, SystemException {

		return _getPortlets(getNarrow2());
	}

	public void setNarrow2Portlets(Portlet[] portlets) {
		setNarrow2(StringUtil.merge(_getPortletIds(portlets)));
	}

	// Wide 1

	public String getWide1() {
		return getTypeSettingsProperties().getProperty(WIDE_1);
	}

	public void setWide1(String wide1) {
		getTypeSettingsProperties().setProperty(WIDE_1, wide1);
	}

	public Portlet[] getWide1Portlets()
		throws PortalException, SystemException {

		return _getPortlets(getWide1());
	}

	public void setWide1Portlets(Portlet[] portlets) {
		setWide1(StringUtil.merge(_getPortletIds(portlets)));
	}

	// Wide 2

	public String getWide2() {
		return getTypeSettingsProperties().getProperty(WIDE_2);
	}

	public void setWide2(String wide2) {
		getTypeSettingsProperties().setProperty(WIDE_2, wide2);
	}

	public Portlet[] getWide2Portlets()
		throws PortalException, SystemException {

		return _getPortlets(getWide2());
	}

	public void setWide2Portlets(Portlet[] portlets) {
		setWide2(StringUtil.merge(_getPortletIds(portlets)));
	}

	// Qualify portlet ids

	public String qualifyPortletIds(String portletIds)
		throws PortalException, SystemException {

		String[] portletIdsArray = StringUtil.split(portletIds);

		for (int i = 0; i < portletIdsArray.length; i++) {
			String portletId = portletIdsArray[i];

			if (!hasPortletId(portletIdsArray[i])) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					getLayout().getCompanyId(), portletId);

				if (portlet.isInstanceable()) {
					portletIdsArray[i] = portletId + _getInstanceSeparator();
				}
			}
		}

		portletIds = StringUtil.merge(portletIdsArray);

		return portletIds;
	}

	// Modify portlets

	public void addPortletId(String portletId) {
		addPortletId(portletId, StringPool.BLANK);
	}

	public void addPortletId(String portletId, String curColumnOrder) {
		Portlet portlet = null;

		try {
			portlet = PortletServiceUtil.getPortletById(
				getLayout().getCompanyId(), portletId);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		if (portlet != null) {
			if (portlet.isInstanceable()) {
				portletId = portletId + _getInstanceSeparator();
			}

			if (Validator.isNull(curColumnOrder)) {
				if (portlet.isNarrow()) {
					curColumnOrder = "n1";
				}
				else {
					curColumnOrder = "w1";
				}
			}

			if (curColumnOrder.equals("n1")) {
				setNarrow1(StringUtil.add(getNarrow1(), portletId));
			}
			else if (curColumnOrder.equals("n2")) {
				setNarrow2(StringUtil.add(getNarrow2(), portletId));
			}
			else if (curColumnOrder.equals("w1")) {
				setWide1(StringUtil.add(getWide1(), portletId));
			}
		}
	}

	public String[] getPortletIds() {
		String[] narrow1 = StringUtil.split(getNarrow1());
		String[] narrow2 = StringUtil.split(getNarrow2());
		String[] wide1 = StringUtil.split(getWide1());
		String[] wide2 = StringUtil.split(getWide2());

		String[] portletIds = new String[
			narrow1.length + narrow2.length + wide1.length + wide2.length];

		System.arraycopy(narrow1, 0, portletIds, 0, narrow1.length);

		System.arraycopy(
			narrow2, 0, portletIds, narrow1.length, narrow2.length);

		System.arraycopy(
			wide1, 0, portletIds, narrow1.length + narrow2.length,
			wide1.length);

		System.arraycopy(
			wide2, 0, portletIds,
			narrow1.length + narrow2.length + wide1.length, wide2.length);

		return portletIds;
	}

	public boolean hasPortletId(String portletId) {
		if (StringUtil.contains(getNarrow1(), portletId) ||
			StringUtil.contains(getNarrow2(), portletId) ||
			StringUtil.contains(getWide1(), portletId) ||
			StringUtil.contains(getWide2(), portletId)) {

			return true;
		}
		else {
			return false;
		}
	}

	public void movePortletIdDown(String portletId) {
		if (StringUtil.contains(getNarrow1(), portletId)) {
			setNarrow1(movePortletIdDown(
				StringUtil.split(getNarrow1()), portletId));
		}
		else if (StringUtil.contains(getNarrow2(), portletId)) {
			setNarrow2(movePortletIdDown(
				StringUtil.split(getNarrow2()), portletId));
		}
		else if (StringUtil.contains(getWide1(), portletId)) {
			setWide1(movePortletIdDown(
				StringUtil.split(getWide1()), portletId));
		}
		else if (StringUtil.contains(getWide2(), portletId)) {
			setWide2(movePortletIdDown(
				StringUtil.split(getWide2()), portletId));
		}
	}

	public String movePortletIdDown(String[] portletIds, String portletId) {
		for (int i = 0; i < portletIds.length && portletIds.length > 1; i++) {
			if (portletIds[i].equals(portletId)) {
				if (i != portletIds.length - 1) {
					portletIds[i] = portletIds[i + 1];
					portletIds[i + 1] = portletId;
				}
				else {
					portletIds[i] = portletIds[0];
					portletIds[0] = portletId;
				}

				break;
			}
		}

		return StringUtil.merge(portletIds);
	}

	public void movePortletIdUp(String portletId) {
		if (StringUtil.contains(getNarrow1(), portletId)) {
			setNarrow1(movePortletIdUp(
				StringUtil.split(getNarrow1()), portletId));
		}
		else if (StringUtil.contains(getNarrow2(), portletId)) {
			setNarrow2(movePortletIdUp(
				StringUtil.split(getNarrow2()), portletId));
		}
		else if (StringUtil.contains(getWide1(), portletId)) {
			setWide1(movePortletIdUp(
				StringUtil.split(getWide1()), portletId));
		}
		else if (StringUtil.contains(getWide2(), portletId)) {
			setWide2(movePortletIdUp(
				StringUtil.split(getWide2()), portletId));
		}
	}

	public String movePortletIdUp(String[] portletIds, String portletId) {
		for (int i = 0; i < portletIds.length && portletIds.length > 1; i++) {
			if (portletIds[i].equals(portletId)) {
				if (i != 0) {
					portletIds[i] = portletIds[i - 1];
					portletIds[i - 1] = portletId;
				}
				else {
					portletIds[0] = portletIds[portletIds.length - 1];
					portletIds[portletIds.length - 1] = portletId;
				}

				break;
			}
		}

		return StringUtil.merge(portletIds);
	}

	public void removePortletId(String portletId) {
		setNarrow1(StringUtil.remove(getNarrow1(), portletId));
		setNarrow2(StringUtil.remove(getNarrow2(), portletId));
		setWide1(StringUtil.remove(getWide1(), portletId));
		setWide2(StringUtil.remove(getWide2(), portletId));
		removeStatesPortletId(portletId);
		removeModesPortletId(portletId);
	}

	// Maximized state

	public String getStateMax() {
		return getTypeSettingsProperties().getProperty(STATE_MAX);
	}

	public void setStateMax(String stateMax) {
		getTypeSettingsProperties().setProperty(STATE_MAX, stateMax);
	}

	public boolean hasStateMax() {
		String[] stateMax = StringUtil.split(getStateMax());

		if (stateMax.length > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addStateMaxPortletId(String portletId) {
		removeStatesPortletId(portletId);
		//setStateMax(StringUtil.add(getStateMax(), portletId));
		setStateMax(StringUtil.add(StringPool.BLANK, portletId));
	}

	public boolean hasStateMaxPortletId(String portletId) {
		if (StringUtil.contains(getStateMax(), portletId)) {
			return true;
		}
		else {
			return false;
		}
	}

	public void removeStateMaxPortletId(String portletId) {
		setStateMax(StringUtil.remove(getStateMax(), portletId));
	}

	// Minimized state

	public String getStateMin() {
		return getTypeSettingsProperties().getProperty(STATE_MIN);
	}

	public void setStateMin(String stateMin) {
		getTypeSettingsProperties().setProperty(STATE_MIN, stateMin);
	}

	public boolean hasStateMin() {
		String[] stateMin = StringUtil.split(getStateMin());

		if (stateMin.length > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addStateMinPortletId(String portletId) {
		removeStateMaxPortletId(portletId);
		setStateMin(StringUtil.add(getStateMin(), portletId));
	}

	public boolean hasStateMinPortletId(String portletId) {
		if (StringUtil.contains(getStateMin(), portletId)) {
			return true;
		}
		else {
			return false;
		}
	}

	public void removeStateMinPortletId(String portletId) {
		setStateMin(StringUtil.remove(getStateMin(), portletId));
	}

	// Normal state

	public boolean hasStateNormalPortletId(String portletId) {
		if (hasStateMaxPortletId(portletId) ||
			hasStateMinPortletId(portletId)) {

			return false;
		}
		else {
			return true;
		}
	}

	// All states

	public void resetStates() {
		setStateMax(StringPool.BLANK);
		setStateMin(StringPool.BLANK);
	}

	public void removeStatesPortletId(String portletId) {
		removeStateMaxPortletId(portletId);
		removeStateMinPortletId(portletId);
	}

	// About mode

	public String getModeAbout() {
		return getTypeSettingsProperties().getProperty(MODE_ABOUT);
	}

	public void setModeAbout(String modeAbout) {
		getTypeSettingsProperties().setProperty(MODE_ABOUT, modeAbout);
	}

	public void addModeAboutPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModeAbout(StringUtil.add(getModeAbout(), portletId));
	}

	public boolean hasModeAboutPortletId(String portletId) {
		return StringUtil.contains(getModeAbout(), portletId);
	}

	public void removeModeAboutPortletId(String portletId) {
		setModeAbout(StringUtil.remove(getModeAbout(), portletId));
	}

	// Config mode

	public String getModeConfig() {
		return getTypeSettingsProperties().getProperty(MODE_CONFIG);
	}

	public void setModeConfig(String modeConfig) {
		getTypeSettingsProperties().setProperty(MODE_CONFIG, modeConfig);
	}

	public void addModeConfigPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModeConfig(StringUtil.add(getModeConfig(), portletId));
	}

	public boolean hasModeConfigPortletId(String portletId) {
		return StringUtil.contains(getModeConfig(), portletId);
	}

	public void removeModeConfigPortletId(String portletId) {
		setModeConfig(StringUtil.remove(getModeConfig(), portletId));
	}

	// Edit mode

	public String getModeEdit() {
		return getTypeSettingsProperties().getProperty(MODE_EDIT);
	}

	public void setModeEdit(String modeEdit) {
		getTypeSettingsProperties().setProperty(MODE_EDIT, modeEdit);
	}

	public void addModeEditPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModeEdit(StringUtil.add(getModeEdit(), portletId));
	}

	public boolean hasModeEditPortletId(String portletId) {
		return StringUtil.contains(getModeEdit(), portletId);
	}

	public void removeModeEditPortletId(String portletId) {
		setModeEdit(StringUtil.remove(getModeEdit(), portletId));
	}

	// Edit defaults mode

	public String getModeEditDefaults() {
		return getTypeSettingsProperties().getProperty(MODE_EDIT_DEFAULTS);
	}

	public void setModeEditDefaults(String modeEditDefaults) {
		getTypeSettingsProperties().setProperty(
			MODE_EDIT_DEFAULTS, modeEditDefaults);
	}

	public void addModeEditDefaultsPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModeEditDefaults(StringUtil.add(getModeEditDefaults(), portletId));
	}

	public boolean hasModeEditDefaultsPortletId(String portletId) {
		return StringUtil.contains(getModeEditDefaults(), portletId);
	}

	public void removeModeEditDefaultsPortletId(String portletId) {
		setModeEditDefaults(
			StringUtil.remove(getModeEditDefaults(), portletId));
	}

	// Help mode

	public String getModeHelp() {
		return getTypeSettingsProperties().getProperty(MODE_HELP);
	}

	public void setModeHelp(String modeHelp) {
		getTypeSettingsProperties().setProperty(MODE_HELP, modeHelp);
	}

	public void addModeHelpPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModeHelp(StringUtil.add(getModeHelp(), portletId));
	}

	public boolean hasModeHelpPortletId(String portletId) {
		return StringUtil.contains(getModeHelp(), portletId);
	}

	public void removeModeHelpPortletId(String portletId) {
		setModeHelp(StringUtil.remove(getModeHelp(), portletId));
	}

	// Preview mode

	public String getModePreview() {
		return getTypeSettingsProperties().getProperty(MODE_PREVIEW);
	}

	public void setModePreview(String modePreview) {
		getTypeSettingsProperties().setProperty(MODE_PREVIEW, modePreview);
	}

	public void addModePreviewPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModePreview(StringUtil.add(getModePreview(), portletId));
	}

	public boolean hasModePreviewPortletId(String portletId) {
		return StringUtil.contains(getModePreview(), portletId);
	}

	public void removeModePreviewPortletId(String portletId) {
		setModePreview(StringUtil.remove(getModePreview(), portletId));
	}

	// Print mode

	public String getModePrint() {
		return getTypeSettingsProperties().getProperty(MODE_PRINT);
	}

	public void setModePrint(String modePrint) {
		getTypeSettingsProperties().setProperty(MODE_PRINT, modePrint);
	}

	public void addModePrintPortletId(String portletId) {
		removeModesPortletId(portletId);
		setModePrint(StringUtil.add(getModePrint(), portletId));
	}

	public boolean hasModePrintPortletId(String portletId) {
		return StringUtil.contains(getModePrint(), portletId);
	}

	public void removeModePrintPortletId(String portletId) {
		setModePrint(StringUtil.remove(getModePrint(), portletId));
	}

	// View mode

	public boolean hasModeViewPortletId(String portletId) {
		if (hasModeAboutPortletId(portletId) ||
			hasModeConfigPortletId(portletId) ||
			hasModeEditPortletId(portletId) ||
			hasModeEditDefaultsPortletId(portletId) ||
			hasModeHelpPortletId(portletId) ||
			hasModePreviewPortletId(portletId) ||
			hasModePrintPortletId(portletId)) {

			return false;
		}
		else {
			return true;
		}
	}

	// All modes

	public void resetModes() {
		setModeAbout(StringPool.BLANK);
		setModeConfig(StringPool.BLANK);
		setModeEdit(StringPool.BLANK);
		setModeEditDefaults(StringPool.BLANK);
		setModeHelp(StringPool.BLANK);
		setModePreview(StringPool.BLANK);
		setModePrint(StringPool.BLANK);
	}

	public void removeModesPortletId(String portletId) {
		removeModeAboutPortletId(portletId);
		removeModeConfigPortletId(portletId);
		removeModeEditPortletId(portletId);
		removeModeEditDefaultsPortletId(portletId);
		removeModeHelpPortletId(portletId);
		removeModePreviewPortletId(portletId);
		removeModePrintPortletId(portletId);
	}

	// Private methods

	private String _getInstanceSeparator() {
		String instanceId = PwdGenerator.getPassword(
			PwdGenerator.KEY1 + PwdGenerator.KEY2 + PwdGenerator.KEY3, 4);

		return Portlet.INSTANCE_SEPARATOR + instanceId;
	}

	private String[] _getPortletIds(Portlet[] portlets) {
		String[] portletIds = new String[portlets.length];

		for (int i = 0; i < portlets.length; i++) {
			portletIds[i] = portlets[i].getPortletId();
		}

		return portletIds;
	}

	private Portlet[] _getPortlets(String portletIds)
		throws PortalException, SystemException {

		String[] portletIdsArray = StringUtil.split(portletIds);

		List portlets = new ArrayList(portletIdsArray.length);

		for (int i = 0; i < portletIdsArray.length; i++) {
			Portlet portlet = PortletServiceUtil.getPortletById(
				getLayout().getCompanyId(), portletIdsArray[i]);

			if (portlet != null) {
				portlets.add(portlet);
			}
		}

		return (Portlet[])portlets.toArray(new Portlet[0]);
	}

	private static final Log _log = LogFactory.getLog(LayoutTypePortlet.class);

	private int _numOfColumns;

}