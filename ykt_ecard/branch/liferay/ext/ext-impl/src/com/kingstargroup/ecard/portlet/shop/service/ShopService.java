package com.kingstargroup.ecard.portlet.shop.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;

public interface ShopService {

	public List createShopJSList(String rootid) throws PortalException;

	public String getStoreLimitString(long userid) throws PortalException;

	public void updateStoreLimit(String userid, String storeLimitString)
			throws PortalException;

	public List getShopList(long userid) throws PortalException;

	public List getShopDinnerReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException;

	public List getShopTodayDinnerReportList(int shopid, int shoplevel)
			throws PortalException;

	public List getShopDinnerTotalReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException;

	public List getShopCatalogReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException;

	public List getShopPosCatalogReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException;

	public List getShopTotalReportList(int shopid, String begindate,
			String enddate, int shoplevel) throws PortalException;

	public List getShopAccountDetailList(int shopid, String begindate,
			String enddate, int termid) throws PortalException;

	public List getShopBrasDetailList(String begindate, String enddate,
			String refno,String stuempno, String custname, String opaccno, String opaccname,
			String status,String brastype) throws PortalException;


	public List getShopPosDetailList(int shopid, String begindate,
			String enddate, String devphyId) throws PortalException;
}
