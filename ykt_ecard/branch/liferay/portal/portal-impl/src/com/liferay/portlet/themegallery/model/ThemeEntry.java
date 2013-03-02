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

package com.liferay.portlet.themegallery.model;

/**
 * <a href="ThemeEntry.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeEntry {

	public ThemeEntry(String name, String description, String download,
					  String imageLarge, String imageMedium,
					  String imageSmall) {

		_name = name;
		_description = description;
		_download = download;
		_imageLarge = imageLarge;
		_imageMedium = imageMedium;
		_imageSmall = imageSmall;
	}

	public String getName() {
		return _name;
	}

	public String getDescription() {
		return _description;
	}

	public String getDownload() {
		return _download;
	}

	public String getImageLarge() {
		return _imageLarge;
	}

	public String getImageMedium() {
		return _imageMedium;
	}

	public String getImageSmall() {
		return _imageSmall;
	}

	private String _name;
	private String _description;
	private String _download;
	private String _imageLarge;
	private String _imageMedium;
	private String _imageSmall;

}