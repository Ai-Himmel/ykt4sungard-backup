package com.kingstargroup.ecard.portlet.pos.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;

public interface PosService {
	public List getPosDetail(String lvol0,String snote,String sdate0,String sdate1,String stime0,String stime1) throws PortalException ;
	
	public List getPostReport(String lvol0,String snote,String sdate0,String sdate1,String stime0,String stime1) throws PortalException ;
	
	public List getPosSwipeReport(String lvol0,String spager,String sall_name,String scert_no,String sdate0,String sdate1) throws PortalException ;
	
	public List getPosSwipeDetail(String spager,String sall_name,String scert_no,String sdate0,String sdate1,String stime0,String stime1) throws PortalException ;
	
	public List getDepartments();
}
