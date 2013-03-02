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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.model.Image;
import com.liferay.util.ImageUtil;

/**
 * <a href="ImageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageImpl extends ImageModelImpl implements Image {

	public static final String TYPE_BMP = ImageUtil.TYPE_BMP;

	public static final String TYPE_GIF = ImageUtil.TYPE_GIF;

	public static final String TYPE_JPEG = ImageUtil.TYPE_JPEG;

	public static final String TYPE_PNG = ImageUtil.TYPE_PNG;

	public static final String TYPE_TIFF = ImageUtil.TYPE_TIFF;

	public static final String TYPE_NOT_AVAILABLE =
		ImageUtil.TYPE_NOT_AVAILABLE;

	public ImageImpl() {
	}

	public byte[] getTextObj() {
		if (_textObj == null) {
			_textObj = (byte[])Base64.stringToObject(getText());
		}

		return _textObj;
	}

	public void setTextObj(byte[] textObj) {
		_textObj = textObj;

		super.setText(Base64.objectToString(textObj));
	}

	private byte[] _textObj;

}