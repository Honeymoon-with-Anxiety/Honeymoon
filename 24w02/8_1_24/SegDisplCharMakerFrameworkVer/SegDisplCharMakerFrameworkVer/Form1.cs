using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace SegDisplCharMakerFrameworkVer
{
    public partial class Form1 : Form
    {
        List<CheckBox> chBoxes = new List<CheckBox>();

        public Form1()
        {
            InitializeComponent();
            chBoxes.Add(checkBox8);
            chBoxes.Add(checkBox7);
            chBoxes.Add(checkBox6);
            chBoxes.Add(checkBox5);
            chBoxes.Add(checkBox4);
            chBoxes.Add(checkBox3);
            chBoxes.Add(checkBox2);
            chBoxes.Add(checkBox1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string parsedBool = "0b";
            foreach (CheckBox chBox in chBoxes)
            {
                parsedBool += Convert.ToInt16(!chBox.Checked);
            }
            listBox1.Items.Add(parsedBool + "\t" + textBox1.Text);
            textBox1.Text = null;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                List<string> listItems = new List<string>();
                foreach (string item in listBox1.Items)
                {
                    listItems.Add(item);
                }
                File.WriteAllLines(saveFileDialog.FileName, listItems.ToArray());
            }
        }
    }
}
