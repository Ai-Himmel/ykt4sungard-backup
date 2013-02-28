using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iWallet
{
    public class CPackAttribute : Attribute
    {
        public string FieldName
        {
            get;
            set;
        }
        public Type FieldType
        {
            get;
            set;
        } 
    }
}
