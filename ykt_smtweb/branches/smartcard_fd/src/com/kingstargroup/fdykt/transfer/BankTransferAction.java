package com.kingstargroup.fdykt.transfer;

import java.sql.SQLException;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2AdminDAO;
import com.kingstargroup.fdykt.util.DateUtil;

public class BankTransferAction extends Action{
	
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		  
		try {
			
			DB2AdminDAO adminDao = new DB2AdminDAO();
			Map work = adminDao.worktime();
			String now = DateUtil.getNow("HHmm");
			int   nowtime = Integer.parseInt(now);
			String   begintime = work.get("keyValue").toString();
			String   endtime = work.get("maxValue").toString();
			
			if(nowtime < Integer.parseInt(begintime) || nowtime > Integer.parseInt(endtime) ){
				StringBuffer sb = new StringBuffer();
				for(int i=4;i >(4-begintime.length());i--){
					sb.append("0");
				}
				begintime = sb + begintime;
				
				request.setAttribute("msg","转账时间在每天  "+begintime.substring(0,2)+" 点 "+begintime.substring(2,4)+"分 至 "+
						endtime.substring(0,2)+" 点 "+ endtime.substring(2,4)+"分" );
				return mapping.findForward("failure"); 
			}else{
				return mapping.findForward("success");
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
			return mapping.findForward("index");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("index");
		}
		
	}

}
