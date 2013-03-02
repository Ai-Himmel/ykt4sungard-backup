package com.kingstargroup.advquery.struts.actions;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.hibernate.util.AccountUtil;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;

public class HandTradeDetailAction extends Action {

    public ActionForward execute(
            ActionMapping mapping,
            ActionForm form,
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {
        String stuempno = request.getParameter("stuempno");
        String tradedevice = request.getParameter("tradedevice");
        String tradecard = request.getParameter("tradecard");
        String tradelogno = request.getParameter("tradelogno");
        String beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
        String endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
        HttpSession session = request.getSession();
        session.setAttribute("stuempno", stuempno);
        session.setAttribute("tradedevice", tradedevice);
        session.setAttribute("tradecard", tradecard);
        session.setAttribute("tradelogno", tradelogno);
        String dateRange = beginDate + "-" + endDate;

        List detail = AccountUtil.getHandTrade(stuempno, beginDate, endDate, tradedevice, tradecard, tradelogno);

        if (null == detail) {
            request.setAttribute("errorcont", "没有你要查询的数据，请重新指定查询条件！");
            return mapping.findForward("errortest");
        }
        request.setAttribute("title", "[" + dateRange + "]手持机交易明细");
        request.setAttribute("result", detail);
        return mapping.findForward("handtrade_queryresult");
    }


}
