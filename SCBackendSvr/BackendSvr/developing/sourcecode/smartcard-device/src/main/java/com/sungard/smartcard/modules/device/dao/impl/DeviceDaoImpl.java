package com.sungard.smartcard.modules.device.dao.impl;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.criteria.CriteriaBuilder.Case;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.modules.device.dao.DeviceDao;

import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

/**
 * 操作员数据库操作类实现
 * 
 * @author shijia.meng
 * @version v1.00
 * @since 2012-02-20
 */
@Repository
public class DeviceDaoImpl implements DeviceDao {

	@Autowired
	private JdbcTemplate jdbcTemplate;

	@Override
	public int saveDeviceTmp(Devicetmp device) {
		String DEVICE_TMP_INFO = "insert into t_devicetmp (batchno,seqno, devicename,  "
			+ "devphytype,devusage,devphyid, areacode,fdeviceid, sysid, svrportno,ip,deviceno,svrportcnt,"
			+ "commtype,portno,devtypecode,cardphytype)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

		return jdbcTemplate.update(DEVICE_TMP_INFO, device.getBatchno(), device
				.getSeqno(), device.getDevicename(), device.getDevphytype(),
				device.getDevusage(), device.getDevphyid(), device
						.getAreacode(), device.getFdeviceid(), device
						.getSysid(), device.getSvrportno(), device.getIp(),
				device.getDeviceno(), device.getSvrportcnt(), device
						.getCommtype(), device.getPortno(), device
						.getDevtypecode(), device.getCardphytype());
	}

	@Override
	public int updateDevice(Device device) {
		String DEVICE_INFO_UPDATE = "update t_device set devicename = ?,devphytype = ?,"
			+ "devusage = ?,devphyid = ?,areacode=?,fdeviceid=?,sysid=?,svrportno=?,ip=?,deviceno=?,"
			+ "svrportcnt = ?,commtype=?,portno=?,devtypecode=?,remark=?,cardphytype=? where deviceid = ?";

		return jdbcTemplate.update(DEVICE_INFO_UPDATE, device.getDevicename(),
				device.getDevphytype(), device.getDevusage(), device
						.getDevphyid(), device.getAreacode(), device
						.getFdeviceid(), device.getSysid(), device
						.getSvrportno(), device.getIp(), device.getDeviceno(),
				device.getSvrportcnt(), device.getCommtype(), device
						.getPortno(), device.getDevtypecode(), device
						.getRemark(), device.getCardphytype(), device
						.getDeviceid());
	}

	@Override
	public int saveDevice(Device device) {
		String DEVICE_INFO = "insert into t_device (deviceid, devicename,  "
			+ "devphytype,devusage,devphyid, areacode,fdeviceid, sysid, svrportno,ip,deviceno,svrportcnt,"
			+ "commtype,portno,devtypecode,remark,cardphytype,status,runstatus)values(seq_device.nextval,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
		return jdbcTemplate.update(DEVICE_INFO, device.getDevicename(), device
				.getDevphytype(), device.getDevusage(), device.getDevphyid(),
				device.getAreacode(), device.getFdeviceid(), device.getSysid(),
				device.getSvrportno(), device.getIp(), device.getDeviceno(),device.getSvrportcnt(),
				device.getCommtype(), device.getPortno(), device
						.getDevtypecode(), device.getRemark(), device
						.getCardphytype(), device.getStatus(), device
						.getRunstatus());
	}

	@Override
	// return 1 代表存在，return 0 代表不存在
	public int isExist(String table,String key, String value) {
		String IS_EXISTS_DEVICE = "select count(1) from "+table+" where 1=1 ";
		if (key != null) {
			if (key.equals("deviceName")) {// 设备名称
				IS_EXISTS_DEVICE += " and devicename=?";
			} else if (key.equals("devicePhyId")) {// 设备物理id
				IS_EXISTS_DEVICE += " and devphyid=?";
			} else if (key.equals("ip")) {// 设备ip
				IS_EXISTS_DEVICE += " and ip=?";
			} else if (key.equals("phyType")) {// 物理类型
				IS_EXISTS_DEVICE += " and phyType=?";
			} else if (key.equals("areaCode")) {// 区域代码
				IS_EXISTS_DEVICE += " and areaCode=?";
			}
			return jdbcTemplate.queryForInt(IS_EXISTS_DEVICE, value);
		}
		return 0;
	}

	@Override
	// return 1 代表存在，return 0 代表不存在
	public int isExistForInt(String table,String key, int value) {
		String IS_EXISTS_DEVICE = "select count(1) from t_device where 1=1 ";
		if (key != null) {
			if (key.equals("deviceid")) {// 设备名称
				IS_EXISTS_DEVICE += " and deviceid=?";
			}else if (key.equals("phyType")) {// 物理型号
				IS_EXISTS_DEVICE += " and phyType=?";
			}
			return jdbcTemplate.queryForInt(IS_EXISTS_DEVICE, value);
		}
		return 0;
	}

	@Override
	public int isExistSys(int value) {
		String IS_EXISTS_SYS = "select count(1) from t_subsystem where 1=1 and sysid = ?";
		return jdbcTemplate.queryForInt(IS_EXISTS_SYS, value);
	}

	@Override
	public int isDeviceCancelled(int deviceId) {
		String IS_DEVICE_CANCELLED = "select count(1) from t_device where status = '2' and deviceid = ?";
		return jdbcTemplate.queryForInt(IS_DEVICE_CANCELLED, deviceId);
	}

	@Override
	public int isExistDeviceAndNotIncludeMineByDevice(int device, String key,
			String value) {
		String IS_EXISTS_DEVICE = "select count(1) from t_device where 1=1 ";
		if (key != null) {
			if (key.equals("DEVICENAME")) {// 设备名称
				IS_EXISTS_DEVICE += " and devicename=? and deviceid<>?";
			} else if (key.equals("IP")) {// 设备ip
				IS_EXISTS_DEVICE += " and ip=?  and deviceid<>?";
			} else if (key.equals("DEVPHYID")) {// 设备物理id
				IS_EXISTS_DEVICE += " and devphyid=?  and deviceid<>?";
			}
			return jdbcTemplate.queryForInt(IS_EXISTS_DEVICE, value, device);
		}
		return 0;
	}

	@Override
	public int updateDeviceStatus(int deviceId) {
		String UPDATE_DEVICE_STATUS = "update t_device set status = 2 where deviceid = ?";
		return jdbcTemplate.update(UPDATE_DEVICE_STATUS, deviceId);
	}

	@Override
	public int deleteDeviceHeartBeat(int deviceId) {
		String DELETE_DEVICE_HEATBEAT = "delete t_devmonitor where deviceid = ?";
		return jdbcTemplate.update(DELETE_DEVICE_HEATBEAT, deviceId);
	}

	@Override
	public int isExistDeviceAndNotIncludeMineByDeviceTmp(String batchNo,
			int seqNo, String key, String value) {
		String IS_EXISTS_DEVICETMP = "select count(1) from t_devicetmp where 1=1 ";
		if (key != null) {
			if (key.equals("DEVICENAME")) {// 设备名称
				IS_EXISTS_DEVICETMP += " and devicename=? and batchno<>? and seqno<>?";
			} else if (key.equals("IP")) {// 设备ip
				IS_EXISTS_DEVICETMP += " and ip=? and batchno<>? and seqno<>?";
			} else if (key.equals("DEVPHYID")) {// 设备物理id
				IS_EXISTS_DEVICETMP += " and devphyid=?  and batchno<>? and seqno<>?";
			}
			return jdbcTemplate.queryForInt(IS_EXISTS_DEVICETMP, value,
					batchNo, seqNo);
		}
		return 0;
	}

	@Override
	public int updateDeviceTmp(Devicetmp device) {
		String DEVICETMP_INFO_UPDATE = "update t_devicetmp set devicename = ?,devphytype = ?,"
			+ "devusage = ?,devphyid = ?,areacode=?,fdeviceid=?,sysid=?,svrportno=?,ip=?,deviceno=?,"
			+ "svrportcnt = ?,commtype=?,portno=?,devtypecod=?,cardphytype=? where batchno = ? and seqno = ?";

		return jdbcTemplate.update(DEVICETMP_INFO_UPDATE, device
				.getDevicename(), device.getDevphytype(), device.getDevusage(),
				device.getDevphyid(), device.getAreacode(), device
						.getFdeviceid(), device.getSysid(), device
						.getSvrportno(), device.getIp(), device.getDeviceno(),
				device.getSvrportcnt(), device.getCommtype(), device
						.getPortno(), device.getDevtypecode(), device
						.getCardphytype(), device.getBatchno(), device
						.getSeqno());
	}

	@Override
	public int isExist2DeviceTmp(String branchNo, int seqNo) {
		String IS_EXISTS_DEVICETMP = "select count(1) from t_devicetmp where 1=1 ";
		IS_EXISTS_DEVICETMP += " and branchNo =? and seqNo = ?";
		return jdbcTemplate.queryForInt(IS_EXISTS_DEVICETMP, branchNo, seqNo);
	}

	@Override
	public int deleteDeviceTmp(String branchNo, int seqNo) {
		String DELETE_DEVICETMP = "delete t_devicetmp where batchno = ? and seqno = ?";
		return jdbcTemplate.update(DELETE_DEVICETMP, branchNo, seqNo);
	}

	@Override
	public int deleteBatchDeviceTmp(String branchNo) {
		String DELETEBATCH_DEVICETMP = "delete t_devicetmp where batchno = ?";
		return jdbcTemplate.update(DELETEBATCH_DEVICETMP, branchNo);
	}

	@Override
	public int updateDeviceTmpErrorMessage(String branchNo, int seqNo,
			String errorMessage) {
		String UPDATE_DEVICE_ERRORMESSAGE = "update t_devicetmp set errmsg = ? where batchno = ? and seqno = ?";
		return jdbcTemplate.update(UPDATE_DEVICE_ERRORMESSAGE, errorMessage,
				branchNo, seqNo);
	}

	@Override
	public int isExist3DeviceTmp(String branchNo, int seqNo, String key) {
		String IS_EXISTS_DEVICE = "select count(1) from t_device where 1=1 ";
		if (key != null) {
			if (key.equals("FDEVICEID")) {// 父设备号
				IS_EXISTS_DEVICE += " and deviceid in(select fdeviceid from t_devicetmp where branchNo = ? and seqNo = ?)";
			} else if (key.equals("DEVICENAME")) {// 设备名称
				IS_EXISTS_DEVICE += " and devicename in(select devicename from t_devicetmp where branchNo = ? and seqNo = ?)";
			} else if (key.equals("IP")) {// 设备ip
				IS_EXISTS_DEVICE += " and ip in(select ip from t_devicetmp where branchNo = ? and seqNo = ?)";
			} else if (key.equals("DEVPHYID")) {// 设备物理ID
				IS_EXISTS_DEVICE += " and devphyid in(select devphyid from t_devicetmp where branchNo = ? and seqNo = ?)";
			}
			return jdbcTemplate.queryForInt(IS_EXISTS_DEVICE, branchNo,
					seqNo);
		}
		return 0;
	}

	@Override
	public int isExistSys2(String branchNo, int seqNo) {
		String IS_EXISTS_SYS2 = "select count(1) from t_subsystem where 1=1 and sysid in(select sysid from t_devicetmp  where batchno = ? and seqno = ? ) ";
		return jdbcTemplate.queryForInt(IS_EXISTS_SYS2, branchNo, seqNo);
	}

	@Override
	public int deviceTmpIntodevice(String branchNo, int seqNo) {
		String DEVICETMP_INTO_DEVICE = "insert into t_device(deviceid, devicename,  "
			+ "devphytype,devusage,devphyid, areacode,fdeviceid, sysid, svrportno,ip,deviceno,svrportcnt,"
			+ "commtype,portno,devtypecode,cardphytype,status,runstatus,batchno) select seq_device.nextval, devicename,  "
			+ "devphytype,devusage,devphyid, areacode,fdeviceid, sysid, svrportno,ip,deviceno,svrportcnt,"
			+ "commtype,portno,devtypecode,cardphytype,'1',0,batchno from t_devicetmp where batchno = ? and seqno = ?";
		return jdbcTemplate.update(DEVICETMP_INTO_DEVICE, branchNo, seqNo);
	}

	@Override
	public List<Device> findDeviceDao(Device device) {
		StringBuffer sql = new StringBuffer(
				"select deviceid, devicename, devphyid, deviceno, devphytype, devtypecode, devverno, cardphytype, fdeviceid, runstatus, status, svrportcnt, svrportno, commtype, ip, portno, baudrate, cardset, cardverno, lastseqno, lasttranstime, purseno, maxamt, sysid, areacode, doorlstver, devusage, opendate, closedate, batchno, lastsaved, remark from t_device where 1=1 ");
		List<String> param = new ArrayList<String>();
		if (device.getDeviceid() != 0) {
			sql.append(" and deviceid = ?");
			param.add("" + device.getDeviceid());
		}
		if (StringUtils.isNotBlank(device.getDevicename())) {
			sql.append(" and devicename like ?");
			param.add("%" + device.getDevicename() + "%");
		}
		if (device.getDevphytype() != 0) {
			sql.append(" and devphytype = ?");
			param.add("" + device.getDevphytype());
		}
		if (device.getDevusage() != 0) {
			sql.append(" and devusage =?");
			param.add("" + device.getDevusage());
		}
		if (StringUtils.isNotBlank(device.getDevphyid())) {
			sql.append(" and devphyid = ?");
			param.add("" + device.getDevphyid());
		}
		if (StringUtils.isNotBlank(device.getAreacode())) {
			sql.append(" and areacode = ?");
			param.add("" + device.getAreacode());
		}
		if (device.getFdeviceid() != 0) {
			sql.append(" and fdeviceid = ?");
			param.add("" + device.getFdeviceid());
		}
		if (device.getSysid() != 0) {
			sql.append(" and sysid = ?");
			param.add("" + device.getSysid());
		}
		if (device.getSvrportcnt() != 0) {
			sql.append(" and svrportno = ?");
			param.add("" + device.getSvrportcnt());
		}
		if (StringUtils.isNotBlank(device.getIp())) {
			sql.append(" and ip = ?");
			param.add("" + device.getIp());
		}
		if (device.getDeviceno() != 0) {
			sql.append(" and deviceno = ?");
			param.add("" + device.getDeviceno());
		}
		if (device.getSvrportcnt() != 0) {
			sql.append(" and svrportcnt = ?");
			param.add("" + device.getSvrportcnt());
		}
		if (device.getCommtype() != 0) {
			sql.append(" and commtype = ?");
			param.add("" + device.getCommtype());
		}
		if (device.getPortno() != 0) {
			sql.append(" and portno = ?");
			param.add("" + device.getPortno());
		}
		if (StringUtils.isNotBlank(device.getDevtypecode())) {
			sql.append(" and devtypecode = ?");
			param.add("" + device.getDevtypecode());
		}
		if (StringUtils.isNotBlank(device.getCardphytype())) {
			sql.append(" and cardphytype = ?");
			param.add("" + device.getCardphytype());
		}
		if (StringUtils.isNotBlank(device.getStatus())) {
			sql.append(" and status = ?");
			param.add("" + device.getStatus());
		}
		if (device.getRunstatus() != 0) {
			sql.append(" and runstatus = ?");
			param.add("" + device.getRunstatus());
		}
		return jdbcTemplate.query(sql.toString(), param.size() > 0 ? param
				.toArray() : null, new BeanPropertyRowMapper(Device.class));
	}

	@Override
	public List<Devicetmp> findDeviceTmpDao(Devicetmp device) {
		StringBuffer sql = new StringBuffer(
				"select batchno, seqno, transdate, transtime, opercode, areacode, devicename, devphyid, devphytype, devtypecode, deviceno, fdeviceid, cardphytype, commtype, ip, portno, svrportno, svrportcnt, sysid, devusage, errmsg from t_devicetmp where 1=1 ");
		List param = new ArrayList();
		if (StringUtils.isNotBlank(device.getBatchno())) {
			sql.append(" and batchno like ?");
			param.add("%" + device.getBatchno() + "%");
		}
		if (device.getSeqno() != 0) {
			sql.append(" and seqno = ?");
			param.add(device.getSeqno());
		}
		if (StringUtils.isNotBlank(device.getDevicename())) {
			sql.append(" and devicename like ?");
			param.add("%" + device.getDevicename() + "%");
		}
		if (device.getDevphytype() != 0) {
			sql.append(" and devphytype = ?");
			param.add(device.getDevphytype());
		}
		if (device.getDevusage() != 0) {
			sql.append(" and devusage =?");
			param.add(device.getDevusage());
		}
		if (StringUtils.isNotBlank(device.getDevphyid())) {
			sql.append(" and devphyid = ?");
			param.add(device.getDevphyid());
		}
		if (StringUtils.isNotBlank(device.getAreacode())) {
			sql.append(" and areacode = ?");
			param.add(device.getAreacode());
		}
		if (device.getFdeviceid() != 0) {
			sql.append(" and fdeviceid = ?");
			param.add(device.getFdeviceid());
		}
		if (device.getSysid() != 0) {
			sql.append(" and sysid = ?");
			param.add(device.getSysid());
		}
		if (device.getSvrportcnt() != 0) {
			sql.append(" and svrportno = ?");
			param.add(device.getSvrportcnt());
		}
		if (StringUtils.isNotBlank(device.getIp())) {
			sql.append(" and ip = ?");
			param.add(device.getIp());
		}
		if (device.getDeviceno() != 0) {
			sql.append(" and deviceno = ?");
			param.add(device.getDeviceno());
		}
		if (device.getSvrportcnt() != 0) {
			sql.append(" and svrportcnt = ?");
			param.add(device.getSvrportcnt());
		}
		if (device.getCommtype() != 0) {
			sql.append(" and commtype = ?");
			param.add(device.getCommtype());
		}
		if (device.getPortno() != 0) {
			sql.append(" and portno = ?");
			param.add(device.getPortno());
		}
		if (StringUtils.isNotBlank(device.getDevtypecode())) {
			sql.append(" and devtypecode = ?");
			param.add(device.getDevtypecode());
		}
		if (StringUtils.isNotBlank(device.getCardphytype())) {
			sql.append(" and cardphytype = ?");
			param.add(device.getCardphytype());
		}

		return jdbcTemplate.query(sql.toString(), param.size() > 0 ? param
				.toArray() : null, new BeanPropertyRowMapper(Devicetmp.class));

	}
}
