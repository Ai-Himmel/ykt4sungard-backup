package com.sungard.smartcard.modules.system.dao;

import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.domain.Site;

import java.util.List;

/**
 * 操作员数据库操作类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
public interface OperatorDao {

    public Operator getOperator(String opercode);

    /*
    * 更新操作员信息登陆信息更新4字段信息LOGINFLAG=?,LOGINTIME=?,LOGINSITENO=(select siteno from t_site where ip=?)
    */
    public int updateOperator(Operator operator);

    /*
    * 更新操作员登出状态
    */
    public int updateOperatorInfoForLogout(Operator operator);

    /*
    * 根据用户名取得用户权限
    */
    public List<Functionality> getOperatorFunctionality(Operator operator);

    /*
    *	判断操作员的ip是否为合法的站点ip
    */
    public boolean isValidateIpAddress(String operatorip);

    /*
    * 根据ip和操作员代码判断操作员对站点的访问权限
    */
    public boolean isValidateIpForOperator(String operatorip, String operatorcode);

    /*
      * 查看网点关联操作员数
      */
    public int getOperatorNumRelateBranch(Integer branchno);

    /*
      * 添加操作员数据
      */
    public void addOprator(Operator operator);

    /*
      * 更新操作员数据
      */
    public void updateOprator(Operator operator);

    /*
      * 删除操作员数据
      */
    public void delOprator(Operator operator);

    /*
      * 查询操作员数据
      */
    public List<Operator> queryOprator(Operator operator);

    /*
      * 更新操作员密码
      */
    public void updateOpratorPW(Site s);

    /*
      * 查询员密码是否正确
      */
    public int getOperatorPwdNum(String pwd, String opercode);

    /*
      * 添加操作员角色
      */
    public void addOperatorRole(String opercode, Integer roleid);

    /*
      * 根据操作员号查看操作员数
      */
    public int getOperatorNumByOpercode(String opercode);

    /**
     * 充值操作员授权
     *
     * @param opercode 操作员编号
     * @return .
     */
    public int authOperator(String opercode);

}
