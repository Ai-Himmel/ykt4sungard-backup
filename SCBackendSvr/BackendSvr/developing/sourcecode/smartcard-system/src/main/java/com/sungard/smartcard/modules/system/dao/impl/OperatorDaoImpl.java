package com.sungard.smartcard.modules.system.dao.impl;

import com.sungard.modules.utils.StringHelper;
import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.modules.system.dao.OperatorDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

/**
 * 操作员数据库操作类实现
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
@Repository
public class OperatorDaoImpl implements OperatorDao {
    @Autowired
    private JdbcTemplate jdbcTemplate;

    private static String OPERATOR_QUERY = "SELECT * FROM T_OPERATOR WHERE OPERCODE=?";
    /**
     * 添加操作员角色
     */
    private static String OPERATOR_ADDROLE = "insert into t_operator_role values(?,?)";
    /**
     * 更新操作员
     */
    private static String OPERATOR_UPDATE = "UPDATE T_OPERATOR SET LOGINFLAG=?,LOGINTIME=?,LOGINSITENO=(select siteno from t_site where ip=?) WHERE OPERCODE=?";
    /**
     * 更新操作员为登出状态
     */
    private static String OPERATOR_UPDATE_FOR_LOGINOUT = "update t_operator set loginflag=?,logouttime=? where opercode=?";
    /**
     * 更新操作员密码
     */
    private static String OPERATOR_UPDATE_FOR_PASSWORD = "update t_operator set operpwd=? where opercode=?";
    /**
     * 更新操作员状态用户注销操作员
     */
    private static String OPERATOR_UPDATE_FOR_STATUS = "update t_operator set status=?,closedate=? where opercode=?";
    /**
     * 获取关联操作员数
     */
    private static String GET_RELATEBRANCHOPERATORNUM = "select count(*) from t_operator where branchno=?";
    /**
     * 获取操作员角色数
     */
    private static String GET_OPERRATORROLENUM = "select count(*) from t_operator_role where opercode=?";
    /**
     * 查看ip是否在site表中存在以判断操作员登陆ip是否合法
     */
    private static String OPERATOR_VALIDATESITE = "select count(*) from t_site ts where ts.ip=?";
    /**
     * 根据操作员代码取得操作员菜单功能权限
     */
    private static String OPERATOR_GETFUNCTIONALITY = "select tp.func_id,tf.pid,tf.name,tf.target_plugin,max(tp.auth_action) from t_permission tp,t_functionality tf where tp.role_id in (select tor.role_id from t_operator_role tor,t_role tr where tor.opercode=? and tr.id=tor.role_id) and tf.id=tp.func_id group by tp.func_id,tf.pid,tf.name,tf.target_plugin";
    /**
     * 查看ip是否在site表中存在以判断操作员登陆ip是否合法
     */
    private static String OPERATOR_ISVALIDATESITE = "select count(*) from t_site ts,t_opersite to where ts.siteno=to.siteno and ts.ip=? and to.opercode=?";


    //TODO 操作员无法继续
    /**
     * 查询操作员
     */
    private static String SELECT_OPERATOR = "select * from t_operator where 1=1";
    /**
     * 添加操作员
     */
    private static String INSERT_OPERATOR = "insert into t_operator(branchno,rightflag,sitelimit,opercode,opername,opertype,operpwd,tel,email,mobile,zipcode,addr,opendate) values(?,?,?,?,?,?,?,?,?,?,?,?,?)";
    /**
     * 更新操作员
     */
    private static String UPDATE_OPERATOR = "update t_operator set branchno=?,sitelimit=?,opername=?,opertype=?,operpwd=?,tel=?,email=?,mobile=?,zipcode=?,addr=? where opercode=?";
    /**
     * 删除操作员
     */
    private static String DELETE_OPERATOR = "delete from t_operator set branchno=?,sitelimit=?,opername=?,opertype=?,operpwd=?,tel=?,email=?,mobile=?,zipcode=?,addr=? where opercode=?";

    public Operator getOperator(String opercode) {
        return jdbcTemplate.queryForObject(OPERATOR_QUERY, Operator.class, opercode);
    }

    @Override
    public int updateOperator(Operator operator) {
        return jdbcTemplate.update(OPERATOR_UPDATE, operator.getLoginflag(), operator.getLogintime(), operator.getAddr(), operator.getOpercode());
    }

    @Override
    public List<Functionality> getOperatorFunctionality(Operator operator) {
        List<Functionality> functionalitys = this.jdbcTemplate.query(
                OPERATOR_GETFUNCTIONALITY,
                new Object[]{operator.getOpercode()},
                new RowMapper<Functionality>() {
                    public Functionality mapRow(ResultSet rs, int rowNum) throws SQLException {
                        Functionality fcl = new Functionality();
                        fcl.setId(rs.getInt(0));
                        fcl.setPid(rs.getInt(1));
                        fcl.setName(rs.getString(2));
                        fcl.setTargetPlugin(rs.getString(3));
                        fcl.setSupportedAction(rs.getInt(4));
                        return fcl;
                    }
                });
        return functionalitys;
    }

    @Override
    public boolean isValidateIpAddress(String operatorip) {
        //返回是否为合法ip地址 true为合法  false为非法
        return jdbcTemplate.queryForInt(OPERATOR_VALIDATESITE, operatorip) == 1;
    }

    @Override
    public boolean isValidateIpForOperator(String operatorip,
                                           String operatorcode) {
        //返回操作员是否为有权利用ip访问
        return jdbcTemplate.queryForInt(OPERATOR_ISVALIDATESITE, operatorip, operatorcode) == 1;
    }

    @Override
    public int updateOperatorInfoForLogout(Operator operator) {
        return jdbcTemplate.update(OPERATOR_UPDATE_FOR_LOGINOUT, operator.getLoginflag(), operator.getLogintime(), operator.getOpercode());
    }

    @Override
    public int getOperatorNumRelateBranch(Integer branchno) {
        return jdbcTemplate.queryForInt(GET_RELATEBRANCHOPERATORNUM, Long.valueOf(branchno));
    }

    @Override
    public void addOprator(Operator o) {
        //branchno,rightflag,sitelimit,opercode,opername,opertype,operpwd,tel,email,mobile,zipcode,addr,opendate
        this.jdbcTemplate.update(INSERT_OPERATOR, Long.valueOf(o.getBranchno()), Long.valueOf(o.getRightflag()), o.getSitelimit(), o.getOpercode(), o.getOpername(), o.getOpertype(), o.getOperpwd(), o.getTel(), o.getEmail(), o.getMobile(), o.getZipcode(), o.getAddr(), o.getOpendate());
    }

    @Override
    public void delOprator(Operator o) {
        this.jdbcTemplate.update(OPERATOR_UPDATE_FOR_STATUS, o.getStatus(), o.getClosedate(), o.getOpercode());
    }

    @Override
    public List<Operator> queryOprator(Operator operator) {
        String s = SELECT_OPERATOR;
        String oc = operator.getOpercode();
        String os = operator.getStatus();
        if (StringHelper.isNotBlank(oc)) {
            s += " and opercode='" + oc + "'";
        }
        if (StringHelper.isNotBlank(os)) {
            s += " and status='" + os + "'";
        }
        List<Operator> operators = this.jdbcTemplate.query(
                s,
                new RowMapper<Operator>() {
                    public Operator mapRow(ResultSet rs, int rowNum) throws SQLException {
                        Operator f = new Operator();
                        f.setOpercode(rs.getString("opercode"));
                        f.setAddr(rs.getString("addr"));
                        f.setBranchno(rs.getInt("branchno"));
                        f.setCardno(rs.getInt("cardno"));
                        f.setEmail(rs.getString("email"));
                        f.setLoginflag(rs.getString("loginflag"));
                        f.setLoginsiteno(rs.getInt("loginsiteno"));
                        f.setMobile(rs.getString("mobile"));
                        f.setOpername(rs.getString("opername"));
                        f.setOpertype(rs.getString("opertype"));
                        f.setRightflag(rs.getInt("rightflag"));
                        f.setSitelimit(rs.getString("sitelimit"));
                        f.setStatus(rs.getString("status"));
                        f.setTel(rs.getString("tel"));
                        f.setZipcode(rs.getString("zipcode"));
                        return f;
                    }
                });
        return operators;
    }

    @Override
    public void updateOprator(Operator o) {
        this.jdbcTemplate.update(UPDATE_OPERATOR, Long.valueOf(o.getBranchno()), o.getSitelimit(), o.getOpername(), o.getOpertype(), o.getOperpwd(), o.getTel(), o.getEmail(), o.getMobile(), o.getZipcode(), o.getAddr(), o.getOpercode());
    }

    @Override
    public void updateOpratorPW(Site s) {
        //s.getIp()用来存放密码 s.getSitename()用来存放操作员号
        this.jdbcTemplate.update(OPERATOR_UPDATE_FOR_PASSWORD, s.getIp(), s.getSitename());
    }

    @Override
    public int getOperatorPwdNum(String pwd, String opercode) {
        String ss = GET_RELATEBRANCHOPERATORNUM.replace("branchno", "opercode");
        ss += " and operpwd=?";
        return this.jdbcTemplate.queryForInt(ss, opercode, pwd);
    }

    @Override
    public void addOperatorRole(String opercode, Integer roleid) {
        this.jdbcTemplate.update(OPERATOR_ADDROLE, opercode, Long.valueOf(roleid));
    }

    @Override
    public int getOperatorNumByOpercode(String opercode) {
        String s = GET_RELATEBRANCHOPERATORNUM.replace("branchno", "opercode");
        return this.jdbcTemplate.update(s, opercode);
    }

    @Override
    public int authOperator(String opercode) {
        String authSql = "update ykt_cur.t_operator t set t.rightflag=1 where t.opercode=?";
        return this.jdbcTemplate.update(authSql, opercode);
    }
}
