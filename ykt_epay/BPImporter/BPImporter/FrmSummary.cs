using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BPImporter
{
    public partial class FrmSummary : Form
    {
        public FrmSummary()
        {
            InitializeComponent();
        }

        public FrmSummary(string summary):this()
        {
            txtSummary.Text = summary;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
