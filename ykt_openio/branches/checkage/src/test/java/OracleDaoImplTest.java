import junit.framework.TestCase;
import org.apache.log4j.Logger;
import org.king.bean.Transdtl;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.dao.JdbcDao;
import org.king.dao.impl.OracleDaoImpl;
import org.king.util.DBUtil;

import java.sql.Connection;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class OracleDaoImplTest extends TestCase {
    private static final Logger logger = Logger.getLogger(OracleDaoImplTest.class);

    private Connection conn;

    private JdbcDao jdbcDao;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        Configuration.load();
        conn = DBUtil.getConnection();
        jdbcDao = new OracleDaoImpl();
    }

    @Override
    protected void tearDown() throws Exception {
        DBUtil.closeConnection(conn);
        super.tearDown();
    }

    public void testFindTransdtl() {
        String checkSql = Configuration.getProperty(Constant.CHECK_SQL);
        List<Transdtl> list = jdbcDao.findCheckRecord(conn,checkSql);
        for (Transdtl transdtl : list) {
            System.out.println(transdtl.toString());
        }
    }
}
