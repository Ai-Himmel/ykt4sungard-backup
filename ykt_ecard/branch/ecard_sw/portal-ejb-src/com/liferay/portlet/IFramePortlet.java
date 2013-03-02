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

package com.liferay.portlet;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.servlet.SessionMessages;

import java.io.IOException;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.GenericPortlet;
import javax.portlet.PortletContext;
import javax.portlet.PortletException;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

/**
 * <a href="IFramePortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.40 $
 *
 */
public class IFramePortlet extends GenericPortlet {

	public static final String DEFAULT_PORTLET_TITLE = "";

	public static final String DEFAULT_SHOW_PORTLET_BORDERS = "true";

	public static final String DEFAULT_BORDER = "0";

	public static final String DEFAULT_BORDERCOLOR = "#000000";

	public static final String DEFAULT_FRAMEBORDER = "0";

	public static final String DEFAULT_HEIGHT_MAXIMIZED = "600";

	public static final String DEFAULT_HEIGHT_NORMAL = "300";

	public static final String DEFAULT_HSPACE = "0";

	public static final String DEFAULT_SCROLLING = "auto";

	public static final String DEFAULT_SRC = "";

	public static final String DEFAULT_VSPACE = "0";

	public static final String DEFAULT_WIDTH = "100%";

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			PortletPreferences prefs = req.getPreferences();

			User user = PortalUtil.getUser(req);

			String portletTitle = prefs.getValue(
				"portlet-title", DEFAULT_PORTLET_TITLE);
			boolean showPortletBorders = GetterUtil.getBoolean(prefs.getValue(
				"show-portlet-borders", DEFAULT_SHOW_PORTLET_BORDERS));

			boolean auth = GetterUtil.getBoolean(
				prefs.getValue("auth", StringPool.BLANK));
			String authType = prefs.getValue("auth-type", StringPool.BLANK);
			String formMethod = prefs.getValue("form-method", StringPool.BLANK);
			String userName = prefs.getValue("user-name", StringPool.BLANK);
			String password = prefs.getValue("password", StringPool.BLANK);
			String hiddenVariables = prefs.getValue(
				"hidden-variables", StringPool.BLANK);

			String border = prefs.getValue("border", DEFAULT_BORDER);
			String bordercolor = prefs.getValue(
				"bordercolor", DEFAULT_BORDERCOLOR);
			String frameborder = prefs.getValue(
				"frameborder", DEFAULT_FRAMEBORDER);
			String heightMaximized = prefs.getValue(
				"height-maximized", DEFAULT_HEIGHT_MAXIMIZED);
			String heightNormal = prefs.getValue(
				"height-normal", DEFAULT_HEIGHT_NORMAL);
			String hspace = prefs.getValue("hspace", DEFAULT_HSPACE);
			String scrolling = prefs.getValue("scrolling", DEFAULT_SCROLLING);
			String src = prefs.getValue("src", DEFAULT_SRC);
			String vspace = prefs.getValue("vspace", DEFAULT_VSPACE);
			String width = prefs.getValue("width", DEFAULT_WIDTH);

			String htmlAttributes =
				"border=" + border + "\n" +
				"bordercolor=" + bordercolor + "\n" +
				"frameborder=" + frameborder + "\n" +
				"height-maximized=" + heightMaximized + "\n" +
				"height-normal=" + heightNormal + "\n" +
				"hspace=" + hspace + "\n" +
				"scrolling=" + scrolling + "\n" +
				"vspace=" + vspace + "\n" +
				"width=" + width + "\n";

			FastStringBuffer sb = new FastStringBuffer();

			sb.append("<form action=\"" + res.createActionURL() + "\" ");
			sb.append("method=\"post\" name=\"" + res.getNamespace() + "fm");
			sb.append("\" onSubmit=\"submitForm(this); return false;\">");
			sb.append("<input name=\"" + res.getNamespace() + Constants.CMD);
			sb.append("\" type=\"hidden\" value=\"" + Constants.UPDATE + "\">");

			sb.append("<table border=\"0\" cellpadding=\"4\" ");
			sb.append("cellspacing=\"0\" width=\"100%\">");
			sb.append("<tr>");
			sb.append("<td align=\"center\">");
			sb.append("<table border=\"0\" cellpadding=\"0\" ");
			sb.append("cellspacing=\"0\">");

			if (SessionMessages.contains(
					req, getPortletConfig().getPortletName() + ".doEdit")) {

				sb.append("<tr>");
				sb.append("<td>");
				sb.append("<font class=\"gamma\" size=\"1\"><span ");
				sb.append("class=\"gamma-pos-alert\">");
				sb.append(
					LanguageUtil.get(
						user,
						"you-have-successfully-updated-your-preferences"));
				sb.append("</span></font>");
				sb.append("</td>");
				sb.append("</tr>");
				sb.append("<tr>");
				sb.append("<td>");
				sb.append("<br>");
				sb.append("</td>");
				sb.append("</tr>");
			}

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<table border=\"0\" cellpadding=\"0\" ");
			sb.append("cellspacing=\"0\">");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "portlet-title"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<input class=\"form-text\" ");
			sb.append("name=\"" + res.getNamespace() + "portlet_title\" ");
			sb.append("size=\"23\" type=\"text\" value=\"");
			sb.append(portletTitle + "\">");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "show-portlet-borders"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<select name=\"");
			sb.append(res.getNamespace() + "show_portlet_borders\">");
			sb.append("<option ");
			sb.append(showPortletBorders ? "selected" : "");
			sb.append(" value=\"1\">");
			sb.append(LanguageUtil.get(user, "yes"));
			sb.append("</option>");
			sb.append("<option ");
			sb.append(!showPortletBorders ? "selected" : "");
			sb.append(" value=\"0\">");
			sb.append(LanguageUtil.get(user, "no"));
			sb.append("</option>");
			sb.append("</select>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "source-url"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<input class=\"form-text\" ");
			sb.append("name=\"" + res.getNamespace() + "src\" size=\"40\" ");
			sb.append("type=\"text\" value=\"");
			sb.append(src + "\">");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "authenticate"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<select name=\"" + res.getNamespace() + "auth\">");
			sb.append("<option ");
			sb.append(auth ? "selected" : "");
			sb.append(" value=\"1\">");
			sb.append(LanguageUtil.get(user, "yes"));
			sb.append("</option>");
			sb.append("<option ");
			sb.append(!auth ? "selected" : "");
			sb.append(" value=\"0\">");
			sb.append(LanguageUtil.get(user, "no"));
			sb.append("</option>");
			sb.append("</select>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "authentication-type"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<select name=\"" + res.getNamespace() + "auth_type\">");
			sb.append("<option ");
			sb.append(authType.equals("basic") ? "selected" : "");
			sb.append(" value=\"basic\">");
			sb.append(LanguageUtil.get(user, "basic"));
			sb.append("</option>");
			sb.append("<option ");
			sb.append(authType.equals("form") ? "selected" : "");
			sb.append(" value=\"form\">");
			sb.append(LanguageUtil.get(user, "form"));
			sb.append("</option>");
			sb.append("</select>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "form-method"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<select name=\"" + res.getNamespace());
			sb.append("form_method\">");
			sb.append("<option ");
			sb.append(formMethod.equals("get") ? "selected" : "");
			sb.append(" value=\"get\">");
			sb.append("Get");
			sb.append("</option>");
			sb.append("<option ");
			sb.append(formMethod.equals("post") ? "selected" : "");
			sb.append(" value=\"post\">");
			sb.append("Post");
			sb.append("</option>");
			sb.append("</select>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "user-name"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<input class=\"form-text\" ");
			sb.append("name=\"" + res.getNamespace() + "user_name\" ");
			sb.append("size=\"23\" type=\"text\" value=\"");
			sb.append(userName + "\">");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "password"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<input class=\"form-text\" ");
			sb.append("name=\"" + res.getNamespace() + "password\" ");
			sb.append("size=\"23\" type=\"password\" value=\"");
			sb.append(password + "\">");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "hidden-variables"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<input class=\"form-text\" ");
			sb.append("name=\"" + res.getNamespace() + "hidden_variables\" ");
			sb.append("size=\"40\" type=\"text\" value=\"");
			sb.append(hiddenVariables + "\">");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td colspan=\"3\">");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"2\">");
			sb.append(LanguageUtil.get(user, "html-attributes"));
			sb.append("</font>");
			sb.append("</td>");
			sb.append("<td width=\"10\">");
			sb.append("&nbsp;");
			sb.append("</td>");
			sb.append("<td>");
			sb.append("<textarea class=\"form-text\" cols=\"40\" ");
			sb.append("name=\"" + res.getNamespace() + "html_attributes\" ");
			sb.append("rows=\"10\">");
			sb.append(htmlAttributes);
			sb.append("</textarea>");
			sb.append("</td>");
			sb.append("</tr>");

			sb.append("</table>");
			sb.append("</td>");
			sb.append("</tr>");
			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<br>");
			sb.append("</td>");
			sb.append("</tr>");
			sb.append("<tr>");
			sb.append("<td align=\"center\">");
			sb.append("<input class=\"portlet-form-button\" type=\"submit\" ");
			sb.append("value=\"");
			sb.append(LanguageUtil.get(user, "save-settings"));
			sb.append("\">");
			sb.append("</td>");
			sb.append("</tr>");
			sb.append("</table>");

			sb.append("<br>");

			sb.append("<table border=\"0\" cellpadding=\"0\" ");
			sb.append("cellspacing=\"0\">");
			sb.append("<tr>");
			sb.append("<td>");
			sb.append("<font class=\"gamma\" size=\"1\">");
			sb.append("<span class=\"gamma-neg-alert\">");
			sb.append(
				LanguageUtil.get(
					user,
					"leave-the-user-name-and-password-fields-blank-to-use-" +
						"your-current-login-information"));
			sb.append("</span>");
			sb.append("</font>");
			sb.append("</td>");
			sb.append("</tr>");
			sb.append("</table>");

			sb.append("</td>");
			sb.append("</tr>");
			sb.append("</table>");

			sb.append("</form>");

			sb.append("<script language=\"JavaScript\">");
			sb.append("document." + res.getNamespace() + "fm.");
			sb.append(res.getNamespace() + "src.focus();");
			sb.append("</script>");

			res.setContentType(Constants.TEXT_HTML);

			res.getWriter().print(sb.toString());
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			PortletPreferences prefs = req.getPreferences();

			String src = getSrc(req, res);

			String content = null;

			if (Validator.isNull(src)) {
				content = getDoViewFailure(req, res);
			}
			else {
				content = getDoViewSuccess(req, res);
			}

			res.setContentType(Constants.TEXT_HTML);

			res.getWriter().print(content);
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		if (req.getPortletMode().equals(PortletMode.EDIT)) {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (cmd.equals(Constants.UPDATE)) {
				PortletPreferences prefs = req.getPreferences();

				String portletTitle = ParamUtil.getString(req, "portlet_title");
				boolean showPortletBorders = ParamUtil.getBoolean(
					req, "show_portlet_borders");

				String src = ParamUtil.get(req, "src", DEFAULT_SRC);
				if (!src.startsWith("/") &&
					!StringUtil.startsWith(src, "http://") &&
					!StringUtil.startsWith(src, "https://")) {

					src = Http.getProtocol(req) + "://" + src;
				}

				boolean auth = ParamUtil.getBoolean(req, "auth");
				String authType = ParamUtil.getString(req, "auth_type");
				String formMethod = ParamUtil.getString(req, "form_method");
				String userName = ParamUtil.getString(req, "user_name");
				String password = ParamUtil.getString(req, "password");
				String hiddenVariables = ParamUtil.getString(
					req, "hidden_variables");
				String[] htmlAttributes = StringUtil.split(ParamUtil.getString(
					req, "html_attributes"), "\n");

				prefs.setValue("portlet-title", portletTitle);
				prefs.setValue(
					"show-portlet-borders",
					Boolean.toString(showPortletBorders));

				prefs.setValue("src", src);

				prefs.setValue("auth", Boolean.toString(auth));
				prefs.setValue("auth-type", authType);
				prefs.setValue("form-method", formMethod);
				prefs.setValue("user-name", userName);
				prefs.setValue("password", password);
				prefs.setValue("hidden-variables", hiddenVariables);

				for (int i = 0; i < htmlAttributes.length; i++) {
					int pos = htmlAttributes[i].indexOf("=");

					if (pos != -1) {
						String key = htmlAttributes[i].substring(0, pos);
						String value = htmlAttributes[i].substring(
							pos + 1, htmlAttributes[i].length());

						prefs.setValue(key, value);
					}
				}

				prefs.store();

				SessionMessages.add(
					req, getPortletConfig().getPortletName() + ".doEdit");
			}
		}
	}

	protected String getDoViewFailure(RenderRequest req, RenderResponse res)
		throws IOException, PortalException, PortletException {

		FastStringBuffer sb = new FastStringBuffer();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		sb.append("<table border=\"0\" cellpadding=\"4\" cellspacing=\"0\" ");
		sb.append("width=\"100%\">");
		sb.append("<tr>");
		sb.append("<td align=\"center\">");
		sb.append("<table border=\"0\" cellpadding=\"8\" cellspacing=\"0\">");
		sb.append("<tr>");
		sb.append("<td>");
		sb.append("<font class=\"gamma\" size=\"2\">");
		sb.append("<span class=\"gamma-neg-alert\">");
		sb.append(LanguageUtil.get(
			themeDisplay.getCompanyId(), themeDisplay.getLocale(),
			"please-contact-the-administrator-to-setup-this-portlet"));
		sb.append("</span>");
		sb.append("</font>");
		sb.append("</td>");
		sb.append("</tr>");
		sb.append("</table>");
		sb.append("</td>");
		sb.append("</tr>");
		sb.append("</table>");

		return sb.toString();
	}

	protected String getDoViewSuccess(RenderRequest req, RenderResponse res)
		throws IOException, PortalException, PortletException, SystemException {

		FastStringBuffer sb = new FastStringBuffer();

		PortletPreferences prefs = req.getPreferences();

		String portletTitle = prefs.getValue(
			"portlet-title", DEFAULT_PORTLET_TITLE);
		boolean showPortletBorders = GetterUtil.getBoolean(prefs.getValue(
			"show-portlet-borders", DEFAULT_SHOW_PORTLET_BORDERS));

		if (Validator.isNotNull(portletTitle)) {
			res.setTitle(portletTitle);
		}

		if (!showPortletBorders) {
			RenderResponseImpl renderResImpl = (RenderResponseImpl)res;

			renderResImpl.setUseDefaultTemplate(Boolean.FALSE);
		}

		String border = prefs.getValue("border", DEFAULT_BORDER);
		String bordercolor = prefs.getValue("bordercolor", DEFAULT_BORDERCOLOR);
		String frameborder = prefs.getValue("frameborder", DEFAULT_FRAMEBORDER);
		String heightMaximized = prefs.getValue(
			"height-maximized", DEFAULT_HEIGHT_MAXIMIZED);
		String heightNormal = prefs.getValue(
			"height-normal", DEFAULT_HEIGHT_NORMAL);
		String hspace = prefs.getValue("hspace", DEFAULT_HSPACE);
		String scrolling = prefs.getValue("scrolling", DEFAULT_SCROLLING);
		String src = prefs.getValue("src", DEFAULT_SRC);
		String vspace = prefs.getValue("vspace", DEFAULT_VSPACE);
		String width = prefs.getValue("width", DEFAULT_WIDTH);

		String height = heightNormal;
		if (req.getWindowState().equals(WindowState.MAXIMIZED)) {
			height = heightMaximized;
		}

		src = transformSrc(req, res);

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		if (!showPortletBorders) {
			sb.append("<div style=\"width: ");
			sb.append(themeDisplay.getPortletDisplay().getWidth());
			sb.append(";\">");
		}

		sb.append("<iframe ");
		sb.append("border=\"").append(border).append("\" ");
		sb.append("bordercolor=\"").append(bordercolor).append("\" ");
		sb.append("frameborder=\"").append(frameborder).append("\" ");
		sb.append("height=\"").append(height).append("\" ");
		sb.append("hspace=\"").append(hspace).append("\" ");
		sb.append("name=\"").append(res.getNamespace()).append("_iframe\" ");
		sb.append("scrolling=\"").append(scrolling).append("\" ");
		sb.append("src=\"").append(src).append("\" ");
		sb.append("vspace=\"").append(vspace).append("\" ");
		sb.append("width=\"").append(width).append("\" ");
		sb.append("></iframe>");

		if (!showPortletBorders) {
			if (portletDisplay.isShowEditIcon()) {
				PortletURL portletURL = res.createActionURL();

				portletURL.setWindowState(WindowState.MAXIMIZED);
				portletURL.setPortletMode(PortletMode.EDIT);

				sb.append("<div style=\"text-align: right;\">");

				sb.append("<font class=\"gamma\" size=\"1\">[");
				sb.append("<a class=\"gamma\" href=\"");
				sb.append(portletURL.toString());
				sb.append("\" styleClass=\"gamma\">");
				sb.append(LanguageUtil.get(
					themeDisplay.getCompanyId(), themeDisplay.getLocale(),
					"edit"));
				sb.append("</a>");
				sb.append("]</font>");

				sb.append("</div>");
			}

			sb.append("</div>");
		}

		return sb.toString();
	}

	protected String getSrc(RenderRequest req, RenderResponse res) {
		PortletPreferences prefs = req.getPreferences();

		return prefs.getValue("src", DEFAULT_SRC);
	}

	protected String getUserName(RenderRequest req, RenderResponse res) {
		PortletPreferences prefs = req.getPreferences();

		return prefs.getValue("user-name", req.getRemoteUser());
	}

	protected String getPassword(RenderRequest req, RenderResponse res)
		throws PortalException, SystemException {

		PortletPreferences prefs = req.getPreferences();

		String defaultPassword = null;
		if (req.getRemoteUser() != null) {
			defaultPassword = PortalUtil.getUser(req).getPassword();
		}

		return prefs.getValue("password", defaultPassword);
	}

	protected String transformSrc(RenderRequest req, RenderResponse res)
		throws PortalException, SystemException {

		PortletPreferences prefs = req.getPreferences();

		String src = getSrc(req, res);

		boolean auth = GetterUtil.getBoolean(
			prefs.getValue("auth", StringPool.BLANK));
		String authType = prefs.getValue("auth-type", StringPool.BLANK);
		String userName = getUserName(req, res);
		String password = getPassword(req, res);

		if (auth) {
			if (authType.equals("basic")) {
				int pos = src.indexOf("://");

				String protocol = src.substring(0, pos + 3);
				String url = src.substring(pos + 3, src.length());

				src =
					protocol + userName + ":" + password +
					"@" + url;
			}
			else {
				PortletContext portletCtx =
					req.getPortletSession().getPortletContext();

				String mainPath =
					(String)portletCtx.getAttribute(WebKeys.MAIN_PATH);

				String companyId = PortalUtil.getCompanyId(req);

				Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

				Portlet portlet = PortletServiceUtil.getPortletById(
					companyId, getPortletConfig().getPortletName());

				src =
					mainPath + "/" + portlet.getStrutsPath() +
						"/proxy?p_l_id=" + layout.getLayoutId();
			}
		}

		return src;
	}

}