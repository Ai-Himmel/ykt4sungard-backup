using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iWallet.BO
{
    public class Customer
    {

        public bool Checked
        {
            get;
            set;
        }


        /// <summary>
        /// 客户号
        /// </summary>
        [CPack(FieldName = "lvol1", FieldType = typeof(int))]
        public int CustomerId
        {
            get;
            set;
        }

        /// <summary>
        /// 学工号
        /// </summary>
        [CPack(FieldName = "scust_auth2", FieldType = typeof(String))]
        public string SchoolId
        {
            get;
            set;
        }

        /// <summary>
        /// 客户姓名
        /// </summary>       
        [CPack(FieldName = "sname", FieldType = typeof(String))]
        public string CustomerName
        {
            get;
            set;
        }


        private string netAccFlag = "";

        /// <summary>
        /// 电子钱包号开通标识
        /// </summary>
        [CPack(FieldName = "sstat_type", FieldType = typeof(String))]
        public string NetAccFlag
        {
            get
            {
                return netAccFlag;
            }
            set
            {
                netAccFlag = value;

            }
        }


        private string netAccFlagDes = "";
        public string NetAccFlagDes
        {
            get
            {
                netAccFlagDes = netAccFlag == "1" ? "已开通" : "未开通";
                return netAccFlagDes;
            }
            set
            {
                netAccFlagDes = value;
            }

        }


        /// <summary>
        /// 性别
        /// </summary>

        [CPack(FieldName = "smarket_code2", FieldType = typeof(String))]
        public string SexName
        {
            get;
            set;
        }

        /// <summary>
        /// 客户类别
        /// </summary>

        [CPack(FieldName = "lvol3", FieldType = typeof(String))]
        public string Category
        {
            get;
            set;
        }

        /// <summary>
        /// 所属部门
        /// </summary>

        [CPack(FieldName = "vsvarstr0", FieldType = typeof(String))]
        public string DeptName
        {
            get;
            set;
        }

        /// <summary>
        /// 客户状态
        /// </summary>

        [CPack(FieldName = "sstatus1", FieldType = typeof(String))]
        public string StatusName
        {
            get;
            set;
        }

        /// <summary>
        /// 注册日期
        /// </summary>
        [CPack(FieldName = "sdate1", FieldType = typeof(String))]
        public string InDate
        {
            get;
            set;
        }


        [CPack(FieldName = "snation_code", FieldType = typeof(String))]
        public string Country
        {
            get;
            set;
        }

        [CPack(FieldName = "spost_code", FieldType = typeof(String))]
        public string Nation
        {
            get;
            set;
        }

        [CPack(FieldName = "semail", FieldType = typeof(String))]
        public string Email
        {
            get;
            set;
        }

        [CPack(FieldName = "sphone", FieldType = typeof(String))]
        public string Tel
        {
            get;
            set;
        }

        [CPack(FieldName = "sphone2", FieldType = typeof(String))]
        public string Mobile
        {
            get;
            set;
        }

    }
}
