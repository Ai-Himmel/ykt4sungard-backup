package com.kingstargroup.ecard.portlet.shop.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;

public class ShopServiceUtil {

	public static List createShopJSList(String rootId)throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.createShopJSList(rootId);
	}
	
	public static String getStoreLimitString(long userid)throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getStoreLimitString(userid);
	}
	
	public static void updateUser(String userid, 
			String storeLimitString)throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();		
		shopService.updateStoreLimit(userid, storeLimitString);
	}
	
	public static List getShopList(long userid)throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopList(userid);
	}
	
	public static List getShopDinnerReportList(int shopid, String begindate, String enddate,
			int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopDinnerReportList(shopid, begindate, enddate, shoplevel);
	}
	
	public static List getShopTodayDinnerReportList(int shopid,int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopTodayDinnerReportList(shopid,shoplevel);
	}
	public static List getShopDinnerTotalReportList(int shopid, String begindate, String enddate,
			int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopDinnerTotalReportList(shopid, begindate, enddate, shoplevel);
	}
	
	public static List getShopCatalogReportList(int shopid, String begindate, String enddate,
			int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopCatalogReportList(shopid, begindate, enddate, shoplevel);
	}
	
	public static List getShopPosCatalogReportList(int shopid, String begindate, String enddate,
			int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopPosCatalogReportList(shopid, begindate, enddate, shoplevel);
	}
	
	public static List getShopTotalReportList(int shopid, String begindate, String enddate,
			int shoplevel) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopTotalReportList(shopid, begindate, enddate, shoplevel);
	}
	
	public static List getShopAccountDetailList(int shopid, String begindate, String enddate, int termid) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopAccountDetailList(shopid,begindate, enddate, termid);
	}
	
	public static List getShopBrasDetailList(String begindate, String enddate,String refno,String stuempno,String custname, String opaccno, String opaccname,String status,String brastype) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopBrasDetailList(begindate, enddate,refno,stuempno,custname, opaccno, opaccname,status,brastype);
	}

	public static List getShopPosDetailList(int shopid, String begindate,String enddate, String devphyId) throws PortalException {
		ShopService shopService = ShopServiceFactory.getService();
		return shopService.getShopPosDetailList(shopid,begindate, enddate, devphyId);
	}
	
}
