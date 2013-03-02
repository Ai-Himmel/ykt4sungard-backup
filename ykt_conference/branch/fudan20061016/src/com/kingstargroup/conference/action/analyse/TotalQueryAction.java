/**
 * 
 */
package com.kingstargroup.conference.action.analyse;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class TotalQueryAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String flag =  ParamUtil.getString(request,"flag");
		String confName =  ParamUtil.getString(request,"conname"); 
		String confRoom = ParamUtil.getString(request,"confroom");
		String confType = ParamUtil.getString(request,"type");
		String beginDate =ParamUtil.getString(request,"begindate");
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		String endDate = "";
		String compere = "";
		String confDept = "";
		try {
			List result = ConferenceUtil.getConfListByQuery
										(confName,confType,confRoom,confDept,beginDate,endDate,compere,username);
			if (null == result){
				request.setAttribute("tipinfo","没有你要查找的会议记录，请重新指定查询条件！");
				return mapping.findForward("error");
			}		
			request.setAttribute("result", result);
			if(null!= flag&&"print".equals(flag)){
				return mapping.findForward("totalqueryprint");
			}else{
				return mapping.findForward("totalquery");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}