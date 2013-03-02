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

FCKToolbarItems.RegisterItem(
	'LiferayPageBreak',
	new FCKToolbarButton('LiferayPageBreak', FCKLang.Source, null, FCK_TOOLBARITEM_ONLYICON, true, true, 1));

var InsertLiferayPageBreakCommand = function() {
};

InsertLiferayPageBreakCommand.prototype.Execute = function() {
}

InsertLiferayPageBreakCommand.GetState = function() {
	return FCK_TRISTATE_OFF;
}

InsertLiferayPageBreakCommand.Execute = function() {
	FCK.Focus();
	FCK.InsertHtml(_TOKEN_PAGE_BREAK);
}

FCKCommands.RegisterCommand('LiferayPageBreak', InsertLiferayPageBreakCommand);

var oInsertVariables = new FCKToolbarButton('LiferayPageBreak', 'Insert page break');

oInsertVariables.IconPath = FCKConfig.PluginsPath + 'liferaypagebreak/pagebreak.gif';

FCKToolbarItems.RegisterItem('LiferayPageBreak', oInsertVariables);