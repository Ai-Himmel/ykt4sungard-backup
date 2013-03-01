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
	 * �õ�ĳһ̨Pos����һ��ʱ���ڵ��������
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
	 * ������������䶯�������ѣ�Ѻ��
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
	 * ������Ա����
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
	 * סѵ��ѵ����Ѳ�ѯ,��ʵ�����Ŀͻ����Ϊcut_type=26
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
			
			double smlbalance = 0; // СǮ����� ���Ƹ�Ϊ��ˮ����� 
			
			double sumfillserfee = 0; // �ѷ��ŷ����
			double sumfillselftotle = 0;	//�Գ�ֵ���
			double sumaccountbal = 0; // �˻���� �����Ƹ�Ϊ���������
			double sumsmlbalance = 0; // СǮ�������Ƹ�Ϊ��ˮ����� 
			double sumfacttotlebal = 0; // �ʻ�ʵ����� ���Ƹ�Ϊ���ʻ������
			//double sumbalance = 0; // ������� ��������ʾ 
			double sumbackbal = 0; // ѧ��Ӧ���ֽ�
			double sumconsbal = 0; // Ӧ��ˢ��� ���Ƹ�Ϊ������ѽ���
			

			while (iter.hasNext()){
				double fillserfee = 0; // �ѷ��ŷ����
				double fillselfFore = 0; //�Գ�ֵ���,ǰ̨
				double fillselfPos = 0; //�Գ�ֵ���,Pos
				double fillselftotle = 0;	//�Գ�ֵ���
				double accountbal = 0; // �˻���� �����Ƹ�Ϊ���������
				
				double facttotlebal = 0; // �ʻ�ʵ����� ���Ƹ�Ϊ���ʻ������
				//double balance = 0; // ������� ��������ʾ 
				double backbal = 0; // ѧ��Ӧ���ֽ�
				double consbal = 0; // Ӧ��ˢ���  ���Ƹ�Ϊ������ѽ���
				
				
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
					   fillserfee =fillserfee + getSerFeeTotle(card_Nos,serFeeStr(),2);//���ڲ��쿨��������������Ҫһ����� 
					   fillselfPos = fillselfPos + getSerFeeTotle(card_Nos,serFeeSelfPos(),1);//���ڲ��쿨��������Գ�ֵ��Ҫһ����� 
					   
					} 
				
				//_log.info("=====custId======"+custId);
				//fillserfee = getSerFeeTotle(cardNo,serFeeStr(),2);
				//fillselfFore = getSerFeeTotle(cardNo,serFeeSelfFore(),0);
				//fillselfPos = getSerFeeTotle(cardNo,serFeeSelfPos(),1);
				accountbal = getSerFeeTotle(cardNo,serAccountBalStr(),0);
				//СǮ�������ú�̨���ܺ�ȡСǮ��������Ѿ�������ֱ��ȥ���ݿ�ȡ
				smlbalance =getSmlBal(custId);//getSerFeeTotle(cardNo,serSmlBal(),2);
				fillselftotle = fillselfFore + fillselfPos;//�Գ�ֵ���
				facttotlebal = accountbal + smlbalance;//�ʻ������=�������+ˮ�����
				
				if (facttotlebal>=fillselftotle){//�ʻ������>=�Գ�ֵ���
				//	balance = facttotlebal - fillselftotle;
					backbal = fillselftotle;//ѧ��Ӧ���ֽ�
					consbal = facttotlebal - fillselftotle;//�ʻ������-�Գ�ֵ���
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
				hm.put("custName","�ϼƣ�");
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
	 * ����
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
	
	//���Ų鵽���ŷ���Ѻϼ�ֵ��ȫ�Ǿ��ѱ�����,���������� 
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
	
	//�Լ���ֵ�Ľ�����ǰ̨��ֵ��pos��ֵ������,ǰ̨��ֵ����
	private String serFeeSelfFore(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_no,sum(amount)amount from YKT_CUR.t_tif_savdtl where bill_type<>3 and card_no=:cardNo group by card_no");
		return sqlstr.toString();
	}
	
	//�Լ���ֵ�Ľ�����ǰ̨��ֵ��pos��ֵ������,Pos��ֵ����+ǰ̨��ֵ����
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
	
	//�ͻ��ʻ����
	private String serAccountBalStr(){
		StringBuffer sqlstr = new StringBuffer(1024);
		sqlstr.append("select card_id as card_no,sum(cur_bala)amount from YKT_CUR.t_aif_account where card_id=:cardNo group by card_id");
		return sqlstr.toString();
	}
	
	//СǮ�����
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
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(), smlBalance);//��ˮ��
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
