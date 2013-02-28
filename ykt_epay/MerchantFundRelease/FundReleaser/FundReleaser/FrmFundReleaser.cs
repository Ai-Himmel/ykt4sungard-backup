using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using SunGard.SmartCard.KSLibInteropServices;
using FundReleaser.BO;

namespace FundReleaser
{
    public partial class FrmFundReleaser : Form
    {

        internal const int Function_843335 = 843335;

        public FrmFundReleaser()
        {
            InitializeComponent();
        }

        private void FrmFundReleaser_Load(object sender, EventArgs e)
        {

            int handle = BccCltWrapper.PrepareRequest(Function_843335);
            List<Merchant> merchants = BccCltWrapper.ExecuteEntityList<Merchant>(handle, Function_843335);
            //create root node
            Merchant root = merchants.Find(delegate(Merchant m)
            {
                return m.ParentShopId == 0;
            });
            TreeNode rootNode = trvMerchant.Nodes.Add(root.ShopAccId, root.ShopName);
            rootNode.Tag = root;
            CreateMerchantTree(merchants, root.ShopId, rootNode);


        }


        #region "private methods"
        void CreateMerchantTree(List<Merchant> merchants, int parentId, TreeNode parentNode)
        {

            List<Merchant> subs = merchants.Where<Merchant>(item => item.ParentShopId == parentId).ToList<Merchant>();
            TreeNode childNode;
            foreach (var item in subs)
            {
                if (parentNode == null)
                {
                    childNode = trvMerchant.Nodes.Add(item.ShopAccId, item.ShopName+ string.Format("{0}--{1}",item.ParentShopId,item.ShopId));
                }
                else
                {
                    childNode = parentNode.Nodes.Add(item.ShopAccId, item.ShopName + string.Format("{0}--{1}", item.ParentShopId, item.ShopId));
                }
                childNode.Tag = item;

                CreateMerchantTree(merchants, item.ShopId, childNode);
            }


            




        }
        #endregion

        private void trvMerchant_AfterSelect(object sender, TreeViewEventArgs e)
        {
            MessageBox.Show(e.Node.Tag.ToString());
        }


    }
}
