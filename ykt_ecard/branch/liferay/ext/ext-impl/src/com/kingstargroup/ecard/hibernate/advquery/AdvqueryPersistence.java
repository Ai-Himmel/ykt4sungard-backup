/**
 *
 */
package com.kingstargroup.ecard.hibernate.advquery;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.custype.TCusttype;
import com.kingstargroup.ecard.hibernate.feetype.TFeetype;
import com.kingstargroup.ecard.hibernate.specialty.TSpecialty;
import com.liferay.portal.service.persistence.BasePersistence;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-19 <br>
 *
 * @author HLQ
 * @since 1.0
 */
public class AdvqueryPersistence extends BasePersistence {


    public List getCardUseByDept(String deptcode) throws HibernateException {
        String execSQL = "CardUsebyDeptSQL";
        Session s = openSession();
        try {
            Query q = s.getNamedQuery(execSQL);
            q.setString("deptcode", deptcode);
            return q.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }


    public List getOneAccountDetail(String custId, String begindate, String enddate) throws HibernateException {

        String execSQL = "OneAccountTransdtlSQL";
        Session s = openSession();
        try {

            Query q = s.getNamedQuery(execSQL);
            q.setString("custid", custId);
            q.setString("begindate", begindate);
            q.setString("enddate", enddate);
            return q.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }


    /**
     * @param stuempno
     *
     * @return
     *
     * @throws HibernateException
     */
    public String getCustIdBystuempNo(String stuempno) throws HibernateException {

        Session s = openSession();
        try {
            StringBuffer sb = new StringBuffer(1024);
            sb.append(" select  custId  from  ykt_cur.t_customer where  status='1' and  stuempno='" + stuempno + "'");
            SQLQuery query = s.createSQLQuery(sb.toString());
            query.addScalar("custId", Hibernate.STRING);
            List list = query.list();
            if (list != null && !list.isEmpty()) {
                return list.get(0).toString();
            }
            return "";
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }

    }

    /**
     * 发卡情况
     *
     * @param enddate
     *
     * @return
     *
     * @throws HibernateException
     */

    public List getCarduse(String enddate) throws HibernateException {

        Session s = openSession();
        try {
            StringBuffer sb = new StringBuffer(1024);
            sb.append(" select c.cardtype cardtype,t.cardtypename typename  ,count(*) cardnum")
                    .append(" from ykt_cur.t_card c ,ykt_cur.t_cardtype t")
                    .append(" where c.cardtype= t.cardtype and c.status='1' ")
                    .append(" and c.opendate <='").append(enddate).append("' ")
                    .append(" group by c.cardtype,t.cardtypename ");
            SQLQuery query = s.createSQLQuery(sb.toString());
            query.addScalar("cardtype", Hibernate.STRING);
            query.addScalar("typename", Hibernate.STRING);
            query.addScalar("cardnum", Hibernate.INTEGER);
            return query.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    public int getCardUseTotal(String enddate) throws HibernateException {

        Session s = openSession();
        try {
            StringBuffer sb = new StringBuffer(1024);
            sb.append("  select count(c.cardno) total   from ykt_cur.t_card c where c.status='1' and c.opendate<='")
                    .append(enddate).append("'");
            SQLQuery query = s.createSQLQuery(sb.toString());
            query.addScalar("total", Hibernate.INTEGER);
            List list = query.list();
            return Integer.parseInt(list.get(0).toString());
        } catch (HibernateException e) {
            _log.error(e);
            return 0;
        }

    }

    /**
     * 卡片使用情况
     *
     * @param begindate
     * @param enddate
     * @param statType
     *
     * @return
     *
     * @throws HibernateException
     */
    public List getCardOpenLoseBack(String begindate, String enddate, String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek").equals(statType)) {
                execSQL = "CardOpenLoseBackSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "CardOpenLoseBackMonthSQL";
            }
            Query q = s.getNamedQuery(execSQL);
            q.getQueryString();
            q.setString("begindate", begindate);
            q.setString("enddate", enddate);
            return q.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }


    /**
     * 存款总体情况统计（存款金额统计）
     *
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getTotleSavingMoneyStat(String beginDate, String endDate,
                                        String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
                execSQL = "TotleMoneySavingStatSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "TotleMoneySavingStatMonthSQL";
            }
            Query q = s.getNamedQuery(execSQL);
            q.setString("begindate", beginDate);
            q.setString("enddate", endDate);
            return q.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 存款总体情况笔数统计 2006-5-31 hjw
     *
     * @param
     *
     * @return
     */
    public List getTotleSavingNumStat(String beginDate, String endDate,
                                      String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
                execSQL = "TotleSavingNumStatSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "TotleSavingNumStatMonthSQL";
            }
            Query q = s.getNamedQuery(execSQL);
            q.setString("begindate", beginDate);
            q.setString("enddate", endDate);
            return q.list();
        } catch (HibernateException e) {
            _log.error(e);

            return null;
        }
    }

    /**
     * 存款情况分类统计
     *
     * @param seriType
     * @param beginDate
     * @param endDate
     * @param statType
     *
     * @throws org.hibernate.HibernateException
     *
     */
    public List getSavingSortStat(String seriType, String beginDate,
                                  String endDate, String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
                execSQL = "savingSortStatSQL_ORACLE";
            } else if ("bymonth".equals(statType)) {
                execSQL = "savingSortStatMonthSQL_ORACLE";
            }
            Query query = s.getNamedQuery(execSQL);
            query.setInteger("seritype", Integer.parseInt(seriType));
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            e.printStackTrace();
            _log.error(e);
            return null;
        }
    }

    /**
     * 返回收费机的名称
     *
     * @return
     */
    public List getPosDeviceList(String posId) {
        Session s = openSession();
        try {
            SQLQuery query = s
                    .createSQLQuery("select DEVICENAME  from ykt_cur.v_device where devtypecode in('1055','0226','0232') and devphyid=:posid");
            query.setString("posid", posId);
            query.addScalar("DEVICENAME", Hibernate.STRING);
            return query.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 得到某一台Pos机在一段时间内的消费情况
     *
     * @param posId
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getConsumeStatByPos(String posId, String beginDate,
                                    String endDate, String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType) || ("byweek".equals(statType)))) {
                execSQL = "ConsumeStatByPosSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "ConsumeStatByPosMonthSQL";
            }
            Query query = s.getNamedQuery(execSQL);
            query.setString("posid", posId);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 商户整体账户变动情况，营业额，管理费金额
     *
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getShopAccountChangeStat(String beginDate, String endDate,
                                         String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
                execSQL = "ShopAccountChangeStatSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "ShopAccountChangeStatMonthSQL";
            }
            Query query = s.getNamedQuery(execSQL);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 返回根据商户编号返回商户名称
     *
     * @return
     */
    public List getShopName(int shopId) throws HibernateException {
        Session s = openSession();
        try {
            Query query = s.createQuery(" from TShop where shopid=:shopid ");
            query.setInteger("shopid", shopId);
            return query.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 各商户营业情况统计
     *
     * @param shopId
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getOneAccountStat(int shopId, String beginDate, String endDate,
                                  String statType) throws HibernateException {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
                execSQL = "OneShopAccountChangeStatSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "OneShopAccountChangeStatMonthSQL";
            }
            Query query = s.getNamedQuery(execSQL);
            query.setInteger("shopid", shopId);
            query.setString("begindate", beginDate);
            query.setString("endate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 各商户营业情况对比
     *
     * @param shopId
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getShopAccountCompare(String shopId, String beginDate,
                                      String endDate, String statType) throws HibernateException {
        StringBuffer execSQL = new StringBuffer(1024);
        Session s = openSession();
        if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
            execSQL
                    .append(
                            "select rpt.shopid,shop.shopname,sum(rpt.transcnt) tradenum,")
                    .append(
                            "sum(rpt.transamt) tradeamt,sum(rpt.rakeoffamt) mngamt,sum(rpt.amount) totalamt ")
                    .append(
                            "from ykt_cur.t_rptshoprakeoff rpt left join ykt_cur.t_shop shop on rpt.shopid=shop.shopid ")
                    .append("where rpt.accdate>='").append(beginDate).append(
                    "' and rpt.accdate<='").append(endDate).append(
                    "' and rpt.shopid in (").append(shopId).append(
                    ") group by rpt.shopid,shop.shopname");
        } else if ("bymonth".equals(statType)) {
            execSQL
                    .append(
                            "select rpt.shopid,shop.shopname,sum(rpt.transcnt) tradenum,")
                    .append(
                            "sum(rpt.transamt) tradeamt,sum(rpt.rakeoffamt) mngamt,sum(rpt.amount) totalamt ")
                    .append(
                            "from ykt_cur.t_rptshoprakeoff rpt left join ykt_cur.t_shop shop on rpt.shopid=shop.shopid ")
                    .append(" where substr(rpt.accdate,1,6)>='").append(
                    beginDate).append(
                    "' and substr(rpt.accdate,1,6)<='").append(endDate)
                    .append("' and rpt.shopid in (").append(shopId).append(
                    ") group by rpt.shopid,shop.shopname");
        }
        try {
            SQLQuery query = s.createSQLQuery(execSQL.toString());
            query.addScalar("shopid", Hibernate.INTEGER);
            query.addScalar("shopname", Hibernate.STRING);
            query.addScalar("tradenum", Hibernate.INTEGER);
            query.addScalar("tradeamt", Hibernate.DOUBLE);
            query.addScalar("mngamt", Hibernate.DOUBLE);
            query.addScalar("totalamt", Hibernate.DOUBLE);
            List list = query.list();

            List result = new ArrayList();
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);
                HashMap accMap = new HashMap();
                accMap.put("shopid", objects[0]);
                accMap.put("shopname", objects[1]);
                accMap.put("tradenum", objects[2]);
                accMap.put("tradeamt", objects[3]);
                accMap.put("mngamt", objects[4]);
                accMap.put("totalamt", objects[5]);
                result.add(accMap);
            }
            return result;
        } catch (HibernateException e) {
            e.printStackTrace();
            _log.error(e);
            return null;
        }
    }

    /**
     * 整体帐务情况变化：存款，消费，押金(按日期范围统计)
     *
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getAllAccountChangeStat(String beginDate, String endDate,
                                        String statType) {
        String execSQL = "";
        Session s = openSession();
        try {
            if (("bydate".equals(statType)) || (("byweek".equals(statType)))) {
                execSQL = "AllAccountChangeStatSQL";
            } else if ("bymonth".equals(statType)) {
                execSQL = "AllAccountChangeMonthSQL";
            }
            Query query = s.getNamedQuery(execSQL);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * Method name:getAllConsumeStat Description: 总体消费情况统计 Return: List
     *
     * @param beginDate
     * @param endDate
     * @param statType
     *
     * @return
     *
     * @throws HibernateException
     */
    public List getAllConsumeStat(String beginDate, String endDate,
                                  String statType) throws HibernateException {
        Session s = openSession();

        StringBuffer sqlStr = new StringBuffer();
        if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
            sqlStr
                    .append(
                            "select t.accdate balance_date,sum(t.transcnt) tradenum,sum(t.cramt)tradeamt,")
                    .append(
                            "sum(0)mngamt from ykt_cur.t_rptsubjledger t left join ykt_cur.t_transtype st on t.transtype=st.transtype ")
                    .append(
                            "where t.transtype=232 and t.subjno='2004' and  t.accdate>='"
                                    + beginDate + "' and t.accdate<='"
                                    + endDate + "' ")
                    .append(
                            "group by t.accdate,t.transtype,st.transname order by t.accdate desc");
        } else if ("bymonth".equals(statType)) {
            sqlStr
                    .append(
                            "select substr(t.accdate,1,6) balance_date,sum(t.transcnt) tradenum,sum(t.cramt)tradeamt,")
                    .append(
                            "sum(0)mngamt from ykt_cur.t_rptsubjledger t left join ykt_cur.t_transtype st on t.transtype=st.transtype ")
                    .append(
                            "where t.transtype=232 and t.subjno='2004' and substr(t.accdate,1,6)>='"
                                    + beginDate
                                    + "' and substr(t.accdate,1,6)<='"
                                    + endDate + "' ")
                    .append(
                            "group by substr(t.accdate,1,6),t.transtype,st.transname order by substr(t.accdate,1,6) desc");
        }

        try {
            //System.out.println(sqlStr.toString());
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("balance_date", Hibernate.STRING);
            q.addScalar("tradeamt", Hibernate.FLOAT);
            q.addScalar("mngamt", Hibernate.FLOAT);
            q.addScalar("tradenum", Hibernate.INTEGER);
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    /**
     * Method name:getDepAccountStat Description: Return: List
     *
     * @param deptCode
     * @param beginDate
     * @param endDate
     * @param statType
     *
     * @return
     */
    public List getDepAccountStat(String deptCode, String beginDate,
                                  String endDate, String statType) throws HibernateException {
        // String execSQL="";
        StringBuffer execSQL = new StringBuffer(1024);
        if (("bydate".equals(statType)) || ("byweek".equals(statType))) {
            // execSQL = "deptAccountStatSQL";
            execSQL
                    .append(
                            "select accdate balance_date,sum(saveamt) saving,sum(conamt)consume,sum(dhfamt)deposit,sum(yjamt)managefee from(")
                    .append("select t.accdate,t.deptcode,dept.deptname,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.transcnt)savecnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.cramt)saveamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.transcnt)concnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.dramt)conamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.transcnt)dhfcnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.dramt)dhfamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.transcnt)yjcnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.cramt)yjamt ")
                    .append("from ykt_portal.t_rptdeptledger t  left join ykt_cur.t_dept dept ")
                    .append("on t.deptcode=dept.deptcode where dept.deptcode='")
                    .append(deptCode).append("')tt ")
                    .append("where accdate>='")
                    .append(beginDate)
                    .append("' and accdate<='")
                    .append(endDate)
                    .append("' group by accdate order by accdate");
        } else if ("bymonth".equals(statType)) {
            // execSQL = "deptAccountStatMonthSQL";
            execSQL
                    .append(
                            "select substr(accdate,1,6) balance_date,sum(saveamt) saving,sum(conamt)consume,sum(dhfamt)deposit,sum(yjamt)managefee from(")
                    .append("select accdate,t.deptcode,dept.deptname,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.transcnt)savecnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.cramt)saveamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.transcnt)concnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.dramt)conamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.transcnt)dhfcnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.dramt)dhfamt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.transcnt)yjcnt,")
                    .append(
                            "(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.cramt)yjamt ")

                    .append(
                            "from ykt_portal.t_rptdeptledger t  left join ykt_cur.t_dept dept ")
                    .append("on t.deptcode=dept.deptcode where dept.deptcode='")
                    .append(deptCode)
                    .append("')tt ")
                    .append("where substr(accdate,1,6)>='")
                    .append(beginDate)
                    .append("' and substr(accdate,1,6)<='")
                    .append(endDate)
                    .append("' group by substr(accdate,1,6) order by substr(accdate,1,6)");
        }
        Session s = openSession();

        try {
            //System.out.println(execSQL.toString());
            SQLQuery query = s.createSQLQuery(execSQL.toString());
            query.addScalar("balance_date", Hibernate.STRING);
            query.addScalar("saving", Hibernate.FLOAT);
            query.addScalar("consume", Hibernate.FLOAT);
            query.addScalar("deposit", Hibernate.FLOAT);
            query.addScalar("managefee", Hibernate.FLOAT);
            List list = query.list();

            List result = new ArrayList();
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);
                HashMap accMap = new HashMap();
                accMap.put("balance_date", objects[0]);
                accMap.put("saving", objects[1]);
                accMap.put("consume", objects[2]);
                accMap.put("deposit", objects[3]);
                accMap.put("managefee", objects[4]);
                result.add(accMap);
            }
            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 根据部门编号得到部门名称
     *
     * @param deptCode
     *
     * @return
     */
    public List getDeptName(String deptCode) {
        Session s = openSession();
        try {
            Query query = s
                    .createQuery(" from TDept where deptcode=:deptcode order by DEPTNAME");
            query.setString("deptcode", deptCode);
            return query.list();
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * Method name:getDeptConsumeStat Description: 3.4.3 整个单位消费情况 Return: List
     *
     * @param deptCode
     * @param beginDate
     * @param endDate
     * @param statType
     *
     * @return
     */
    public List getDeptConsumeStat(String deptCode, String beginDate,
                                   String endDate, String statType) {
        StringBuffer execSQL = new StringBuffer(1024);
        if (("bydate".equals(statType)) || ("byweek".equals(statType))) {

            execSQL
                    .append("select accdate balance_date,sum(concnt) consumenum,sum(conamt)consumemoney,")
                    .append("(case when sum(concnt)=0 then 0 else to_number(sum(conamt))/to_number(sum(concnt)) end) avgmoney ")
                    .append("from (select t.accdate,t.deptcode,dept.deptname,")
                    .append("(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.transcnt)savecnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.cramt)saveamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.transcnt)concnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.dramt)conamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.transcnt)dhfcnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.dramt)dhfamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.transcnt)yjcnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.cramt)yjamt ")
                    .append("from ykt_portal.t_rptdeptledger t  left join ykt_cur.t_dept dept ")
                    .append("on t.deptcode=dept.deptcode ");
            if (deptCode != null && !deptCode.equals("")) {
                execSQL.append("where dept.deptcode='")
                        .append(deptCode)
                        .append("')tt ");
            } else {
                execSQL.append(")tt ");
            }
            execSQL.append("where accdate>='")
                    .append(beginDate)
                    .append("' and accdate<='")
                    .append(endDate)
                    .append("' group by accdate order by accdate");
        } else if ("bymonth".equals(statType)) {
            execSQL
                    .append("select substr(accdate,1,6) balance_date,sum(concnt) consumenum,sum(conamt)consumemoney,")
                    .append("(case when sum(concnt)=0 then 0 else to_number(sum(conamt))/to_number(sum(concnt)) end) avgmoney ")
                    .append("from (select t.accdate,t.deptcode,dept.deptname,")
                    .append("(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.transcnt)savecnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(201,202,203,204) then 1 else 0 end)*(t.cramt)saveamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.transcnt)concnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(232) then 1 else 0 end)*(t.dramt)conamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.transcnt)dhfcnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(604) then 1 else 0 end)*(t.dramt)dhfamt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.transcnt)yjcnt,")
                    .append("(case when t.subjno in(2001) and t.transtype in(601,602) then 1 else 0 end)*(t.cramt)yjamt ")
                    .append("from ykt_portal.t_rptdeptledger t  left join ykt_cur.t_dept dept ")
                    .append("on t.deptcode=dept.deptcode ");
            if (deptCode != null && !deptCode.equals("")) {
                execSQL.append("where dept.deptcode='")
                        .append(deptCode)
                        .append("')tt ");
            } else {
                execSQL.append(")tt ");
            }
            execSQL.append("where substr(accdate,1,6)>='")
                    .append(beginDate)
                    .append("' and substr(accdate,1,6)<='")
                    .append(endDate)
                    .append("' group by substr(accdate,1,6) order by substr(accdate,1,6)");
        }
        Session s = openSession();
        try {
            //System.out.println(execSQL.toString());
            SQLQuery query = s.createSQLQuery(execSQL.toString());
            query.addScalar("balance_date", Hibernate.STRING);
            query.addScalar("consumenum", Hibernate.INTEGER);
            query.addScalar("consumemoney", Hibernate.FLOAT);
            query.addScalar("avgmoney", Hibernate.FLOAT);

            List list = query.list();
            List result = new ArrayList();
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);
                HashMap conMap = new HashMap();
                conMap.put("balance_date", objects[0]);
                conMap.put("consumenum", objects[1]);
                conMap.put("consumemoney", objects[2]);
                conMap.put("avgmoney", objects[3]);
                result.add(conMap);
            }
            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 拍照情况统计（所有人）
     *
     * @param cutType
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getphotoNumAll(String beginDate, String endDate, String statType) {
        String sqlQuery = "";
        Session session = openSession();
        if ("bymonth".equals(statType)) {
            sqlQuery = "photoNumByTypeMonthAllSQL";
        } else if ("bydate".equals(statType)) {
            sqlQuery = "photoNumByTypeAllSQL";
        }
        try {
            Query query = session.getNamedQuery(sqlQuery);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 拍照情况统计按人员类别统计
     *
     * @param cutType
     * @param beginDate
     * @param endDate
     *
     * @return
     */
    public List getphotoNumByType(String cutType, String beginDate,
                                  String endDate, String statType) {
        String sqlQuery = "";
        Session session = openSession();
        if ("bymonth".equals(statType)) {
            sqlQuery = "photoNumByTypeMonthSQL";
        } else if ("bydate".equals(statType)) {
            sqlQuery = "photoNumByTypeSQL";
        }
        try {
            Query query = session.getNamedQuery(sqlQuery);
            query.setString("cuttype", cutType);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 圈存成功率统计 2006-6-6 hjw
     *
     * @param beginDate
     * @param endDate
     *
     * @return List
     */
    public List isHasTransfer(String beginDate, String endDate) {
        Session session = openSession();
        Session s = openSession();
        StringBuffer sqlStr = new StringBuffer();
        sqlStr.append(" select s.accdate,sum(s.transcnt)transcnt from ykt_cur.t_rptsubjledger s ")
                .append(" where s.transtype in (204,210) and ")
                .append(" s.accdate>= '" + beginDate + "'")
                .append(" and s.accdate<='" + endDate + "'")
                .append(" group by s.accdate");
        try {
            SQLQuery q = s.createSQLQuery(sqlStr.toString());

            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    public List getTransferSuccessRate(String beginDate, String endDate,
                                       String statType) throws HibernateException {
        String execSQL = "";
        Session session = openSession();
        try {
            if (("bydate".equals(statType) || ("byweek".equals(statType)))) {
                execSQL = "TransferSuccessRateSQL_ORACLE";
            } else if ("bymonth".equals(statType)) {
                execSQL = "TransferSuccessRateMonthSQL_ORACLE";
            }
            Query query = session.getNamedQuery(execSQL);
            query.setString("begindate", beginDate);
            query.setString("enddate", endDate);
            List list = query.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * Method name:getDeviceUsed Description:根据日期取得设备的使用数 Return: List
     *
     * @param serialtype
     * @param beginDate
     * @param endDate
     * @param statType
     *
     * @return
     *
     * @throws HibernateException
     */
    public List getDeviceUsed(int serialtype, String beginDate, String endDate,
                              String statType) throws HibernateException {
        Session s = openSession();
        String nowDate = com.kingstargroup.ecard.util.DateUtilExtend
                .getNowDate2();
        StringBuffer sqlStr = new StringBuffer();
        if ("bydate".equals(statType)) {
            sqlStr
                    .append(
                            "select dtl.transdate balance_date,count(distinct dtl.devphyid)devuse ")
                    .append("from ykt_cur.t_posdtl dtl ")
                    .append("where dtl.transcode=")
                    .append(serialtype)
                    .append(" and dtl.transdate>='")
                    .append(beginDate)
                    .append("' and dtl.transdate<='")
                    .append(endDate)
                    .append(
                            "' group by dtl.transdate order by dtl.transdate desc");
        } else if ("bymonth".equals(statType)) {
            sqlStr
                    .append(
                            "select substr(dtl.transdate,1,6) balance_date,count(distinct dtl.devphyid)devuse ")
                    .append("from ykt_cur.t_posdtl dtl ")
                    .append("where dtl.transcode=")
                    .append(serialtype)
                    .append(" and substr(dtl.transdate,1,6)>='")
                    .append(beginDate)
                    .append("' and substr(dtl.transdate,1,6)<='")
                    .append(endDate)
                    .append(
                            "' group by substr(dtl.transdate,1,6) order by substr(dtl.transdate,1,6) desc");
        }
        try {
            //System.out.println(sqlStr.toString());
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("balance_date", Hibernate.STRING);
            q.addScalar("devuse", Hibernate.INTEGER);
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    /**
     * Method name:getDeviceNum Description: 取得设备总数 Return: String
     *
     * @param devType
     *
     * @return
     *
     * @throws HibernateException
     */
    public String getDeviceNum(String devType) throws HibernateException {
        Session s = openSession();
        StringBuffer sqlStr = new StringBuffer();
        sqlStr.append("Select count(*) as devnum from YKT_CUR.V_DEVICE ")
                .append(" where devtypecode in " + devType + " and status=1");
        try {
            //System.out.println("devNum:" + sqlStr.toString());
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("devnum", Hibernate.INTEGER);
            return q.list().get(0).toString();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    /**
     * 得到照片信息人员类别列表
     */
    public List getEmpType() {
        Session session = openSession();
        try {
            SQLQuery sqlquery = session
                    .createSQLQuery("select * from ykt_cur.t_custtype cust order by cust.custtype");
            sqlquery.addEntity(TCusttype.class);
            List list = sqlquery.list();
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 得到部门信息
     */
    public List getDeptList() {
        Session session = openSession();
        StringBuffer sqlStr = new StringBuffer();
        sqlStr.append("from TDept");
        try {
            Query sqlquery = session.createQuery(sqlStr.toString());
            List list = sqlquery.list();
            Comparator comp1 = new Comparator() {
                public int compare(Object o1, Object o2) {
                    TDept m1 = (TDept) o1;
                    TDept m2 = (TDept) o2;
                    Collator col = Collator.getInstance(Locale.CHINA);
                    String deptName1 = (String) m1.getDeptname();
                    String deptName2 = (String) m2.getDeptname();
                    CollationKey c1 = col.getCollationKey(deptName1);
                    CollationKey c2 = col.getCollationKey(deptName2);
                    return c1.compareTo(c2);
                }
            };
            Collections.sort(list, comp1);
            return list;
        } catch (Exception e) {
            e.printStackTrace();
            _log.error(e);
            return null;
        }
    }

    /**
     * 得到专业信息
     *
     * @return
     */
    public List getSpecialityList() {
        Session session = openSession();
        try {
            Query sqlquery = session.createQuery("from TSpecialty");
            List list = sqlquery.list();
            Comparator comp1 = new Comparator() {
                public int compare(Object o1, Object o2) {
                    TSpecialty m1 = (TSpecialty) o1;
                    TSpecialty m2 = (TSpecialty) o2;
                    Collator col = Collator.getInstance(Locale.CHINA);
                    String specialtyname1 = (String) m1.getSpecialtyname();
                    String specialtyname2 = (String) m2.getSpecialtyname();
                    CollationKey c1 = col.getCollationKey(specialtyname1);
                    CollationKey c2 = col.getCollationKey(specialtyname2);
                    return c1.compareTo(c2);
                }
            };
            Collections.sort(list, comp1);
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 得到客户类别信息
     *
     * @return
     */
    public List getCusttypeList() throws HibernateException {
        Session s = openSession();
        try {
            Query q = s.createQuery(" from TCusttype ");
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    /**
     * 得到收费类别信息
     *
     * @return
     */
    public List getFeeTypeList() {
        Session session = openSession();
        try {
            Query q = session.createQuery(" from TFeetype ");
            List list = q.list();
            Comparator comp1 = new Comparator() {
                public int compare(Object o1, Object o2) {
                    TFeetype m1 = (TFeetype) o1;
                    TFeetype m2 = (TFeetype) o2;
                    Collator col = Collator.getInstance(Locale.CHINA);
                    String Feename1 = (String) m1.getFeename();
                    String Feename2 = (String) m2.getFeename();
                    CollationKey c1 = col.getCollationKey(Feename1);
                    CollationKey c2 = col.getCollationKey(Feename2);
                    return c1.compareTo(c2);
                }
            };
            Collections.sort(list, comp1);
            return list;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /*
      * 查找语句 select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,
      * fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no,
      * dept.dept_name,cust.s_code,spec.s_name,cust.class_no,
      * rc.card_no,rc.meal,count(rc.amount)amcount,sum(rc.amount)amsum,
      * sum(rc.amount)/count(rc.amount) avg from t_rcstatdata rc left join
      * t_pif_card card on rc.card_no=card.card_id left join t_cif_customer cust
      * on card.cosumer_id=cust.cut_id left join t_cif_cuttypefee ctype on
      * cust.cut_type=ctype.cut_type left join t_pif_feetype fee on cust.fee_type
      * = fee.fee_type left join t_cif_dept dept on cust.classdept_no =
      * dept.dept_code left join t_cif_speciality spec on cust.s_code =
      * spec.s_code group by
      * rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,
      * cust.fee_type,fee.fee_name,
      * cust.cut_name,cust.stuemp_no,cust.classdept_no
      * ,dept.dept_name,cust.s_code, spec.s_name,cust.class_no,rc.meal order by
      * avg,meal desc 过滤结果集，把消费次数小于规定的消费次数的人员去掉。amcount<次数
      */
    /*
      * 贫困生查找，参数： 开始日期，结束日期，院系，专业，班级，客户类别，收费类别，开始学号，结束学号，消费频度
      */
    public List getSpecialList(String bDate, String eDate, String deptNo,
                               String specNo, String classNo, int custType, int feeType,
                               String bStuempNo, String eStuempNo, int per, String meal,
                               float bavgRange, float eavgRange, String selPer, int perRange) {
        StringBuffer strSql = new StringBuffer(1024);
        strSql
                .append(
                        "select cust.custid cut_id,cust.custtype cut_type,ctype.custtypename type_name,cust.feetype fee_type,")
                .append(
                        " fee.feename fee_name,cust.custname cut_name,cust.stuempno stuemp_no,cust.DEPTCODE classdept_no,")
                .append(
                        " dept.deptname dept_name,cust.SPECIALTYCODE s_code,spec.SPECIALTYNAME s_name,cust.CLASSCODE class_no,");
        if (!"".equals(meal)) {
            strSql.append(" rc.meal,");
        }
        strSql
                .append(
                        " rc.card_no,count(rc.amount)amcount,(sum(rc.amount))amsum,")
                .append(" ((sum(rc.amount)/count(rc.amount))) avg")
                .append(" from ykt_portal.t_rcstatdata rc ")
                .append(
                        " left join ykt_cur.t_card card on rc.card_no=card.cardno")
                .append(
                        " left join ykt_cur.t_customer cust on card.custid=cust.custid")
                .append(
                        " left join ykt_cur.t_custtype ctype on cust.custtype=ctype.custtype")
                .append(
                        " left join ykt_cur.t_feetype fee on cust.feetype = fee.feetype")
                .append(
                        " left join ykt_cur.t_dept dept on cust.deptcode = dept.deptcode")
                .append(
                        " left join ykt_cur.t_specialty spec on cust.SPECIALTYCODE = spec.SPECIALTYCODE")
                .append(" where rc.tx_date>='").append(bDate).append(
                "' and rc.tx_date<='").append(eDate).append("'");
        // .append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and rc.tx_date<=:qeDate");
        // 添加分析条件
        if (!"".equals(meal)) {
            strSql.append(" and rc.meal='").append(meal).append("'");
        }
        if (!"".equals(deptNo)) {
            strSql.append(" and cust.deptcode='").append(deptNo).append("'");
        }
        if (!"".equals(specNo)) {
            strSql.append(" and cust.SPECIALTYCODE='").append(specNo).append(
                    "'");
        }
        if (!"".equals(classNo)) {
            strSql.append(" and cust.classcode='").append(classNo).append("'");
        }
        if (custType > 0) {
            strSql.append(" and cust.custtype=").append(custType);
        }
        if (feeType > 0) {
            strSql.append(" and cust.feetype=").append(feeType);
        }
        if (!"".equals(bStuempNo)) {
            strSql.append(" and cust.stuempno>='").append(bStuempNo)
                    .append("'");
        }
        if (!"".equals(eStuempNo)) {
            strSql.append(" and cust.stuempno<='").append(eStuempNo)
                    .append("'");
        }

        strSql
                .append(
                        " group by rc.card_no,cust.custid,cust.custtype,ctype.custtypename,cust.feetype,fee.feename,")
                .append(
                        " cust.custname,cust.stuempno,cust.deptcode,dept.deptname,cust.SPECIALTYCODE,")
                .append(" spec.SPECIALTYNAME,cust.classcode");
        if (!"".equals(meal)) {
            strSql.append(",rc.meal having count(rc.amount)>=").append(per);
        } else {
            strSql.append(" having count(rc.amount)>=").append(per * 3);
        }
        strSql.append(" order by avg");
        //System.out.println(strSql.toString());
        Session session = openSession();
        try {
            SQLQuery query = session.createSQLQuery(strSql.toString());
            query.addScalar("cut_id", Hibernate.INTEGER);
            query.addScalar("cut_type", Hibernate.INTEGER);
            query.addScalar("type_name", Hibernate.STRING);
            query.addScalar("fee_type", Hibernate.INTEGER);
            query.addScalar("fee_name", Hibernate.STRING);
            query.addScalar("cut_name", Hibernate.STRING);
            query.addScalar("stuemp_no", Hibernate.STRING);
            query.addScalar("classdept_no", Hibernate.STRING);
            query.addScalar("dept_name", Hibernate.STRING);
            query.addScalar("s_code", Hibernate.STRING);
            query.addScalar("s_name", Hibernate.STRING);
            query.addScalar("class_no", Hibernate.STRING);
            query.addScalar("card_no", Hibernate.INTEGER);
            query.addScalar("amcount", Hibernate.INTEGER);
            query.addScalar("amsum", Hibernate.INTEGER);
            query.addScalar("avg", Hibernate.FLOAT);
            if (!"".equals(meal)) {
                query.addScalar("meal", Hibernate.STRING);
            }
            List list = query.list();
            float avgValue = 0;
            if (!"".equals(selPer)) {
                Map avgMap = (Map) getSpecStat(meal).get(0);
                avgValue = Float.parseFloat(avgMap.get("totavg").toString());
                /*
                     * System.out.println("avgValue"+avgMap.get("totavg").toString())
                     * ;
                     */
            }
            List result = new ArrayList();
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);

                if ((bavgRange > 0) && (eavgRange > 0)) {
                    if ((Float.parseFloat(objects[15].toString()) < bavgRange)
                            || (Float.parseFloat(objects[15].toString()) > eavgRange)) {
                        continue;
                    }
                }

                if (!"".equals(selPer)) {
                    // 比较值
                    float compValue = 0;
                    if ("up".equals(selPer)) {
                        compValue = avgValue * perRange / 100 + avgValue;
                        if (compValue > Float
                                .parseFloat(objects[15].toString())) {
                            continue;
                        }
                    }
                    if ("down".equals(selPer)) {
                        compValue = avgValue - avgValue * perRange / 100;
                        if (compValue < Float
                                .parseFloat(objects[15].toString())) {
                            continue;
                        }
                    }

                }
                HashMap accMap = new HashMap();
                accMap.put("cut_id", objects[0]);
                accMap.put("cut_type", objects[1]);
                accMap.put("type_name", objects[2]);
                accMap.put("fee_type", objects[3]);
                accMap.put("fee_name", objects[4]);
                accMap.put("cut_name", objects[5]);
                accMap.put("stuemp_no", objects[6]);
                accMap.put("classdept_no", objects[7]);
                accMap.put("dept_name", objects[8]);
                accMap.put("s_code", objects[9]);
                accMap.put("s_name", objects[10]);
                accMap.put("class_no", objects[11]);
                accMap.put("card_no", objects[12]);
                accMap.put("amcount", objects[13]);
                accMap.put("amsum", objects[14]);
                accMap.put("avg", objects[15]);
                if (!"".equals(meal)) {
                    accMap.put("meal", mealTrans(objects[16].toString()));
                } else {
                    accMap.put("meal", "全天");
                }

                result.add(accMap);
            }
            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    /**
     * 按年取得总体平均消费金额，男生平均和女士平均
     *
     * @return
     */
    private List getSpecStat(String meal) {
        StringBuffer strSql = new StringBuffer(1024);
        strSql
                .append(
                        "select c.accyear,(a.femaleavg)femaleavg,(b.maleavg)maleavg,(c.totavg)totavg from")
                .append(" (select accyear,sum(amount)/count(*) femaleavg from")
                .append(
                        " (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
                .append(" from ykt_portal.t_rcstatdata rc")
                .append(
                        " left join ykt_cur.t_card card on rc.card_no=card.cardno")
                .append(
                        " left join ykt_cur.t_customer cust on card.custid=cust.custid")
                .append(" where cust.sex='1'");
        if (!"".equals(meal)) {
            strSql.append("and rc.meal='").append(meal).append("'");
        }
        strSql
                .append(") group by accyear)a,")

                .append(" (select accyear,sum(amount)/count(*) maleavg from")
                .append(
                        " (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
                .append(" from ykt_portal.t_rcstatdata rc")
                .append(
                        " left join ykt_cur.t_card card on rc.card_no=card.cardno")
                .append(
                        " left join ykt_cur.t_customer cust on card.custid=cust.custid")
                .append(" where cust.sex='2'");
        if (!"".equals(meal)) {
            strSql.append("and rc.meal='").append(meal).append("'");
        }
        strSql.append(") group by accyear)b,")

                .append(" (select accyear,sum(amount)/count(*) totavg from").append(
                " (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
                .append(" from ykt_portal.t_rcstatdata rc");

        if (!"".equals(meal)) {
            strSql.append(" where rc.meal='").append(meal).append("'");
        }
        strSql.append(") group by accyear)c")

                .append(" where c.accyear=b.accyear(+) and c.accyear=a.accyear(+)")
                .append(" order by c.accyear desc");
        //System.out.println(strSql);
        Session session = openSession();
        try {
            SQLQuery query = session.createSQLQuery(strSql.toString());
            query.addScalar("accyear", Hibernate.STRING);
            query.addScalar("femaleavg", Hibernate.FLOAT);
            query.addScalar("maleavg", Hibernate.FLOAT);
            query.addScalar("totavg", Hibernate.FLOAT);
            List list = query.list();
            List result = new ArrayList();
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);
                HashMap accMap = new HashMap();
                accMap.put("accyear", objects[0]);
                accMap.put("femaleavg", nullToString(objects[1]));
                accMap.put("maleavg", nullToString(objects[2]));
                accMap.put("totavg", nullToString(objects[3]));
                result.add(accMap);
            }
            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    private String mealTrans(String in) {
        if ("bk".equals(in.trim())) {
            return "早餐";
        } else if ("lun".equals(in.trim())) {
            return "午餐";
        } else if ("sup".equals(in.trim())) {
            return "晚餐";
        } else {
            return "全天";
        }
    }

    private String nullToString(Object o) {
        if ((o == null)) {
            return "0";
        } else if ("".equals(o.toString())) {
            return "0";
        } else {
            return o.toString();
        }
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
        StringBuffer strSql = new StringBuffer(1024);
        StringBuffer wheresql2 = new StringBuffer(1024);
        StringBuffer wheresql1 = new StringBuffer(1024);

        if (!"".equals(bDate)) {
            wheresql1.append(" and rc.tx_date >='").append(bDate).append("'");
        }
        if (!"".equals(eDate)) {
            wheresql1.append(" and  rc.tx_date <='").append(eDate).append("'");
        }
        if (!"".equals(meal)) {
            wheresql1.append(" and rc.meal='").append(meal).append("'");
        }

        if (!"".equals(deptNo)) {
            wheresql2.append(" and cust.deptcode='").append(deptNo).append("'");
        }
        if (!"".equals(specNo)) {
            wheresql2.append(" and cust.SPECIALTYCODE='").append(specNo)
                    .append("'");
        }
        if (!"".equals(classNo)) {
            wheresql2.append(" and cust.classcode='").append(classNo).append(
                    "'");
        }
        if (custType > 0) {
            wheresql2.append(" and cust.custtype=").append(custType);
        }
        if (feeType > 0) {
            wheresql2.append(" and cust.feetype=").append(feeType);
        }
        if (!"".equals(bStuempNo)) {
            wheresql2.append(" and cust.stuempno>='").append(bStuempNo).append(
                    "'");
        }
        if (!"".equals(eStuempNo)) {
            wheresql2.append(" and cust.stuempno<='").append(eStuempNo).append(
                    "'");
        }
        wheresql2.append(" ) group by cut_name  ");
        if (!"".equals(meal)) {
            wheresql2.append(" having count(*) >=").append(per);
        } else {
            wheresql2.append(" having count(*) >=").append(per * 3);
        }

        strSql
                .append(
                        " select (a.femaleavg)femaleavg,(b.maleavg)maleavg,(c.totavg)totavg ")
                .append(" from (select NVL(sum(amount)/sum(num),0) femaleavg ")
                .append(
                        " from ( select sum(amount) amount ,count(*) num, cut_name  ")
                .append(
                        " from ( select  rc.meal,rc.amount,cust.custname cut_name  ")
                .append(
                        " from ykt_portal.t_rcstatdata rc inner join ykt_cur.t_card card on rc.card_no=card.cardno  ")

                .append(wheresql1)
                .append(
                        " inner join ykt_cur.t_customer cust on card.custid=cust.custid  ")
                .append(
                        " inner join ykt_cur.t_custtype ctype on cust.custtype=ctype.custtype ")
                .append(
                        " inner join ykt_cur.t_feetype fee on cust.feetype = fee.feetype ")
                .append(
                        " inner join ykt_cur.t_dept dept on cust.deptcode = dept.deptcode ")
                .append(
                        " left join ykt_cur.t_specialty spec on cust.SPECIALTYCODE = spec.SPECIALTYCODE  where cust.sex='1' ")
                .append(wheresql2)
                .append(" ))a,  ")
                .append(" (select NVL(sum(amount)/sum(num),0) maleavg ")
                .append(
                        " from ( select sum(amount) amount ,count(*) num, cut_name  ")
                .append(
                        " from ( select  rc.meal,rc.amount,cust.custname cut_name  ")
                .append(
                        " from ykt_portal.t_rcstatdata rc inner join ykt_cur.t_card card on rc.card_no=card.cardno  ")
                .append(wheresql1)
                .append(
                        " inner join ykt_cur.t_customer cust on card.custid=cust.custid  ")
                .append(
                        " inner join ykt_cur.t_custtype ctype on cust.custtype=ctype.custtype ")
                .append(
                        " inner join ykt_cur.t_feetype fee on cust.feetype = fee.feetype ")
                .append(
                        " inner join ykt_cur.t_dept dept on cust.deptcode = dept.deptcode ")
                .append(
                        " left join ykt_cur.t_specialty spec on cust.SPECIALTYCODE = spec.SPECIALTYCODE  where cust.sex='2' ")
                .append(wheresql2)
                .append(" ))b, ")

                .append(" (select NVL(sum(amount)/sum(num),0) totavg ")
                .append(
                        " from ( select sum(amount) amount ,count(*) num, cut_name  ")
                .append(
                        " from ( select  rc.meal,rc.amount,cust.custname cut_name  ")
                .append(
                        " from ykt_portal.t_rcstatdata rc  inner join ykt_cur.t_card card on rc.card_no=card.cardno ")
                .append(wheresql1)
                .append(
                        " inner join ykt_cur.t_customer cust on card.custid=cust.custid  ")
                .append(
                        " inner join ykt_cur.t_custtype ctype on cust.custtype=ctype.custtype ")
                .append(
                        " inner join ykt_cur.t_feetype fee on cust.feetype = fee.feetype ")
                .append(
                        " inner join ykt_cur.t_dept dept on cust.deptcode = dept.deptcode ")
                .append(
                        " left join ykt_cur.t_specialty spec on cust.SPECIALTYCODE = spec.SPECIALTYCODE where cust.sex in ('1','2')")
                .append(wheresql2).append("))c ");

        Session session = openSession();
        try {
            //System.out.println(strSql.toString());
            SQLQuery query = session.createSQLQuery(strSql.toString());

            query.addScalar("femaleavg", Hibernate.FLOAT);
            query.addScalar("maleavg", Hibernate.FLOAT);
            query.addScalar("totavg", Hibernate.FLOAT);
            List list = query.list();
            List result = new ArrayList();
            float avgValue = 0;
            if (!"".equals(selPer)) {
                Map avgMap = (Map) getSpecStat(meal).get(0);
                avgValue = Float.parseFloat(avgMap.get("totavg").toString());

            }
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);
//
//				if ((bavgRange > 0)&&(eavgRange>0)) {
//					if ((Float.parseFloat(objects[2].toString()) < bavgRange)
//							|| (Float.parseFloat(objects[2].toString()) > eavgRange)) {
//						continue;
//					}
//				}
//				if (!"".equals(selPer)) {
//					// 比较值
//					float compValue = 0;
//					if ("up".equals(selPer)) {
//						compValue = avgValue * perRange / 100 + avgValue;
//						if (compValue > Float.parseFloat(objects[2].toString())) {
//							continue;
//						}
//					}
//					if ("down".equals(selPer)) {
//						compValue = avgValue - avgValue * perRange / 100;
//						if (compValue < Float.parseFloat(objects[2].toString())) {
//							continue;
//						}
//					}
//				}
                HashMap accMap = new HashMap();
                accMap.put("acctime", bDate + "-" + eDate);
                accMap.put("femaleavg", nullToString(objects[0]));
                accMap.put("maleavg", nullToString(objects[1]));
                accMap.put("totavg", nullToString(objects[2]));
                result.add(accMap);
            }

            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    // 平均消费金额，人数分布图
    public List getConsemeAvg(String bDate, String eDate, String deptNo,
                              String specNo, String classNo, int custType, int feeType,
                              String bStuempNo, String eStuempNo, int per, String meal,
                              float bavgRange, float eavgRange, String selPer, int perRange) {
        StringBuffer strSql = new StringBuffer(1024);

        strSql
                .append(" select count(cut_id) num,round(avg,0) amavg from ( ")
                .append(
                        " select cust.custid cut_id, count(rc.amount) amcount ,")

                .append(" ((sum(rc.amount)/count(rc.amount))) avg")
                .append(" from ykt_portal.t_rcstatdata rc ")
                .append(
                        " inner join ykt_cur.t_card card on rc.card_no=card.cardno")
                .append(
                        " inner join ykt_cur.t_customer cust on card.custid=cust.custid")
                .append(
                        " inner join ykt_cur.t_custtype ctype on cust.custtype=ctype.custtype")
                .append(
                        " inner join ykt_cur.t_feetype fee on cust.feetype = fee.feetype")
                .append(
                        " inner join ykt_cur.t_dept dept on cust.deptcode = dept.deptcode")
                .append(
                        " left join ykt_cur.t_specialty spec on cust.SPECIALTYCODE = spec.SPECIALTYCODE")
                .append(" where rc.tx_date>='").append(bDate).append(
                "' and rc.tx_date<='").append(eDate).append("'");
        // .append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and
        // rc.tx_date<=:qeDate");
        // 添加分析条件
        if (!"".equals(meal)) {
            strSql.append(" and rc.meal='").append(meal).append("'");
        }
        if (!"".equals(deptNo)) {
            strSql.append(" and cust.deptcode='").append(deptNo).append("'");
        }
        if (!"".equals(specNo)) {
            strSql.append(" and cust.SPECIALTYCODE='").append(specNo).append(
                    "'");
        }
        if (!"".equals(classNo)) {
            strSql.append(" and cust.classcode='").append(classNo).append("'");
        }
        if (custType > 0) {
            strSql.append(" and cust.custtype=").append(custType);
        }
        if (feeType > 0) {
            strSql.append(" and cust.feetype=").append(feeType);
        }
        if (!"".equals(bStuempNo)) {
            strSql.append(" and cust.stuempno>='").append(bStuempNo)
                    .append("'");
        }
        if (!"".equals(eStuempNo)) {
            strSql.append(" and cust.stuempno<='").append(eStuempNo)
                    .append("'");
        }

        strSql.append(" group by cust.custid,").append(" cust.custname")
                .append(" ");
        if (!"".equals(meal)) {
            strSql.append(",rc.meal");
        }
        if ("".equals(meal)) {
            per = per * 3;
        }
        strSql.append(" having count(rc.amount) >=").append(per)

                .append(" ) w group by round(avg,0) ").append(
                "   order by round(avg,0) ");

        Session session = openSession();
        try {
            //System.out.println(strSql.toString());
            SQLQuery query = session.createSQLQuery(strSql.toString());
            query.addScalar("num", Hibernate.INTEGER);
            query.addScalar("amavg", Hibernate.FLOAT);
            List list = query.list();
            List result = new ArrayList();
            float avgValue = 0;
            if (!"".equals(selPer)) {
                Map avgMap = (Map) getSpecStat(meal).get(0);
                avgValue = Float.parseFloat(avgMap.get("totavg").toString());

            }
            for (int i = 0; i < list.size(); i++) {
                Object[] objects = (Object[]) list.get(i);

                if ((bavgRange > 0) && (eavgRange > 0)) {
                    if ((Float.parseFloat(objects[1].toString()) < bavgRange)
                            || (Float.parseFloat(objects[1].toString()) > eavgRange)) {
                        continue;
                    }
                }

                if (!"".equals(selPer)) {
                    // 比较值
                    float compValue = 0;
                    if ("up".equals(selPer)) {
                        compValue = avgValue * perRange / 100 + avgValue;
                        if (compValue > Float.parseFloat(objects[1].toString())) {
                            continue;
                        }
                    }
                    if ("down".equals(selPer)) {
                        compValue = avgValue - avgValue * perRange / 100;
                        if (compValue < Float.parseFloat(objects[1].toString())) {
                            continue;
                        }
                    }

                }

                HashMap accMap = new HashMap();
                accMap.put("num", objects[0]);
                accMap.put("amavg", objects[1]);
                result.add(accMap);
            }
            return result;
        } catch (HibernateException e) {
            _log.error(e);
            return null;
        }
    }

    private static final Log _log = LogFactory
            .getLog(AdvqueryPersistence.class);
}
