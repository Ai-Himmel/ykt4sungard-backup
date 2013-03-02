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

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Image;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ImageModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>Image</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.Image
 * @see com.liferay.portal.service.model.ImageModel
 * @see com.liferay.portal.service.model.impl.ImageImpl
 *
 */
public class ImageModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "Image";
	public static final Object[][] TABLE_COLUMNS = {
			{ "imageId", new Integer(Types.BIGINT) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "text_", new Integer(Types.CLOB) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "height", new Integer(Types.INTEGER) },
			

			{ "width", new Integer(Types.INTEGER) },
			

			{ "size_", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table Image (imageId LONG not null primary key,modifiedDate DATE null,text_ TEXT null,type_ VARCHAR(75) null,height INTEGER,width INTEGER,size_ INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table Image";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.Image"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.Image"));

	public ImageModelImpl() {
	}

	public long getPrimaryKey() {
		return _imageId;
	}

	public void setPrimaryKey(long pk) {
		setImageId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_imageId);
	}

	public long getImageId() {
		return _imageId;
	}

	public void setImageId(long imageId) {
		if (imageId != _imageId) {
			_imageId = imageId;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public String getText() {
		return GetterUtil.getString(_text);
	}

	public void setText(String text) {
		if (((text == null) && (_text != null)) ||
				((text != null) && (_text == null)) ||
				((text != null) && (_text != null) && !text.equals(_text))) {
			_text = text;
		}
	}

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
		}
	}

	public int getHeight() {
		return _height;
	}

	public void setHeight(int height) {
		if (height != _height) {
			_height = height;
		}
	}

	public int getWidth() {
		return _width;
	}

	public void setWidth(int width) {
		if (width != _width) {
			_width = width;
		}
	}

	public int getSize() {
		return _size;
	}

	public void setSize(int size) {
		if (size != _size) {
			_size = size;
		}
	}

	public Image toEscapedModel() {
		if (isEscapedModel()) {
			return (Image)this;
		}
		else {
			Image model = new ImageImpl();

			model.setEscapedModel(true);

			model.setImageId(getImageId());
			model.setModifiedDate(getModifiedDate());
			model.setText(Html.escape(getText()));
			model.setType(Html.escape(getType()));
			model.setHeight(getHeight());
			model.setWidth(getWidth());
			model.setSize(getSize());

			model = (Image)Proxy.newProxyInstance(Image.class.getClassLoader(),
					new Class[] { Image.class }, new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ImageImpl clone = new ImageImpl();

		clone.setImageId(getImageId());
		clone.setModifiedDate(getModifiedDate());
		clone.setText(getText());
		clone.setType(getType());
		clone.setHeight(getHeight());
		clone.setWidth(getWidth());
		clone.setSize(getSize());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ImageImpl image = (ImageImpl)obj;

		int value = 0;

		if (getImageId() < image.getImageId()) {
			value = -1;
		}
		else if (getImageId() > image.getImageId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ImageImpl image = null;

		try {
			image = (ImageImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = image.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private long _imageId;
	private Date _modifiedDate;
	private String _text;
	private String _type;
	private int _height;
	private int _width;
	private int _size;
}