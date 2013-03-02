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

package com.liferay.portal.service;


/**
 * <a href="RegionServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portal.service.RegionService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portal.service.RegionServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.RegionService
 * @see com.liferay.portal.service.RegionServiceFactory
 *
 */
public class RegionServiceUtil {
	public static com.liferay.portal.model.Region addRegion(long countryId,
		java.lang.String regionCode, java.lang.String name, boolean active)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.addRegion(countryId, regionCode, name, active);
	}

	public static java.util.List getRegions()
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.getRegions();
	}

	public static java.util.List getRegions(long countryId)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.getRegions(countryId);
	}

	public static java.util.List getRegions(boolean active)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.getRegions(active);
	}

	public static java.util.List getRegions(long countryId, boolean active)
		throws com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.getRegions(countryId, active);
	}

	public static com.liferay.portal.model.Region getRegion(long regionId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		RegionService regionService = RegionServiceFactory.getService();

		return regionService.getRegion(regionId);
	}
}