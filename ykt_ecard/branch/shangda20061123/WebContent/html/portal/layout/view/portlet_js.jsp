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

<script language="JavaScript">
	function addPortlet(layoutId, portletId, columnId) {
		self.location = "<%= themeDisplay.getPathMain() %>/portal/add_portlet?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId + "&#p_" + portletId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId + "&p_l_cur_co=" + columnId;
	}

	function buildColumnHTML(portletIds, columnId) {
		var html = "";

		for (var i = 0; i < portletIds.length; i++) {
			html += buildPortletHTML(portletIds[i]);
		}

		var columnEl = document.getElementById("layout-column_" + columnId);
		columnEl.innerHTML = html;
	}

	function buildPortletHTML(portletId) {
		var html = "";
		html += "<a name='p_" + portletId + "'></a>";
		html += "<div id='p_p_id_" + portletId + "_'>";
		html += document.getElementById("p_p_id_" + portletId + "_").innerHTML;
		html += "</div>";

		return html;
	}

	function closePortlet(layoutId, portletId, columnId) {
		if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-remove-this-component") %>')) {
			if (is_ns_4) {
				self.location = "<%= themeDisplay.getPathMain() %>/portal/remove_portlet?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId;
			}
			else {
				document.getElementById("p_p_id_" + portletId + "_").style.display = "none";

				if (columnId == "n1") {
					n1Portlets = closePortletId(n1Portlets, portletId);
				}
				else if (columnId == "n2") {
					n2Portlets = closePortletId(n2Portlets, portletId);
				}
				else if (columnId == "w1") {
					w1Portlets = closePortletId(w1Portlets, portletId);
				}

				<c:if test="<%= !layoutMaximized %>">
					loadPage("<%= themeDisplay.getPathMain() %>/portal/remove_portlet", "p_l_id=" + layoutId + "&p_p_id=" + portletId);
				</c:if>

				<c:if test="<%= layoutMaximized %>">
					self.location = "<%= themeDisplay.getPathMain() %>/portal/remove_portlet?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId;
				</c:if>

				eval("var portletTitle = portletTitles_" + columnId + "[portletId];");

				if (portletTitle != null) {
					eval("addItem(document.layout_" + columnId + "_fm.add_" + columnId + "_sel, portletTitles_" + columnId + "[portletId], portletId, true);");
				}
			}
		}
		else {
			self.focus();
		}
	}

	function closePortletId(portletIds, portletId) {
		var tempPortletIds = new Array();

		var count = 0;

		for (var i = 0; i < portletIds.length; i++) {
			if (portletIds[i] != portletId) {
				tempPortletIds[count++] = portletIds[i];
			}
		}

		return tempPortletIds;
	}

	function minimizePortlet(layoutId, portletId, restore) {
		if (is_ns_4) {
			self.location = "<%= themeDisplay.getPathMain() %>/portal/minimize_portlet?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId + "&#p_" + portletId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId + "&p_p_restore=" + restore;
		}
		else {
			<c:if test="<%= !layoutMaximized %>">
				if (restore) {
					document.getElementById("p_p_body_" + portletId).style.display = "";

					var buttonsEl = document.getElementById("p_p_body_" + portletId + "_min_buttons");

					var html = buttonsEl.innerHTML;
					html = html.replace(", true", ", false");
					html = html.replace("_restore", "_min");
					html = html.replace("_restore", "_min");
					html = html.replace("_restore", "_min");
					html = html.replace("<%= LanguageUtil.get(pageContext, "restore") %>", "<%= LanguageUtil.get(pageContext, "minimize") %>");

					buttonsEl.innerHTML = html;

					loadPage("<%= themeDisplay.getPathMain() %>/portal/minimize_portlet", "p_l_id=" + layoutId + "&p_p_id=" + portletId + "&p_p_restore=" + restore);
				}
				else {
					document.getElementById("p_p_body_" + portletId).style.display = "none";

					var buttonsEl = document.getElementById("p_p_body_" + portletId + "_min_buttons");

					var html = buttonsEl.innerHTML;
					html = html.replace(", false", ", true");
					html = html.replace("_min", "_restore");
					html = html.replace("_min", "_restore");
					html = html.replace("_min", "_restore");
					html = html.replace("<%= LanguageUtil.get(pageContext, "minimize") %>", "<%= LanguageUtil.get(pageContext, "restore") %>");

					buttonsEl.innerHTML = html;

					loadPage("<%= themeDisplay.getPathMain() %>/portal/minimize_portlet", "p_l_id=" + layoutId + "&p_p_id=" + portletId + "&p_p_restore=" + restore);
				}
			</c:if>

			<c:if test="<%= layoutMaximized %>">
				self.location = "<%= themeDisplay.getPathMain() %>/portal/minimize_portlet?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId + "&#p_" + portletId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId + "&p_p_restore=" + restore;
			</c:if>
		}
	}

	function movePortletDown(layoutId, portletId, columnId) {
		if (is_ns_4) {
			self.location = "<%= themeDisplay.getPathMain() %>/portal/move_portlet_down?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId + "&#p_" + portletId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId;
		}
		else {
			if (columnId == "n1") {
				movePortletIdDown(n1Portlets, n1PortletsStatic, portletId, columnId);
			}
			else if (columnId == "n2") {
				movePortletIdDown(n2Portlets, n2PortletsStatic, portletId, columnId);
			}
			else if (columnId == "w1") {
				movePortletIdDown(w1Portlets, w1PortletsStatic, portletId, columnId);
			}

			loadPage("<%= themeDisplay.getPathMain() %>/portal/move_portlet_down", "p_l_id=" + layoutId + "&p_p_id=" + portletId);
		}
	}

	function movePortletUp(layoutId, portletId, columnId) {
		if (is_ns_4) {
			self.location = "<%= themeDisplay.getPathMain() %>/portal/move_portlet_up?referer=" + encodeURIComponent("<%= themeDisplay.getPathMain() %>/portal/layout?p_l_id=" + layoutId + "&#p_" + portletId) + "&p_l_id=" + layoutId + "&p_p_id=" + portletId;
		}
		else {
			if (columnId == "n1") {
				movePortletIdUp(n1Portlets, n1PortletsStatic, portletId, columnId);
			}
			else if (columnId == "n2") {
				movePortletIdUp(n2Portlets, n2PortletsStatic, portletId, columnId);
			}
			else if (columnId == "w1") {
				movePortletIdUp(w1Portlets, w1PortletsStatic, portletId, columnId);
			}

			loadPage("<%= themeDisplay.getPathMain() %>/portal/move_portlet_up", "p_l_id=" + layoutId + "&p_p_id=" + portletId);
		}
	}

	function movePortletIdDown(portletIds, portletStatics, portletId, columnId) {
		var numOfStaticPortlets = 0;

		for (var i = 0; i < portletStatics.length; i++) {
			if (portletStatics[i] == "true") {
				numOfStaticPortlets++;
			}
		}

		if ((portletIds.length - numOfStaticPortlets) > 1) {
			for (var i = 0; i < portletIds.length; i++) {
				if (portletIds[i] == portletId) {
					if (i == portletIds.length - 1) {
						var firstNonStaticPortletPos = 0;

						for (var j = 0; j < portletIds.length; j++) {
							if (portletStatics[j] == "false") {
								firstNonStaticPortletPos = j;

								break;
							}
						}

						portletIds[i] = portletIds[firstNonStaticPortletPos]
						portletIds[firstNonStaticPortletPos] = portletId;
					}
					else {
						if (portletStatics[i + 1] == "false") {
							portletIds[i] = portletIds[i + 1];
							portletIds[i + 1] = portletId;
						}
						else {
							var firstNonStaticPortletPos = 0;

							for (var j = 0; j < portletIds.length; j++) {
								if (portletStatics[j] == "false") {
									firstNonStaticPortletPos = j;

									break;
								}
							}

							portletIds[i] = portletIds[firstNonStaticPortletPos]
							portletIds[firstNonStaticPortletPos] = portletId;
						}
					}

					break;
				}
			}
		}

		buildColumnHTML(portletIds, columnId);
	}

	function movePortletIdUp(portletIds, portletStatics, portletId, columnId) {
		var numOfStaticPortlets = 0;

		for (var i = 0; i < portletStatics.length; i++) {
			if (portletStatics[i] == "true") {
				numOfStaticPortlets++;
			}
		}

		if ((portletIds.length - numOfStaticPortlets) > 1) {
			for (var i = 0; i < portletIds.length; i++) {
				if (portletIds[i] == portletId) {
					if (i == 0) {
						var lastNonStaticPortletPos = portletIds.length - 1;

						for (var j = i; j < portletIds.length; j++) {
							if (portletStatics[j] == "true") {
								lastNonStaticPortletPos = j - 1;

								break;
							}
						}

						portletIds[i] = portletIds[lastNonStaticPortletPos]
						portletIds[lastNonStaticPortletPos] = portletId;
					}
					else {
						if (portletStatics[i - 1] == "false") {
							portletIds[i] = portletIds[i - 1];
							portletIds[i - 1] = portletId;
						}
						else {
							var lastNonStaticPortletPos = portletIds.length - 1;

							for (var j = i; j < portletIds.length; j++) {
								if (portletStatics[j] == "true") {
									lastNonStaticPortletPos = j - 1;

									break;
								}
							}

							portletIds[i] = portletIds[lastNonStaticPortletPos]
							portletIds[lastNonStaticPortletPos] = portletId;
						}
					}

					break;
				}
			}
		}

		buildColumnHTML(portletIds, columnId);
	}

	var n1Portlets = new Array();
	var n1PortletsStatic = new Array();

	var n2Portlets = new Array();
	var n2PortletsStatic = new Array();

	var w1Portlets = new Array();
	var w1PortletsStatic = new Array();
</script>