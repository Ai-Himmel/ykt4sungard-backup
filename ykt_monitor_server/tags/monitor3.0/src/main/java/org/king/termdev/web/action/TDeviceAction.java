package org.king.termdev.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.web.action.BaseAction;
import org.king.template.service.TemplateService;
import org.king.termdev.domain.MonitorDevtem;
import org.king.termdev.service.TermdevService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-2
 */
public class TDeviceAction extends BaseAction {
    private TermdevService termdevService;

    private TemplateService templateService;

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward listTDevice(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String fdeviceName = (String) ((DynaActionForm) form).get("fdeviceName");
        String deviceName = (String) ((DynaActionForm) form).get("deviceName");
        String templateId = (String) ((DynaActionForm) form).get("templateId");
        String devtypecode = (String) ((DynaActionForm) form).get("devtypecode");

        String[] args = new String[]{fdeviceName, deviceName, templateId, devtypecode};

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findTDeviceByPage(page, args);
        List templateList = templateService.findAllMonitorTermdevTemplate();
        Map deviceType = termdevService.getDeviceType();

        request.setAttribute("tdeviceList", page);
        request.setAttribute("templateList", templateList);
        request.setAttribute("deviceType", deviceType);
        ((DynaActionForm) form).set("fdeviceName", fdeviceName);
        ((DynaActionForm) form).set("deviceName", deviceName);
        ((DynaActionForm) form).set("templateId", templateId);
        ((DynaActionForm) form).set("devtypecode", devtypecode);

        return mapping.findForward("list");
    }

    public ActionForward editMonitorDevtem(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceid = request.getParameter("deviceid");
        String devicename = termdevService.getTDeviceName(Integer.valueOf(deviceid));
        List templateList = templateService.findAllMonitorTermdevTemplate();
        String templateId = termdevService.getTemplateIdByDeviceid(Integer.valueOf(deviceid));

        request.setAttribute("devicename", devicename);
        request.setAttribute("deviceid", deviceid);
        request.setAttribute("templateList", templateList);
        request.setAttribute("templateId", templateId);
        return mapping.findForward("input");
    }

    public ActionForward addMonitorDevtem(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        MonitorDevtem monitorDevtem = (MonitorDevtem) ((DynaActionForm) form).get("monitorDevtem");
        try {
            termdevService.saveOrUpdateMonitorDevtem(monitorDevtem);
            writer.write("分配模板成功！");
        } catch (Exception e) {
            writer.write("error:分配模板失败！");
            log.error(e.getMessage());
        }
        return null;
    }
}
