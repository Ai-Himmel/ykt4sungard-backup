package org.king.servlet;

import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.domain.Order;
import org.king.utils.MD5;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-13
 */
public class ResultServlet extends HttpServlet {
    private static final Logger logger = Logger.getLogger(ResultServlet.class);

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        result(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        result(request, response);
    }

    private void result(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String v_oid = request.getParameter("v_oid");
        String v_status = request.getParameter("v_status");
        String v_code = request.getParameter("v_code");
        String v_amount = request.getParameter("v_amount");
        String v_currency = request.getParameter("v_currency");
        String v_errcode = request.getParameter("v_errcode");
        String v_errmsg = request.getParameter("v_errmsg");
        String v_name = request.getParameter("v_name");
        String v_remark = request.getParameter("v_remark");
        //一卡通交易流水号
        String v_refno = request.getParameter("v_refno");

        String key = Configuration.getProperty(Constant.KEY, "");
        String code = MD5.MD5Encode(v_oid + v_status + v_amount + v_currency + key);
        List<Order> orders = (List<Order>) request.getSession().getAttribute("orders");
        Order order = null;
        for (Order o : orders) {
            if (o.getOid().equals(v_oid)) {
                order = o;
                break;
            }
        }

        //order normally could not be null, try to do something when you couldn't find order with v_oid
        if (order != null && code.equals(v_code)) {
            if ("1".equals(v_status)) {
                request.setAttribute("status", "支付成功");
                request.setAttribute("msg", "");
                order.setStatus("支付成功");
            } else {
                request.setAttribute("status", "支付失败");
                order.setStatus("支付失败");
                request.setAttribute("msg", "[" + v_errcode + "," + v_errmsg + "]");
            }
        } else {
            //illegal request,do something here
            logger.warn("Received an illegal request");
            request.setAttribute("status", "校验失败");
            request.setAttribute("msg", "【非法请求】");
        }

        request.setAttribute("v_oid", v_oid);
        request.setAttribute("v_status", v_status);
        request.setAttribute("v_code", v_code);
        request.setAttribute("v_amount", v_amount);
        request.setAttribute("v_currency", v_currency);
        request.setAttribute("v_errcode", v_errcode);
        request.setAttribute("v_errmsg", v_errmsg);
        request.setAttribute("v_name", v_name);
        request.setAttribute("v_remark", v_remark);
        request.setAttribute("v_refno", v_refno);

        getServletConfig().getServletContext().getRequestDispatcher("/WEB-INF/pages/result.jsp").forward(request, response);
    }
}
