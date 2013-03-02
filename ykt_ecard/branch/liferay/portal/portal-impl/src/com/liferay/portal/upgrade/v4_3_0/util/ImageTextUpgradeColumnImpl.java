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

package com.liferay.portal.upgrade.v4_3_0.util;

import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.impl.ImageImpl;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.upgrade.util.BaseUpgradeColumnImpl;
import com.liferay.portal.upgrade.util.UpgradeColumn;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ImageTextUpgradeColumnImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageTextUpgradeColumnImpl extends BaseUpgradeColumnImpl {

	public ImageTextUpgradeColumnImpl(UpgradeColumn imageIdColumn) {
		super("text_");

		_imageIdColumn = imageIdColumn;
	}

	public Object getNewValue(Object oldValue) throws Exception {
		_type = null;
		_height = null;
		_width = null;
		_size = null;

		String text = (String)oldValue;

		byte[] bytes = (byte[])Base64.stringToObject(text);

		try {
			Image image = ImageLocalUtil.getImage(bytes);

			_type = image.getType();
			_height = new Integer(image.getHeight());
			_width = new Integer(image.getWidth());
			_size = new Integer(image.getSize());
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				String imageId = (String)_imageIdColumn.getOldValue();

				_log.warn(
					"Unable to get image data for " + imageId + ": " +
						e.getMessage());
			}

			_type = ImageImpl.TYPE_NOT_AVAILABLE;
			_height = null;
			_width = null;
			_size = new Integer(bytes.length);
		}

		return oldValue;
	}

	public String getType() {
		return _type;
	}

	public Integer getHeight() {
		return _height;
	}

	public Integer getWidth() {
		return _width;
	}

	public Integer getSize() {
		return _size;
	}

	private static Log _log =
		LogFactory.getLog(ImageTextUpgradeColumnImpl.class);

	private UpgradeColumn _imageIdColumn;
	private String _type;
	private Integer _height;
	private Integer _width;
	private Integer _size;

}