/**
 * 
 */
package com.kingstargroup.advquery.tradeserial;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.advquery.common.BccctlInit;
import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;



/**
 * @author Administrator
 *
 */
public class TradeSerialDAO {

	/**
	 * 得到某一台Pos机在一段时间内的消费情况
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "ConsumeStatByPosSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "ConsumeStatByPosMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("posid",posId);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 个人帐务情况变动：存款，消AllAccountChangeStatByNoSQL费，押金
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	/*public List getAllAccountChangeStatByCustId(String manIds,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		List  list = new ArrayList();
		StringBuffer   dateSql = new StringBuffer(1024);
		dateSql.append(" select balance_date, saving,consume,ensure from (select operate_date as balance_date, ")
			   .append(" (sum(transfer)+sum(cash)+sum(Pos)+sum(outlay)+sum(ticket)) as saving, ")
			   .append(" sum(consume) consume, sum(ensure)ensure")
			   .append(" from ")	
			.append(" (Select a.operate_date, ")
			//<--圈存转账-->
			.append(" (case when a.serial_type =240001 then 1 else 0 end )*(a.trade_fee) transfer,	")
			//<!--现金充值-->	   
			.append(" (case when a.serial_type =847106 then 1 else 0 end )*(a.trade_fee) cash, ")
			//<!--Pos充值-->
			.append(" (case when a.serial_type =930034 then 1 else 0 end )*(a.trade_fee) Pos,")
			//<!--经费本充值-->
			.append(" (case when a.serial_type =8471062 then 1 else 0 end )*(a.trade_fee) outlay, ")
			//<!--支票充值-->
			.append(" (case when a.serial_type =8471063 then 1 else 0 end )*(a.trade_fee) ticket,")
			//<!--消费-->
			.append(" (case when a.serial_type =930031 then 1 else 0 end )*(a.trade_fee) consume,")
			//<!--押金-->
			.append(" (case when a.serial_type =9003 then 1 else 0 end)*(a.trade_fee) ensure")
			.append(" from YKT_CUR.T_TIF_TRADESERIAL a,YKT_CUR.T_PIF_CARD b,YKT_CUR.T_CIF_CUSTOMER cust")
			.append(" where a.card_id=b.card_id and cust.cut_id=b.cosumer_id and cust.man_id in ("+manIds+")")
			.append(" and operate_date>=:begindate and not(operate_date>:enddate))t")
			.append(" group by operate_date")
			.append(" union")
			.append(" select operate_date as balance_date,")
			.append(" (sum(transfer)+sum(cash)+sum(Pos)+sum(outlay)+sum(ticket)) as saving,")
			.append("	sum(consume) consume,	sum(ensure)ensure")
			.append(" from")
			.append(" (Select a.operate_date,")
			//<!--圈存转账-->
			.append(" (case when a.serial_type =240001 then 1 else 0 end )*(a.trade_fee) transfer,	")
			//<!--现金充值-->	   
			.append(" (case when a.serial_type =847106 then 1 else 0 end )*(a.trade_fee) cash, ")
			//<!--Pos充值-->
			.append(" (case when a.serial_type =930034 then 1 else 0 end )*(a.trade_fee) Pos,")
			//<!--经费本充值-->
			.append(" (case when a.serial_type =8471062 then 1 else 0 end )*(a.trade_fee) outlay, ")
			//<!--支票充值-->
			.append(" (case when a.serial_type =8471063 then 1 else 0 end )*(a.trade_fee) ticket,")
			//<!--消费-->
			.append(" (case when a.serial_type =930031 then 1 else 0 end )*(a.trade_fee) consume,")
			//<!--押金-->
			.append(" (case when a.serial_type =9003 then 1 else 0 end)*(a.trade_fee) ensure")
			.append(" from ykt_his.t_tif_TRADESERIAL_his a,YKT_CUR.T_PIF_CARD b,YKT_CUR.T_CIF_CUSTOMER cust")
			.append(" where a.card_id=b.card_id and cust.cut_id=b.cosumer_id and cust.man_id in ("+manIds+")")
			.append(" and operate_date>=:begindate and not(operate_date>:enddate))t")
			.append(" group by operate_date) ss")
			.append(" order by balance_date ");
		
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				SQLQuery query = session.createSQLQuery(dateSql.toString());
				query.addScalar("balance_date",Hibernate.STRING);
				query.addScalar("saving",Hibernate.FLOAT);
				query.addScalar("consume",Hibernate.FLOAT);
				query.addScalar("ensure",Hibernate.FLOAT);
				query.setString("begindate",beginDate);
				query.setString("enddate",endDate);
				list = query.list();
				
			}else if ("bymonth".equals(statType)){
				execSQL = "AllAccountChangeStatByNoMonthSQL";
			}
			List result = new ArrayList();
			if(list !=null && !list.isEmpty()){
				for(int i=0;i<list.size();i++){
				   Map m = new HashMap();
				      Object[] obj = (Object[])list.get(i);
			       m.put("balance_date",obj[0]);
			       m.put("saving",obj[1]);
			       m.put("consume",obj[2]);
			       m.put("ensure",obj[3]);
			       result.add(m);
				}
			}
			
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return list;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}*/
	public List getAllAccountChangeStatByCustId(String custId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "AllAccountChangeStatByNoSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllAccountChangeStatByNoMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("custid",custId);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	
	/**
	 * 特殊人员查找
	 * @param dateRange
	 * @param beginDate
	 * @param endDate
	 * @param bNum
	 * @param eNum
	 * @param bFee
	 * @param eFee
	 * @return
	 */
	public List getSpecialList(int dateRange,String beginDate,String endDate,int bNum,int eNum,float bFee,float eFee){
		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.getNamedQuery("SpecialListSQL");
			query.setInteger("daterange",dateRange);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			query.setInteger("bnum",bNum);
			query.setInteger("enum",eNum);
			query.setFloat("bfee",bFee);
			query.setFloat("efee",eFee);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 住训培训服务费查询,真实环境的客户类别为cut_type=26
	 * @param classno
	 * @param patchno
	 * @param certno
	 * @return
	 */
	public List getSerFeeList(String classno,String patchno,String certno ,String stuempno){
		StringBuffer sqlstr = new StringBuffer(1024);
		
		
		sqlstr.append(" select acc.account_id,acc.customer_id,acc.card_id, acc.cut_name,cust.stuemp_no, ")
			  .append("  cust.class_no,cust.batch_no,cust.man_id ")
			  .append(" from t_aif_account acc ")
			  .append(" left join  t_cif_customer cust on  ")
			  .append(" acc.customer_id = cust.cut_id ")
		      .append(" left join t_pif_card  card on ")
		      .append(" card.card_id = acc.card_id ")
		      .append(" where cust.cut_state=1 ")
              .append(" and  cust.cut_type=26   ")
              .append(" and card.state_id <2000 ");
		
		if (!"".equals(classno)){
			sqlstr.append(" and cust.class_no='").append(classno).append("'");
		}
		if (!"".equals(patchno)){
			sqlstr.append(" and cust.batch_no='").append(patchno).append("'");
		}
		if (!"".equals(certno)){
			sqlstr.append(" and cust.man_id='").append(certno).append("'");
		}
	/*	if(!"".equals(name)){
			sqlstr.append(" and acc.cut_name like '%").append(name).append("%'");
		}*/
		if(!"".equals(stuempno)){
			sqlstr.append(" and cust.stuemp_no ='").append(stuempno).append("'");
		}
				Session session = HibernateSessionFactory.currentSession();
		try{
			//System.out.println(sqlstr.toString());
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			query.addScalar("account_id",Hibernate.STRING);
			query.addScalar("customer_id",Hibernate.INTEGER);
			query.addScalar("card_id",Hibernate.INTEGER);
			query.addScalar("cut_name",Hibernate.STRING);
			query.addScalar("stuemp_no",Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("batch_no",Hibernate.STRING);
			query.addScalar("man_id",Hibernate.STRING);

			List list = query.list();
			List result = new ArrayList();
			Iterator iter = list.iterator();
			int cardNo = 0;
			int custId = 0;
			String actId="";
			
			
			double sumfillserfee = 0; // 已发放服务费
			double sumfillselftotle = 0;//自充值金额
			double sumaccountbal = 0; // 账户余额 ，名称改为：消费余额
			double sumsmlbalance = 0; // 小钱包余额，名称改为：水控余额 
			double sumfacttotlebal = 0; // 帐户实际余额 名称改为：帐户总余额
			double sumbackbal = 0; // 学生应退现金
			double sumconsbal = 0; // 应补刷金额 名称改为：服务费结余
			

			while (iter.hasNext()){
				double fillserfee = 0; // 已发放服务费
				double smlbalance = 0; // 小钱包余额 名称改为：水控余额 
				double fillself = 0; //自充值金额,包括前台和pos
				double accountbal = 0; // 账户余额 ，名称改为：消费余额
				double facttotlebal = 0; // 帐户实际余额 名称改为：帐户总余额
				double backbal = 0; // 学生应退现金
				double consbal = 0; // 应补刷金额  名称改为：服务费结余
				
				
				Object[] objs = (Object[])iter.next(); 
				
				HashMap hm = new HashMap();
			
				actId =objs[0].toString();
				
				custId = Integer.parseInt(objs[1].toString());
					
				fillself =  getSerFeeTotle(actId,serFeeSelf(),2);
				
				fillserfee =  getSerFeeTotle(actId,serFeeStr(),2);
				
				accountbal = getSerFeeTotle(actId,serAccountBalStr(),1);
				//小钱包金额，调用后台功能号取小钱包金额，如果已经销户，直接去数据库取
				smlbalance =getSmlBal(custId);
				
				facttotlebal = accountbal + smlbalance;//帐户总余额=消费余额+水控余额
				
				if (facttotlebal>=fillself){//帐户总余额>=自充值金额
				//	balance = facttotlebal - fillselftotle;
					backbal = fillself;//学生应退现金
					consbal = facttotlebal - fillself;//帐户总余额-自充值金额
				}else{
				//	balance = 0;
					backbal = facttotlebal;
					consbal = 0;
				}
				
				hm.put("custId",objs[1]);
				hm.put("cardId",objs[2]);
				hm.put("custName",objs[3]);
				hm.put("stuempNo",objs[4]);
				hm.put("classNo",objs[5]);
				hm.put("batchNo",objs[6]);
				hm.put("manId",objs[7]);
				
				hm.put("fillserfee",new Double (fillserfee));
				hm.put("fillselftotle",new Double (fillself));
				hm.put("accountbal",new Double (accountbal));
				hm.put("smlbalance",new Double (smlbalance));
				hm.put("facttotlebal",new Double (facttotlebal));
				hm.put("backbal",new Double (backbal));
				hm.put("consbal",new Double (consbal));
				sumfillserfee = sumfillserfee+fillserfee;
				sumfillselftotle = sumfillselftotle+fillself;
				sumaccountbal = sumaccountbal+accountbal;
				sumsmlbalance = sumsmlbalance+smlbalance;
				sumfacttotlebal = sumfacttotlebal+facttotlebal;
				sumbackbal = sumbackbal+backbal;
				sumconsbal = sumconsbal+consbal;				
				result.add(hm);			
			}
			if (list.size()>0){
				HashMap hm = new HashMap();
				hm.put("custId",new Integer(0));
				hm.put("cardId",new Integer(0));
				hm.put("custName","合计：");
				hm.put("stuempNo","");
				hm.put("classNo","");
				hm.put("batchNo","");
				hm.put("manId","");
				hm.put("fillserfee",new Double (sumfillserfee));
				hm.put("fillselftotle",new Double (sumfillselftotle));
				hm.put("accountbal",new Double (sumaccountbal));
				hm.put("smlbalance",new Double (sumsmlbalance));
				hm.put("facttotlebal",new Double (sumfacttotlebal));
				hm.put("backbal",new Double (sumbackbal));
				hm.put("consbal",new Double (sumconsbal));
				result.add(hm);
			}
			
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 根据
	 * @param custId
	 * @return
	 */
	private double getSerFeeTotle(String  accId,String sqlStr,int sign){
		Session session = HibernateSessionFactory.currentSession();
		//System.out.println(sqlStr);
		try{
			SQLQuery query = session.createSQLQuery(sqlStr);
			query.setString("accId",accId);
			if(sign==2){
			query.setString("accId2",accId);
			}
			query.addScalar("act_id",Hibernate.STRING);
			query.addScalar("fee",Hibernate.DOUBLE);
			List reList = query.list();
			if (reList.size()==0) {
				return 0;
			}else{
				Object[] objs = (Object[])reList.get(0);
				double amount = Double.parseDouble(objs[1].toString());
				return amount;
			}
		} catch (HibernateException e) {
			_log.error(e);
			return 0;
		} finally {
			HibernateSessionFactory.closeSession();
		}		
	}
	

	
	//帐号查到自充值，包括前台和pos机器
	private String serFeeSelf(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("  select act_id,sum(fee) fee from( ")
		 .append("	 select act_id,sum(op_fee) fee from ykt_cur.t_tif_tradelog ")
		 .append("	where act_id=:accId and other_actid='1011' and outorin=2 ")
		 .append("	group by act_id ")
		 .append("	union all ")
		 .append("	select act_id,sum(op_fee) fee from ykt_his.t_tif_tradelog_his ")
		 .append("	where act_id=:accId2 and other_actid='1011' and outorin=2 ")
		 .append("	group by act_id ")
		 .append("	) ")
		 .append("	group by act_id ");
		
		return sqlstr.toString();
	}
	
   //账号查到发放服务费合计值，全是经费本发放,还包括补助 
	private String serFeeStr(){
		StringBuffer sqlstr = new StringBuffer(1024);
		 
		 sqlstr.append(" select act_id,sum(fee) fee from( ")
		 .append(" select act_id,sum(op_fee) fee from ykt_cur.t_tif_tradelog ")
		 .append(" where act_id=:accId and (rtrim(other_actid)='1041' or rtrim(other_actid)='2071') and outorin=2 ")
		 .append(" group by act_id ")
		 .append(" union all ")
		 .append(" select act_id,sum(op_fee) fee from ykt_his.t_tif_tradelog_his ")
		 .append(" where act_id=:accId2 and (rtrim(other_actid)='1041' or rtrim(other_actid)='2071') and outorin=2 ")
		 .append(" group by act_id ")
		 .append(" ) ")
		 .append(" group by act_id ");

		return sqlstr.toString();
	}
	

	
	//客户帐户余额
	private String serAccountBalStr(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append(" select account_id  act_id ,cur_bala  fee  from t_aif_account t  where account_id=:accId ");
		return sqlstr.toString();
	}
	

	
	private double getSmlBal(int custId){
		long xpackhandle = 0;
		bccclt bcc = null;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		double[] smlBalance = new double[1];
		try{
			//_log.info("-------------begin--------------"+bcc);
			bcc = BccctlInit.getBccctlInstance();
			//_log.info("-------------getBccctlInstance--------------"+bcc);
			//bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(BccctlInit.getCpack().getBytes());
			//_log.info("-------------NewXpackHandle--------------");
			if (0 != xpackhandle){
				bcc.SetRequestType(xpackhandle, BccctlInit.FUNCNO);
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(), custId);
				boolean bccret = false;
				//_log.info("-------------bccret1--------------"+bccret);
				bccret = bcc.CallRequest(xpackhandle, 0, 0,BccctlInit.MAINFUNC, 3000, errcode, errmsg);
				//_log.info("-------------bccret2--------------"+bccret);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							//double[] smlBalance = new double[10];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(), smlBalance);//流水号
						}else{
							//_log.info("-------------RetCode[0]--------------"+RecordCount[0]);
							//smlBalance = 0;
						}
					}else{
						//_log.info("-------------RetCode[0]--------------"+RetCode[0]);
						//smlBalance = 0;
					}
				}
				 
			}
			//_log.info("-------------RetCode[0]--------------"+Double.parseDouble(String.valueOf(smlBalance[0])));
			return Double.parseDouble(String.valueOf(smlBalance[0]));
		}catch(UnsatisfiedLinkError e){
			//_log.info("-------------UnsatisfiedLinkError----------------"+e.getMessage());
			_log.error(e.getMessage());
			return 0;
		}catch(Exception e){
			//_log.info("------------Exception-----------------"+e.getMessage());
			_log.error(e.getMessage());
			return 0;
		
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
		}
			
	}		
	}
	/*
	 * 贫困生查找，参数：
	 * 开始日期，结束日期，院系，专业，班级，客户类别，收费类别，开始学号，结束学号，消费频度
	 */
	public List getSpecialList(String bDate,String eDate,
			String deptNo,String specNo,
			String classNo,int custType,
			int feeType,String bStuempNo,
			String eStuempNo,int per,String meal,
			double bavgRange,double eavgRange,
			String selPer,int perRange){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append(" select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type, ")
		.append(" fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no, ")
		.append(" dept.dept_name,cust.s_code,spec.s_name,cust.class_no, ")
		.append(" rc.card_no,count(rc.amount)amcount,(sum(rc.amount)/100)amsum ")
		.append(" ,((sum(rc.amount)/100)/count(rc.amount)) avg ");
		if (!"".equals(meal)){
			strSql.append(", rc.meal ");
		}
		strSql.append(" from ykt_cur.t_rcstatdata rc ")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" left join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type")
		.append(" left join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type")
		.append(" left join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code")
		.append(" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code")
		.append(" where rc.tx_date>='")
		.append(bDate).append("' and rc.tx_date<='").append(eDate).append("'");
		//.append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and rc.tx_date<=:qeDate");
		//添加分析条件
		if (!"".equals(meal)){
			strSql.append(" and rc.meal='").append(meal).append("'");
		}
		if (!"".equals(deptNo)){
			strSql.append(" and cust.classdept_no='").append(deptNo).append("'");
		}
		if (!"".equals(specNo)){
			strSql.append(" and cust.s_code='").append(specNo).append("'");
		}
		if (!"".equals(classNo)){
			strSql.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType>0){
			strSql.append(" and cust.cut_type=").append(custType);
		}
		if (feeType>0){
			strSql.append(" and cust.fee_type=").append(feeType);
		}
		if (!"".equals(bStuempNo)){
			strSql.append(" and cust.stuemp_no>='").append(bStuempNo).append("'");
		}
		if (!"".equals(eStuempNo)){
			strSql.append(" and cust.stuemp_no<='").append(eStuempNo).append("'");
		}
		

		strSql.append(" group by rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,fee.fee_name,")
		.append(" cust.cut_name,cust.stuemp_no,cust.classdept_no,dept.dept_name,cust.s_code,")
		.append(" spec.s_name,cust.class_no");
		if (!"".equals(meal)){
			strSql.append(",rc.meal");
		}
		strSql.append(" order by avg");
		//System.out.println(strSql.toString());
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("cut_id",Hibernate.INTEGER);
			query.addScalar("cut_type",Hibernate.INTEGER);
			query.addScalar("type_name",Hibernate.STRING);
			query.addScalar("fee_type",Hibernate.INTEGER);
			query.addScalar("fee_name",Hibernate.STRING);
			query.addScalar("cut_name",Hibernate.STRING);
			query.addScalar("stuemp_no",Hibernate.STRING);
			query.addScalar("classdept_no",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("s_code",Hibernate.STRING);
			query.addScalar("s_name",Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("card_no",Hibernate.INTEGER);
			query.addScalar("amcount",Hibernate.INTEGER);
			query.addScalar("amsum",Hibernate.DOUBLE);
			query.addScalar("avg",Hibernate.DOUBLE);
			if (!"".equals(meal)){
				query.addScalar("meal",Hibernate.STRING);
			}
			List list = query.list();			
			double avgValue = 0;
			if (!"".equals(selPer)){
				Map avgMap= (Map)getSpecStat(meal).get(0);
				avgValue = Double.parseDouble(avgMap.get("totavg").toString());
			/*	System.out.println("avgValue"+avgMap.get("totavg").toString());
			*/	
			}
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				if (Integer.parseInt(objects[13].toString())<per){
					continue;
				}
				
				if ((Float.parseFloat(objects[15].toString())<bavgRange)||
							(Float.parseFloat(objects[15].toString())>eavgRange)){
						continue;
				}
				
				
				if (!"".equals(selPer)){
					//比较值
					double compValue = 0;
					if ("up".equals(selPer)){
						compValue = avgValue*perRange/100 + avgValue;
						if (compValue>Float.parseFloat(objects[15].toString())){
							continue;
						}
					}
					if ("down".equals(selPer)){
						compValue = avgValue - avgValue*perRange/100 ;
						if (compValue<Float.parseFloat(objects[15].toString())){
							continue;
						}
					}
					
				}
				HashMap accMap = new HashMap();
				accMap.put("cut_id",objects[0]);
				accMap.put("cut_type",objects[1]);
				accMap.put("type_name",objects[2]);
				accMap.put("fee_type",objects[3]);
				accMap.put("fee_name",objects[4]);
				accMap.put("cut_name",objects[5]);
				accMap.put("stuemp_no",objects[6]);
				accMap.put("classdept_no",objects[7]);
				accMap.put("dept_name",objects[8]);
				accMap.put("s_code",objects[9]);
				accMap.put("s_name",objects[10]);
				accMap.put("class_no",objects[11]);
				accMap.put("card_no",objects[12]);
				accMap.put("amcount",objects[13]);
				accMap.put("amsum",objects[14]);
				accMap.put("avg",objects[15]);
				if (!"".equals(meal)){
					accMap.put("meal",mealTrans(objects[16].toString()));
				}else{
					accMap.put("meal","全天");
				}

				
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 按年取得总体平均消费金额，男生平均和女士平均
	 * @return
	 */
	public List getSpecStat(String meal){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("select c.accyear,(a.femaleavg/100)femaleavg,(b.maleavg/100)maleavg,(c.totavg/100)totavg from")
		.append(" (select accyear,sum(amount)/count(*) femaleavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" where cust.sex='1'");
		if (!"".equals(meal)){
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)a,")

		.append(" (select accyear,sum(amount)/count(*) maleavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" where cust.sex='2'");
		if (!"".equals(meal)){
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)b,")

		.append(" (select accyear,sum(amount)/count(*) totavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc");
		
		if (!"".equals(meal)){
			strSql.append(" where rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)c")

		.append(" where c.accyear=b.accyear(+) and c.accyear=a.accyear(+)")
		.append(" order by c.accyear desc");
		//System.out.println(strSql);
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("accyear",Hibernate.STRING);
			query.addScalar("femaleavg",Hibernate.DOUBLE);
			query.addScalar("maleavg",Hibernate.DOUBLE);
			query.addScalar("totavg",Hibernate.DOUBLE);
			List list = query.list();
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("accyear",objects[0]);
				accMap.put("femaleavg",nullToString(objects[1]));
				accMap.put("maleavg",nullToString(objects[2]));
				accMap.put("totavg",nullToString(objects[3]));
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	//平均消费金额，人数分布图
	public List getConsemeAvg(String meal,String bDate,String eDate){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("select count(card_no)num,(amount/100)amavg from ykt_cur.t_rcstatdata")
		.append(" where tx_date>='").append(bDate).append("' and tx_date<='").append(eDate).append("'");
		if (!"".equals(meal)){
			strSql.append(" and meal='").append(meal).append("'");
		}		
		strSql.append(" group by amount/100")
		.append(" order by amount/100");
		//System.out.println(strSql);
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("num",Hibernate.INTEGER);
			query.addScalar("amavg",Hibernate.DOUBLE);
			List list = query.list();
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("num",objects[0]);
				accMap.put("amavg",objects[1]);
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	private String mealTrans(String in){
		if ("bk".equals(in.trim())){
			return "早餐";
		}else if ("lun".equals(in.trim())){
			return "午餐";
		}else if ("sup".equals(in.trim())){
			return "晚餐";
		}else{
			return "全天";
		}
	}
	private String nullToString(Object o){
		if ((o==null)){
			return "0";
		}else if ("".equals(o.toString())){
			return "0";
		}else{
			return o.toString();
		}
	}

	private static final Logger _log = Logger.getLogger(TradeSerialDAO.class);
	
}
