/**
 * 
 */
package com.kingstargroup.advquery.tradeserial;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

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
public class CopyOfTradeSerialDAO {

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
	 * 个人帐务情况变动：存款，消费，押金
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
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
	public List getSerFeeList(String classno,String patchno,String certno){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select cust.cut_id,card.card_id,cust.cut_name,cust.stuemp_no,")
		.append(" cust.class_no,cust.batch_no,cust.man_id from YKT_CUR.t_cif_customer cust")
		.append(" left join YKT_CUR.t_pif_card card on cust.cut_id=card.cosumer_id")
		.append(" where cust.cut_state=1  and cust.cut_type=26 and card.state_id <2000 ");
		if (!"".equals(classno)){
			sqlstr.append(" and cust.class_no='").append(classno).append("'");
		}
		if (!"".equals(patchno)){
			sqlstr.append(" and cust.batch_no='").append(patchno).append("'");
		}
		if (!"".equals(certno)){
			sqlstr.append(" and cust.man_id='").append(certno).append("'");
		}
		
		Session session = HibernateSessionFactory.currentSession();
		try{
			//System.out.println(sqlstr.toString());
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			query.addScalar("cut_id",Hibernate.INTEGER);
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
			
			double smlbalance = 0; // 小钱包余额 名称改为：水控余额 
			
			double sumfillserfee = 0; // 已发放服务费
			double sumfillselftotle = 0;	//自充值金额
			double sumaccountbal = 0; // 账户余额 ，名称改为：消费余额
			double sumsmlbalance = 0; // 小钱包余额，名称改为：水控余额 
			double sumfacttotlebal = 0; // 帐户实际余额 名称改为：帐户总余额
			//double sumbalance = 0; // 结余余额 ，不用显示 
			double sumbackbal = 0; // 学生应退现金
			double sumconsbal = 0; // 应补刷金额 名称改为：服务费结余
			

			while (iter.hasNext()){
				double fillserfee = 0; // 已发放服务费
				double fillselfFore = 0; //自充值金额,前台
				double fillselfPos = 0; //自充值金额,Pos
				double fillselftotle = 0;	//自充值金额
				double accountbal = 0; // 账户余额 ，名称改为：消费余额
				
				double facttotlebal = 0; // 帐户实际余额 名称改为：帐户总余额
				//double balance = 0; // 结余余额 ，不用显示 
				double backbal = 0; // 学生应退现金
				double consbal = 0; // 应补刷金额  名称改为：服务费结余
				
				
				Object[] objs = (Object[])iter.next(); 
				HashMap hm = new HashMap();
				if (objs[1]==null){
					cardNo = 0;
				}else{
					cardNo = Integer.parseInt(objs[1].toString());
				}
				
				
				custId = Integer.parseInt(objs[0].toString());//17214
				List cardlist  = getCardnoByCustId(custId);
				
				for(int i=0; i<cardlist.size() ;i++){
					   int  card_Nos = ((Integer)cardlist.get(i)).intValue();
					   fillserfee =fillserfee + getSerFeeTotle(card_Nos,serFeeStr(),2);//存在补办卡的情况，服务费需要一起加上 
					   fillselfPos = fillselfPos + getSerFeeTotle(card_Nos,serFeeSelfPos(),1);//存在补办卡的情况，自充值需要一起加上 
					   
					} 
				
				//_log.info("=====custId======"+custId);
				//fillserfee = getSerFeeTotle(cardNo,serFeeStr(),2);
				//fillselfFore = getSerFeeTotle(cardNo,serFeeSelfFore(),0);
				//fillselfPos = getSerFeeTotle(cardNo,serFeeSelfPos(),1);
				accountbal = getSerFeeTotle(cardNo,serAccountBalStr(),0);
				//小钱包金额，调用后台功能号取小钱包金额，如果已经销户，直接去数据库取
				smlbalance =getSmlBal(custId);//getSerFeeTotle(cardNo,serSmlBal(),2);
				fillselftotle = fillselfFore + fillselfPos;//自充值金额
				facttotlebal = accountbal + smlbalance;//帐户总余额=消费余额+水控余额
				
				if (facttotlebal>=fillselftotle){//帐户总余额>=自充值金额
				//	balance = facttotlebal - fillselftotle;
					backbal = fillselftotle;//学生应退现金
					consbal = facttotlebal - fillselftotle;//帐户总余额-自充值金额
				}else{
				//	balance = 0;
					backbal = facttotlebal;
					consbal = 0;
				}
				
				hm.put("custId",objs[0]);
				hm.put("cardId",objs[1]);
				hm.put("custName",objs[2]);
				hm.put("stuempNo",objs[3]);
				hm.put("classNo",objs[4]);
				hm.put("batchNo",objs[5]);
				hm.put("manId",objs[6]);
				
				hm.put("fillserfee",new Double (fillserfee));
				hm.put("fillselftotle",new Double (fillselftotle));
				hm.put("accountbal",new Double (accountbal));
				hm.put("smlbalance",new Double (smlbalance));
				hm.put("facttotlebal",new Double (facttotlebal));
				//hm.put("balance",new Double (balance));
				hm.put("backbal",new Double (backbal));
				hm.put("consbal",new Double (consbal));
				sumfillserfee = sumfillserfee+fillserfee;
				sumfillselftotle = sumfillselftotle+fillselftotle;
				sumaccountbal = sumaccountbal+accountbal;
				sumsmlbalance = sumsmlbalance+smlbalance;
				sumfacttotlebal = sumfacttotlebal+facttotlebal;
				//sumbalance = sumbalance+balance;
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
				//hm.put("balance",new Double (sumbalance));
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
	private double getSerFeeTotle(int cardNo,String sqlStr,int sign){
		Session session = HibernateSessionFactory.currentSession();
		//System.out.println(sqlStr);
		try{
			SQLQuery query = session.createSQLQuery(sqlStr);
			query.setInteger("cardNo",cardNo);
			if (sign==1){
				query.setInteger("cardNo2",cardNo);
				query.setInteger("cardNo3",cardNo);
			}
			if (sign==2){
				query.setInteger("cardNo2",cardNo);
				
			}
			
			query.addScalar("card_no",Hibernate.INTEGER);
			query.addScalar("amount",Hibernate.DOUBLE);
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
	
	private  List  getCardnoByCustId(int custId){
		Session session = HibernateSessionFactory.currentSession();
		List list = new ArrayList();
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append(" select card_id  from ykt_cur.t_pif_card where cosumer_id=:custId ");
		try{
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			query.setInteger("custId",custId);
			query.addScalar("card_id",Hibernate.INTEGER);
		    list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return list;
		} finally {
			HibernateSessionFactory.closeSession();
		}		
	}
	
	//卡号查到发放服务费合计值，全是经费本发放,还包括补助 
	private String serFeeStr(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("  select card_no , sum(amount) amount from ( ")
			  .append("	 select card_no,sum(amount)amount from YKT_CUR.t_tif_savdtl where bill_type=3 ")
			  .append("	 and card_no=:cardNo group by card_no ") 
			  .append("	 union all ")
              .append("	 select card_no,sum(amount)amount  from ykt_cur.t_tif_subsidy  where ")  
		      .append("	 status=3 and bill_type=3  and card_no=:cardNo2 group by card_no ) t1 ")
			  .append("	 group by card_no ");
		//sqlstr.append("select card_no,sum(amount)amount from YKT_CUR.t_tif_savdtl where bill_type=3  and card_no=:cardNo group by card_no");
		//sqlstr.append(" select card_no,sum(amount)amount  from ykt_cur.t_tif_subsidy  where  	status=3 and bill_type=3  and card_no=:cardNo group by card_no ");
		return sqlstr.toString();
	}
	
	//自己充值的金额，包括前台充值和pos充值两部分,前台充值部分
	private String serFeeSelfFore(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_no,sum(amount)amount from YKT_CUR.t_tif_savdtl where bill_type<>3 and card_no=:cardNo group by card_no");
		return sqlstr.toString();
	}
	
	//自己充值的金额，包括前台充值和pos充值两部分,Pos充值部分+前台充值部分
	private String serFeeSelfPos(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_id as card_no,(sum(trade_fee)-sum(nvl(s.amount,0)))amount   from (")
		.append(" select card_id,trade_fee,serial_type,serial_state from YKT_CUR.t_tif_tradeserial")
		.append(" where (serial_type=930034 or serial_type=847106) and serial_state=2 and card_id=:cardNo")
		.append(" union all")
		.append(" select card_id,trade_fee,serial_type,serial_state from YKT_HIS.t_tif_tradeserial_his")
		.append(" where (serial_type=930034 or serial_type=847106) and serial_state=2 and card_id=:cardNo2")
		.append(" )ser  ")
		.append(" left join   (select card_no, nvl(amount,0)amount  from ykt_cur.t_tif_savdtl t where tx_code=847106  and card_no=:cardNo3  ) s ")
		.append(" on s.card_no = ser.card_id ")
		.append(" group by card_id");
		return sqlstr.toString();
	}
	
	//客户帐户余额
	private String serAccountBalStr(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_id as card_no,sum(cur_bala)amount from YKT_CUR.t_aif_account where card_id=:cardNo group by card_id");
		return sqlstr.toString();
	}
	
	//小钱包金额
	private String serSmlBal(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_id as card_no,sum(trade_fee)amount from (")
		.append(" select card_id,trade_fee,serial_type,serial_state from YKT_CUR.t_tif_tradeserial")
		.append(" where serial_type=847309 and serial_state=2 and card_id=:cardNo")
		.append(" union all")
		.append(" select card_id,trade_fee,serial_type,serial_state from YKT_HIS.t_tif_tradeserial_his")
		.append(" where serial_type=847309 and serial_state=2 and card_id=:cardNo2")
		.append(" )ser")
		.append(" group by card_id");
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
	private static final Logger _log = Logger.getLogger(CopyOfTradeSerialDAO.class);
	
}
