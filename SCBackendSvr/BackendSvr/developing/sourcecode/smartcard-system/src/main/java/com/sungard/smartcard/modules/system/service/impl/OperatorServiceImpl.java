package com.sungard.smartcard.modules.system.service.impl;

import com.sungard.modules.utils.StringHelper;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.domain.Opersite;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.OperatorDao;
import com.sungard.smartcard.modules.system.dao.SiteDao;
import com.sungard.smartcard.modules.system.service.OperatorService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

/**
 * 操作员业务处理实现
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
@Service
public class OperatorServiceImpl implements OperatorService {
    private static final Logger logger = LoggerFactory
            .getLogger(OperatorServiceImpl.class);
    @Autowired
    @Qualifier("siteDaoImpl")
    private SiteDao siteDao;

    public void setSiteDao(SiteDao siteDao) {
        this.siteDao = siteDao;
    }

    @Autowired
    @Qualifier("operatorDaoImpl")
    private OperatorDao operatorDao;

    public Operator getOperator(String opercode) {
        return operatorDao.getOperator(opercode);
    }

    @Override
    @Transactional
    public List<Functionality> operatorLogin(Operator operator)
            throws FunctionException {
        logger.info("操作员[{}]登陆业务", new Object[]{operator.getOpercode()});
        /** 获取传入的参数共4个 */
        // 操作员代码
        String opercode = operator.getOpercode();
        // 操作员密码
        String userpassword = operator.getOperpwd();
        // 操作员ip地址
        String operatorip = operator.getAddr();
        // 操作员mac地址
        String macaddress = operator.getZipcode();
        logger
                .debug("[功能输入参数：用户名{}----密码：{}----登陆ip地址：{}------登陆mac地址：{}]",
                        new Object[]{opercode, userpassword, operatorip,
                                macaddress});
        /** 操作数据库根据操作员代码获取操作员信息 */
        Operator ot = operatorDao.getOperator(opercode);
        /** 操作员不存在返回 */
        if (ot == null) {
            throw new FunctionException(RetCode.OPERATOR_NOT_EXIST, opercode);
        }
        /** 操作员状态 */
        int status = new Integer(ot.getStatus());
        logger.debug("操作员状态为[{}]", new Object[]{status});
        switch (status) {
            // 操作员被锁定 抛出异常
            case 0:
                throw new FunctionException(RetCode.OPERATOR_LOCK, opercode);
                // 操作员被注销 抛出异常
            case 2:
                throw new FunctionException(RetCode.OPERATOR_CANCEL, opercode);
        }
        /** 判断用户密码是否正确 */
        if (!ot.getOperpwd().equals(userpassword)) {
            throw new FunctionException(RetCode.OPERATOR_WRONG_PASSWORD,
                    opercode);
        }
        /** 返回是否为合法ip地址 true为合法 false为非法 */
        boolean isValidateIp = operatorDao.isValidateIpAddress(operatorip);
        /** 判断站点ip是否合法 */
        if (isValidateIp == false) {
            throw new FunctionException(RetCode.OPERATOR_WRONG_SITEIP);
        }
        /** 判断操作员是否有权限利用合法ip访问站点 */
        boolean isValidateoperatorip = operatorDao.isValidateIpForOperator(
                operatorip, opercode);
        if (isValidateoperatorip == false) {
            throw new FunctionException(RetCode.OPERATOR_WRONG_OPERSITEIP,
                    opercode, operatorip);
        }
        /** 更新操作员登陆状态 */
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
        operator.setLogintime(sdf.format(new Date()));
        operator.setLoginflag("1");
        operatorDao.updateOperator(operator);
        /** 操作员登陆后获取菜单权限列表 */
        logger
                .debug("获取操作员[{}]菜单权限列表",
                        new Object[]{operator.getOpercode()});
        List<Functionality> functionalitys = operatorDao
                .getOperatorFunctionality(operator);
        // TODO 登陆日志记录功能未完成
        return functionalitys;
    }

    @Override
    @Transactional
    public void operatorLoginOut(Operator operator) throws FunctionException {
        logger.info("操作员[{}]登出业务", new Object[]{operator.getOpercode()});
        /** 操作数据库根据操作员代码获取操作员信息 */
        String opercode = operator.getOpercode();
        Operator ot = operatorDao.getOperator(opercode);
        /** 操作员不存在返回 */
        if (ot == null) {
            throw new FunctionException(RetCode.OPERATOR_NOT_EXIST, opercode);
        }
        /** 操作员状态 */
        int status = new Integer(ot.getStatus());
        logger.debug("操作员状态为[{}]", new Object[]{status});
        switch (status) {
            // 操作员被锁定 抛出异常
            case 0:
                throw new FunctionException(RetCode.OPERATOR_LOCK, opercode);
                // 操作员被注销 抛出异常
            case 2:
                throw new FunctionException(RetCode.OPERATOR_CANCEL, opercode);
        }
        /** 设置操作员登陆状态为未登陆 */
        operator.setLoginflag("0");
        /** 将操作员登出时间为当前时间 */
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
        operator.setLogouttime(sdf.format(new Date()));
        /** 数据库更新当前对象 */
        operatorDao.updateOperatorInfoForLogout(operator);
        // TODO 登出日志记录功能未完成
    }

    @Override
    @Transactional
    public void addOperator(Operator operator) throws FunctionException {
        //类型，站点限制，网点号
        String oc = operator.getOpercode();
        String on = operator.getOpername();
        String ot = operator.getOpertype();
        String os = operator.getSitelimit();
        int ob = operator.getBranchno();
        /**判断操作人号是否为空*/
        if (StringHelper.isBlank(oc)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERCODE);
        }
        /**判断操作名称是否为空*/
        if (StringHelper.isBlank(on)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERNAME);
        }
        /**判断操作类型是否为空*/
        if (StringHelper.isBlank(ot)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERTYPE);
        }
        /**判断是否站点限制为空*/
        if (StringHelper.isBlank(os)) {
            throw new FunctionException(RetCode.OPERATOR_NULLSITELIMIT);
        }
        /**网点号是否设置*/
        if (ob == 0) {
            throw new FunctionException(RetCode.OPERATOR_NULLBRANCHNO);
        }
        /**将操作员登出时间为当前时间*/
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
        operator.setOpendate(sdf.format(new Date()));
        operator.setStatus("1");
        /**设置是否有收费管理权限*/
        operator.setRightflag(0);
        /**如果已经设置角色id为操作员添加角色*/
        int role = operator.getLoginsiteno();
        if (role != 0) {
            operatorDao.addOperatorRole(operator.getOpercode(), role);
        }
        operatorDao.addOprator(operator);
    }

    @Override
    @Transactional
    public void delOperator(Operator operator) throws FunctionException {
        /**check where the opercode from input was set*/
        String opercode = operator.getOpercode();
        if (StringHelper.isBlank(opercode)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERCODE);
        }
        /**check whether the data of operator is stored in database.when not exist, throws error code to client*/
        int opnum = operatorDao.getOperatorNumByOpercode(opercode);
        if (opnum == 0) {
            throw new FunctionException(RetCode.OPERATOR_NOT_EXIST, operator);
        }
        /**set the operator`s cancel date*/
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
        operator.setClosedate(sdf.format(new Date()));
        operator.setStatus("2");
        operatorDao.delOprator(operator);
    }

    @Override
    @Transactional
    public void modifyOperator(Operator operator) throws FunctionException {
        String oc = operator.getOpercode();
        String on = operator.getOpername();
        String ot = operator.getOpertype();
        String os = operator.getSitelimit();
        int ob = operator.getBranchno();
        /**判断操作人号是否为空*/
        if (StringHelper.isBlank(oc)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERCODE);
        }
        /**判断操作名称是否为空*/
        if (StringHelper.isBlank(on)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERNAME);
        }
        /**判断操作类型是否为空*/
        if (StringHelper.isBlank(ot)) {
            throw new FunctionException(RetCode.OPERATOR_NULLOPERTYPE);
        }
        /**判断是否站点限制为空*/
        if (StringHelper.isBlank(os)) {
            throw new FunctionException(RetCode.OPERATOR_NULLSITELIMIT);
        }
        /**网点号是否设置*/
        if (ob == 0) {
            throw new FunctionException(RetCode.OPERATOR_NULLBRANCHNO);
        }
        /**将操作员登出时间为当前时间*/
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
        operator.setOpendate(sdf.format(new Date()));
        /**设置是否有收费管理权限*/
        operator.setRightflag(0);
        /**如果已经设置角色id为操作员添加角色*/
        int role = operator.getLoginsiteno();
        if (role != 0) {
            operatorDao.addOperatorRole(operator.getOpercode(), role);
        }
        operatorDao.updateOprator(operator);
    }

    @Override
    public List<Operator> queryOperators(Operator operator)
            throws FunctionException {
        List<Operator> operators = operatorDao.queryOprator(operator);
        return operators;
    }

    @Override
    @Transactional
    /**
     * 添加站点操作员关系
     */
    public void addOperatorSite(Opersite os) throws FunctionException {
        String opercode = os.getOpercode();
        int siteno = os.getSiteno();
        /**操作员号不能为空*/
        if (StringHelper.isBlank(opercode)) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_NULLOPERCODE);
        }
        /**站点号不能为空*/
        if (siteno == 0) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_NULLOPSITENO);
        }
        /**关系已经存在*/
        int opsitenum = siteDao.hasOperatorSiteNum(os);
        if (opsitenum > 0) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_EXISTSOPSITENUM);
        }
        /**将操作员登出时间为当前时间*/
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
        os.setLastsaved(sdf.format(new Date()));
        siteDao.addOSite(os);
        //TODO 添加关系日志
    }

    @Override
    @Transactional
    public void delOperatorSite(Opersite os) throws FunctionException {
        String opercode = os.getOpercode();
        int siteno = os.getSiteno();
        /**操作员号不能为空*/
        if (StringHelper.isBlank(opercode)) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_NULLOPERCODE);
        }
        /**站点号不能为空*/
        if (siteno == 0) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_NULLOPSITENO);
        }
        /**关系已经存在*/
        int opsitenum = siteDao.hasOperatorSiteNum(os);
        if (opsitenum == 0) {
            throw new FunctionException(RetCode.ADDOPSITE_WRONG_NOTEXISTSOPSITENUM);
        }
        /**删除站点操作员关系*/
        siteDao.delOSite(os);
        //TODO 删除关系日志
    }

    @Override
    public void modifyOperatorSite(Opersite os) throws FunctionException {
        //无需求
    }

    @Override
    public List<Site> queryOperatorSites(Opersite os)
            throws FunctionException {
        List<Site> sites = siteDao.queryOSite(os);
        //TODO 登陆日志记录功能未完成
        return sites;
    }

    @Override
    public void modifyOperatorPW(Site s) throws FunctionException {
        /**s.getIp()用来存放密码 s.getSitename()用来存放操作员号s.getMachinecode()存放操作员原密码;*/
        /**根据原密码判断操作员是否能够修改此密码*/
        String oldpassword = s.getMachinecode();
        int operatornum = operatorDao.getOperatorPwdNum(oldpassword, s.getSitename());
        if (operatornum == 0) {
            throw new FunctionException(RetCode.OPERATOR_WRONG_NOPRIORITY);
        }
        operatorDao.updateOpratorPW(s);
        //TODO 修改密码日志记录功能未完成
    }

    @Override
    public void resetOperatorPW(Site s) throws FunctionException {
        /**s.getIp()用来存放密码 s.getSitename()用来存放操作员号s.getMachinecode()存放操作员原密码;*/
        operatorDao.updateOpratorPW(s);
        //TODO 重置密码日志记录功能未完成
    }

    /**
     * 充值操作员授权
     *
     * @param opercode 操作员编号
     * @return .
     * @throws FunctionException
     */
    @Override
    public int authOperator(String opercode) throws FunctionException {
        return operatorDao.authOperator(opercode);
    }
}
