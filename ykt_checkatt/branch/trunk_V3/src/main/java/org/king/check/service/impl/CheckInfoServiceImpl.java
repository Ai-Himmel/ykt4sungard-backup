package org.king.check.service.impl;

import java.text.ParseException;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.lang.StringUtils;
import org.king.check.dao.CheckDeviceLocationDAO;
import org.king.check.dao.CheckInfoDAO;
import org.king.check.dao.CheckLocationDAO;
import org.king.check.domain.TCheckDeviceLocation;
import org.king.check.domain.TCheckInfo;
import org.king.check.domain.TCheckLocation;
import org.king.check.service.CheckInfoService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.GetPropertiesUtil;
import org.king.framework.service.impl.BaseService;
import org.springframework.jdbc.core.JdbcTemplate;

public class CheckInfoServiceImpl extends BaseService implements CheckInfoService {

	private CheckInfoDAO checkInfoDAO;
	
	private JdbcTemplate jdbcTemplate;
	
	private CheckLocationDAO checkLocationDAO;
	
	private CheckDeviceLocationDAO checkDeviceLocationDAO;
	
	public void setCheckInfoDAO(CheckInfoDAO checkInfoDAO) {
		this.checkInfoDAO = checkInfoDAO;
	}
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
	public void setCheckLocationDAO(CheckLocationDAO checkLocationDAO) {
		this.checkLocationDAO = checkLocationDAO;
	}

	public void setCheckDeviceLocationDAO(CheckDeviceLocationDAO checkDeviceLocationDAO) {
		this.checkDeviceLocationDAO = checkDeviceLocationDAO;
	}

	/**
	 * �Կ�����ˮ���кϲ������࣬���ɿ�����ϸ
	 * @param startDate
	 * @param endDate
	 * @throws Exception
	 */
	public void createCheckInfo(String startDate,String endDate) throws Exception {
		saveClockCheckInfo(startDate,endDate);
		saveCheckInfo(startDate,endDate);
	}
	
	/**
	 * ˢ��ָ��ʱ��εĿ���
	 * 
	 * @param startDate
	 * @param endDate
	 */
	public void refreshCheckInfo(String startDate,String endDate) throws Exception  {
		deleteCheckInfo(startDate,endDate);
		saveClockCheckInfo(startDate,endDate);
		saveCheckInfo(startDate,endDate);
	}
	
	private void deleteCheckInfo(String startDate,String endDate){
		String sql = "DELETE FROM YKT_CK.T_CHECK_INFO WHERE CHECK_DATE BETWEEN '" + startDate + "' AND '" + endDate + "'";
		jdbcTemplate.execute(sql);
	}
	
	/**
	 * ���������ݿ��ڣ������ݿ�����Ҫ�ϲ�����ʱ��������ļ�¼����¼����ʱ����뿪ʱ��
	 * 
	 * @param startDate
	 * @param endDate
	 */
	private void saveClockCheckInfo(String startDate,String endDate){
		//ͳ�����м�ʱ���ڣ�checkTypeΪ3��ʾ��ʱ����
		StringBuffer sql = new StringBuffer();
		sql.append("select t.cust_id, t.att_date, t.att_time, cdl.location_id, cdl.check_type from");
		sql.append(" (select a.cust_id, a.att_date, a.att_time, a.device_id from ykt_ck.t_attserial a");
		sql.append(" where a.att_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(") t,ykt_ck.t_check_device_location cdl,ykt_cur.t_customer cus");
		sql.append(" where t.device_id = cdl.device_id and cdl.check_type = '3'");
		sql.append(" and t.cust_id = cus.custid and cus.custtype = 1");
		sql.append(" order by cdl.location_id, t.att_date, t.cust_id, t.att_time desc");
		
		List checkList = jdbcTemplate.queryForList(sql.toString());
		if(checkList==null || checkList.size()==0){
			return;
		}
		String checkDate = null;
		String custid = null;
		String checkTime = null;
		String checkType = null;
		String locationId = null;
		String checkinTime = null;
		String checkoutTime = null;
		Stack<String> stack = new Stack<String>();
		//checkList should order by locationid,checkDate,custid,checkTime desc
		for(int i=0;i<checkList.size();i++){
			Map row = (Map) checkList.get(i);
			String currentLocationId =  row.get("LOCATION_ID")==null?"":row.get("LOCATION_ID").toString();
			String currentCheckDate = row.get("ATT_DATE")==null?"":row.get("ATT_DATE").toString();
			String currentCustid =  row.get("CUST_ID")==null?"":row.get("CUST_ID").toString();
			String currentCheckType =  row.get("CHECK_TYPE")==null?"":row.get("CHECK_TYPE").toString();
			checkTime = row.get("ATT_TIME")==null?"":row.get("ATT_TIME").toString();
			
			if(StringUtils.isNotBlank(custid)){
				//�ų���һ����¼
				if (!currentLocationId.equals(locationId) || !currentCheckDate.equals(checkDate) || !currentCustid.equals(custid)) {
					//���locationId��checkDate��custid�е��κ�һ���Ѿ��ı䣬��ôӦ�úϲ�֮ǰ�ļ�¼�������¿�ʼһ���¼�¼
					//���ڼ�ʱ���ڣ�ÿһ��locationId��ӦΨһһ��checkType����������ǽ��뻹���뿪�����Ե�locationId�仯��ʱ��checkType��ȻҲ���ű仯
					combineCheckInfo(locationId,checkDate,custid,checkType,stack);
				}
			}
			locationId = currentLocationId;
			checkDate = currentCheckDate;
			custid = currentCustid;
			checkType = currentCheckType;
			stack.push(checkTime);
		}
		//�������һ����¼
		combineCheckInfo(locationId,checkDate,custid,checkType,stack);
	}
	
	/**
	 * �ϲ��û���ˢ����¼��һ��һ����Ϊһ����¼��ͨ��ʱ����Ⱥ����жϽ����������������¼Ĭ��Ϊ����ļ�¼
	 * 
	 * @param locationId
	 * @param checkDate
	 * @param custid
	 * @param checkType
	 * @param stack
	 */
	private void combineCheckInfo(String locationId, String checkDate,String custid, String checkType, Stack<String> stack) {
		while (!stack.isEmpty()) {
			String checkinTime = stack.pop();
			String checkoutTime = null;
			if (!stack.isEmpty()) {
				checkoutTime = stack.pop();
			}
			TCheckInfo checkInfo = new TCheckInfo();
			checkInfo.setCustId(Integer.valueOf(custid));
			checkInfo.setCheckDate(checkDate);
			checkInfo.setLocationId(locationId);
			checkInfo.setCheckType(checkType);
			checkInfo.setCheckNum(Integer.valueOf(1));
			checkInfo.setCheckinTime(checkinTime);
			checkInfo.setCheckoutTime(checkoutTime);
			checkInfo.setDelayNum(Integer.valueOf(0));
			checkInfo.setEarlyNum(Integer.valueOf(0));
			if(StringUtils.isBlank(checkoutTime)){
				//����뿪ʱû��ˢ������ô����볡��һ�Σ�ʱ��Ϊ0����
				checkInfo.setCheckDuration(Integer.valueOf(0));
			} else {
				try {
					checkInfo.setCheckDuration(DateUtilExtend.getMinutes(checkinTime, checkoutTime));
				} catch (ParseException e) {
					log.error("��ȡˢ��ʱ����ʧ�ܣ�"+e.getMessage());
				}
			}
			checkInfoDAO.save(checkInfo);
		}
	}
	
	/**
	 * ����У�ſڿ������ݣ�У�ſڿ��ڲ���Ҫ�ϲ�������ˮ��ֻ��Ҫ��¼�ǽ��뻹���뿪�Լ�ˢ��ʱ��
	 * 
	 * @param startDate
	 * @param endDate
	 */
	private void saveCheckInfo(String startDate,String endDate){
		//ͳ�����зǼ�ʱ���ڣ�checkTypeΪ1��Ϊ������ˮ��checkTypeΪ2��Ϊ�뿪��ˮ
		StringBuffer sql = new StringBuffer();
		sql.append("select t.cust_id, t.att_date, t.att_time, cdl.location_id, cdl.check_type from");
		sql.append(" (select a.cust_id, a.att_date, a.att_time, a.device_id from ykt_ck.t_attserial a");
		sql.append(" where a.att_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(") t,ykt_ck.t_check_device_location cdl,ykt_cur.t_customer cus");
		sql.append(" where t.device_id = cdl.device_id and (cdl.check_type = '1' or cdl.check_type='2')");
		sql.append(" and t.cust_id = cus.custid and cus.custtype = 1");
		sql.append(" order by t.att_date, t.cust_id, t.att_time");
		
		List checkList = jdbcTemplate.queryForList(sql.toString());
		//����Ǽ�ʱ����
		if(checkList==null || checkList.size()==0){
			return;
		}
		String checkDate = null;
		String custid = null;
		String checkTime = null;
		String checkType = null;
		String locationId = null;
		for(int i=0;i<checkList.size();i++){
			Map row = (Map) checkList.get(i);
			checkDate = row.get("ATT_DATE")==null?"":row.get("ATT_DATE").toString();
			custid =  row.get("CUST_ID")==null?"":row.get("CUST_ID").toString();
			checkTime =  row.get("ATT_TIME")==null?"":row.get("ATT_TIME").toString();
			checkType =  row.get("CHECK_TYPE")==null?"":row.get("CHECK_TYPE").toString();
			locationId =  row.get("LOCATION_ID")==null?"":row.get("LOCATION_ID").toString();
			
			TCheckInfo checkInfo = new TCheckInfo();
			checkInfo.setCustId(Integer.valueOf(custid));
			checkInfo.setCheckDate(checkDate);
			checkInfo.setLocationId(locationId);
			checkInfo.setCheckNum(Integer.valueOf(1));
			checkInfo.setCheckType(checkType);
			
			if ("1".equals(checkType)) {
				//checkin����ٵ�
				checkInfo.setCheckinTime(checkTime);
				checkInfo.setDelayNum(Integer.valueOf(1));
				checkInfo.setEarlyNum(Integer.valueOf(0));
			} else if ("2".equals(checkType)) {
				//checkout��������
				checkInfo.setCheckoutTime(checkTime);
				checkInfo.setDelayNum(Integer.valueOf(0));
				checkInfo.setEarlyNum(Integer.valueOf(1));
			}
			checkInfoDAO.save(checkInfo);	
		}
	}

	public List viewCheckInfoDetail(String startDate, String endDate,String stuempNo,String className,String locationId,String custName) throws Exception {
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,ci.checkin_time as checkintime,ci.checkout_time as checkouttime,ci.check_date as checkdate,cl.name as locationname");
		sql.append(" from ykt_ck.t_check_info ci,ykt_ck.t_check_location cl,ykt_cur.t_customer cus");
		sql.append(" where (ci.check_type = '1' or check_type = '2')");
		sql.append(" and ci.check_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(" and ci.location_id = cl.id and ci.cust_id = cus.custid");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and ci.location_id = '").append(locationId).append("'");
		}
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		sql.append(" order by cl.name, ci.check_date, cus.classname, cus.stuempno");
		
		return jdbcTemplate.queryForList(sql.toString());
	}

	public List viewCheckInfoTotal(String startDate, String endDate,String stuempNo,String className,String locationId,String custName) throws Exception {
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,cl.name as locationname,sum(ci.check_num) as checknum,sum(ci.delay_num) as delaynum,sum(ci.early_num) as earlynum");
		sql.append(" from ykt_ck.t_check_info ci,ykt_ck.t_check_location cl,ykt_cur.t_customer cus");
		sql.append(" where (ci.check_type = '1' or check_type = '2')");
		sql.append(" and ci.check_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(" and ci.location_id = cl.id and ci.cust_id = cus.custid");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and ci.location_id = '").append(locationId).append("'");
		}
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		sql.append(" group by cus.stuempno, cus.custname, cus.classname, cl.name");
		sql.append(" order by cl.name, cus.classname, cus.stuempno");
		
		return jdbcTemplate.queryForList(sql.toString());
	}

	public List viewClockCheckInfoDetail(String startDate, String endDate,String stuempNo,String className,String locationId,String custName) throws Exception {
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,ci.checkin_time as checkintime,ci.checkout_time as checkouttime,ci.check_date as checkdate,cl.name as locationname,ci.check_duration as duration");
		sql.append(" from ykt_ck.t_check_info ci,ykt_ck.t_check_location cl,ykt_cur.t_customer cus");
		sql.append(" where ci.check_type = '3'");
		sql.append(" and ci.check_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(" and ci.location_id = cl.id and ci.cust_id = cus.custid");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and ci.location_id = '").append(locationId).append("'");
		}
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		sql.append(" order by cl.name, ci.check_date, cus.classname, cus.stuempno");
		
		return jdbcTemplate.queryForList(sql.toString());
	}

	public List viewClockCheckInfoTotal(String startDate, String endDate,String stuempNo,String className,String locationId,String custName) throws Exception {
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,cl.name as locationname,sum(ci.check_num) as checknum,sum(ci.check_duration) as duration");
		sql.append(" from ykt_ck.t_check_info ci,ykt_ck.t_check_location cl,ykt_cur.t_customer cus");
		sql.append(" where ci.check_type = '3'");
		sql.append(" and ci.check_date between '").append(startDate).append("' and '").append(endDate).append("'");
		sql.append(" and ci.location_id = cl.id and ci.cust_id = cus.custid");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and ci.location_id = '").append(locationId).append("'");
		}
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		sql.append(" group by cus.stuempno, cus.custname, cus.classname, cl.name");
		sql.append(" order by cl.name, cus.classname, cus.stuempno");
		
		return jdbcTemplate.queryForList(sql.toString());
	}

	public List findAllLocation() throws Exception {
		String hql = "from TCheckLocation t order by t.name";
		return checkLocationDAO.find(hql);
	}

	public TCheckLocation getCheckLocation(String id) throws Exception {
		return checkLocationDAO.get(id);
	}

	public void deleteCheckLocations(String[] locationIds) {
		if(locationIds==null || locationIds.length==0){
			return;
		}
		for(String locationId:locationIds){
			TCheckLocation checkLocation = checkLocationDAO.get(locationId);
			List checkDeviceLocations = checkDeviceLocationDAO.find("from TCheckDeviceLocation t where t.id.locationId='"+locationId+"'");
			if(checkDeviceLocations!=null && checkDeviceLocations.size()>0){
				for(int i=0;i<checkDeviceLocations.size();i++){
					TCheckDeviceLocation checkDeviceLocation = (TCheckDeviceLocation) checkDeviceLocations.get(i);
					checkDeviceLocationDAO.delete(checkDeviceLocation);
				}
			}
			checkLocationDAO.delete(checkLocation);
		}
	}

	public void saveCheckLocation(TCheckLocation checkLocation) {
		checkLocationDAO.save(checkLocation);
	}

	public void updateCheckLocation(TCheckLocation checkLocation) {
		checkLocationDAO.update(checkLocation);
	}

	public void deleteCheckDeviceLocation(String deviceId) {
		TCheckDeviceLocation checkDeviceLocation = checkDeviceLocationDAO.getCheckDeviceLocation(deviceId);
		if(checkDeviceLocation!=null){
			checkDeviceLocationDAO.delete(checkDeviceLocation);
		}
	}

	public void saveCheckDeviceLocation(TCheckDeviceLocation checkDeviceLocation) {
		checkDeviceLocationDAO.save(checkDeviceLocation);
	}

	public List findCheckDeviceLocation(String locationId){
		String sql = "select cdl.device_id as deviceid,cdl.check_type as checktype,d.devicename from ykt_ck.t_check_device_location cdl,t_device d where d.deviceid = cdl.device_id";
		sql += " and cdl.location_id='" + locationId + "'";
		return jdbcTemplate.queryForList(sql);
	}
	
	public List findDevice() {
		String sql = "select d.deviceid, d.devicename from ykt_cur.t_device d left join ykt_ck.t_check_device_location cdl on d.deviceid = cdl.device_id where cdl.device_id is null and d.devtypecode='0121'";
		return jdbcTemplate.queryForList(sql);
	}
	
	
	public List findClockLocation() {
		String sql = "select distinct cl.* from ykt_ck.t_check_location cl,ykt_ck.t_check_device_location cdl where cdl.location_id=cl.id and cdl.check_type='3' order by cl.name";
		return jdbcTemplate.queryForList(sql); 
	}

	public List findNoneClockLocation() {
		String sql = "select distinct cl.* from ykt_ck.t_check_location cl,ykt_ck.t_check_device_location cdl where cdl.location_id=cl.id and (cdl.check_type='1' or cdl.check_type='2') order by cl.name";
		return jdbcTemplate.queryForList(sql); 
	}
	
	public List findNormalLocation() {
		String sql = "select distinct cl.* from ykt_ck.t_check_location cl,ykt_ck.t_check_device_location cdl where cdl.location_id=cl.id and cdl.check_type='4' order by cl.name";
		return jdbcTemplate.queryForList(sql); 
	}

	/**
	 * �鿴��ͨ������ˮ��ʵʱ��
	 */
	public List viewCheckDetail(String startDate, String endDate,String stuempNo, String className, String locationId,String custName) throws Exception {
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		String custtype = config.getString("checkinfo.custtype");
		
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,t1.att_date as checkdate,t1.att_time as checktime,t2.name as locationname");
		sql.append(" from (select att.att_date, att.att_time, att.device_id, att.cust_id from ykt_ck.t_attserial att");
		sql.append(" where att.att_date between '").append(startDate).append("' and '").append(endDate).append("') t1,");
		sql.append(" (select cl.name, cdl.device_id from ykt_ck.t_check_location cl,ykt_ck.t_check_device_location cdl");
		sql.append(" where cl.id = cdl.location_id and cdl.check_type = '4'");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and cl.id = '").append(locationId).append("'");
		}
		sql.append(" ) t2,ykt_cur.t_customer cus");
		sql.append(" where t1.device_id = t2.device_id and t1.cust_id = cus.custid");
		
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		if(StringUtils.isNotBlank(custtype)){
			custtype = custtype.replaceAll("-", ",");
			sql.append(" and cus.custtype in (").append(custtype).append(")");
		}
		sql.append(" order by t2.name,t1.att_date,cus.classname,cus.stuempno,t1.att_time");
		
		return jdbcTemplate.queryForList(sql.toString());
	}

	/**
	 * �鿴��ͨ������ˮͳ�ƣ�ʵʱ��
	 */
	public List viewCheckTotal(String startDate, String endDate,String stuempNo, String className, String locationId,String custName) throws Exception {
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		String custtype = config.getString("checkinfo.custtype");
		
		StringBuffer sql = new StringBuffer("select cus.stuempno,cus.custname,cus.classname,t2.name as locationname,count(*) as checknum");
		sql.append(" from (select att.device_id, att.cust_id from ykt_ck.t_attserial att");
		sql.append(" where att.att_date between '").append(startDate).append("' and '").append(endDate).append("') t1,");
		sql.append(" (select cl.name, cdl.device_id from ykt_ck.t_check_location cl,ykt_ck.t_check_device_location cdl");
		sql.append(" where cl.id = cdl.location_id and cdl.check_type = '4'");
		if(StringUtils.isNotBlank(locationId)){
			sql.append(" and cl.id = '").append(locationId).append("'");
		}
		sql.append(" ) t2,ykt_cur.t_customer cus");
		sql.append(" where t1.device_id = t2.device_id and t1.cust_id = cus.custid");
		
		if(StringUtils.isNotBlank(stuempNo)){
			sql.append(" and cus.stuempno like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(className)){
			sql.append(" and cus.classname like '%").append(className).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sql.append(" and cus.custname like '%").append(custName).append("%'");
		}
		if(StringUtils.isNotBlank(custtype)){
			custtype = custtype.replaceAll("-", ",");
			sql.append(" and cus.custtype in (").append(custtype).append(")");
		}
		sql.append(" group by cus.stuempno, cus.custname, cus.classname, t2.name");
		sql.append(" order by t2.name, cus.classname, cus.stuempno");
		
		return jdbcTemplate.queryForList(sql.toString());
	}
}
