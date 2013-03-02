<%
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
%>

<c:if test="<%= (layouts != null) && (layouts.size() > 0) %>">
	<table width="1000" border="0" cellspacing="0" cellpadding="0">
	  <tr height="2">
	    <td></td>
	<%
	int tabNameMaxLength = GetterUtil.getInteger(PropsUtil.get(PropsUtil.LAYOUT_NAME_MAX_LENGTH));
	int tabsPerRow = GetterUtil.getInteger(PropsUtil.get(PropsUtil.LAYOUT_TABS_PER_ROW));
	int totalTabs = layouts.size();
	int totalTabRows = (totalTabs / tabsPerRow);

	if ((totalTabs % tabsPerRow) > 0) {
		totalTabRows++;
	}

	int tabLeftImageWidth = 9;
	int tabSeparatorWidth = 24;
	int tabRightImageWidth = 9;

	int layoutCounter = 0;
	int rowCounter = 0;
	int tabCounter = 0;

	int currentTab = 0;

	boolean isSelectedTab = false;
	boolean isPrevSelectedTab = false;

	int selectedRow = 0;
	int selectedTab = 0;

	String rows[][] = new String[totalTabRows][tabsPerRow];

	String ancestorLayoutId = "";
	if (layout != null) {
		ancestorLayoutId = layout.getAncestorLayoutId();
	}

	for (int i = 0; i < layouts.size(); i++) {
		Layout curLayout = (Layout)layouts.get(i);

		String tabName = StringUtil.shorten(curLayout.getName(), tabNameMaxLength);
		String tabToolTipName = curLayout.getName();
		String tabHREF = PortalUtil.getLayoutURL(curLayout, themeDisplay);
		boolean isGroupTab = curLayout.isGroup();
		isSelectedTab = selectable && (layout != null && (layoutId.equals(curLayout.getLayoutId()) || curLayout.getLayoutId().equals(ancestorLayoutId)));

		if (isSelectedTab && layoutTypePortlet.hasStateMax() && (layoutTypePortlet.getPortletIds().length > 1)) {
			String portletId = StringUtil.split(layoutTypePortlet.getStateMax())[0];

			PortletURLImpl portletURLImpl = new PortletURLImpl(request, portletId, layoutId, false);

			portletURLImpl.setWindowState(WindowState.NORMAL);
			portletURLImpl.setPortletMode(PortletMode.VIEW);
			portletURLImpl.setAnchor(false);

			tabHREF = portletURLImpl.toString();
		}

		String target = PortalUtil.getLayoutTarget(curLayout);

		String tabText = null;

		if (isSelectedTab) {%>
			<td bgcolor="#FEA66B"></td>
			<%
			tabText = "<td width=\"92\" height=\"35\" align=\"center\" bgcolor=\"#F5F9FF\"><a class=\"text_blue_14\" href=\"" + tabHREF + "\" " + target + ">" + tabName + "</a></td>";
			selectedRow = rowCounter;
			selectedTab = currentTab;
		}
		else {%>
			<td></td>
			<%			
			tabText = "<td width=\"92\" height=\"35\" align=\"center\" bgcolor=\"#3B639E\"><a class=\"w_14_link\" href=\"" + tabHREF + "\" " + target + ">" + tabName + "</a></td>";
		}

		rows[rowCounter][currentTab] = tabText;

		if (currentTab == tabsPerRow - 1) {
			rowCounter++;
			currentTab = 0;
		}
		else {
			currentTab++;
		}
	}

	// Reorder the array so the row with the selected tab is on the bottom row

	if (rows.length > 1) {
		Collections.swap(Arrays.asList(rows), selectedRow, rows.length - 1);
	}
	%>	  
		<td></td>
	  </tr>
	  <tr bgcolor="#3B639E">
	    <td bgcolor="#3B639E" height="35" width="3"></td>
	    <%

			// Render each row

			for (int i = 0; i < rows.length; i++) {

				// Calculate the number of tabs in this row

				int tabsInRow = 0;

				for (int j = 0; j < rows[i].length; j++) {
					if (rows[i][j] != null) {
						tabsInRow++;
					}
					else {
						break;
					}
				}

				// Calculate the tab width if there is only one tab

				int singleTabWidth = 0;

				if (layouts.size() == 1) {
					int tempTabRightImageWidth = tabRightImageWidth;
					tabRightImageWidth = tabSeparatorWidth;
					tabsInRow++;

					singleTabWidth = (themeDisplay.getResTotal() - (tabLeftImageWidth + tabRightImageWidth + (tabSeparatorWidth * (tabsInRow - 1)))) / tabsInRow;

					tabRightImageWidth = tempTabRightImageWidth;
					tabsInRow--;
				}

				// Render the tabs

				for (int j = 0; j < rows[i].length; j++) {
					String tabLeftImage = null;
					String tabRightImage = null;

					String tabImageMulti = (i == 0) ? StringPool.BLANK : "_multi";
					String tabImageOn = (isSelectedTab) ? "_on" : "_off";
					String tabImageSuffix = ".gif";

					// Set the tab images accroding to the total number of rows

					if (rows[i][j] != null) {

						// Are we on the selected tab?

						if (selectable && (i == rows.length - 1) && (j == selectedTab)) {
							isSelectedTab = true;
						}
						else {
							isSelectedTab = false;
						}

						tabImageOn = (isSelectedTab) ? "_on" : "_off";

						// Are we on the first tab in the row?

						if (j == 0) {
							tabLeftImage = "tab_left" + tabImageMulti + tabImageOn + tabImageSuffix;
						}
						else {
							if (isPrevSelectedTab) {
								tabLeftImage = "tab_join_right" + tabImageMulti + "_on.gif";
							}
							else {
								tabLeftImage = isSelectedTab ? "tab_join_left" + tabImageMulti + "_on" + tabImageSuffix : "tab_join_right" + tabImageMulti + "_off" + tabImageSuffix;
							}
						}

						// Are we on the last tab in the row?

						if (j == rows[i].length - 1) {
							tabRightImage = "tab_right" + tabImageMulti + tabImageOn + tabImageSuffix;
						}
						else {
							tabRightImage = "tab_join_right" + tabImageMulti + tabImageOn + tabImageSuffix;
						}

						// Set the tab's background image

						String tabBackgroundImage = isSelectedTab ? "tab_middle_on.gif" : "tab_middle" + tabImageMulti + "_off" + tabImageSuffix;

						// Set the previous selected tab flag, this is used to set the left image of the next tab

						isPrevSelectedTab = isSelectedTab;

						// Netscape 4 requires you to set the exact width

						int tabWidth = (themeDisplay.getResTotal() - (tabLeftImageWidth + tabRightImageWidth + (tabSeparatorWidth * (tabsInRow - 1)))) / tabsInRow;
						int tabWidthMod = (themeDisplay.getResTotal() - (tabLeftImageWidth + tabRightImageWidth + (tabSeparatorWidth * (tabsInRow - 1)))) % tabsInRow;

						if ((tabWidthMod > 0) && (j == (tabsInRow - 1))) {
							tabWidth += tabWidthMod;
						}

						// Make an exception if there is only one tab

						if (layouts.size() == 1) {
							tabWidth = singleTabWidth;
						}
			%>

				<%= rows[i][j] %>

			<%
					}
					else {
						if (j == rows[i].length - 1) {
							tabRightImage = "tab_right" + tabImageMulti + tabImageOn + tabImageSuffix;

							// Make an exception if there is only one tab

							if (layouts.size() == 1) {
								tabRightImage = "tab_right_single" + tabImageOn + tabImageSuffix;
							}
						}
					}
			%>


			<%
				}
			%>

				<c:if test="<%= layouts.size() == 1 %>">
					<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="<%= themeDisplay.getResTotal() - singleTabWidth - tabLeftImageWidth - tabSeparatorWidth %>"></td>
				</c:if>

			<%
			}
			%>	    
	    <td height="35" bgcolor="#3B639E">&nbsp;</td>
	  </tr>
	</table>
</c:if>