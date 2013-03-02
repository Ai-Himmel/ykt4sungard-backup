<%
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
%>

<%@ page import="com.liferay.portal.kernel.util.ParamUtil" %>
<%@ page import="com.liferay.portal.util.PropsUtil"%>
<%@ page import="com.liferay.util.HttpUtil" %>

<%
long plid = ParamUtil.getLong(request, "p_l_id");
String mainPath = ParamUtil.getString(request, "p_main_path");
String doAsUserId = ParamUtil.getString(request, "doAsUserId");

String connectorURL = HttpUtil.encodeURL(mainPath + "/portal/fckeditor?p_l_id=" + plid + "&doAsUserId=" + HttpUtil.encodeURL(doAsUserId));
%>

FCKConfig.IncludeLatinEntities	= false ;

FCKConfig.ToolbarSets["liferay"] = [
	['FontName','FontSize','-','TextColor','BGColor'],
	['Bold','Italic','Underline','StrikeThrough'],
	['Subscript','Superscript'],
	'/',
	['Undo','Redo','-','Cut','Copy','Paste','PasteText','PasteWord','-','SelectAll','RemoveFormat'],
	['Find','Replace','SpellCheck'],
	['OrderedList','UnorderedList','-','Outdent','Indent'],
	['JustifyLeft','JustifyCenter','JustifyRight','JustifyFull'],
	'/',
	['Source'],
	['Link','Unlink','Anchor'],
	['Image','Flash','Table','-','Smiley','SpecialChar']
] ;

FCKConfig.ToolbarSets["liferay-article"] = [
	['FontName','FontSize','-','TextColor','BGColor'],
	['Bold','Italic','Underline','StrikeThrough'],
	['Subscript','Superscript'],
	'/',
	['Undo','Redo','-','Cut','Copy','Paste','PasteText','PasteWord','-','SelectAll','RemoveFormat'],
	['Find','Replace','SpellCheck'],
	['OrderedList','UnorderedList','-','Outdent','Indent'],
	['JustifyLeft','JustifyCenter','JustifyRight','JustifyFull'],
	'/',
	['Source'],
	['Link','Unlink','Anchor'],
	['Image','Flash','Table','-','Smiley','SpecialChar','LiferayPageBreak']
] ;

FCKConfig.ToolbarSets["edit-in-place"] = [
	['Style','FontFormat'],
	['Bold','Italic','Underline','StrikeThrough'],
	['Subscript','Superscript','SpecialChar'],
	['Undo','Redo'],
	['SpellCheck'],
	['OrderedList','UnorderedList','-','Outdent','Indent'],['Source','RemoveFormat'],
] ;

FCKConfig.LinkBrowserURL = FCKConfig.BasePath + "filemanager/browser/liferay/browser.html?Connector=<%= connectorURL %>";
FCKConfig.ImageBrowserURL = FCKConfig.BasePath + "filemanager/browser/liferay/browser.html?Type=Image&Connector=<%= connectorURL %>";
FCKConfig.FlashBrowser = false ;
FCKConfig.LinkUpload = false ;
FCKConfig.ImageUpload = false ;
FCKConfig.FlashUpload = false ;

var sOtherPluginPath = FCKConfig.BasePath.substr(0, FCKConfig.BasePath.length - 7) + 'editor/plugins/' ;

var _TOKEN_PAGE_BREAK = '<%= _TOKEN_PAGE_BREAK %>';

FCKConfig.Plugins.Add('liferaypagebreak', null, sOtherPluginPath ) ;

<%!
private static final String _TOKEN_PAGE_BREAK = PropsUtil.get(PropsUtil.JOURNAL_ARTICLE_TOKEN_PAGE_BREAK);
%>