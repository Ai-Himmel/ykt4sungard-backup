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

package com.liferay.portal.model;

import com.liferay.portal.SystemException;

import java.util.List;

/**
 * <a href="LayoutTypePortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface LayoutTypePortlet extends LayoutType {

	public LayoutTemplate getLayoutTemplate();

	public String getLayoutTemplateId();

	public void setLayoutTemplateId(long userId, String newLayoutTemplateId);

	public void setLayoutTemplateId(
		long userId, String newLayoutTemplateId, boolean checkPermission);

	public int getNumOfColumns();

	public List getAllPortlets(String columnId) throws SystemException;

	public List addStaticPortlets(
			List portlets, List startPortlets, List endPortlets)
		throws SystemException;

	public String addPortletId(long userId, String portletId);

	public String addPortletId(
		long userId, String portletId, boolean checkPermission);

	public String addPortletId(
		long userId, String portletId, String columnId, int columnPos);

	public String addPortletId(
		long userId, String portletId, String columnId, int columnPos,
		boolean checkPermission);

	public void addPortletIds(
		long userId, String[] portletIds, boolean checkPermission);

	public void addPortletIds(
		long userId, String[] portletIds, String columnId,
		boolean checkPermission);

	public List getPortlets() throws SystemException;

	public List getPortletIds();

	public boolean hasPortletId(String portletId);

	public void movePortletId(
		long userId, String portletId, String columnId, int columnPos);

	public void removePortletId(String portletId);

	public void removePortletId(String portletId, boolean modeAndState);

	public void setPortletIds(String columnId, String portletIds);

	public void reorganizeNestedColumns(
		String portletId, List newColumns, List oldColumns);

	public void reorganizePortlets(List newColumns, List oldColumns);

	public String getStateMax();

	public void setStateMax(String stateMax);

	public boolean hasStateMax();

	public void addStateMaxPortletId(String portletId);

	public String getStateMaxPortletId();

	public boolean hasStateMaxPortletId(String portletId);

	public void removeStateMaxPortletId(String portletId);

	public String getStateMaxPrevious();

	public void setStateMaxPrevious(String stateMaxPrevious);

	public void removeStateMaxPrevious();

	public String getStateMin();

	public void setStateMin(String stateMin);

	public boolean hasStateMin();

	public void addStateMinPortletId(String portletId);

	public boolean hasStateMinPortletId(String portletId);

	public void removeStateMinPortletId(String portletId);

	public boolean hasStateNormalPortletId(String portletId);

	public void resetStates();

	public void removeStatesPortletId(String portletId);

	public String getModeAbout();

	public void setModeAbout(String modeAbout);

	public void addModeAboutPortletId(String portletId);

	public boolean hasModeAboutPortletId(String portletId);

	public void removeModeAboutPortletId(String portletId);

	public String getModeConfig();

	public void setModeConfig(String modeConfig);

	public void addModeConfigPortletId(String portletId);

	public boolean hasModeConfigPortletId(String portletId);

	public void removeModeConfigPortletId(String portletId);

	public String getModeEdit();

	public void setModeEdit(String modeEdit);

	public void addModeEditPortletId(String portletId);

	public boolean hasModeEditPortletId(String portletId);

	public void removeModeEditPortletId(String portletId);

	public String getModeEditDefaults();

	public void setModeEditDefaults(String modeEditDefaults);

	public void addModeEditDefaultsPortletId(String portletId);

	public boolean hasModeEditDefaultsPortletId(String portletId);

	public void removeModeEditDefaultsPortletId(String portletId);

	public String getModeEditGuest();

	public void setModeEditGuest(String modeEditGuest);

	public void addModeEditGuestPortletId(String portletId);

	public boolean hasModeEditGuestPortletId(String portletId);

	public void removeModeEditGuestPortletId(String portletId);

	public String getModeHelp();

	public void setModeHelp(String modeHelp);

	public void addModeHelpPortletId(String portletId);

	public boolean hasModeHelpPortletId(String portletId);

	public void removeModeHelpPortletId(String portletId);

	public String getModePreview();

	public void setModePreview(String modePreview);

	public void addModePreviewPortletId(String portletId);

	public boolean hasModePreviewPortletId(String portletId);

	public void removeModePreviewPortletId(String portletId);

	public String getModePrint();

	public void setModePrint(String modePrint);

	public void addModePrintPortletId(String portletId);

	public boolean hasModePrintPortletId(String portletId);

	public void removeModePrintPortletId(String portletId);

	public boolean hasModeViewPortletId(String portletId);

	public void resetModes();

	public void removeModesPortletId(String portletId);

	public void removeNestedColumns(String portletId);

}