using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.NetworkInformation;
using SunGard.SmartCard.KSLibInteropServices;
using System.Reflection;


namespace iWallet
{
    public sealed class Utility
    {
        public static string GetHostName()
        {
            return Dns.GetHostName();
        }

        public static string GetHostIP()
        {

            IPHostEntry entry = Dns.GetHostEntry(Dns.GetHostName());
            IPAddress[] addr = entry.AddressList;
            return addr.Length > 0 ? addr[0].ToString() : string.Empty;
        }

        public static string GetHostMac()
        {
            NetworkInterface[] adapters = NetworkInterface.GetAllNetworkInterfaces();
            NetworkInterface i = Array.Find<NetworkInterface>(adapters, c => c.OperationalStatus == OperationalStatus.Up);

            return i.GetPhysicalAddress().ToString();

        }

        public static List<T> GetEntities<T>(int handle) where T : new()
        {
            List<T> list = new List<T>();
            int cnt = 0;
            BCCHelper.GetRecordCount(handle, ref cnt);
            for (int rowIndex = 0; rowIndex < cnt; rowIndex++)
            {
                //populate single entity for per row
                T obj = new T();
                Type t = typeof(T);
                PropertyInfo[] pros = t.GetProperties();
                foreach (PropertyInfo p in pros)
                {
                    object[] attrs = p.GetCustomAttributes(typeof(CPackAttribute), false);
                    if (attrs.Length > 0 && attrs[0] is CPackAttribute)
                    {
                        CPackAttribute cpa = attrs[0] as CPackAttribute;
                        if (cpa != null)
                        {
                            string field = cpa.FieldName;
                            if (cpa.FieldType == typeof(int))
                            {
                                int iVal = 0;
                                BCCHelper.GetIntFieldByName(handle, rowIndex, field, ref iVal);
                                p.SetValue(obj, iVal, null);
                            }
                            else if (cpa.FieldType == typeof(double))
                            {
                                double dVal = 0.0d;
                                BCCHelper.GetDoubleFieldByName(handle, rowIndex, field, ref dVal);
                                p.SetValue(obj, dVal, null);
                            }
                            else   //char[] type for CPack 
                            {
                                string sval = BCCHelper.GetStringFieldByName(handle, rowIndex, field);
                                p.SetValue(obj, sval, null);
                            }
                        }
                    }
                } //end for foreach PropertyInfo
                //add entity to result list
                list.Add(obj);
            } //end for each row
            return list;
        } //end for function

        public static SortableBindingList<T> GetSorttableList<T>(int handle) where T:new()
        {
            SortableBindingList<T> list = new SortableBindingList<T>();
            int cnt = 0;
            BCCHelper.GetRecordCount(handle, ref cnt);
            for (int rowIndex = 0; rowIndex < cnt; rowIndex++)
            {
                //populate single entity for per row
                T obj = new T();
                Type t = typeof(T);
                PropertyInfo[] pros = t.GetProperties();
                foreach (PropertyInfo p in pros)
                {
                    object[] attrs = p.GetCustomAttributes(typeof(CPackAttribute), false);
                    if (attrs.Length > 0 && attrs[0] is CPackAttribute)
                    {
                        CPackAttribute cpa = attrs[0] as CPackAttribute;
                        if (cpa != null)
                        {
                            string field = cpa.FieldName;
                            if (cpa.FieldType == typeof(int))
                            {
                                int iVal = 0;
                                BCCHelper.GetIntFieldByName(handle, rowIndex, field, ref iVal);
                                p.SetValue(obj, iVal, null);
                            }
                            else if (cpa.FieldType == typeof(double))
                            {
                                double dVal = 0.0d;
                                BCCHelper.GetDoubleFieldByName(handle, rowIndex, field, ref dVal);
                                p.SetValue(obj, dVal, null);
                            }
                            else   //char[] type for CPack 
                            {
                                string sval = BCCHelper.GetStringFieldByName(handle, rowIndex, field);
                                p.SetValue(obj, sval, null);
                            }
                        }
                    }
                } //end for foreach PropertyInfo
                //add entity to result list
                list.Add(obj);
            } //end for each row
            return list;
        }


    } //end for Class
}
