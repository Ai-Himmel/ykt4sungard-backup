package org.king.status.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DateDecorator;
import org.king.common.displaytag.decorator.DateIntervalDecorator;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.web.action.BaseAction;
import org.king.monitor.domain.TDevice;
import org.king.template.service.TemplateService;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.termdev.service.TermdevService;
import org.king.utils.DateUtil;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class TermdeviceStatusAction extends BaseAction {
    private TermdevService termdevService;

    private TemplateService templateService;

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public void setTemplateService(TemplateService templateService) {
        this.templateService = templateService;
    }

    public ActionForward listMonitorTermdeviceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        String devicename = (String) ((DynaActionForm) form).get("devicename");
        String fdevicename = (String) ((DynaActionForm) form).get("fdevicename");
        String currentState = (String) ((DynaActionForm) form).get("currentState");
        String templateId = (String) ((DynaActionForm) form).get("templateId");
        String devtypecode = (String) ((DynaActionForm) form).get("devtypecode");
        String deviceid = (String) ((DynaActionForm) form).get("deviceid");
        String fdeviceid = (String) ((DynaActionForm) form).get("fdeviceid");
        String isLeaf = (String) ((DynaActionForm) form).get("isLeaf");
        String[] conditions = new String[]{devicename, fdevicename, currentState,templateId,devtypecode,deviceid,fdeviceid,isLeaf};


        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findMonitorTermdeviceStatusByPage(page, conditions);
        List templateList = templateService.findAllMonitorTermdevTemplate();
        String[][] result = termdevService.calculateTermdeviceStatus();
        StateDecorator termdeviceStatusDecorator = DecoratorFactory.getTermdeviceStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();
        DateIntervalDecorator dateIntervalDecorator = DecoratorFactory.getDateIntervalDecorator();
        Map deviceType = termdevService.getDeviceType();

        request.setAttribute("termdeviceStatusDecorator", termdeviceStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);
        request.setAttribute("dateIntervalDecorator", dateIntervalDecorator);
        request.setAttribute("termdeviceStatusList", page);
        request.setAttribute("result", result);
        request.setAttribute("templateList", templateList);
        request.setAttribute("deviceType", deviceType);

        return mapping.findForward("listTermdeviceStatus");
    }

    public ActionForward viewMonitorTermdeviceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String deviceId = request.getParameter("deviceId");
        MonitorTermdeviceStatus monitorTermdeviceStatus = termdevService.getMonitorTermdeviceStatus(Integer.valueOf(deviceId));
        String deviceName = termdevService.getTDeviceName(monitorTermdeviceStatus.getDeviceId());
        
        String statusDuration = DateUtil.convertTime(monitorTermdeviceStatus.getLastStateChange());
        String updateDuration = DateUtil.convertTime(monitorTermdeviceStatus.getStatusUpdateTime());
        if (StringUtils.isNotBlank(statusDuration)) {
            statusDuration = "(for " + statusDuration + ")";
        }
        if (StringUtils.isNotBlank(updateDuration)) {
            updateDuration = "(" + updateDuration + " ago)";
        }

        ((DynaActionForm) form).set("monitorTermdeviceStatus", monitorTermdeviceStatus);
        request.setAttribute("deviceName", deviceName);
        request.setAttribute("statusDuration", statusDuration);
        request.setAttribute("updateDuration", updateDuration);

        return mapping.findForward("viewTermdeviceStatus");
    }

    public ActionForward caculateDeviceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List result = termdevService.categorizeDeviceStatus();
        request.setAttribute("result",result);
        return mapping.findForward("caculateTermdeviceStatus");
    }
}