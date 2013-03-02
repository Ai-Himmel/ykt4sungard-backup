package com.kingstargroup.conference.action.sign;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

/**
 * 无卡签到
 * @author hjw
 *
 */
public class NoCardSignAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm from, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String cmd = ParamUtil.getString(request,"cmd");
		int confid = ParamUtil.getInteger(request,"confid");
		TConference tconference = ConferenceUtil.getConfById(new Long(confid));
		
		if ("query".equals(cmd)){			
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String deptcode = ParamUtil.getString(request,"deptcode");
			String dlgtcode = ParamUtil.getString(request, "dlgtcode");
			String duty = ParamUtil.getString(request,"duty");
			if("2".equals(tconference.getPreplan1())){
				request.setAttribute("result",AttendeeUtil.getEcardCustListMapSPE(confid,custno,custname,duty,deptcode,dlgtcode));
			}else{
				request.setAttribute("result",AttendeeUtil.getCustListMapSPE(confid,custno,custname,duty,deptcode,dlgtcode));
			}
			
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("dlgtcode",dlgtcode);
			request.setAttribute("confid",new Integer(confid));
			return mapping.findForward("nocardsign");
			
		}else if ("sign".equals(cmd)){
	//		String[] custid = request.getParameterValues("custid");
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","签到失败:请选择要签到的与会人员！");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
	//		String signtime = ParamUtil.getString(request,"signtime");
			String signtime = DateUtilExtend.getNowTime();

			for(int i=0;i<custid.length;i++){
				if (SignUtil.getSignedOrNot(confid,Integer.parseInt(custid[i]))){
					request.setAttribute("tipinfo","该与会人员 "+custid[i]+" 已经签到！");
					return mapping.findForward("error");
				}				
			}
			String custs ="";
			
			if("2".equals(tconference.getPreplan1())){
				if (SignUtil.ecardAttendeeNoCardSign(confid,custid,signtime)){				
					for(int i=0;i<custid.length;i++){
						custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
					}
					request.setAttribute("tipinfo",custs+"签到成功！");
					return mapping.findForward("succeed");
				}else{
					request.setAttribute("tipinfo","签到失败，请检查原因！");
					return mapping.findForward("error");
				}
			}else{
				if (SignUtil.attendeeNoCardSign(confid,custid,signtime)){				
					for(int i=0;i<custid.length;i++){
						custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
					}
					request.setAttribute("tipinfo",custs+"签到成功！");
					return mapping.findForward("succeed");
				}else{
					request.setAttribute("tipinfo","签到失败，请检查原因！");
					return mapping.findForward("error");
				}
			}
			
		}else if ("unsign".equals(cmd)){
			String custids = request.getParameter("custids");
			if(custids.lastIndexOf(",")==-1){
				request.setAttribute("tipinfo","签到失败:请选择要取消签到的与会人员！");
				return mapping.findForward("error");
			}
			custids = custids.substring(0,custids.lastIndexOf(","));
			String[] custid = custids.split(",");
			String signtime = DateUtilExtend.getNowTime();
			String custs ="";
			if (SignUtil.attendeeNoCardUnSign(confid,custid,signtime)){
				
				for(int i=0;i<custid.length;i++){
					custs+=GetDictionary.getCustNameById(Integer.parseInt(custid[i]))+" ";
				}
				request.setAttribute("tipinfo",custs+"取消签到成功！");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","取消签到失败，请检查原因！");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
