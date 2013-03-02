package com.kingstargroup.ecard.portlet.advquery.action;


import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.servlet.SessionErrors;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;


public class QueryAccountDtlByCustIdAction extends Action {

    public ActionForward execute(
            ActionMapping mapping,
            ActionForm form,
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {

        response.setCharacterEncoding("UTF-8");
        
        DynaActionForm  queryaccountdtlform = (DynaActionForm)form;
        
        String beginDate = queryaccountdtlform.getString("queryaccountdtl_begindate");
        String endDate = queryaccountdtlform.getString("queryaccountdtl_enddate");
        String custId = queryaccountdtlform.getString("custId");
        String stuempno = queryaccountdtlform.getString("stuempno");
        
		
        request.setAttribute("custId", custId);
        request.setAttribute("stuempno", stuempno);
        String dateRange = beginDate + "-" + endDate;
        if ("".equals(custId) && "".equals(stuempno)) {
            SessionErrors.add(request, EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST, "请输入要查询的客户号或学工号！");

            return mapping.findForward("errortest");
        } else if (!"".equals(stuempno)) {
            custId = AdvqueryServiceUtil.getCustIdBystuempNo(stuempno);
        }

        /*
		if(!"".equals(stuempno)){
	          String 	temp_custId =  AdvqueryServiceUtil.getCustIdBystuempNo(stuempno);
	          if((!"".equals(custId))&&!temp_custId.equals(custId)){
	        	 
	        	  SessionErrors.add(request,EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST,"客户不存在，请重新输入！");
				  return mapping.findForward("errortest");
	          }else{
	        	  custId = temp_custId;
	          }
		}
		*/

        List detail = AdvqueryServiceUtil.getOneAccountDetail(custId, beginDate, endDate);
        if (null == detail || detail.isEmpty()) {
            SessionErrors.add(request, EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST, "没有你要查询的数据，请重新指定查询条件！");
            return mapping.findForward("errortest");
        }
        request.setAttribute("title", "个人交易情况明细[" + dateRange + "]");
        request.setAttribute("result", detail);
        return mapping.findForward("accounttransdtl_queryresult");

    }
}
