package com.kingstargroup.advquery.hibernate.dao;
 
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.dao.BasicDAO;
import com.kingstargroup.advquery.lunch.TCifCosumerLunch;
import com.kingstargroup.advquery.util.Utility;

public class LunchDAO extends BasicDAO {

    private static LunchDAO _instance;

    /**
     * Description:singleton pattern
     *   
     * @return Modify History:
     */     
    public static LunchDAO getInstance() {  
        if (_instance == null) {  
            _instance = new LunchDAO();
        }
        return _instance;
    }  
    
    public boolean delePerson(TCifCosumerLunch lunch)throws HibernateException {
    	 try {
                 Session s = getSession();
            	 lunch.setState(new Integer(3));
            	 s.update(lunch);
            	 s.flush();
             return true;
          } catch (HibernateException e) {
             return false;
         }
    	
    }

    public boolean saveLunch(Map tempMap,String lunchtype) throws HibernateException {
        try {
            Session s = getSession();
            TCifCosumerLunch lun = new TCifCosumerLunch();
            lun.setCutId((Integer) tempMap.get("cutId"));
            lun.setCutName((String) tempMap.get("cutName"));
            lun.setCardId((Integer) tempMap.get("cardId"));
            lun.setCutState((Integer) tempMap.get("cutState"));
            lun.setCutType((Integer) tempMap.get("cutType"));
            lun.setManId((String) tempMap.get("manId"));
            lun.setPhyId((String) tempMap.get("physicalNo"));
            lun.setSex((String) tempMap.get("sex"));
            lun.setStuempNo((String) tempMap.get("stuempNo"));
            lun.setState(new Integer(1));
            lun.setLunchType(Integer.valueOf(lunchtype));
            s.save(lun);
            s.flush();
            return true;
        } catch (HibernateException e) {
            return false;
        }
    }

    public boolean delLunch(TCifCosumerLunch lun) throws HibernateException {
        try {
            Session s = getSession();
            lun.setState(new Integer(3));
            s.saveOrUpdate(lun);
            s.flush();
            return true;
        } catch (HibernateException e) {
            return false;
        }
    }
    
    public boolean updateLunch(TCifCosumerLunch lun) throws HibernateException {
    	try {
            Session s = getSession();
            s.saveOrUpdate(lun);
            s.flush();
            return true;
        } catch (HibernateException e) {
            return false;
        }
    }
    
    public List getLunchTotal(String beginDate, String endDate, String tradedept,String lunchtype) throws HibernateException {
        Session s = getSession();
        StringBuffer sqlStr = new StringBuffer();
    
        String[] dept = tradedept.split(",");  
        sqlStr.append(" select dept_name,stuemp_no,cut_name,type_name,cosumer_id,lunch_type, count(*) as total from   ");
        sqlStr.append(" (select a5.*,a6.dept_name,a7.type_name,a9.lunch_type from ");
        sqlStr.append(" (select a3.*,a4.cut_name,a4.stuemp_no,a4.cut_type,a4.classdept_no  from ");
        sqlStr.append(" (select a1.tx_date, a1.card_no, a2.cosumer_id ");
        sqlStr.append(" from t_tif_lunchrcvdtl a1 left join t_pif_card a2 on a1.card_no=a2.card_id  where a1.rowid in (select max(rowid) from t_tif_lunchrcvdtl where 1=1");
        if (!Utility.isEmpty(beginDate)) {
            sqlStr.append(" and tx_date >= '" + beginDate + "'");
        } 
        if (!Utility.isEmpty(endDate)) {
            sqlStr.append(" and tx_date <='" + endDate + "'");
        }
        sqlStr.append(" group by tx_date,card_no)");
        if (!Utility.isEmpty(beginDate)) {
            sqlStr.append(" and a1.tx_date >= '" + beginDate + "'");
        } 
        if (!Utility.isEmpty(endDate)) {
            sqlStr.append(" and a1.tx_date <='" + endDate + "'");
        }
        sqlStr.append(" ) a3  ");
        sqlStr.append(" left join t_cif_customer a4 on a3.cosumer_id=a4.cut_id) a5 " );
        sqlStr.append(" inner join   t_cif_cosumer_lunch a9  on  a5.cosumer_id =a9.cut_id ") ;   
        sqlStr.append(" left join t_cif_dept a6 on a6.dept_code=a5.classdept_no ");
        sqlStr.append(" left join t_cif_cuttypefee a7 on a7.cut_type=a5.cut_type) a8  where 1=1 ");

        if (dept.length > 0 && !"".equals(dept[0])) {
            sqlStr.append(" and ( ");
            for (int i = 0; i < dept.length; i++) {
                if (i != dept.length - 1) {
                    sqlStr.append(" dept_name like '%" + dept[i].toUpperCase() + "%' or ");
                } else {
                    sqlStr.append(" dept_name like '%" + dept[i].toUpperCase() + "%' ) ");
                }
            } 
        }
        if (!Utility.isEmpty(lunchtype)) {
        	 sqlStr.append(" and lunch_type ="+ lunchtype);
        }
        if (!Utility.isEmpty(beginDate)) {
            sqlStr.append(" and tx_date >= '" + beginDate + "'");
        } 
        if (!Utility.isEmpty(endDate)) {
            sqlStr.append(" and tx_date <='" + endDate + "'");
        }
        sqlStr.append(" group by cosumer_id,dept_name,stuemp_no,cut_name,type_name,lunch_type ");
       // System.out.println(sqlStr);
        try {
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("dept_name", Hibernate.STRING);
            q.addScalar("stuemp_no", Hibernate.STRING);
            q.addScalar("cut_name", Hibernate.STRING);
            q.addScalar("type_name", Hibernate.STRING);
            q.addScalar("cosumer_id", Hibernate.STRING);
            q.addScalar("lunch_type", Hibernate.STRING);
            q.addScalar("total", Hibernate.STRING);
            
            _log.debug(q.getQueryString());
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }


    public TCifCosumerLunch finLunch(Integer cutId) throws HibernateException {
        Session s = getSession();
        Query q = s.createQuery(" from TCifCosumerLunch t where  t.cutId=" + cutId);
        List list = q.list();
        if (list != null && list.size() > 0) {
            return (TCifCosumerLunch) list.get(0);
        }
        return null;
    }

   

    public List getLunch(String stuempno, String beginDate, String endDate, String tradedept,String lunchtype) throws HibernateException {
        Session s = getSession();
        StringBuffer sqlStr = new StringBuffer();

        String[] dept = tradedept.split(",");

        sqlStr.append(" select a.*,b.dept_name ,lun.lunch_type  from (select T_TIF_LUNCHRCVDTL.*,t_cif_customer.stuemp_no,t_cif_customer.cut_name,t_cif_customer.classdept_no , t_cif_customer.cut_id from T_TIF_LUNCHRCVDTL " )
        	  .append(" left join (select t_cif_customer.*,t_pif_card.card_id from t_pif_card left join t_cif_customer on t_pif_card.cosumer_id=t_cif_customer.cut_id) t_cif_customer on T_TIF_LUNCHRCVDTL.card_no =t_cif_customer.card_id)" )
        	  .append(" a left join t_cif_dept b on a.classdept_no=b.dept_code " )
        	  .append(" left join t_cif_cosumer_lunch lun  on a.cut_id = lun.cut_id ")
              .append(" where 1=1  ");
        
        if (!Utility.isEmpty(lunchtype)) {
            sqlStr.append(" and lun.lunch_type=" + lunchtype );
        }
        if (!Utility.isEmpty(stuempno)) {
            sqlStr.append(" and stuemp_no='" + stuempno.toUpperCase() + "'");
        }
        if (dept.length > 0 && !"".equals(dept[0])) {
            sqlStr.append(" and ( ");
            for (int i = 0; i < dept.length; i++) {
                if (i != dept.length - 1) {
                    sqlStr.append(" dept_name like '%" + dept[i].toUpperCase() + "%' or ");
                } else {
                    sqlStr.append(" dept_name like '%" + dept[i].toUpperCase() + "%' ) ");
                }
            }
        }
        if (!Utility.isEmpty(beginDate)) {
            sqlStr.append(" and tx_date >= '" + beginDate + "'");
        }
        if (!Utility.isEmpty(endDate)) {
            sqlStr.append(" and tx_date <='" + endDate + "'");
        }

        sqlStr.append(" order by COL_TIMESTAMP desc");
        try {
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("tx_date", Hibernate.STRING);
            q.addScalar("tx_time", Hibernate.STRING);
            q.addScalar("card_no", Hibernate.STRING);
            q.addScalar("cut_name", Hibernate.STRING);
            q.addScalar("device_id", Hibernate.STRING);
            q.addScalar("COL_TIMESTAMP", Hibernate.STRING);
            q.addScalar("stuemp_no", Hibernate.STRING);
            q.addScalar("dept_name", Hibernate.STRING);
            q.addScalar("lunch_type", Hibernate.STRING);
            _log.debug(q.getQueryString());
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }

    public List getLunchPerson(String stuempno, String tradedept,String lunchtype) {
        Session s = getSession();
        StringBuffer sqlStr = new StringBuffer();

        String[] dept = tradedept.split(",");

        sqlStr.append(" select a.CUT_NAME as cut_name ,a.PHY_ID  as phy_ID,a.STUEMP_NO as stuemp_no ,	state ,  d.dept_name  as dept_name ,a.cut_id as cut_id , a.lunch_type from T_CIF_COSUMER_LUNCH a " +
                " left join t_cif_customer c on c.cut_id=a.CUT_ID " +
        		" left  join t_cif_dept  d on c.classdept_no=d.dept_code "	 );
                
        sqlStr.append(" where state <>3  ");
        if (!Utility.isEmpty(stuempno)) {
            sqlStr.append(" and a.stuemp_no='" + stuempno.toUpperCase() + "'");
        }
        if (!Utility.isEmpty(lunchtype)) {
            sqlStr.append(" and a.lunch_type=" + lunchtype);
        }
        if (dept.length > 0 && !"".equals(dept[0])) {
            sqlStr.append(" and ( ");
            for (int i = 0; i < dept.length; i++) {
                if (i != dept.length - 1) {
                    sqlStr.append(" d.dept_name like '%" + dept[i].toUpperCase() + "%' or ");
                } else {
                    sqlStr.append(" d.dept_name like '%" + dept[i].toUpperCase() + "%' ) ");
                }
            }
        }

        sqlStr.append(" order by dept_name desc");
        try {
            SQLQuery q = s.createSQLQuery(sqlStr.toString());
            q.addScalar("cut_name", Hibernate.STRING);
            q.addScalar("phy_ID", Hibernate.STRING);
            q.addScalar("stuemp_no", Hibernate.STRING);
            q.addScalar("state", Hibernate.STRING);
            q.addScalar("dept_name", Hibernate.STRING);
            q.addScalar("cut_id",  Hibernate.STRING);
            q.addScalar("lunch_type",  Hibernate.STRING);
            _log.debug(q.getQueryString());
            return q.list();
        } catch (HibernateException he) {
            _log.error(he);
            return null;
        }
    }
    
    private Log _log = LogFactory.getLog(LunchDAO.class.getClass());
}
