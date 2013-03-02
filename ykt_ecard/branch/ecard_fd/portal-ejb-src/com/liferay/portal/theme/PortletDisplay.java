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

package com.liferay.portal.theme;

import com.liferay.util.StringPool;

import java.io.Serializable;

import javax.portlet.PortletURL;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletDisplay.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.21 $
 *
 */
public class PortletDisplay implements Cloneable, Serializable {

	public String getId() {
		return _id;
	}

	public void setId(String id) {
		_id = id;
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		_title = title;
	}

	public int getWidth() {
		return _width;
	}

	public void setWidth(int width) {
		_width = width;
	}

	public boolean isNarrow() {
		return _narrow;
	}

	public void setNarrow(boolean narrow) {
		_narrow = narrow;
	}

	public boolean isAccess() {
		return _access;
	}

	public void setAccess(boolean access) {
		_access = access;
	}

	public boolean isActive() {
		return _active;
	}

	public void setActive(boolean active) {
		_active = active;
	}

	public String getCurColumnOrder() {
		return _curColumnOrder;
	}

	public void setCurColumnOrder(String curColumnOrder) {
		_curColumnOrder = curColumnOrder;
	}

	public int getCurColumnPos() {
		return _curColumnPos;
	}

	public void setCurColumnPos(int curColumnPos) {
		_curColumnPos = curColumnPos;
	}

	public int getCurColumnCount() {
		return _curColumnCount;
	}

	public void setCurColumnCount(int curColumnCount) {
		_curColumnCount = curColumnCount;
	}

	public boolean isStateMax() {
		return _stateMax;
	}

	public void setStateMax(boolean stateMax) {
		_stateMax = stateMax;
	}

	public boolean isStateMin() {
		return _stateMin;
	}

	public void setStateMin(boolean stateMin) {
		_stateMin = stateMin;
	}

	public boolean isStatePopUp() {
		return _statePopUp;
	}

	public void setStatePopUp(boolean statePopUp) {
		_statePopUp = statePopUp;
	}

	public boolean isModeAbout() {
		return _modeAbout;
	}

	public void setModeAbout(boolean modeAbout) {
		_modeAbout = modeAbout;
	}

	public boolean isModeConfig() {
		return _modeConfig;
	}

	public void setModeConfig(boolean modeConfig) {
		_modeConfig = modeConfig;
	}

	public boolean isModeEdit() {
		return _modeEdit;
	}

	public void setModeEdit(boolean modeEdit) {
		_modeEdit = modeEdit;
	}

	public boolean isModeEditDefaults() {
		return _modeEditDefaults;
	}

	public void setModeEditDefaults(boolean modeEditDefaults) {
		_modeEditDefaults = modeEditDefaults;
	}

	public boolean isModeHelp() {
		return _modeHelp;
	}

	public void setModeHelp(boolean modeHelp) {
		_modeHelp = modeHelp;
	}

	public boolean isModePreview() {
		return _modePreview;
	}

	public void setModePreview(boolean modePreview) {
		_modePreview = modePreview;
	}

	public boolean isModePrint() {
		return _modePrint;
	}

	public void setModePrint(boolean modePrint) {
		_modePrint = modePrint;
	}

	public boolean isShowEditIcon() {
		return _showEditIcon;
	}

	public void setShowEditIcon(boolean showEditIcon) {
		_showEditIcon = showEditIcon;
	}

	public boolean isShowHelpIcon() {
		return _showHelpIcon;
	}

	public void setShowHelpIcon(boolean showHelpIcon) {
		_showHelpIcon = showHelpIcon;
	}

	public boolean isShowMoveIcon() {
		return _showMoveIcon;
	}

	public void setShowMoveIcon(boolean showMoveIcon) {
		_showMoveIcon = showMoveIcon;
	}

	public boolean isShowMinIcon() {
		return _showMinIcon;
	}

	public void setShowMinIcon(boolean showMinIcon) {
		_showMinIcon = showMinIcon;
	}

	public boolean isShowMaxIcon() {
		return _showMaxIcon;
	}

	public void setShowMaxIcon(boolean showMaxIcon) {
		_showMaxIcon = showMaxIcon;
	}

	public boolean isShowCloseIcon() {
		return _showCloseIcon;
	}

	public void setShowCloseIcon(boolean showCloseIcon) {
		_showCloseIcon = showCloseIcon;
	}

	public PortletURL getURLEdit() {
		return _urlEdit;
	}

	public void setURLEdit(PortletURL urlEdit) {
		_urlEdit = urlEdit;
	}

	public PortletURL getURLHelp() {
		return _urlHelp;
	}

	public void setURLHelp(PortletURL urlHelp) {
		_urlHelp = urlHelp;
	}

	public PortletURL getURLMax() {
		return _urlMax;
	}

	public void setURLMax(PortletURL urlMax) {
		_urlMax = urlMax;
	}

	public boolean isRestoreCurrentView() {
		return _restoreCurrentView;
	}

	public void setRestoreCurrentView(boolean restoreCurrentView) {
		_restoreCurrentView = restoreCurrentView;
	}

	public void recycle() {
		_log.debug("Recycling instance " + hashCode());

		_id = StringPool.BLANK;
		_title = null;
		_width = 0;
		_narrow = false;
		_access = false;
		_active = false;
		_curColumnOrder = null;
		_stateMax = false;
		_stateMin = false;
		_statePopUp = false;
		_modeAbout = false;
		_modeConfig = false;
		_modeEdit = false;
		_modeEditDefaults = false;
		_modeHelp = false;
		_modePreview = false;
		_modePrint = false;
		_showEditIcon = false;
		_showHelpIcon = false;
		_showMoveIcon = false;
		_showMinIcon = false;
		_showMaxIcon = false;
		_showCloseIcon = false;
		_urlEdit = null;
		_urlHelp = null;
		_urlMax = null;
		_restoreCurrentView = false;
	}

	public void copyFrom(PortletDisplay master) {
		_id = master.getId();
		_title = master.getTitle();
		_width = master.getWidth();
		_narrow = master.isNarrow();
		_access = master.isAccess();
		_active = master.isActive();
		_curColumnOrder = master.getCurColumnOrder();
		_stateMax = master.isStateMax();
		_stateMin = master.isStateMin();
		_statePopUp = master.isStatePopUp();
		_modeAbout = master.isModeAbout();
		_modeConfig = master.isModeConfig();
		_modeEdit = master.isModeEdit();
		_modeEditDefaults = master.isModeEditDefaults();
		_modeHelp = master.isModeHelp();
		_modePreview = master.isModePreview();
		_modePrint = master.isModePrint();
		_showEditIcon = master.isShowEditIcon();
		_showHelpIcon = master.isShowHelpIcon();
		_showMoveIcon = master.isShowMoveIcon();
		_showMinIcon = master.isShowMinIcon();
		_showMaxIcon = master.isShowMaxIcon();
		_showCloseIcon = master.isShowCloseIcon();
		_urlEdit = master.getURLEdit();
		_urlHelp = master.getURLHelp();
		_urlMax = master.getURLMax();
		_restoreCurrentView = master.isRestoreCurrentView();
	}

	public void copyTo(PortletDisplay slave) {
		slave.setId(_id);
		slave.setId(_id );
		slave.setTitle(_title);
		slave.setWidth(_width);
		slave.setNarrow(_narrow);
		slave.setAccess(_access);
		slave.setActive(_active);
		slave.setCurColumnOrder(_curColumnOrder);
		slave.setStateMax(_stateMax);
		slave.setStateMin(_stateMin);
		slave.setStatePopUp(_statePopUp);
		slave.setModeAbout(_modeAbout);
		slave.setModeConfig(_modeConfig);
		slave.setModeEdit(_modeEdit);
		slave.setModeEditDefaults(_modeEditDefaults);
		slave.setModeHelp(_modeHelp);
		slave.setModePreview(_modePreview);
		slave.setModePrint(_modePrint);
		slave.setShowEditIcon(_showEditIcon);
		slave.setShowHelpIcon(_showHelpIcon);
		slave.setShowMoveIcon(_showMoveIcon);
		slave.setShowMinIcon(_showMinIcon);
		slave.setShowMaxIcon(_showMaxIcon);
		slave.setShowCloseIcon(_showCloseIcon);
		slave.setURLEdit(_urlEdit);
		slave.setURLHelp(_urlHelp);
		slave.setURLMax(_urlMax);
		slave.setRestoreCurrentView(_restoreCurrentView);
	}

	public Object clone() {
		PortletDisplay clone = null;

		try {
			clone = PortletDisplayFactory.create();

			copyTo(clone);
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}

		return clone;
	}

	protected PortletDisplay() {
		_log.debug("Creating new instance " + hashCode());
	}

	private static final Log _log = LogFactory.getLog(PortletDisplay.class);

	private String _id = StringPool.BLANK;
	private String _title;
	private int _width;
	private boolean _narrow;
	private boolean _access;
	private boolean _active;
	private String _curColumnOrder;
	private int _curColumnPos;
	private int _curColumnCount;
	private boolean _stateMax;
	private boolean _stateMin;
	private boolean _statePopUp;
	private boolean _modeAbout;
	private boolean _modeConfig;
	private boolean _modeEdit;
	private boolean _modeEditDefaults;
	private boolean _modeHelp;
	private boolean _modePreview;
	private boolean _modePrint;
	private boolean _showEditIcon;
	private boolean _showHelpIcon;
	private boolean _showMoveIcon;
	private boolean _showMinIcon;
	private boolean _showMaxIcon;
	private boolean _showCloseIcon;
	private PortletURL _urlEdit;
	private PortletURL _urlHelp;
	private PortletURL _urlMax;
	private boolean _restoreCurrentView;

}