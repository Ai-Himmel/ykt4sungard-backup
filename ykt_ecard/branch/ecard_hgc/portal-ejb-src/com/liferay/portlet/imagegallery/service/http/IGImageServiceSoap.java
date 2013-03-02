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

package com.liferay.portlet.imagegallery.service.http;

import com.liferay.portlet.imagegallery.service.spring.IGImageServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="IGImageServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGImageServiceSoap {
	public static void deleteImage(java.lang.String imageId)
		throws RemoteException {
		try {
			IGImageServiceUtil.deleteImage(imageId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteImage(
		com.liferay.portlet.imagegallery.model.IGImage image)
		throws RemoteException {
		try {
			IGImageServiceUtil.deleteImage(image);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImageModel getImage(
		java.lang.String imageId) throws RemoteException {
		try {
			com.liferay.portlet.imagegallery.model.IGImage returnValue = IGImageServiceUtil.getImage(imageId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImageModel[] getImages(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = IGImageServiceUtil.getImages(companyId);

			return (com.liferay.portlet.imagegallery.model.IGImage[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGImage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImageModel[] getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			java.util.List returnValue = IGImageServiceUtil.getImages(folder);

			return (com.liferay.portlet.imagegallery.model.IGImage[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGImage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImageModel[] getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder, int begin,
		int end) throws RemoteException {
		try {
			java.util.List returnValue = IGImageServiceUtil.getImages(folder,
					begin, end);

			return (com.liferay.portlet.imagegallery.model.IGImage[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGImage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImageModel[] getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws RemoteException {
		try {
			java.util.List returnValue = IGImageServiceUtil.getImages(folder,
					begin, end, obc);

			return (com.liferay.portlet.imagegallery.model.IGImage[])returnValue.toArray(new com.liferay.portlet.imagegallery.model.IGImage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getImagesSize(java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = IGImageServiceUtil.getImagesSize(companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getImagesSize(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws RemoteException {
		try {
			int returnValue = IGImageServiceUtil.getImagesSize(folder);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}