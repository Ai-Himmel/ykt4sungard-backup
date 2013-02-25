package com.sungard.smartcard;

import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.domain.Syspara;
import com.sungard.smartcard.domain.Transcode;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowCallbackHandler;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

/**
 * 初始化环境，包括初始化MessageCode
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
@Component
public class AppContext {

    private static Logger logger = LoggerFactory.getLogger(AppContext.class);

    private static String MESSAGE_CODE_QUERY = "select ret_code as retCode ,ret_msg as retMsg from t_message_code";
    private static String TRANSCODE_QUERY = "select transcode,transname,logflag,limitflag,feeflag,transflag,disableflag from t_transcode";
    private static String CFGFEE_QUERY = "select feetype, transcode, cardtype, transtype, ratetype, rateamt, remark from t_cfgfee";
    private static String SYSPARA_QUERY = "select paraid,paraval,paraname,paraunit,displayflag,remark,lastsaved from t_syspara";

    private static Map<Integer, String> messageCodeMap;

    private static Map<Integer, Transcode> transcodeMap;

    private static Map<Integer, Syspara> sysparaMap;

    private static Map<String, Cfgfee> cfgfeeMap;

    @Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public AppContext() {
        logger.debug("--->>--constracute AppContext()");
    }

    /**
     * 初始化返回消息表中的数据
     */
    @PostConstruct
    private void initMessageCode() {
        messageCodeMap = new HashMap<Integer, String>();
        jdbcTemplate.query(MESSAGE_CODE_QUERY, new RowCallbackHandler() {
            @Override
            public void processRow(ResultSet resultSet) throws SQLException {
                messageCodeMap.put(Integer.valueOf(resultSet.getInt("RETCODE")), resultSet.getString("RETMSG"));
            }
        });
    }

    /**
     * 根据消息返回码获得对应的返回信息
     *
     * @param retCode 返回状态码
     * @return 返回码对应的消息
     */
    public static String getRetMsg(Integer retCode) {
        return messageCodeMap.get(retCode);
    }

    /**
     * 加载交易码表
     */
    @PostConstruct
    private void initTranscode() {
        transcodeMap = new HashMap<Integer, Transcode>();
        jdbcTemplate.query(TRANSCODE_QUERY, new RowCallbackHandler() {
            @Override
            public void processRow(ResultSet resultSet) throws SQLException {
                Transcode transcode = new Transcode();
                transcode.setTranscode(resultSet.getInt("TRANSCODE"));
                transcode.setTransname(resultSet.getString("TRANSNAME"));
                transcode.setLogflag(resultSet.getInt("LOGFLAG"));
                transcode.setLimitflag(resultSet.getInt("LIMITFLAG"));
                transcode.setFeeflag(resultSet.getInt("FEEFLAG"));
                transcode.setTransflag(resultSet.getInt("TRANSFLAG"));
                transcode.setDisableflag(resultSet.getInt("DISABLEFLAG"));
                transcodeMap.put(transcode.getTranscode(), transcode);
            }
        });
    }

    /**
     * 加载交易收费配置表
     */
    @PostConstruct
    private void initCfgFee() {
        cfgfeeMap = new HashMap<String, Cfgfee>();
        jdbcTemplate.query(CFGFEE_QUERY, new RowCallbackHandler() {
            @Override
            public void processRow(ResultSet resultSet) throws SQLException {
                Cfgfee cfgfee = new Cfgfee();
                cfgfee.setFeetype(resultSet.getInt("FEETYPE"));
                cfgfee.setTranscode(resultSet.getInt("TRANSCODE"));
                cfgfee.setCardtype(resultSet.getInt("CARDTYPE"));
                cfgfee.setTranstype(resultSet.getInt("TRANSTYPE"));
                cfgfee.setRatetype(resultSet.getInt("RATETYPE"));
                cfgfee.setRateamt(resultSet.getDouble("RATEAMT"));
                cfgfee.setRemark(resultSet.getString("REMARK"));
                String key = cfgfee.getFeetype().toString() + cfgfee.getCardtype().toString() + cfgfee.getTranscode().toString() + cfgfee.getTranstype().toString();
                cfgfeeMap.put(key, cfgfee);
            }
        });
    }

    /**
     * 加载系统参数表
     */
    @PostConstruct
    private void initSyspara() {
        sysparaMap = new HashMap<Integer, Syspara>();
        jdbcTemplate.query(SYSPARA_QUERY, new RowCallbackHandler() {
            @Override
            public void processRow(ResultSet resultSet) throws SQLException {
                Syspara syspara = new Syspara();
                syspara.setParaid(resultSet.getInt("PARAID"));
                syspara.setParaval(resultSet.getString("PARAVAL"));
                syspara.setParaname(resultSet.getString("PARANAME"));
                syspara.setParaunit(resultSet.getString("PARAUNIT"));
                syspara.setDisplayflag(resultSet.getString("DISPLAYFLAG"));
                syspara.setRemark(resultSet.getString("REMARK"));
                syspara.setRemark(resultSet.getString("LASTSAVED"));
                sysparaMap.put(syspara.getParaid(), syspara);
            }
        });
    }

    /**
     * 加载系统配置文件，包括t_transcode，t_cfgfee，t_syspara
     */
    public static void loadCfg() {


    }
}
