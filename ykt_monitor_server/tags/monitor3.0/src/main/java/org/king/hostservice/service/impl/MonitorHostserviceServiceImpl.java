package org.king.hostservice.service.impl;

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
import org.king.hostservice.dao.MonitorServiceCheckDAO;
import org.king.hostservice.dao.MonitorServiceDAO;
import org.king.hostservice.dao.MonitorServiceStatusDAO;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceAll;
import org.king.hostservice.domain.MonitorServiceCheck;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.utils.Contants;
import org.king.utils.DateUtil;
import org.king.utils.ResultTransform;

import java.sql.Types;
import java.util.*;

public class MonitorHostserviceServiceImpl extends BaseService implements MonitorHostserviceService {

    private static Log log = LogFactory.getLog(MonitorHostserviceServiceImpl.class);

    private MonitorServiceDAO monitorServiceDAO;
    private MonitorServiceStatusDAO monitorServiceStatusDAO;
    private MonitorServiceCheckDAO monitorServiceCheckDAO;

    public void setMonitorServiceDAO(MonitorServiceDAO monitorServiceDAO) {
        this.monitorServiceDAO = monitorServiceDAO;
    }

    public void setMonitorServiceStatusDAO(MonitorServiceStatusDAO monitorServiceStatusDAO) {
        this.monitorServiceStatusDAO = monitorServiceStatusDAO;
    }


    public void setMonitorServiceCheckDAO(MonitorServiceCheckDAO monitorServiceCheckDAO) {
        this.monitorServiceCheckDAO = monitorServiceCheckDAO;
    }

    public MonitorService getMonitorService(Integer Objectid) {
        return monitorServiceDAO.get(Objectid);
    }

    public MonitorServiceStatus getMonitorServiceStatus(Integer Objectid) {
        return monitorServiceStatusDAO.get(Objectid);
    }


    public void saveMonitorServiceStatus(MonitorServiceStatus monitorServiceStatus)
            throws BusinessException {
        monitorServiceStatusDAO.save(monitorServiceStatus);

    }


    public void updateMonitorServiceStatus(MonitorServiceStatus monitorServiceStatus)
            throws BusinessException {
        monitorServiceStatusDAO.update(monitorServiceStatus);

    }

    /**
     * 保存主机服务
     *
     * @param monitorService .
     */
    public void saveMonitorService(MonitorService monitorService) {
        monitorServiceDAO.save(monitorService);
    }

    public List findAllMonitorService() {
        return monitorServiceDAO.getAll();
    }

    public List findMonitorService(Integer hostId) {
        String hql = "from MonitorService s where s.monitorHost.hostId=" + hostId;
        return monitorServiceDAO.find(hql);
    }

    /**
     * 分页查找MonitorService对象，查询条件MyQuery统一在service中构造并初始化
     *
     * @param page 。
     */
    public void findMonitorServiceByPage(DBPaginatedList page, MonitorService monitorService) {
        String hql = "from MonitorService s";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //添加查询条件
        if (StringUtils.isNotBlank(monitorService.getServiceName())) {
            queryTranslate.addLikeCondition("s.serviceName", monitorService.getServiceName());
        }
        if (StringUtils.isNotBlank(monitorService.getMonitorHost().getAlias())) {
            queryTranslate.addLikeCondition("s.monitorHost.alias", monitorService.getMonitorHost().getAlias());
        }
        if (StringUtils.isNotBlank(monitorService.getCheckCommand().getCommandName())) {
            queryTranslate.addLikeCondition("s.checkCommand.commandName", monitorService.getCheckCommand().getCommandName());
        }

        //设置排序规则
        queryTranslate.setOrderby(" order by s.monitorHost.hostId,s.serviceId " + page.getOrder());

        monitorServiceDAO.findMonitorServiceByPage(page, queryTranslate);
    }

    /**
     * 更新主机服务对象
     *
     * @param monitorService .
     */
    public void updateMonitorService(MonitorService monitorService) {
        monitorServiceDAO.update(monitorService);
    }

    /**
     * 根据id删除主机服务对象
     * delete status and check first
     *
     * @param id .
     */
    public void deleteMonitorService(Integer id) {
        monitorServiceStatusDAO.execute("delete from MonitorServiceStatus t where t.serviceId=" + id);
        monitorServiceCheckDAO.execute("delete from MonitorServiceCheck t where t.serviceId=" + id);
        monitorServiceDAO.delete(getMonitorService(id));
    }

    public List findMonitorServiceCheck(Integer serviceId, Date startTime, Date endTime) {
        String hql = "from MonitorServiceCheck c where c.serviceId=? and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
        MyQuery myQuery = new MyQuery();
        myQuery.setQueryString(hql);

        String startTimeStr = DateUtil.formatDate(startTime);
        String endTimeStr = DateUtil.formatDate(endTime);
        myQuery.addPara(serviceId, Types.INTEGER);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        return monitorServiceCheckDAO.find(myQuery);
    }

    public void findMonitorServiceStatusByPage(DBPaginatedList page, String[] conditions) {
        String hql = "select ss.serviceId as serviceId,h.displayName as displayName,s.serviceName as serviceName,ss.currentState as currentState,ss.lastCheck as lastCheck,ss.lastStateChange as lastStateChange,ss.currentCheckAttempt as currentCheckAttemp,ss.maxCheckAttempts as maxCheckAttemps,ss.output as output from MonitorServiceStatus ss,MonitorService s,MonitorHost h where ss.serviceId=s.serviceId and s.monitorHost.hostId=h.hostId";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(conditions[0])) {
            queryTranslate.addLikeCondition("h.displayName", conditions[0]);
        }
        if (StringUtils.isNotBlank(conditions[1])) {
            queryTranslate.addLikeCondition("s.serviceName", conditions[1]);
        }
        if (StringUtils.isNotBlank(conditions[2]) && !"-1".equals(conditions[2])) {
            queryTranslate.addEqualCondition("ss.currentState", conditions[2]);
        }

        //设置排序规则，默认按照当前状态来排序
        if (StringUtils.isBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by ss.currentState desc,h.displayName,s.serviceName");
        } else if ("h.displayName".equals(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by h.displayName " + page.getOrder()+",s.serviceName");
        } else if("s.serviceName".equals(page.getSortCriterion())){
            queryTranslate.setOrderby(" order by s.serviceName " + page.getOrder());
        } else if("ss.lastStateChange".equals(page.getSortCriterion())){
            //持续时间=当前时间-上次状态变换时间，所以持续时间的升序排列即对应状态变换的倒叙排列
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOppositeOrder() + ",h.displayName,s.serviceName");
        } else {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder() + ",h.displayName,s.serviceName");
        }

        monitorServiceStatusDAO.findMonitorServiceStatusByPage(page, queryTranslate);
        String[] keys = new String[]{"serviceId", "displayName", "serviceName", "currentState", "lastCheck", "lastStateChange", "currentCheckAttempt", "maxCheckAttempts", "output"};
        page.setResult(ResultTransform.arrayToMap(page.getList(), keys));
    }

    /**
     * 统计服务状态
     *
     * @return
     */
    public String[][] calculateServiceStatus() {
        String hql = "select t.currentState,count(t) from MonitorServiceStatus t group by t.currentState order by t.currentState";
        List list = monitorServiceStatusDAO.find(hql);

        String[][] result = new String[][]{{"ok", "0"}, {"warning", "0"}, {"critical", "0"}, {"unknow", "0"}, {"pending", "0"}};
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                int state = Integer.parseInt(row[0].toString());
                result[state][1] = row[1].toString();
            }
        }
        return result;
    }

    public void saveMonitorServiceCheck(MonitorServiceCheck MScheck) throws BusinessException {
        monitorServiceCheckDAO.save(MScheck);
    }

    public void findServiceHistoryStatusByPage(DBPaginatedList page, Object[] conditions) {
        String hql = "select c.serviceId from MonitorServiceCheck c,MonitorService s,MonitorHost h where c.serviceId=s.serviceId and s.monitorHost.hostId=h.hostId and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
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
            queryTranslate.addLikeCondition("h.displayName", conditions[0].toString());
        }
        if (conditions[1] != null && StringUtils.isNotBlank(conditions[1].toString())) {
            queryTranslate.addLikeCondition("s.serviceName", conditions[1].toString());
        }

        //设置排序规则
        queryTranslate.setGroupby(" group by c.serviceId,h.displayName,s.serviceName");
        queryTranslate.setOrderby(" order by h.displayName desc,s.serviceName desc");
        //先找出当前页的所有的服务id，然后用in查找出服务id对应的历史记录
        monitorServiceCheckDAO.findMonitorServiceCheckByPage(page, queryTranslate);
        if (page.getList() != null && page.getList().size() > 0) {
            List result = ResultTransform.calculateStatusResult(combineMonitorServiceCheck(monitorServiceCheckDAO.find(composeServiceHistoryQuery(queryTranslate, page.getList())), (Date) conditions[2], (Date) conditions[3]), Contants.SERVICE_STATUS);
            ResultTransform.sortResult(result, new String[]{"displayName", "serviceId"});
            page.setResult(result);
            MyQuery countQuery = ResultTransform.getMyQuery(queryTranslate, "select count(distinct c.serviceId)");
            page.setTotalCount(ResultTransform.getCount(monitorServiceCheckDAO.find(countQuery)).intValue());
        }
        //排序
        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("displayName", comparator));    
        sortFields.add(new BeanComparator("serviceName", comparator));
        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(page.getList(), multiSort);
    }

    /**
     * 根据当前页的服务id查找出该服务id在满足条件下对应的历史记录
     *
     * @param queryTranslate .
     * @param serviceIds     .
     */
    public MyQuery composeServiceHistoryQuery(QueryTranslate queryTranslate, List serviceIds) {
        MyQuery myQuery = new MyQuery();
        myQuery.getParalist().addAll(queryTranslate.getParalist());
        myQuery.setOrderby(queryTranslate.getOrderby());

        StringBuffer hql = new StringBuffer("select c.serviceId,h.displayName,s.serviceName,c.state,c.startTime,c.endTime ");
        String queryString = queryTranslate.getQueryString();
        int index = queryString.indexOf("from");
        if (index != -1) {
            hql.append(queryString.substring(index, queryString.length()));
        }
        hql.append("and c.serviceId in (");
        for (int i = 0; i < serviceIds.size(); i++) {
            hql.append("?,");
            myQuery.addPara(serviceIds.get(i), Types.INTEGER);
        }
        hql.deleteCharAt(hql.length() - 1);
        hql.append(")");
        myQuery.setQueryString(hql.toString());
        return myQuery;
    }

    /**
     * 根据状态统计每个服务对应状态所占的比例
     *
     * @param list      .
     * @param startTime .
     * @param endTime   .
     * @return .
     */
    private Map combineMonitorServiceCheck(List list, Date startTime, Date endTime) {
        String now = DateUtil.getNow();
        Map map = new HashMap();
        //每一个服务将对应一个map，其中存放displayName，serviceName,serviceId，各种状态对应的持续时间
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Object serviceId = row[0];

                //计算当前记录持续时间
                long duration;
                if (row[5] == null) {
                    duration = DateUtil.getDuration(row[4].toString(), now, startTime, endTime);
                } else {
                    duration = DateUtil.getDuration(row[4].toString(), row[5].toString(), startTime, endTime);
                }

                Map serviceChecks;
                Object value = map.get(serviceId);
                if (value == null) {
                    serviceChecks = new HashMap();
                    serviceChecks.put("serviceId", row[0]);
                    serviceChecks.put("displayName", row[1]);
                    serviceChecks.put("serviceName", row[2]);
                    serviceChecks.put(row[3], Long.valueOf(duration));
                    serviceChecks.put("total", Long.valueOf(duration));
                    map.put(serviceId, serviceChecks);
                } else {
                    serviceChecks = (Map) value;
                    //增量式添加
                    serviceChecks.put("total", ((Long) serviceChecks.get("total")).longValue() + duration);
                    //先找出相同状态当前对应的总持续时间，如果存在，则在此基础上加上现在的持续时间
                    Object totalDuration = serviceChecks.get(row[3]);
                    if (totalDuration != null) {
                        duration = ((Long) totalDuration).longValue() + duration;
                    }
                    //value不为空的时候，total肯定也不为空
                    serviceChecks.put(row[3], Long.valueOf(duration));
                }
            }
        }
        return map;
    }

    public void findMonitorServiceCheckByPage(DBPaginatedList page, Object[] conditions) {
        String hql = "select c.state,c.startTime,c.endTime,c.output from MonitorServiceCheck c where ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null)) and c.serviceId=?";
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

        monitorServiceCheckDAO.findMonitorServiceCheckByPage(page, queryTranslate);
        page.setResult(convertMonitorServiceCheck(page.getList(), startTime, endTime));
    }

    private List convertMonitorServiceCheck(List list, String startTime, String endTime) {
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

    public MonitorServiceCheck getLattestMonitorServiceCheck(Integer Objectid) {
        String hql = "from MonitorServiceCheck c where c.serviceId=" + Objectid + " and c.endTime is null";
        List list = monitorServiceCheckDAO.find(hql);
        if (list != null && list.size() > 0) {
            return (MonitorServiceCheck) list.get(0);
        }
        return null;
    }

    public void updateMonitorServiceCheck(MonitorServiceCheck MScheck)
            throws BusinessException {
        monitorServiceCheckDAO.update(MScheck);
    }

    public MonitorServiceAll getMonitorServiceAll(Integer Objectid) {
        // TODO Auto-generated method stub
        return monitorServiceDAO.getServiceAll(Objectid);
    }

    public void updateMonitorServiceAll(MonitorServiceAll monitorServiceAll) {
        monitorServiceDAO.updateServiceAll(monitorServiceAll);

    }
}
