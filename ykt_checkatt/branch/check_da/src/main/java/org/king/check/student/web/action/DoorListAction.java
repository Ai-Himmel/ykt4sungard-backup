package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.util.InsertDoorList;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * .
 * User: Yiming.You
 * Date: 2010-10-13
 */
public class DoorListAction extends BaseAction {
    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
        return mapping.findForward("result");
    }

    public ActionForward insertDoorList(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            new InsertDoorList();
            writer.write("下发名单成功！");
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }
}
