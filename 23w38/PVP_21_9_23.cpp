using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Abaksus_WinForm
{
    public partial class Main : Form
    {
        int[] arrValues = {0, 0};
        Label lastLabel;


        public Main() { InitializeComponent(); }
        private void Main_KeyDown(object sender, KeyEventArgs e)
        {
            e.SuppressKeyPress = true;
            if (e.KeyCode == Keys.Escape) { Application.Exit(); }
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            textBox1.Text = new string((from c in textBox1.Text where char.IsDigit(c) select c).ToArray());
        }

        private void tsbAddRow_Click(object sender, EventArgs e)
        {
            arrValues[arrValues.Length] = 0;
            tslRowCount.Text = $"Rows: {arrValues.Length}";

            Label label = new Label();
            label.Text = $"Row {(arrValues.Length-1).ToString("00")}";
            if (lastLabel != null) label.Location = new System.Drawing.Point(lastLabel.Location.X, lastLabel.Location.Y + 26);
            else label.Location = new System.Drawing.Point(12, 83);
            label.Size = new System.Drawing.Size(42, 13);


            TextBox textBox = new TextBox();
            textBox.Text = arrValues[arrValues.Length-1].ToString();
        }
    }
}
