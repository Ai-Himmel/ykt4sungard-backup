package com.kingstargroup.advquery.struts.actions;

import java.net.URLDecoder;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.advquery.hibernate.util.LunchUtil;

public class LunchPersonAction extends Action {

    public ActionForward execute(
            ActionMapping mapping,
            ActionForm form,
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {
    	
        //DynaActionForm dform = (DynaActionForm)form;
    	// request.setCharacterEncoding("gb2312");
         String stuempno = request.getParameter("stuempno");
         String tradedept =request.getParameter("tradedept");
         String lunchtype = request.getParameter("lunchtype");
         /*if(request.getMethod().equals("GET")){ 
         	tradedept =  new String(tradedept.getBytes(),"utf-8");
         }*/
         if(StringUtils.isNotBlank(tradedept)){
         	tradedept = URLDecoder.decode(tradedept,"GBK");
         }
        //String beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
        //String endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
        HttpSession session = request.getSession();	
        session.setAttribute("stuempno", stuempno);
        session.setAttribute("tradedept", tradedept);
        session.setAttribute("lunchtype", lunchtype);
        //request.setAttribute("beginDate", beginDate);
        //request.setAttribute("endDate", endDate);
        //String dateRange = beginDate + "-" + endDate;

        List detail = LunchUtil.getLunchPerson(stuempno, tradedept,lunchtype);

        if (null == detail) {
            request.setAttribute("errorcont", "没有你要查询的数据，请重新指定查询条件！");
            return mapping.findForward("errortest");
        }
        request.setAttribute("title", "自助餐人员列表");
        request.setAttribute("result", detail);
        return mapping.findForward("lunchperson_queryresult");
    }


}
