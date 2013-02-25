package com.sungard.smartcard.modules.system.service;

import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.domain.Opersite;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;

import java.util.List;

/**
 * 操作员业务处理接口
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
public interface OperatorService {

    public Operator getOperator(String opercode);

    /*
    * 操作员登陆	接受4个参数并验证参数是非为空
    * @param or.getAddr()		操作员ip
    * @param or.getZipcode()	操作员mac地址
    * @param or.getOpercode()	操作员代码
    * @param or.getOperpwd()	操作员密码
    * @return
    * @author HongYi.Wang
    */
    public List<Functionality> operatorLogin(Operator operator) throws FunctionException;

    /*
    * 操作员登出
    * @param or.getOpercode()	操作员代码
    * @author HongYi.Wang
    */
    public void operatorLoginOut(Operator operator) throws FunctionException;

    /*
    * 添加操作员
    * @param or.getOpercode()	操作员代码
    * @author HongYi.Wang
    */
    public void addOperator(Operator operator) throws FunctionException;

    /*
    * 修改操作员
    * @param or.getOpercode()	操作员代码
    * @author HongYi.Wang
    */
    public void modifyOperator(Operator operator) throws FunctionException;

    /*
    * 删除操作员
    * @param or.getOpercode()	操作员代码
    * @author HongYi.Wang
    */
    public void delOperator(Operator operator) throws FunctionException;

    /*
    * 查询操作员
    * @param or.getOpercode()	操作员代码
    * @author HongYi.Wang
    */
    public List<Operator> queryOperators(Operator operator) throws FunctionException;

    /*
    * 添加操作员站点关系
    * @author HongYi.Wang
    */
    public void addOperatorSite(Opersite os) throws FunctionException;

    /*
    * 修改操作员站点关系
    * @author HongYi.Wang
    */
    public void modifyOperatorSite(Opersite os) throws FunctionException;

    /*
    * 删除操作员站点关系
    * @author HongYi.Wang
    */
    public void delOperatorSite(Opersite os) throws FunctionException;

    /*
    * 查询操作员站点关系
    * @author HongYi.Wang
    */
    public List<Site> queryOperatorSites(Opersite os) throws FunctionException;

    /*
    * 修改操作员密码
    * @author HongYi.Wang
    */
    public void modifyOperatorPW(Site s) throws FunctionException;

    /*
    * 重置操作员密码
    * @author HongYi.Wang
    */
    public void resetOperatorPW(Site s) throws FunctionException;

    /**
     * 充值操作员授权
     *
     * @param opercode 操作员编号
     * @throws FunctionException .
     */
    public int authOperator(String opercode) throws FunctionException;


}
