package org.king.termdev.service.impl;

import org.apache.commons.beanutils.BeanComparator;
import org.apache.commons.collections.ComparatorUtils;
import org.apache.commons.collections.comparators.ComparableComparator;
import org.apache.commons.collections.comparators.ComparatorChain;
import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.template.util.DeviceXmlUtil;
import org.king.termdev.dao.*;
import org.king.termdev.domain.*;
import org.king.termdev.exception.TermdevServiceAlreadyExistException;
import org.king.termdev.service.TermdevService;
import org.king.utils.Contants;
import org.king.utils.DateUtil;
import org.king.utils.ResultTransform;

import java.sql.Types;
import java.util.*;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-10
 */
public class TermdevServiceImpl extends BaseService implements TermdevService {
    private static Log log = LogFactory.getLog(TermdevServiceImpl.class);

    private MonitorTermdevServiceDAO monitorTermdevServiceDAO;

    private MonitorTermdevserviceStatusDAO monitorTermdevserviceStatusDAO;

    private MonitorTermdeviceStatusDAO monitorTermdeviceStatusDAO;

    private MonitorDevtemDAO monitorDevtemDAO;

    private MonitorTermdevchecksDAO monitorTermdevchecksDAO;

    public void setMonitorTermdevServiceDAO(MonitorTermdevServiceDAO monitorTermdevServiceDAO) {
        this.monitorTermdevServiceDAO = monitorTermdevServiceDAO;
    }

    public void setMonitorTermdevserviceStatusDAO(MonitorTermdevserviceStatusDAO monitorTermdevserviceStatusDAO) {
        this.monitorTermdevserviceStatusDAO = monitorTermdevserviceStatusDAO;
    }

    public void setMonitorTermdeviceStatusDAO(MonitorTermdeviceStatusDAO monitorTermdeviceStatusDAO) {
        this.monitorTermdeviceStatusDAO = monitorTermdeviceStatusDAO;
    }

    public void setMonitorDevtemDAO(MonitorDevtemDAO monitorDevtemDAO) {
        this.monitorDevtemDAO = monitorDevtemDAO;
    }

    public void setMonitorTermdevchecksDAO(MonitorTermdevchecksDAO monitorTermdevchecksDAO) {
        this.monitorTermdevchecksDAO = monitorTermdevchecksDAO;
    }

    /**
     * 保存设备服务
     *
     * @param monitorTermdevService .
     */
    public void saveMonitorTermdevService(MonitorTermdevService monitorTermdevService) throws TermdevServiceAlreadyExistException {
        if (monitorTermdevServiceDAO.isExistMonitorTermdevService(monitorTermdevService.getDevserviceName())) {
            throw new TermdevServiceAlreadyExistException("该设备服务名称已被使用！");
        }
        monitorTermdevServiceDAO.save(monitorTermdevService);
    }

    public List findAllMonitorTermdevService() {
        return monitorTermdevServiceDAO.getAll();
    }

    /**
     * 分页查找MonitorTermdevService对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorTermdevServiceByPage(DBPaginatedList page, MonitorTermdevService monitorTermdevService) {
        String hql = "from MonitorTermdevService";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加查询条件
        if (StringUtils.isNotBlank(monitorTermdevService.getDevserviceName())) {
            queryTranslate.addLikeCondition("devserviceName", monitorTermdevService.getDevserviceName());
        }
        if (StringUtils.isNotBlank(monitorTermdevService.getCheckCommand().getCommandName())) {
            queryTranslate.addLikeCondition("checkCommand.commandName", monitorTermdevService.getCheckCommand().getCommandName());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTermdevServiceDAO.findMonitorTermdevServiceByPage(page, queryTranslate);
    }

    /**
     * 根据id查找设备服务
     *
     * @param id .
     * @return .
     */
    public MonitorTermdevService findMonitorTermdevServiceById(Integer id) {
        return monitorTermdevServiceDAO.get(id);
    }

    /**
     * 更新设备服务
     *
     * @param monitorTermdevService .
     */
    public void updateMonitorTermdevService(MonitorTermdevService monitorTermdevService) {
        monitorTermdevServiceDAO.update(monitorTermdevService);
    }

    /**
     * 根据id删除设备服务
     *
     * @param id .
     */
    public void deleteMonitorTermdevService(Integer id) {
        monitorTermdevServiceDAO.delete(findMonitorTermdevServiceById(id));
    }

    public void findMonitorTermdevserviceStatusByPage(DBPaginatedList page, MonitorTermdevserviceStatus monitorTermdevserviceStatus) {
        String hql = "from MonitorTermdevserviceStatus";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //todo 添加查询条件
        if (monitorTermdevserviceStatus.getCurrentState() != null && monitorTermdevserviceStatus.getCurrentState().intValue() != -1) {
            queryTranslate.addEqualCondition("currentState", monitorTermdevserviceStatus.getCurrentState());
        }

        //设置排序规则
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorTermdevserviceStatusDAO.findMonitorTermdevserviceStatusByPage(page, queryTranslate);
    }

    /**
     * 统计设备服务状态
     *
     * @return .
     */
    public String[][] calculateTermdevserviceStatus() {
        String hql = "select t.currentState,count(t) from MonitorTermdevserviceStatus t group by t.currentState order by t.currentState";
        List list = monitorTermdevserviceStatusDAO.find(hql);

        String[][] result = new String[][]{{"ok", "0"}, {"warning", "0"}, {"critical", "0"}};
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                int state = Integer.parseInt(row[0].toString());
                result[state][1] = row[1].toString();
            }
        }
        return result;
    }

    public void findMonitorTermdeviceStatusByPage(DBPaginatedList page, String[] conditions) {
        String hql = "select d.devicename as devicename,p.devicename as fdevicename,s.deviceId as deviceId,s.currentState as currentState,s.lastCheck as lastCheck,s.lastStateChange as lastStateChange,s.output as output from MonitorTermdeviceStatus s,TDevice d,TDevice p,MonitorDevtem dt where s.deviceId=d.deviceid and d.fdeviceid=p.deviceid and d.status=1 and dt.deviceid=d.deviceid";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加设备名称，父设备名称，当前状态查询条件
        if (StringUtils.isNotBlank(conditions[0])) {
            queryTranslate.addLikeCondition("d.devicename", conditions[0]);
        }
        if (StringUtils.isNotBlank(conditions[1])) {
            queryTranslate.addLikeCondition("p.devicename", conditions[1]);
        }
        if (StringUtils.isNotBlank(conditions[2]) && !"-1".equals(conditions[2])) {
            queryTranslate.addEqualCondition("s.currentState", conditions[2]);
        }
        if (StringUtils.isNotBlank(conditions[3])) {
            queryTranslate.addEqualCondition("dt.templateid", conditions[3]);
        }
        if (StringUtils.isNotBlank(conditions[4])) {
            queryTranslate.addEqualCondition("d.devtypecode", conditions[4]);
        }
        if (StringUtils.isNotBlank(conditions[5])) {
            queryTranslate.addEqualCondition("d.deviceid", conditions[5]);
        }
        if (StringUtils.isNotBlank(conditions[6])) {
            queryTranslate.addEqualCondition("d.fdeviceid", conditions[6]);
        }
        if ("1".equals(conditions[7])) {
            String devtypecode = Contants.getFormatDevtypeCode();
            queryTranslate.setQueryString("select d.devicename as devicename,p.devicename as fdevicename,s.deviceId as deviceId,s.currentState as currentState,s.lastCheck as lastCheck,s.lastStateChange as lastStateChange,s.output as output from MonitorTermdeviceStatus s,TDevice d,TDevice p,MonitorDevtem dt where s.deviceId=d.deviceid and d.fdeviceid=p.deviceid and d.status=1 and dt.deviceid=d.deviceid and (p.devtypecode is null or p.devtypecode not in ("+devtypecode+", '0010', '0020'))");
        }

        //设置排序规则，默认按照当前状态来排序
        if (StringUtils.isBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by s.currentState desc,p.devicename,d.devicename");
        } else if ("p.devicename".equals(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by p.devicename " + page.getOrder()+",d.devicename");
        } else if("d.devicename".equals(page.getSortCriterion())){
            queryTranslate.setOrderby(" order by d.devicename " + page.getOrder());
        } else if("s.lastStateChange".equals(page.getSortCriterion())){
            //持续时间=当前时间-上次状态变换时间，所以持续时间的升序排列即对应状态变换的倒叙排列
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOppositeOrder() + ",p.devicename,d.devicename");
        } else {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder() + ",p.devicename,d.devicename");
        }

        monitorTermdeviceStatusDAO.findMonitorTermdeviceStatusByPage(page, queryTranslate);
        String[] keys = new String[]{"devicename", "fdevicename", "deviceId", "currentState", "lastCheck", "lastStateChange", "output"};
        page.setResult(ResultTransform.arrayToMap(page.getList(), keys));
    }

    /**
     * 统计设备状态
     *
     * @return .
     */
    public String[][] calculateTermdeviceStatus() {
        String hql = "select t.currentState,count(t) from MonitorTermdeviceStatus t,TDevice d,TDevice p,MonitorDevtem dt where t.deviceId=d.deviceid and d.fdeviceid=p.deviceid and d.status=1 and dt.deviceid=d.deviceid group by t.currentState order by t.currentState";
        List list = monitorTermdevserviceStatusDAO.find(hql);

        String[][] result = new String[][]{{"up", "0"}, {"down", "0"}, {"unreachable", "0"}};
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                int state = Integer.parseInt(row[0].toString());
                result[state][1] = row[1].toString();
            }
        }
        return result;
    }

    /**
     * Description: 返回状态表所有信息
     *
     * @param @return
     * @return List
     *         Modify History: 2010-7-16 Linqing.He create
     */
    public List getAllTermdevStatus() {
        List list = monitorTermdeviceStatusDAO.getAll();
        return list;
    }

    public List getSqlList(String sql) {
        List list = monitorTermdeviceStatusDAO.find(sql);
        return list;
    }

    public MonitorTermdeviceStatus getMonitorTermdeviceStatus(Integer deviceid) {
        return monitorTermdeviceStatusDAO.get(deviceid);
    }

    public void updateMonitormonitorTermdeviceStatus(MonitorTermdeviceStatus monitorTermdeviceStatus) {
        monitorTermdeviceStatusDAO.update(monitorTermdeviceStatus);
    }

    public void saveMonitormonitorTermdeviceStatus(MonitorTermdeviceStatus monitorTermdeviceStatus) {
        monitorTermdeviceStatusDAO.save(monitorTermdeviceStatus);
    }

    public void findTDeviceByPage(DBPaginatedList page, String[] conditions) {
        //0010 圈存机，0020 多媒体机
        //如果templateId不为空，那么和MonitorTermdevTemplate关联进行查询
        String hql;
        if (StringUtils.isNotBlank(conditions[2])) {
            hql = "select p.devicename,d.devicename,d.deviceid,dic.dictcaption,d.deviceid from TDevice d,TDevice p,TDictionary dic,MonitorDevtem dt,MonitorTermdevTemplate t where dic.id.dictval=d.devtypecode and d.fdeviceid=p.deviceid and d.status=1 and d.devtypecode<>'0010' and d.devtypecode<>'0020' and dt.deviceid=d.deviceid and dt.templateid=t.templateId and t.templateId=" + conditions[2];
        } else {
            hql = "select p.devicename,d.devicename,d.deviceid,dic.dictcaption,d.deviceid from TDevice d,TDevice p,TDictionary dic where dic.id.dictval=d.devtypecode and d.fdeviceid=p.deviceid and d.status=1 and d.devtypecode<>'0010' and d.devtypecode<>'0020'";
        }

        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(conditions[0])) {
            queryTranslate.addLikeCondition("p.devicename", conditions[0]);
        }
        if (StringUtils.isNotBlank(conditions[1])) {
            queryTranslate.addLikeCondition("d.devicename", conditions[1]);
        }
        if (StringUtils.isNotBlank(conditions[3])) {
            queryTranslate.addEqualCondition("d.devtypecode", conditions[3]);
        }

        //设置排序规则
        page.setSortCriterion("d.fdeviceid,d.deviceid");
        queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());

        monitorDevtemDAO.findTDeviceByPage(page, queryTranslate);
        page.setResult(toDeviceMap(page.getList()));
    }

    /**
     * 获得设备字典类型
     *
     * @return .
     */
    public Map getDeviceType() {
        String hql = "select dic.id.dictval,dic.dictcaption from TDictionary dic where dic.id.dictval<>'0010' and dic.id.dictval<>'0020' and dic.id.dicttype=47";
        List list = monitorDevtemDAO.find(hql);

        Map result = new HashMap();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                result.put(row[0].toString(), row[1].toString());
            }
        }
        return result;
    }

    /**
     * 根据设备id查找对应的模板
     *
     * @param deviceid .
     * @return
     */
    public String getTemplateIdByDeviceid(Integer deviceid) {
        String hql = "select t.templateId from MonitorTermdevTemplate t,MonitorDevtem d where d.templateid=t.templateId and d.deviceid=" + deviceid;
        List list = monitorDevtemDAO.find(hql);
        String templateId = "";
        if (list != null && list.size() > 0) {
            templateId = (list.get(0)).toString();
        }
        return templateId;
    }

    private Map findAllTermdevTemplate() {
        String hql = "select dt.deviceid,t.templateName from MonitorDevtem dt,MonitorTermdevTemplate t where dt.templateid=t.templateId";
        List list = monitorDevtemDAO.find(hql);
        Map result = new HashMap();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                result.put(row[0].toString(), row[1].toString());
            }
        }
        return result;
    }

    /**
     * 将设备查询结果中的数组转换成数组
     * todo 使用query中的transform来转换
     *
     * @param list .
     */
    private List toDeviceMap(List list) {
        List result = new ArrayList();
        Map template = findAllTermdevTemplate();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Map map = new HashMap();
                map.put("fdevicename", row[0].toString());
                map.put("devicename", row[1].toString());
                map.put("templateName", template.get(row[2].toString()));
                map.put("dictcaption", row[3].toString());
                map.put("deviceid", row[4].toString());
                result.add(map);
            }
        }
        return result;
    }

    /**
     * 根据设备id查找对应的设备与模板的关联实体
     *
     * @param deviceid .
     * @return .
     */
    public MonitorDevtem getMonitorDevtem(Integer deviceid) {
        return monitorDevtemDAO.get(deviceid);
    }

    /**
     * 更新设备与模板的关联
     *
     * @param monitorDevtem .
     */
    public void saveOrUpdateMonitorDevtem(MonitorDevtem monitorDevtem) {
        boolean isExist = monitorDevtemDAO.isExistMonitorDevtem(monitorDevtem.getDeviceid());
        if (isExist) {
            //如果关联模板为空，那么删除关联表中的记录
            if (monitorDevtem.getTemplateid() == null) {
                monitorDevtemDAO.delete(monitorDevtemDAO.get(monitorDevtem.getDeviceid()));
            } else {
                MonitorDevtem entity = monitorDevtemDAO.get(monitorDevtem.getDeviceid());
                entity.setTemplateid(monitorDevtem.getTemplateid());
                monitorDevtemDAO.update(entity);
            }
        } else {
            if (monitorDevtem.getTemplateid() != null) {
                monitorDevtemDAO.save(monitorDevtem);
            }
        }
    }

    /**
     * 根据设备id查找设备名称
     *
     * @param deviceid .
     * @return .
     */
    public String getTDeviceName(Integer deviceid) {
        String hql = "select t.devicename from TDevice t where t.deviceid=" + deviceid;
        String result = "";
        List list = monitorDevtemDAO.find(hql);
        if (list != null && list.size() > 0) {
            result = list.get(0).toString();
        }
        return result;
    }

    /**
     * 根据设备模板查找该模板当前已关联的设备
     *
     * @param templateId .
     * @return .
     */
    public List findBindingDevice(Integer templateId) {
        String hql = "select d.deviceid,d.devicename from TDevice d,MonitorDevtem dev where d.deviceid=dev.deviceid and dev.templateid=" + templateId;
        List list = monitorDevtemDAO.find(hql);
        if (list == null) {
            list = new ArrayList();
        }
        return list;
    }

    /**
     * 获得未和templateId对应模板之外的其他模板关联的所有设备，包括未和模板关联的设备以及和templateId对应模板关联的设备
     *
     * @param templateId .
     * @return .
     */
    public String getDeviceXmlTree(Integer templateId) {
        String sql = "select t.deviceid,t.devicename,t.fdeviceid from t_device t where t.status=1 start with t.deviceid=1 connect by t.fdeviceid=prior deviceid";
        sql = "select t.deviceid, t.devicename, t.fdeviceid,dt.templateid from t_device t left join ykt_mon.monitor_devtem dt on dt.deviceid = t.deviceid where t.status = 1 start with t.deviceid = 1 connect by t.fdeviceid = prior t.deviceid ";
        List list = monitorDevtemDAO.findBySql(sql);
        return DeviceXmlUtil.generateXml(list);
    }

    /**
     * devices为要绑定在templateId对应模板上的设备id的集合，集合里为字符串形式id
     * todo 提高效率，可以先比较，再更新
     *
     * @param templateId .
     * @param devices    .
     */
    public void updateBindingDevice(Integer templateId, Set devices) {
        //delete all devtem by templateId first
        String hql = "from MonitorDevtem dt where dt.templateid=" + templateId;
        List oldList = monitorDevtemDAO.find(hql);
        if (oldList != null && oldList.size() > 0) {
            for (int i = 0; i < oldList.size(); i++) {
                monitorDevtemDAO.delete((MonitorDevtem) oldList.get(i));
            }
        }
        //insert new devtem
        Iterator iterator = devices.iterator();
        String deviceid;
        while (iterator.hasNext()) {
            deviceid = iterator.next().toString();
            MonitorDevtem entity = new MonitorDevtem();
            entity.setTemplateid(templateId);
            entity.setDeviceid(Integer.valueOf(deviceid));
            monitorDevtemDAO.save(entity);
        }
    }

    public List findMonitorTermdevchecks(Integer deviceId, Date startTime, Date endTime) {
        String hql = "from MonitorTermdevchecks c where c.deviceId=? and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
        MyQuery myQuery = new MyQuery();
        myQuery.setQueryString(hql);

        String startTimeStr = DateUtil.formatDate(startTime);
        String endTimeStr = DateUtil.formatDate(endTime);
        myQuery.addPara(deviceId, Types.INTEGER);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        return monitorTermdevchecksDAO.find(myQuery);
    }

    public void findTermdevHistoryStatusByPage(DBPaginatedList page, Object[] conditions) {
        String hql;
        if (conditions[4] != null && StringUtils.isNotBlank(conditions[4].toString())) {
            hql = "select c.deviceId from MonitorTermdevchecks c,TDevice d,TDevice p,MonitorDevtem dt where dt.deviceid=d.deviceid and c.deviceId=d.deviceid and d.fdeviceid=p.deviceid and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
        } else {
            hql = "select c.deviceId from MonitorTermdevchecks c,TDevice d,TDevice p where c.deviceId=d.deviceid and d.fdeviceid=p.deviceid and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
        }
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        String startTime = DateUtil.formatDate((Date) conditions[2]);
        String endTime = DateUtil.formatDate((Date) conditions[3]);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(endTime, Types.VARCHAR);
        queryTranslate.addPara(endTime, Types.VARCHAR);
        if (conditions[0] != null && StringUtils.isNotBlank(conditions[0].toString())) {
            queryTranslate.addLikeCondition("p.devicename", conditions[0].toString());
        }
        if (conditions[1] != null && StringUtils.isNotBlank(conditions[1].toString())) {
            queryTranslate.addLikeCondition("d.devicename", conditions[1].toString());
        }
        if (conditions[4] != null && StringUtils.isNotBlank(conditions[4].toString())) {
            queryTranslate.addEqualCondition("dt.templateid", Integer.valueOf(conditions[4].toString()));
        }

        //设置排序规则
        queryTranslate.setGroupby(" group by c.deviceId,p.devicename,d.devicename");
        queryTranslate.setOrderby(" order by p.devicename desc,d.devicename desc");

        monitorTermdevchecksDAO.findMonitorTermdevchecksByPage(page, queryTranslate);
        if (page.getList() != null && page.getList().size() > 0) {
            List result = ResultTransform.calculateStatusResult(combineMonitorTermdevchecks(monitorTermdevchecksDAO.find(composeTermdevHistoryQuery(queryTranslate, page.getList())), (Date) conditions[2], (Date) conditions[3]), Contants.TERMDEVICE_STATUS);
            ResultTransform.sortResult(result, new String[]{"fdevicename", "deviceId"});
            page.setResult(result);
            MyQuery countQuery = ResultTransform.getMyQuery(queryTranslate, "select count(distinct c.deviceId)");
            page.setTotalCount(ResultTransform.getCount(monitorTermdevchecksDAO.find(countQuery)).intValue());
        }
        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("fdevicename", comparator));    
        sortFields.add(new BeanComparator("devicename", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(page.getList(), multiSort);
    }

    /**
     * 根据当前页的设备id查找出该设备id在满足条件下对应的历史记录
     *
     * @param queryTranslate .
     * @param deviceIds      .
     */
    public MyQuery composeTermdevHistoryQuery(QueryTranslate queryTranslate, List deviceIds) {
        MyQuery myQuery = new MyQuery();
        myQuery.getParalist().addAll(queryTranslate.getParalist());
        myQuery.setOrderby(queryTranslate.getOrderby());

        StringBuffer hql = new StringBuffer("select c.deviceId,p.devicename,d.devicename,c.state,c.startTime,c.endTime ");
        String queryString = queryTranslate.getQueryString();
        int index = queryString.indexOf("from");
        if (index != -1) {
            hql.append(queryString.substring(index, queryString.length()));
        }
        hql.append("and c.deviceId in (");
        for (int i = 0; i < deviceIds.size(); i++) {
            hql.append("?,");
            myQuery.addPara(deviceIds.get(i), Types.INTEGER);
        }
        hql.deleteCharAt(hql.length() - 1);
        hql.append(")");
        myQuery.setQueryString(hql.toString());
        return myQuery;
    }

    /**
     * 根据状态统计每个设备对应状态所占的比例
     *
     * @param list      .
     * @param startTime .
     * @param endTime   .
     * @return .
     */
    private Map combineMonitorTermdevchecks(List list, Date startTime, Date endTime) {
        String now = DateUtil.getNow();
        Map map = new HashMap();
        //每一个设备将对应一个map，其中存放fdevicename，devicename,deviceId，各种状态对应的持续时间
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Object deviceId = row[0];

                //计算当前记录持续时间
                long duration;
                if (row[5] == null) {
                    duration = DateUtil.getDuration(row[4].toString(), now, startTime, endTime);
                } else {
                    duration = DateUtil.getDuration(row[4].toString(), row[5].toString(), startTime, endTime);
                }

                Map termdevchecks;
                Object value = map.get(deviceId);
                if (value == null) {
                    termdevchecks = new HashMap();
                    termdevchecks.put("deviceId", row[0]);
                    termdevchecks.put("fdevicename", row[1]);
                    termdevchecks.put("devicename", row[2]);
                    termdevchecks.put(row[3], Long.valueOf(duration));
                    termdevchecks.put("total", Long.valueOf(duration));
                    map.put(deviceId, termdevchecks);
                } else {
                    termdevchecks = (Map) value;
                    //增量式添加
                    termdevchecks.put("total", ((Long) termdevchecks.get("total")).longValue() + duration);
                    //先找出相同状态当前对应的总持续时间，如果存在，则在此基础上加上现在的持续时间
                    Object totalDuration = termdevchecks.get(row[3]);
                    if (totalDuration != null) {
                        duration = ((Long) totalDuration).longValue() + duration;
                    }
                    //value不为空的时候，total肯定也不为空
                    termdevchecks.put(row[3], Long.valueOf(duration));
                }
            }
        }
        return map;
    }

    public void findMonitorTermdevchecksByPage(DBPaginatedList page, Object[] conditions) {
        String hql = "select c.state,c.startTime,c.endTime,c.output from MonitorTermdevchecks c where ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null)) and c.deviceId=?";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        String startTime = DateUtil.formatDate((Date) conditions[2]);
        String endTime = DateUtil.formatDate((Date) conditions[3]);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(startTime, Types.VARCHAR);
        queryTranslate.addPara(endTime, Types.VARCHAR);
        queryTranslate.addPara(endTime, Types.VARCHAR);
        queryTranslate.addPara(conditions[0], Types.INTEGER);
        if (conditions[1] != null && StringUtils.isNotBlank(conditions[1].toString()) && !"-1".equals(conditions[1])) {
            queryTranslate.addEqualCondition("c.state", conditions[1].toString());
        }

        //设置排序规则
        queryTranslate.setOrderby(" order by c.endTime desc");

        monitorTermdevchecksDAO.findMonitorTermdevchecksByPage(page, queryTranslate);
        page.setResult(convertMonitorTermdevchecks(page.getList(), startTime, endTime));
    }

    private List convertMonitorTermdevchecks(List list, String startTime, String endTime) {
        List result = new ArrayList();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Map map = new HashMap();
                map.put("state", row[0]);
                if (startTime.compareTo(row[1].toString()) > 0) {
                    map.put("startTime", startTime);
                } else {
                    map.put("startTime", row[1]);
                }
                String rowEndTime;
                if (row[2] == null) {
                    //if endTime is null,then now time is the default value,and now time is bigger than endTime,so we put the endTime into the map
                    rowEndTime = endTime;
                } else {
                    if (endTime.compareTo(row[2].toString()) < 0) {
                        rowEndTime = endTime;
                    } else {
                        rowEndTime = row[2].toString();
                    }
                }
                map.put("endTime", rowEndTime);

                map.put("output", row[3]);
                long duration = DateUtil.getDuration(row[1].toString(), rowEndTime);
                map.put("duration", DateUtil.convertTime(duration, DateUtil.duration, DateUtil.alias, 4));
                result.add(map);
            }
        }
        return result;
    }

    public void saveMonitorTermdevchecks(MonitorTermdevchecks MTdevchecks) throws BusinessException {
        monitorTermdevchecksDAO.save(MTdevchecks);
    }

    public MonitorTermdevchecks getLattestMonitorTermdevchecks(Integer Objectid) {
        String hql = "from MonitorTermdevchecks c where c.deviceId=" + Objectid + " and c.endTime is null";
        List list = monitorTermdevchecksDAO.find(hql);
        if (list != null && list.size() > 0) {
            return (MonitorTermdevchecks) list.get(0);
        }
        return null;
    }

    public void updateMonitorTermdevchecks(MonitorTermdevchecks MTdevchecks) throws BusinessException {
        monitorTermdevchecksDAO.update(MTdevchecks);
    }

    /**
     * 统计一级设备状态
     *
     * @return .
     */
    public List categorizeDeviceStatus() {
        String devtypecode = Contants.getFormatDevtypeCode();
        //先统计ccu和lanport的子设备状态
        StringBuffer parentSql = new StringBuffer("select count(p.deviceid), p.deviceid, p.devicename, ts.current_state,p.devtypecode,dic.dictcaption");
        parentSql.append(" from ykt_cur.t_device p, ykt_cur.t_dictionary dic,ykt_cur.t_device d,ykt_mon.monitor_termdevice_status ts");
        parentSql.append(" where ts.device_id = d.deviceid and d.status = 1 and dic.dictval=p.devtypecode and d.fdeviceid = p.deviceid and p.status = 1 and p.devtypecode in (").append(devtypecode).append(")");
        parentSql.append(" group by p.deviceid, p.devicename, ts.current_state,p.devtypecode,dic.dictcaption");
        Map parentMap = dealDeviceStatus(monitorDevtemDAO.findBySql(parentSql.toString()));

        StringBuffer leafSql = new StringBuffer("select count(d.deviceid), d.devtypecode, '', ts.current_state,d.devtypecode,dic.dictcaption");
        leafSql.append(" from ykt_cur.t_dictionary dic, ykt_cur.t_device d,ykt_mon.monitor_termdevice_status ts,ykt_cur.t_device p");
        leafSql.append(" where ts.device_id = d.deviceid and dic.dictval = d.devtypecode and d.status = 1  and d.devtypecode not in (").append(devtypecode).append(", '0010', '0020') and p.deviceid=d.fdeviceid and nvl(p.devtypecode,' ') not in (").append(devtypecode).append(",'0010', '0020')");
        leafSql.append(" group by d.devtypecode, dic.dictcaption, ts.current_state");
        Map leafMap = dealDeviceStatus(monitorDevtemDAO.findBySql(leafSql.toString()));

        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("down", comparator));
        sortFields.add(new BeanComparator("unreachable",comparator));
        sortFields.add(new BeanComparator("code",comparator));

        ComparatorChain multiSort = new ComparatorChain(sortFields);

        List result = new ArrayList();
        result.addAll(getValueList(parentMap));
        result.addAll(getValueList(leafMap));

        Collections.sort(result, multiSort);
        return result;
    }

    /**
     * 合并设备状态统计
     *
     * @param list .
     */
    private Map dealDeviceStatus(List list) {
        Map result = new HashMap();
        if (list == null) {
            return result;
        }
        String[] states = new String[]{"up","down","unreachable"};
        //用于存储显示结果的结构Map{up:0,down:0,unreachable:0,code,name,caption,id}
        for (int i = 0; i < list.size(); i++) {
            Object[] row = (Object[]) list.get(i);
            String id = row[1].toString();
            String name = row[2] == null ? "" : row[2].toString();
            String code = row[4].toString();
            String caption = row[5].toString();

            Map value = (Map) result.get(id);
            if (value == null) {
                value = new HashMap();
                value.put("up", Integer.valueOf(0));
                value.put("down", Integer.valueOf(0));
                value.put("unreachable", Integer.valueOf(0));
                value.put("code", code);
                value.put("name", name);
                value.put("caption", caption);
                value.put("id", id);
                result.put(id, value);
            }
            if (row[3] != null) {
                Integer state = Integer.valueOf(row[3].toString());
                Integer currentCount = Integer.valueOf(row[0].toString());
                Integer lastCount = (Integer) value.get(states[state]);
                value.put(states[state], currentCount + lastCount);
            }
        }
        return result;
    }

    private List getValueList(Map map) {
        List result = new ArrayList();
        result.addAll(map.values());
        return result;
    }

    public List findBsverErrorWarningList(String blackSheet_warning_sherold,String blackSheet_critical_sherold) {
		return monitorTermdevServiceDAO.find("select t from TDevice t,MonitorDevtem m " +
				"where t.deviceid=m.deviceid and t.cardverno<='"+blackSheet_warning_sherold+"' " +
						"and t.cardverno>='"+blackSheet_critical_sherold+"' and t.status=1 " +
						"and (t.devtypecode='0226' or t.devtypecode='0201' or t.devtypecode='0232') " +
						"and t.cardverno is not null and t.cardverno<>'000000000000' order by t.cardverno");
	}

	public List findBsverErrorCriticalList(String blackSheet_warning_sherold,String blackSheet_critical_sherold) {
		return monitorTermdevServiceDAO.find("select t from TDevice t,MonitorDevtem m " +
				"where t.deviceid=m.deviceid " +
						"and t.cardverno<'"+blackSheet_critical_sherold+"' and t.status=1 " +
						"and (t.devtypecode='0226' or t.devtypecode='0201' or t.devtypecode='0232') " +
						"and t.cardverno is not null and t.cardverno<>'000000000000' order by t.cardverno");
	}

	public String getmaxVolumeTimeFromTcardVer() {
		List list = monitorTermdevServiceDAO.find("select a.accdate||a.acctime from TTransdtl a,TCardver b " +
				"where t.accdate=b.accdate and t.termid=b.termid and t.termseqno=b.termseqno " +
				"and b.cardverno=(select max(cardverno) as maxVolume from TCardver)");
		if(list!=null&&list.size()>0){
			return (String)list.get(0);
		}
		return null;
	}
	 public String getVolumeFromTcardVer(String blackSheet_sherold,String max_blackSheet_sherold){
		 List list = monitorTermdevServiceDAO.find("(select max(b.cardverno) as maxVolume from TTransdtl a,TCardver b " +
					"where t.accdate=b.accdate and t.termid=b.termid and t.termseqno=b.termseqno " +
					"and a.accdate||a.acctime<='"+blackSheet_sherold+"' and a.accdate||a.acctime>='"+max_blackSheet_sherold+"'");
			if(list!=null&&list.size()>0){
				return (String)list.get(0);
			}
			return null;
	 }
}
