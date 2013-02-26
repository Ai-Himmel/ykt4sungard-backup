package org.king.service.impl;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.bean.ReceiveBean;
import org.king.bean.ReceiveItem;
import org.king.bean.SendBean;
import org.king.bean.Transdtl;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.dao.JdbcDao;
import org.king.http.HttpResponser;
import org.king.http.HttpsRequester;
import org.king.service.CheckService;
import org.king.util.DBUtil;
import org.king.util.DateUtil;
import org.king.util.EncryptUtil;
import org.king.util.Transformer;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class JJLinkServiceImpl implements CheckService {
    private static final Logger logger = Logger.getLogger(JJLinkServiceImpl.class);

    private JdbcDao jdbcDao;

    private Transformer transformer = new Transformer();

    public void setJdbcDao(JdbcDao jdbcDao) {
        this.jdbcDao = jdbcDao;
    }

    /**
     * step 1.find jjlink record
     * step2.send record to the third pay system
     * step3.according to the response of check_request,update third pay record
     */
    public void checkRecord() {
        Connection conn = null;
        try {
            logger.info("start checking record...");
            conn = DBUtil.getConnection();
            if (conn == null) {
                throw new RuntimeException("can't get connection");
            }
            conn.setAutoCommit(false);
            String checkSql = Configuration.getProperty(Constant.CHECK_SQL);
            List<Transdtl> list = jdbcDao.findCheckRecord(conn, checkSql);
            logger.info("jjlink check record size:" + list.size());
            if (list.size() > 0) {
                SendBean sendBean = new SendBean();
                sendBean.setData(list);
                ReceiveBean receiveBean = sendRequest(sendBean);
                updateCheckRecord(conn, receiveBean);
            }
            conn.commit();
            logger.info("succeed checking record");
        } catch (Exception e) {
            DBUtil.rollback(conn);
            logger.error("fail to check record");
            logger.error(e);
        } finally {
            DBUtil.closeConnection(conn);
        }
    }

    /**
     * send record to the third pay system and parse the response content
     * we will sleep for a short time in order to make sure three requests are sent at different time
     *
     * @param sendBean .
     * @return .
     * @throws Exception .
     */
    private ReceiveBean sendRequest(SendBean sendBean) throws Exception {
        String checkUrl = Configuration.getProperty(Constant.CHECK_URL);

        HttpsRequester request = new HttpsRequester(checkUrl);
        sendInitRequest(request);
        //sleep for two seconds
        Thread.sleep(2000);
        ReceiveBean receiveBean = sendCheckRequest(request, sendBean);
        Thread.sleep(2000);
        sendDestroyRequest(request);

        return receiveBean;
    }

    /**
     * init session in the third pay system
     *
     * @return .
     * @throws Exception .
     */
    private boolean sendInitRequest(HttpsRequester request) throws Exception {
        logger.info("send init session request");
        request.cleanParameter();
        String ip = Configuration.getProperty(Constant.IP);
        long time = System.currentTimeMillis() / 1000;
        request.addParameter("action", Constant.INIT_ACTION);
        request.addParameter("time", String.valueOf(time));
        request.addParameter("code", EncryptUtil.getJJLinkMD5String(ip, time));
        HttpResponser response = request.send();
        return transformer.parseInitResult(response.getContent());
    }

    /**
     * step1.send check request to third pay system
     * step2.parse the response of check request
     *
     * @param sendBean .
     * @return .
     * @throws Exception .
     */
    private ReceiveBean sendCheckRequest(HttpsRequester request, SendBean sendBean) throws Exception {
        logger.info("send check request");
        request.cleanParameter();
        String ip = Configuration.getProperty(Constant.IP);
        long time = System.currentTimeMillis() / 1000;
        request.addParameter("action", Constant.CHECK_ACTION);
        request.addParameter("time", String.valueOf(time));
        request.addParameter("code", EncryptUtil.getJJLinkMD5String(ip, time));
        request.addParameter("request_time", DateUtil.getNowTime());
        int i = 0;
        for (Transdtl transdtl : sendBean.getData()) {
            request.addParameter("data[" + i + "][ecard_id]", transdtl.getEcardId());
            request.addParameter("data[" + i + "][request_time]", transdtl.getRequestTime());
            request.addParameter("data[" + i + "][ecard_num]", transdtl.getEcardNum());
            request.addParameter("data[" + i + "][username]", transdtl.getUserName());
            request.addParameter("data[" + i + "][fullname]", transdtl.getFullName());
            request.addParameter("data[" + i + "][amount]", transdtl.getAmount());
            request.addParameter("data[" + i + "][ecard_machine_id]", transdtl.getEcardMachineId());
            request.addParameter("data[" + i + "][ecard_ip]", transdtl.getEcardIp());
            request.addParameter("data[" + i + "][inpayamount_id]", transdtl.getInpayamountId());
            request.addParameter("data[" + i + "][reply_time]", transdtl.getReplyTime());
            request.addParameter("data[" + i + "][ack_time]", transdtl.getAckTime());
            logger.debug(transdtl);
            i++;
        }

        HttpResponser response = request.send();
        logger.debug(response.getContent());
        return transformer.parseCheckResult(response.getContent());
    }

    /**
     * destroy session in the third pay system
     *
     * @return .
     * @throws Exception .
     */
    private boolean sendDestroyRequest(HttpsRequester request) throws Exception {
        logger.info("send destroy session request");
        request.cleanParameter();
        String ip = Configuration.getProperty(Constant.IP);
        long time = System.currentTimeMillis() / 1000;
        request.addParameter("action", Constant.DESTROY_ACTION);
        request.addParameter("time", String.valueOf(time));
        request.addParameter("code", EncryptUtil.getJJLinkMD5String(ip, time));
        HttpResponser response = request.send();

        return transformer.parseDestroyResult(response.getContent());
    }

    /**
     * update third pay record
     * args{ecard_id,status}
     *
     * @param conn        .
     * @param receiveBean .
     * @throws SQLException .
     */
    private void updateCheckRecord(Connection conn, ReceiveBean receiveBean) throws SQLException {
        logger.info("update check record");
        List<ReceiveItem> items = receiveBean.getData();
        String[][] args = new String[items.size()][2];
        int i = 0;
        for (ReceiveItem item : items) {
            if (StringUtils.isBlank(item.getEcardId())) {
                logger.error("find a check result without ecard_id,[ecard_id:" + item.getEcardId() + ",status:" + item.getStatus() + "]");
            } else {
                args[i] = new String[2];
                args[i][0] = item.getEcardId();
                args[i][1] = item.getStatus();
                i++;
            }
        }

        jdbcDao.updateThirdPayRecord(conn, args);
    }
}
