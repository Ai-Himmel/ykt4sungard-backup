package org.king.host.service.impl;

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
import org.king.host.dao.MonitorHostDAO;
import org.king.host.dao.MonitorHostStatusDAO;
import org.king.host.dao.MonitorHostchecksDAO;
import org.king.host.dao.MonitorHostgroupsDAO;
import org.king.host.domain.*;
import org.king.host.exception.HostAlreadyExistException;
import org.king.host.exception.HostgroupsAlreadyExistException;
import org.king.host.service.MonitorHostService;
import org.king.utils.Contants;
import org.king.utils.DateUtil;
import org.king.utils.ResultTransform;

import java.sql.Types;
import java.util.*;

public class MonitorHostServiceImpl extends BaseService implements MonitorHostService {

    private static Log log = LogFactory.getLog(MonitorHostServiceImpl.class);

    private MonitorHostDAO monitorHostDAO;

    private MonitorHostgroupsDAO monitorHostgroupsDAO;

    private MonitorHostStatusDAO monitorHostStatusDAO;

    private MonitorHostchecksDAO monitorHostchecksDAO;

    public void setMonitorHostDAO(MonitorHostDAO monitorHostDAO) {
        this.monitorHostDAO = monitorHostDAO;
    }

    public MonitorHost getMonitorHost(Integer Objectid) {
        return monitorHostDAO.get(Objectid);
    }

    public MonitorHostAll getMonitorHostAll(Integer Objectid) {
        return monitorHostDAO.getHostAll(Objectid);
    }

    public void setMonitorHostgroupsDAO(MonitorHostgroupsDAO monitorHostgroupsDAO) {
        this.monitorHostgroupsDAO = monitorHostgroupsDAO;
    }

    public void setMonitorHostStatusDAO(MonitorHostStatusDAO monitorHostStatusDAO) {
        this.monitorHostStatusDAO = monitorHostStatusDAO;
    }

    public void setMonitorHostchecksDAO(MonitorHostchecksDAO monitorHostchecksDAO) {
        this.monitorHostchecksDAO = monitorHostchecksDAO;
    }

    public void saveMonitorHostchecks(MonitorHostchecks MHc) throws BusinessException {
        monitorHostchecksDAO.save(MHc);
    }

    /**
     * ��������
     *
     * @param monitorHost .
     */
    public void saveMonitorHost(MonitorHost monitorHost) throws HostAlreadyExistException {
        if (monitorHostDAO.isExistMonitorHost(monitorHost.getHostAddress())) {
            throw new HostAlreadyExistException("�������Ѵ��ڣ�");
        }
        monitorHostDAO.save(monitorHost);
    }

    public List findAllMonitorHost() {
        return monitorHostDAO.getAll();
    }

    public List findMonitorHost(Integer hostgroupId) {
        String hql = "from MonitorHost h where h.hostgroups.hostgroupId=" + hostgroupId;
        return monitorHostDAO.find(hql);
    }

    /**
     * ��ҳ����MonitorHost���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page ��
     */
    public void findMonitorHostByPage(DBPaginatedList page, MonitorHost monitorHost) {
        String hql = "from MonitorHost";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorHost.getAlias())) {
            queryTranslate.addLikeCondition("alias", monitorHost.getAlias());
        }
        if (StringUtils.isNotBlank(monitorHost.getDisplayName())) {
            queryTranslate.addLikeCondition("displayName", monitorHost.getDisplayName());
        }
        if (StringUtils.isNotBlank(monitorHost.getHostAddress())) {
            queryTranslate.addLikeCondition("hostAddress", monitorHost.getHostAddress());
        }
        if (monitorHost.getHostgroups().getHostgroupId() != null) {
            queryTranslate.addEqualCondition("hostgroups.hostgroupId",monitorHost.getHostgroups().getHostgroupId());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorHostDAO.findMonitorHostByPage(page, queryTranslate);
    }

    /**
     * ������������
     *
     * @param monitorHost .
     */
    public void updateMonitorHost(MonitorHost monitorHost) {
        monitorHostDAO.update(monitorHost);
    }

    public void updateMonitorHostAll(MonitorHostAll monitorHostAll) {
        monitorHostDAO.updateHostAll(monitorHostAll);
    }

    /**
     * ����idɾ����������
     * delete status and checks first
     *
     * @param id .
     */
    public void deleteMonitorHost(Integer id) throws BusinessException {
        if (isRelatedHost(id)) {
            throw new BusinessException("�������ѱ�������");
        }
        monitorHostStatusDAO.execute("delete from MonitorHostStatus t where t.hostId=" + id);
        monitorHostchecksDAO.execute("delete from MonitorHostchecks t where t.hostId=" + id);
        monitorHostDAO.delete(getMonitorHost(id));
    }

    /**
     * ��������Ƿ�����ʵ�����
     * �������ܺ������������
     *
     * @param hostId .
     * @return .
     */
    private boolean isRelatedHost(Integer hostId) {
        String hql = "select count(t.serviceId) from MonitorService t where t.monitorHost.hostId=" + hostId;
        if (ResultTransform.getCount(monitorHostDAO.find(hql)).intValue() > 0) {
            return true;
        }
        return false;
    }

    /**
     * ����id����������
     *
     * @param id .
     * @return .
     */
    public MonitorHostgroups getMonitorHostgroups(Integer id) {
        return monitorHostgroupsDAO.get(id);
    }

    /**
     * ����������
     *
     * @param monitorHostgroups .
     * @throws HostgroupsAlreadyExistException
     *          .
     */
    public void saveMonitorHostgroups(MonitorHostgroups monitorHostgroups) throws HostgroupsAlreadyExistException {
        if (monitorHostgroupsDAO.isExistMonitorHostgroups(monitorHostgroups.getGroupName())) {
            throw new HostgroupsAlreadyExistException("���������Ѵ��ڣ�");
        }
        monitorHostgroupsDAO.save(monitorHostgroups);
    }

    /**
     * �������е�������
     *
     * @return .
     */
    public List findAllMonitorHostgroups() {
        return monitorHostgroupsDAO.getAll();
    }

    /**
     * ��ҳ����MonitorHostgroups���󣬲�ѯ����MyQueryͳһ��service�й��첢��ʼ��
     *
     * @param page              .
     * @param monitorHostgroups .
     */
    public void findMonitorHostgroupsByPage(DBPaginatedList page, MonitorHostgroups monitorHostgroups) {
        String hql = "from MonitorHostgroups";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        //��Ӳ�ѯ����
        if (StringUtils.isNotBlank(monitorHostgroups.getGroupName())) {
            queryTranslate.addLikeCondition("groupName", monitorHostgroups.getGroupName());
        }

        //�����������
        if (StringUtils.isNotBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        }
        monitorHostgroupsDAO.findMonitorHostgroupsByPage(page, queryTranslate);
    }

    /**
     * ���������飬����ʱgroupName���ܺ����������ظ�
     *
     * @param monitorHostgroups .
     */
    public void updateMonitorHostgroups(MonitorHostgroups monitorHostgroups) throws HostgroupsAlreadyExistException {
        String hql = "from MonitorHostgroups t where t.hostgroupId<>" + monitorHostgroups.getHostgroupId() + " and t.groupName='" + monitorHostgroups.getGroupName() + "'";
        List result = monitorHostgroupsDAO.find(hql);
        if (result != null && result.size() > 0) {
            throw new HostgroupsAlreadyExistException("���������Ѵ��ڣ�");
        }
        monitorHostgroupsDAO.update(monitorHostgroups);
    }

    /**
     * ��������ɾ��������
     *
     * @param id .
     */
    public void deleteMonitorHostgroups(Integer id) throws BusinessException {
        if (isRelatedHostgroups(id)) {
            throw new BusinessException("���������ѱ�������");
        }
        monitorHostgroupsDAO.delete(getMonitorHostgroups(id));
    }

    /**
     * �����������Ƿ�����ʵ�����
     * ���ܹ�����ʵ���У�MonitorHostTemplate,MonitorHost
     *
     * @param groupId .
     * @return .
     */
    private boolean isRelatedHostgroups(Integer groupId) {
        List list = new ArrayList();
        list.add("select count(t.templateId) from MonitorHostTemplate t where t.hostgroups.hostgroupId=" + groupId);
        list.add("select count(t.hostId) from MonitorHost t where t.hostgroups.hostgroupId=" + groupId);
        for (int i = 0; i < list.size(); i++) {
            String hql = list.get(i).toString();
            if (ResultTransform.getCount(monitorHostgroupsDAO.find(hql)).intValue() > 0) {
                return true;
            }
        }
        return false;
    }

    /**
     * ��������״̬ͳ����Ϣ
     *
     * @param page       .
     * @param conditions .
     * @return .
     */
    public void findMonitorHostStatusByPage(DBPaginatedList page, String[] conditions) {
        String hql = "select s.hostId as hostId,h.hostAddress as hostAddress,h.displayName as displayName,s.currentState as currentState,s.lastCheck as lastCheck,s.lastStateChange as lastStateChange,s.output as output from MonitorHostStatus s,MonitorHost h where s.hostId=h.hostId";
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());

        if (StringUtils.isNotBlank(conditions[0])) {
            queryTranslate.addLikeCondition("h.displayName", conditions[0]);
        }
        if (StringUtils.isNotBlank(conditions[1])) {
            queryTranslate.addLikeCondition("h.hostAddress", conditions[1]);
        }
        if (StringUtils.isNotBlank(conditions[2]) && !"-1".equals(conditions[2])) {
            queryTranslate.addEqualCondition("s.currentState", conditions[2]);
        }
        if (StringUtils.isNotBlank(conditions[3])) {
            queryTranslate.addEqualCondition("h.hostgroups.hostgroupId", Integer.valueOf(conditions[3]));
        }

        //�����������Ĭ�ϰ��յ�ǰ״̬������
        if (StringUtils.isBlank(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by s.currentState desc,h.displayName");
        } else if ("h.displayName".equals(page.getSortCriterion())) {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder());
        } else if("s.lastStateChange".equals(page.getSortCriterion())){
            //����ʱ��=��ǰʱ��-�ϴ�״̬�任ʱ�䣬���Գ���ʱ����������м���Ӧ״̬�任�ĵ�������
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOppositeOrder() + ",h.displayName");
        } else {
            queryTranslate.setOrderby(" order by " + page.getSortCriterion() + " " + page.getOrder() + ",h.displayName");
        }

        monitorHostStatusDAO.findMonitorHostStatusByPage(page, queryTranslate);
        String[] keys = new String[]{"hostId", "hostAddress", "displayName", "currentState", "lastCheck", "lastStateChange", "output"};
        page.setResult(ResultTransform.arrayToMap(page.getList(), keys));
    }

    /**
     * ͳ������״̬
     *
     * @return .
     */
    public String[][] calculateHostStatus() {
        String hql = "select t.currentState,count(t) from MonitorHostStatus t group by t.currentState order by t.currentState";
        List list = monitorHostStatusDAO.find(hql);

        String[][] result = new String[][]{{"up", "0"}, {"down", "0"}, {"unreachable", "0"}, {"pending", "0"}};
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                int state = Integer.parseInt(row[0].toString());
                result[state][1] = row[1].toString();
            }
        }
        return result;
    }

    public MonitorHostStatus getMonitorHostStatus(Integer Objectid) {
        return monitorHostStatusDAO.get(Objectid);
    }


    public void saveMonitorHostStatus(MonitorHostStatus monitorHostStatus) throws BusinessException {
        monitorHostStatusDAO.save(monitorHostStatus);
    }


    public void updateMonitorHostStatus(MonitorHostStatus monitorHostStatus) throws BusinessException {
        monitorHostStatusDAO.update(monitorHostStatus);
    }

    /**
     * startTime and endTime can't not be null
     *
     * @param hostId    .
     * @param startTime .
     * @param endTime   .
     * @return .
     */
    public List findMonitorHostchecks(Integer hostId, Date startTime, Date endTime) {
        String hql = "from MonitorHostchecks c where c.hostId=? and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
        MyQuery myQuery = new MyQuery();
        myQuery.setQueryString(hql);

        String startTimeStr = DateUtil.formatDate(startTime);
        String endTimeStr = DateUtil.formatDate(endTime);
        myQuery.addPara(hostId, Types.INTEGER);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(startTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        myQuery.addPara(endTimeStr, Types.VARCHAR);
        return monitorHostchecksDAO.find(myQuery);
    }

    public void findHostHistoryStatusByPage(DBPaginatedList page, Object[] conditions) {
        String hql = "select c.hostId from MonitorHostchecks c,MonitorHost h where c.hostId=h.hostId and ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null))";
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
            queryTranslate.addLikeCondition("h.hostAddress", conditions[1].toString());
        }
        if (conditions[4]!=null && StringUtils.isNotBlank(conditions[4].toString())) {
            queryTranslate.addEqualCondition("h.hostgroups.hostgroupId", Integer.valueOf(conditions[4].toString()));
        }

        queryTranslate.setGroupby(" group by c.hostId,h.displayName");
        queryTranslate.setOrderby(" order by h.displayName desc");
        monitorHostchecksDAO.findMonitorHostchecksByPage(page, queryTranslate);
        if (page.getList() != null && page.getList().size() > 0) {
            List result = ResultTransform.calculateStatusResult(combineMonitorHostchecks(monitorHostchecksDAO.find(composeHostHistoryQuery(queryTranslate, page.getList())), (Date) conditions[2], (Date) conditions[3]), Contants.HOST_STATUS);
            ResultTransform.sortResult(result, new String[]{"hostId"});
            page.setResult(result);
            MyQuery countQuery = ResultTransform.getMyQuery(queryTranslate, "select count(distinct c.hostId)");
            page.setTotalCount(ResultTransform.getCount(monitorHostchecksDAO.find(countQuery)).intValue());
        }

        Comparator comparator = ComparableComparator.getInstance();
        comparator = ComparatorUtils.nullLowComparator(comparator);
        comparator = ComparatorUtils.reversedComparator(comparator);
        ArrayList<Object> sortFields = new ArrayList<Object>();
        sortFields.add(new BeanComparator("displayName", comparator));

        ComparatorChain multiSort = new ComparatorChain(sortFields);

        Collections.sort(page.getList(), multiSort);
    }

    /**
     * ���ݵ�ǰҳ������id���ҳ�������id�����������¶�Ӧ����ʷ��¼
     *
     * @param queryTranslate .
     * @param hostIds        .
     */
    public MyQuery composeHostHistoryQuery(QueryTranslate queryTranslate, List hostIds) {
        MyQuery myQuery = new MyQuery();
        myQuery.getParalist().addAll(queryTranslate.getParalist());
        myQuery.setOrderby(queryTranslate.getOrderby());

        StringBuffer hql = new StringBuffer("select c.hostId,h.displayName,c.state,c.startTime,c.endTime ");
        String queryString = queryTranslate.getQueryString();
        int index = queryString.indexOf("from");
        if (index != -1) {
            hql.append(queryString.substring(index, queryString.length()));
        }
        hql.append("and c.hostId in (");
        for (int i = 0; i < hostIds.size(); i++) {
            hql.append("?,");
            myQuery.addPara(hostIds.get(i), Types.INTEGER);
        }
        hql.deleteCharAt(hql.length() - 1);
        hql.append(")");
        myQuery.setQueryString(hql.toString());
        return myQuery;
    }

    /**
     * ����״̬ͳ��ÿ��������Ӧ״̬��ռ�ı���
     *
     * @param list      .
     * @param startTime .
     * @param endTime   .
     * @return .
     */
    private Map combineMonitorHostchecks(List list, Date startTime, Date endTime) {
        String now = DateUtil.getNow();
        Map map = new HashMap();
        //ÿһ����������Ӧһ��map�����д��displayName��hostId������״̬��Ӧ�ĳ���ʱ��
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Object[] row = (Object[]) list.get(i);
                Object hostId = row[0];

                //���㵱ǰ��¼����ʱ��
                long duration;
                if (row[4] == null) {
                    duration = DateUtil.getDuration(row[3].toString(), now, startTime, endTime);
                } else {
                    duration = DateUtil.getDuration(row[3].toString(), row[4].toString(), startTime, endTime);
                }

                Map hostchecks;
                Object value = map.get(hostId);
                if (value == null) {
                    hostchecks = new HashMap();
                    hostchecks.put("hostId", row[0]);
                    hostchecks.put("displayName", row[1]);
                    hostchecks.put(row[2], Long.valueOf(duration));
                    hostchecks.put("total", Long.valueOf(duration));
                    map.put(hostId, hostchecks);
                } else {
                    hostchecks = (Map) value;
                    //����ʽ���
                    hostchecks.put("total", ((Long) hostchecks.get("total")).longValue() + duration);
                    //���ҳ���ͬ״̬��ǰ��Ӧ���ܳ���ʱ�䣬������ڣ����ڴ˻����ϼ������ڵĳ���ʱ��
                    Object totalDuration = hostchecks.get(row[2]);
                    if (totalDuration != null) {
                        duration = ((Long) totalDuration).longValue() + duration;
                    }
                    //value��Ϊ�յ�ʱ��total�϶�Ҳ��Ϊ��
                    hostchecks.put(row[2], Long.valueOf(duration));
                }
            }
        }
        return map;
    }

    public void findMonitorHostchecksByPage(DBPaginatedList page, Object[] conditions) {
        String hql = "select c.state,c.startTime,c.endTime,c.output from MonitorHostchecks c where ((c.startTime<? and c.endTime>?) or (c.startTime>=? and c.startTime<?) or (c.startTime<? and c.endTime is null)) and c.hostId=?";
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

        //�����������
        queryTranslate.setOrderby(" order by c.endTime desc");

        monitorHostchecksDAO.findMonitorHostchecksByPage(page, queryTranslate);
        page.setResult(convertMonitorHostchecks(page.getList(), startTime, endTime));
    }

    private List convertMonitorHostchecks(List list, String startTime, String endTime) {
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

    public MonitorHostchecks getLattestMonitorHostchecks(Integer Objectid) {
        String hql = "from MonitorHostchecks c where c.hostId=" + Objectid + " and c.endTime is null";
        List list = monitorHostchecksDAO.find(hql);
        if (list != null && list.size() > 0) {
            return (MonitorHostchecks) list.get(0);
        }
        return null;
    }

    public void updateMonitorHostchecks(MonitorHostchecks MHc) throws BusinessException {
        monitorHostchecksDAO.update(MHc);
    }
}
