using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SunGard.SmartCard.KSLibInteropServices;

namespace FundReleaser.BO
{
    /// <summary>
    /// 
    /// </summary>
    public class Merchant
    {
        /// <summary>
        /// 商户号
        /// </summary>
        [CPack(FieldName = "lvol3", FieldType = typeof(Int32))]
        public int ShopId
        {
            get;
            set;
        }

        /// <summary>
        /// 上级商户号
        /// </summary>
        [CPack(FieldName = "lvol1", FieldType = typeof(Int32))]
        public int ParentShopId
        {
            get;
            set;
        }

        /// <summary>
        /// 商户名
        /// </summary>
        [CPack(FieldName = "sall_name", FieldType = typeof(String))]
        public string ShopName
        {
            get;
            set;
        }


        /// <summary>
        /// 商户账号
        /// </summary>
        [CPack(FieldName = "sbank_acc", FieldType = typeof(String))]
        public string ShopAccId
        {
            get;
            set;
        }

        public override string ToString()
        {
            return string.Format("ShopId={0},ParentShopId={1},ShopName={2},ShopAccId={3}", ShopId, ParentShopId, ShopName, ShopAccId);
        }


    }
}
