package org.king.topo.service.impl;

import org.apache.commons.lang.StringUtils;
import org.king.framework.service.impl.BaseService;
import org.king.template.util.DeviceXmlUtil;
import org.king.topo.dao.MonitorTopoDeviceGroupDAO;
import org.king.topo.dao.MonitorTopoGroupDAO;
import org.king.topo.dao.MonitorTopoLocationDAO;
import org.king.topo.domain.MonitorTopoDeviceGroup;
import org.king.topo.domain.MonitorTopoDeviceGroupId;
import org.king.topo.domain.MonitorTopoGroup;
import org.king.topo.domain.MonitorTopoLocation;
import org.king.topo.service.MonitorTopoService;
import org.king.topo.service.TopoCalculatorService;
import org.king.utils.ResultTransform;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-21
 */
public class MonitorTopoServiceImpl extends BaseService implements MonitorTopoService {

    private MonitorTopoLocationDAO monitorTopoLocationDAO;

    private MonitorTopoGroupDAO monitorTopoGroupDAO;

    private MonitorTopoDeviceGroupDAO monitorTopoDeviceGroupDAO;

    private TopoCalculatorService topoCalculatorService;

    public void setMonitorTopoLocationDAO(MonitorTopoLocationDAO monitorTopoLocationDAO) {
        this.monitorTopoLocationDAO = monitorTopoLocationDAO;
    }

    public void setMonitorTopoGroupDAO(MonitorTopoGroupDAO monitorTopoGroupDAO) {
        this.monitorTopoGroupDAO = monitorTopoGroupDAO;
    }

    public void setMonitorTopoDeviceGroupDAO(MonitorTopoDeviceGroupDAO monitorTopoDeviceGroupDAO) {
        this.monitorTopoDeviceGroupDAO = monitorTopoDeviceGroupDAO;
    }

    public void setTopoCalculatorService(TopoCalculatorService topoCalculatorService) {
        this.topoCalculatorService = topoCalculatorService;
    }

    public List findAllMonitorTopoLocation() {
        String hql = "from MonitorTopoLocation order by locationindex asc";
        return monitorTopoLocationDAO.find(hql);
    }

    public void saveMonitorTopoLocation(MonitorTopoLocation monitorTopoLocation) {
        monitorTopoLocationDAO.save(monitorTopoLocation);
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public void updateMonitorTopoLocation(MonitorTopoLocation monitorTopoLocation) {
        monitorTopoLocationDAO.update(monitorTopoLocation);
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public void deleteMonitorTopoLocation(Integer locationId) {
        MonitorTopoLocation monitorTopoLocation = monitorTopoLocationDAO.get(locationId);
        if (monitorTopoLocation == null) {
            return;
        }
        //先找到该校区对应的所有组别信息
        List<MonitorTopoGroup> locations = monitorTopoGroupDAO.find("from MonitorTopoGroup tg where tg.location.locationid=" + locationId.toString());
        for (MonitorTopoGroup monitorTopoGroup : locations) {
            //删除设备与组的关联信息
            List<MonitorTopoDeviceGroup> deviceGroups = monitorTopoDeviceGroupDAO.find("from MonitorTopoDeviceGroup dg where dg.id.devicegroupid=" + monitorTopoGroup.getDevicegroupid());
            for (MonitorTopoDeviceGroup deviceGroup : deviceGroups) {
                monitorTopoDeviceGroupDAO.delete(deviceGroup);
            }
            //删除组别
            monitorTopoGroupDAO.delete(monitorTopoGroup);
        }

        //最后删除校区信息
        monitorTopoLocationDAO.delete(monitorTopoLocation);
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public MonitorTopoLocation getMonitorTopoLocation(Integer locationId) {
        return monitorTopoLocationDAO.get(locationId);
    }

    public List findAllMonitorTopoGroup() {
        String hql = "from MonitorTopoGroup order by location.locationid asc,groupxindex asc,groupyindex asc";
        return monitorTopoGroupDAO.find(hql);
    }

    public List findMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup) {
        StringBuffer hql = new StringBuffer("from MonitorTopoGroup t where 1=1");
        if (StringUtils.isNotBlank(monitorTopoGroup.getDevicegroupname())) {
            hql.append(" and t.devicegroupname like '%").append(monitorTopoGroup.getDevicegroupname()).append("%'");
        }
        if (monitorTopoGroup.getLocation().getLocationid() != null) {
            hql.append(" and t.location.locationid=").append(monitorTopoGroup.getLocation().getLocationid());
        }
        hql.append(" order by location.locationid asc,groupxindex asc,groupyindex asc");
        return monitorTopoGroupDAO.find(hql.toString());
    }

    public void saveMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup) {
        monitorTopoGroupDAO.save(monitorTopoGroup);
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public void updateMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup) {
        monitorTopoGroupDAO.update(monitorTopoGroup);
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public void deleteMonitorTopoGroup(Integer deviceGroupId) {
        //先删除设备与组的关联信息
        List deviceGroupList = monitorTopoDeviceGroupDAO.find("from MonitorTopoDeviceGroup dg where dg.id.devicegroupid=" + deviceGroupId);
        if (deviceGroupList != null) {
            for (int i = 0; i < deviceGroupList.size(); i++) {
                MonitorTopoDeviceGroup monitorTopoDeviceGroup = (MonitorTopoDeviceGroup) deviceGroupList.get(i);
                monitorTopoDeviceGroupDAO.delete(monitorTopoDeviceGroup);
            }
        }
        //再删除组别信息
        MonitorTopoGroup monitorTopoGroup = monitorTopoGroupDAO.get(deviceGroupId);
        if (monitorTopoGroup != null) {
            monitorTopoGroupDAO.delete(monitorTopoGroup);
        }
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    public MonitorTopoGroup getMonitorTopoGroup(Integer deviceGroupId) {
        return monitorTopoGroupDAO.get(deviceGroupId);
    }

    public List findBindingDevice(Integer deviceGroupId) {
        String hql = "select d.deviceid,d.devicename from TDevice d,MonitorTopoDeviceGroup dg where d.deviceid=dg.id.deviceid and dg.id.devicegroupid=" + deviceGroupId;
        List list = monitorTopoDeviceGroupDAO.find(hql);
        if (list == null) {
            list = new ArrayList();
        }
        return list;
    }

    public String getDeviceXmlTree(Integer deviceGroupId) {
        String sql = "select t.deviceid, t.devicename, t.fdeviceid, dg.devicegroupid from ykt_cur.t_device t left join ykt_mon.monitor_topo_device_group dg on dg.deviceid = t.deviceid";
        sql += " where t.status = 1 and t.devtypecode not in ('0228','1055','8001','8999','9000','9001','9002','9003','9004','9005') start with t.deviceid = 1 connect by t.fdeviceid = prior t.deviceid";
        List list = monitorTopoDeviceGroupDAO.findBySql(sql);
        return DeviceXmlUtil.generateXml(list);
    }

    /**
     * 为组别绑定设备
     *
     * @param deviceGroupId .
     * @param devices       .
     */
    public void updateBindingDevice(Integer deviceGroupId, Set devices) {
        //delete all devtem by templateId first
        String hql = "from MonitorTopoDeviceGroup dg where dg.id.devicegroupid=" + deviceGroupId;
        List oldList = monitorTopoDeviceGroupDAO.find(hql);
        if (oldList != null && oldList.size() > 0) {
            for (int i = 0; i < oldList.size(); i++) {
                monitorTopoDeviceGroupDAO.delete((MonitorTopoDeviceGroup) oldList.get(i));
            }
        }
        //insert new devtem
        Iterator iterator = devices.iterator();
        String deviceid;
        while (iterator.hasNext()) {
            deviceid = iterator.next().toString();
            MonitorTopoDeviceGroup entity = new MonitorTopoDeviceGroup();
            MonitorTopoDeviceGroupId id = new MonitorTopoDeviceGroupId();
            entity.setId(id);
            id.setDevicegroupid(deviceGroupId);
            id.setDeviceid(Integer.valueOf(deviceid));
            monitorTopoDeviceGroupDAO.save(entity);
        }
        //更新vml信息
        topoCalculatorService.calculateDevgroupInfo();
        topoCalculatorService.calculateDivHtml();
    }

    /**
     * 查找设备绑定情况
     *
     * @return .
     */
    public List findDeviceGroup(String[] conditions) {
        StringBuffer hql = new StringBuffer("select d.devicename,dic.dictcaption,g.devicegroupname,g.location.locationname from MonitorTopoDeviceGroup dg,TDevice d,TDictionary dic,MonitorTopoGroup g where dic.id.dictval=d.devtypecode and d.status=1 and dg.id.deviceid=d.deviceid and dg.id.devicegroupid=g.devicegroupid");
        if (StringUtils.isNotBlank(conditions[0])) {
            hql.append(" and d.devicename like '%").append(conditions[0]).append("%'");
        }
        if (StringUtils.isNotBlank(conditions[1])) {
            hql.append(" and g.devicegroupname like '%").append(conditions[1]).append("%'");
        }
        if (StringUtils.isNotBlank(conditions[2])) {
            hql.append(" and g.location.locationname like '%").append(conditions[2]).append("%'");
        }
        hql.append(" order by g.location.locationid asc,g.groupxindex asc,g.groupyindex asc");
        return ResultTransform.arrayToMap(monitorTopoDeviceGroupDAO.find(hql.toString()), new String[]{"devicename", "dictcaption", "devicegroupname", "locationname"});
    }
}
