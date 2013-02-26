import junit.framework.TestCase;
import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.dao.impl.OracleDaoImpl;
import org.king.service.CheckService;
import org.king.service.impl.JJLinkServiceImpl;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class CheckServiceImplTest extends TestCase {
    private static final Logger logger = Logger.getLogger(CheckServiceImplTest.class);

    private CheckService checkService;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        Configuration.load();
        checkService = new JJLinkServiceImpl();
        checkService.setJdbcDao(new OracleDaoImpl());
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void testCheckRecord() {
        checkService.checkRecord();
    }
}
