package com.kingstargroup.ecard.portlet.advquery.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.util.AdvWebKeys;
import com.kingstargroup.ecard.util.DateUtilExtend;

public class AdvqueryServiceImpl extends AdvqueryServiceBase {
	
	
	
	
	
	public List getCardUse(String enddate){
		List  result = new ArrayList();
		try{
		List carduse =  advqueryPersistence.getCarduse(enddate);
		int  total = advqueryPersistence.getCardUseTotal(enddate);
		for(int i=0 ;i<carduse.size();i++){
			Object[] obj = (Object[])carduse.get(i);
			HashMap map = new HashMap();
			map.put("typename", obj[1]);
			map.put("cardnum", obj[2]);
			if(total==0){
				map.put("rate", new Float("0"));
			}else{
			map.put("rate",new Float(Integer.parseInt(obj[2].toString())*100/total));
			}
			result.add(map);
		}
		return result;
		}catch(Exception he){
			he.printStackTrace();
			return null;
		}
		
	}
	
	/**
	 * 
	 */
	public List  getCardOpenLoseBack(String begindate,String enddate,String  statType){
		List  result = new ArrayList();
		try{
			List  cardList = advqueryPersistence.getCardOpenLoseBack(begindate,enddate,statType);
			for(int i=0;i<cardList.size();i++){
				Object[] obj =(Object[])cardList.get(i);
				HashMap map = new HashMap();
				map.put("balance_date", obj[0]);
				map.put("open", obj[1]);
				map.put("receive", obj[2]);
				map.put("lose", obj[3]);
				map.put("cool", obj[4]);
				result.add(map);
			}
			return result;
		}catch(Exception he){
			he.printStackTrace();
			return null;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getTotleSavingMoneyStat(java.lang.String, java.lang.String,
	 * java.lang.String)
	 */
	public List getTotleSavingMoneyStat(String beginDate, String endDate,
			String statType) {
		List result = new ArrayList();
		try {
			List saving = advqueryPersistence.getTotleSavingMoneyStat(
					beginDate, endDate, statType);
			if ("bydate".equals(statType)) {
				for (int i = 0; i < saving.size(); i++) {
					Object[] objects = (Object[]) saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date", objects[0]);
					accMap.put("transfer", objects[1]);
					accMap.put("cash", objects[2]);
					accMap.put("pos", objects[3]);
					accMap.put("outlay", objects[5]);
					accMap.put("ticket", objects[4]);
					accMap.put("week", DateUtilExtend.getWeekByDate(objects[0]
							.toString()));
					accMap.put("sysdate", new Integer((int) DateUtilExtend
							.diffDate(AdvWebKeys.sysBeginDate, objects[0]
									.toString()) + 1));
					result.add(accMap);
				}
			} else {
				for (int i = 0; i < saving.size(); i++) {
					Object[] objects = (Object[]) saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date", objects[0]);
					accMap.put("transfer", objects[1]);
					accMap.put("cash", objects[2]);
					accMap.put("pos", objects[3]);
					accMap.put("outlay", objects[5]);
					accMap.put("ticket", objects[4]);
					result.add(accMap);
				}
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getTotleSavingNumStat(java.lang.String, java.lang.String,
	 * java.lang.String)
	 */
	public List getTotleSavingNumStat(String beginDate, String endDate,
			String statType) throws PortalException {
		List result = new ArrayList();
		try {
			List saving = advqueryPersistence.getTotleSavingNumStat(beginDate,
					endDate, statType);
			if ("bydate".equals(statType)) {
				for (int i = 0; i < saving.size(); i++) {
					Object[] objects = (Object[]) saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date", objects[0]);
					accMap.put("transfer", objects[1]);
					accMap.put("cash", objects[2]);
					accMap.put("pos", objects[3]);
					accMap.put("week", DateUtilExtend.getWeekByDate(objects[0]
							.toString()));
					accMap.put("sysdate", new Integer((int) DateUtilExtend
							.diffDate(AdvWebKeys.sysBeginDate, objects[0]
									.toString()) + 1));
					result.add(accMap);
				}
			} else {
				for (int i = 0; i < saving.size(); i++) {
					Object[] objects = (Object[]) saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date", objects[0]);
					accMap.put("transfer", objects[1]);
					accMap.put("cash", objects[2]);
					accMap.put("pos", objects[3]);
					result.add(accMap);
				}
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getSavingSortStat(java.lang.String, java.lang.String, java.lang.String,
	 * java.lang.String)
	 */
	public List getSavingSortStat(String seriType, String beginDate,
			String endDate, String statType) throws PortalException {
		return advqueryPersistence.getSavingSortStat(seriType, beginDate,
				endDate, statType);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getPosDeviceList(java.lang.String)
	 */
	public List getPosDeviceList(String posId) {
		return advqueryPersistence.getPosDeviceList(posId);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getConsumeStatByPos(java.lang.String, java.lang.String, java.lang.String,
	 * java.lang.String)
	 */
	public List getConsumeStatByPos(String posId, String beginDate,
			String endDate, String statType) throws HibernateException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getConsumeStatByPos(posId, beginDate,
				endDate, statType);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seecom.kingstargroup.ecard.portlet.advquery.service.AdvqueryService#
	 * getShopAccountChangeStat(java.lang.String, java.lang.String,
	 * java.lang.String)
	 */
	public List getShopAccountChangeStat(String beginDate, String endDate,
			String statType) throws HibernateException {
		return advqueryPersistence.getShopAccountChangeStat(beginDate, endDate,
				statType);
	}

	public List getShopName(int shopId) {
		// TODO Auto-generated method stub
		return advqueryPersistence.getShopName(shopId);
	}

	public List getOneAccountStat(int shopId, String beginDate, String endDate,
			String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getOneAccountStat(shopId, beginDate, endDate, statType);
	}

	public List getShopAccountCompare(String shopId, String beginDate,
			String endDate, String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getShopAccountCompare(shopId, beginDate, endDate, statType);
	}

	public List getAllAccountChangeStat(String beginDate, String endDate,
			String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getAllAccountChangeStat(beginDate, endDate, statType);
	}

	public List getAllConsumeStat(String beginDate, String endDate,
			String statType) throws PortalException {
		List result = new ArrayList();
		try {
			List consume = advqueryPersistence.getAllConsumeStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("tradeamt",objects[1]);
					accMap.put("mngamt",objects[2]);
					accMap.put("tradenum",objects[3]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(AdvWebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("tradeamt",objects[1]);
					accMap.put("mngamt",objects[2]);
					accMap.put("tradenum",objects[3]);
					result.add(accMap);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		}
	}

	public List getDepAccountStat(String deptCode, String beginDate,
			String endDate, String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getDepAccountStat(deptCode, beginDate, endDate, statType);
	}

	public List getDeptName(String deptCode) {
		// TODO Auto-generated method stub
		return advqueryPersistence.getDeptName(deptCode);
	}

	public List getDeptConsumeStat(String deptCode, String beginDate,
			String endDate, String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getDeptConsumeStat(deptCode, beginDate, endDate, statType);
	}

	public List getphotoNumAll(String beginDate, String endDate, String statType)
			throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getphotoNumAll(beginDate, endDate, statType);
	}

	public List getphotoNumByType(String cutType, String beginDate,
			String endDate, String statType) throws PortalException {
		// TODO Auto-generated method stub
		return advqueryPersistence.getphotoNumByType(cutType, beginDate, endDate, statType);
	}

	public List getTransferSuccessRate(String beginDate, String endDate,
			String statType) throws PortalException {
		List result = new ArrayList();
		try {
			
				
			List saving = advqueryPersistence.getTransferSuccessRate(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("account",objects[1]);
					accMap.put("inaccount",objects[2]);
					accMap.put("rate",objects[3]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(AdvWebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("account",objects[1]);
					accMap.put("inaccount",objects[2]);
					accMap.put("rate",objects[3]);
					result.add(accMap);
				}
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		}
	}

	public List getDeviceRate(int serialtype, String beginDate, String endDate,
			String devType, String statType) throws PortalException {
		int devNum = Integer.parseInt(advqueryPersistence.getDeviceNum(devType));
		List result = new ArrayList();
		try {
			List devused = advqueryPersistence.getDeviceUsed(serialtype,beginDate,endDate,statType);
			for (int i=0 ;i<devused.size();i++){
				Object[] objects = (Object[])devused.get(i);
				HashMap accMap = new HashMap();
				accMap.put("balance_date",objects[0]);
				accMap.put("devuse",objects[1]);
				if (devNum==0){
					accMap.put("rate",new Float(0));
				}else{
					accMap.put("rate",new Float(Integer.parseInt(objects[1].toString())*100/devNum));
				}
				accMap.put("total",new Integer(devNum));
				result.add(accMap);
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		}
	}

	public List getEmpType() {
		// TODO Auto-generated method stub
		return advqueryPersistence.getEmpType();
	}

	public List getCusttypeList() {
		// TODO Auto-generated method stub
		return advqueryPersistence.getCusttypeList();
	}

	public List getDeptList() {
		// TODO Auto-generated method stub
		return advqueryPersistence.getDeptList();
	}

	public List getFeeTypeList() {
		// TODO Auto-generated method stub
		return advqueryPersistence.getFeeTypeList();
	}

	public List getSpecialityList() {
		// TODO Auto-generated method stub
		return advqueryPersistence.getSpecialityList();
	}

	public List getSpecialList(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
		// TODO Auto-generated method stub
		return advqueryPersistence.getSpecialList(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);
	}
	
	/**
	 * 按年取得总体平均消费金额，男生平均和女士平均 gejinfeng 按条件查询 2009-01-04
	 * 
	 * @return
	 */
	public List getSpecStat(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
		return advqueryPersistence.getSpecStat(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);
	}
	
	// 平均消费金额，人数分布图
	public List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
		return advqueryPersistence.getConsemeAvg(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);
	}
   
	
	public   String getCustIdBystuempNo(String stuempno)
			throws PortalException {
		  
		return advqueryPersistence.getCustIdBystuempNo(stuempno);
	}

	public List getOneAccountDetail(String custId, String beginDate,
			String endDate) throws PortalException {
		// TODO Auto-generated method stub
		try{
			List list = advqueryPersistence.getOneAccountDetail(custId,beginDate,endDate);
			List result = new ArrayList();
			for(int i=0;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap map = new HashMap();
				map.put("transdate", objects[0]);
				map.put("transtime", objects[1]);
				map.put("custid", objects[2]);
				map.put("custname", objects[3]);
				map.put("cardno", objects[4]);
				map.put("cardcnt", objects[5]);
				map.put("cardbefbal", objects[6]);
				map.put("cardaftbal", objects[7]);
				map.put("amount", objects[8]);
				map.put("TRANSNAME", objects[9]);
				result.add(map);
			}
			return result;
		 }catch(Exception he) {
				he.printStackTrace();
				return null;		
	    }
	}

	public List getCardUseByDept(String deptcode) throws PortalException {
		try{
		List  list = advqueryPersistence.getCardUseByDept(deptcode);
		List result = new ArrayList();
		for(int i=0;i<list.size();i++){
			Object[] objects = (Object[])list.get(i);
			HashMap map = new HashMap();
			map.put("deptname", objects[2]);
			map.put("cardnum", objects[0]);
			map.put("cardtypename", objects[1]);
		    result.add(map);
		}
		return result;
	 }catch(Exception he) {
		he.printStackTrace();
		return null;		
	 }
	}

	public List isHasTransfer(String beginDate, String endDate)
			throws PortalException {
		try{
			List  list = advqueryPersistence.isHasTransfer(beginDate, endDate);
			
			return list;
		 }catch(Exception he) {
			he.printStackTrace();
			return null;		
		 }
	}

	
}
