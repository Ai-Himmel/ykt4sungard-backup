
    /**
     * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
     * File name: .java<br>
     * Description: AccountUtil个人消费明细<br>
     * Return: List<br>
     * Modify History: <br>
     * 操作类型    操作人     操作时间       操作内容<br>
     * ======================================<br>
     * 创建      韩纪伟     2006-5-15  <br>
     *
     * @author 韩纪伟
     * @version
     * @since 1.0
     */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.AccountDAO;

public class AccountUtil extends BasicUtil {

    public static List getHandTrade(String stuempno,String beginDate, String endDate, String tradedevice, String tradecard, String tradelogno) {

        //todo
        AccountDAO dao = AccountDAO.getInstance();
        List result = new ArrayList();
        try {
            List handList = dao.getHandTrade(stuempno,beginDate, endDate, tradedevice, tradecard, tradelogno);
            for (int i = 0; i < handList.size(); i++) {
                Object[] objects = (Object[]) handList.get(i);
                HashMap accMap = new HashMap();
                accMap.put("serial_no", objects[0]);
                accMap.put("STUEMP_NO", objects[1]);
                accMap.put("cut_name", objects[2]);
                accMap.put("card_id", objects[3]);
                accMap.put("operate_date", objects[4]);
                accMap.put("operate_time", objects[5]);
                accMap.put("collect_date", objects[6]);
                accMap.put("collect_time", objects[7]);
                accMap.put("enteract_date", objects[8]);
                accMap.put("enteract_time", objects[9]);
                accMap.put("devphy999_id", objects[10]);
                result.add(accMap);
            }
            return result;
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }
    }

    public static List getOneAccountDetail(String custNo, String beginDate, String endDate) {
        AccountDAO dao = AccountDAO.getInstance();
        List result = new ArrayList();
        try {
            List account = dao.getOneAccountDetail(custNo, beginDate, endDate);
            for (int i = 0; i < account.size(); i++) {
                Object[] objects = (Object[]) account.get(i);
                HashMap accMap = new HashMap();
                accMap.put("operdate", objects[0]);
                accMap.put("opertime", objects[1]);
                accMap.put("devid", dao.getDevNameByDevId(Integer.parseInt(objects[2].toString())));
                accMap.put("operator", objects[3]);
                accMap.put("comments", objects[4]);
                accMap.put("opfee", objects[5]);
                result.add(accMap);
            }
            return result;
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }
    }

    public static String getCustIdBystuempNo(String stuempNo) {
        try {
            AccountDAO dao = AccountDAO.getInstance();
            return dao.getCustIdBystuempNo(stuempNo);
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }
    }

}
