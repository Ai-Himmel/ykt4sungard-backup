package com.kingstargroup.ecard.portlet.pos.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;

public class PosServiceUtil {
	
	public static List getPosDetail(String lvol0,String snote,String sdate0,String sdate1,String stime0,String stime1) throws PortalException {
		PosService posService = PosServiceFactory.getService();
		return posService.getPosDetail(lvol0,snote,sdate0,sdate1,stime0,stime1);
	}
	
	public static List getPostReport(String lvol0,String snote,String sdate0,String sdate1,String stime0,String stime1) throws PortalException{
		PosService posService = PosServiceFactory.getService();
		return posService.getPostReport(lvol0,snote,sdate0,sdate1,stime0,stime1);
	}
	
	public static List getPosSwipeReport(String lvol0,String spager,String sall_name,String scert_no,String sdate0,String sdate1) throws PortalException {
		PosService posService = PosServiceFactory.getService();
		return posService.getPosSwipeReport(lvol0,spager,sall_name,scert_no,sdate0,sdate1);
	}
	
	public static List getPosSwipeDetail(String spager,String sall_name,String scert_no,String sdate0,String sdate1,String stime0,String stime1) throws PortalException {
		PosService posService = PosServiceFactory.getService();
		return posService.getPosSwipeDetail(spager,sall_name,scert_no,sdate0,sdate1,stime0,stime1);
	}
	
	public static List getDepartments() {
		PosService posService = PosServiceFactory.getService();
		return posService.getDepartments();
	}

}
