using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Xml;
using iWallet.Caching;
using SunGard.SmartCard.KSLibInteropServices;
using System.Text;
using iWallet.BO;

namespace iWallet
{
    public sealed class DataCacher
    {

        static DataCacher _instance;
        private static object syncRoot = new object();

        public List<Master> this[MasterKind kind]
        {
            get
            {
                return cache[kind];
            }
        }

        public static Dictionary<MasterKind, List<Master>> cache;//= new Dictionary<MasterKind, List<MasterKind>>();

        static DataCacher()
        {
            cache = new Dictionary<MasterKind, List<Master>>();
        }

        private DataCacher()
        {

        }

        public static DataCacher Instance
        {
            get
            {
                if (_instance == null)
                {
                    lock (syncRoot)
                    {
                        if (_instance == null)
                        {
                            _instance = new DataCacher();
                            InitializeCache();
                        }
                    }
                }
                return _instance;
            }
        }

        private static void InitializeCache()
        {

        }

        public void InitializeMasterData()
        {
            cache.Add(MasterKind.CustomerType, new List<Master>());
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "11",
                Name = "11-学生"
            });
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "12",
                Name = "12-教职工"
            });
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "13",
                Name = "13-教职工-党员"
            });
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "14",
                Name = "14-返聘"
            });
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "15",
                Name = "15-外聘"
            });
            cache[MasterKind.CustomerType].Add(new Master
            {
                Code = "16",
                Name = "16-贵宾"
            });

            Master[] feeType = new Master[cache[MasterKind.CustomerType].Count];
            cache[MasterKind.CustomerType].CopyTo(feeType);
            cache.Add(MasterKind.FeeType, new List<Master>(feeType));

            cache.Add(MasterKind.Sex, new List<Master>());
            cache[MasterKind.Sex].Add(new Master
            {
                Code = "1",
                Name = "男"
            });
            cache[MasterKind.Sex].Add(new Master
            {
                Code = "2",
                Name = "女"
            });
            cache.Add(MasterKind.CustomerStatus, new List<Master>());
            cache[MasterKind.CustomerStatus].Add(new Master
            {
                Code="1",
                Name = "注册"
            });
            cache[MasterKind.CustomerStatus].Add(new Master
            {
                Code = "2",
                Name = "休学"
            });

            cache[MasterKind.CustomerStatus].Add(new Master
            {
                Code = "3",
                Name = "毕业注销"
            });

            cache[MasterKind.CustomerStatus].Add(new Master
            {
                Code = "4",
                Name = "退学注销"
            });



          
        }

    }//end if CLASS




}
